//
// Created by Paul on 17.04.2017.
//

#include <chrono>
#include <iostream>

#include <paxcore/Engine.h>
#include <paxcore/Game.h>
#include <paxcore/plugin/EnginePlugin.h>
#include <paxcore/plugin/EngineInternalPlugin.h>

#include <paxutil/Sleep.h>
#include <paxutil/io/Settings.h>
#include <paxutil/log/Log.h>
#include <paxcore/function/UpdateOptions.h>

namespace PAX {
    Engine *Engine::instance = nullptr;

    Engine::Engine() = default;

    Engine::~Engine() = default;

    bool Engine::initialize(Game *game, const std::vector<EnginePlugin*> &plugins) {
        Log::out.info() << "[Engine::initialize] start" << std::endl;
        //PAX_assertNotNull(setup, "Engine::initialize: Setup not set! Abort initialization!");
        PAX_assertNotNull(game, "Engine::initialize: Game not set! Abort initialization!")

        _game = game;

        // Check if all dependencies of plugins are met
        for (const EnginePlugin* p : plugins) {
            p->checkDependencies(plugins);
        }

        _plugins.push_back(new EngineInternalPlugin());
        // Copy plugins to member list
        _plugins.insert(std::end(_plugins), std::begin(plugins), std::end(plugins));

        Log::out.info() << "[Engine::initialize] Plugins: initializing" << std::endl;
        for (EnginePlugin *plugin : _plugins) {
            plugin->initialize(*this);
        }

        Log::out.info() << "[Engine::initialize] Plugins: registering Services" << std::endl;
        for (EnginePlugin *plugin : _plugins) {
            plugin->registerServices(_services);
        }

        Log::out.info() << "[Engine::initialize] Plugins: registering ResourceLoaders" << std::endl;
        for (EnginePlugin *plugin : _plugins) {
            plugin->registerResourceLoaders(Services::GetResources());
        }

        Log::out.info() << "[Engine::initialize] Plugins: registering Factories" << std::endl;
        for (EnginePlugin *plugin : _plugins) {
            plugin->registerFactories(Services::GetFactoryService());
        }

        Log::out.info() << "[Engine::initialize] initialize Services" << std::endl;
        _services.initialize();

        _targetFPS = Services::GetGlobalSettings().get<int>("core_targetFPS");
        _targetUPS = Services::GetGlobalSettings().get<int>("core_targetUPS");

        Log::out.info() << "[Engine::initialize] initialize Renderer" << std::endl;
        _renderer.initialize();

        Log::out.info() << "[Engine::initialize] Plugins: registering Properties" << std::endl;
        for (EnginePlugin * plugin : _plugins) {
            plugin->registerProperties();
        }

        Log::out.info() << "[Engine::initialize] Plugins: registering Systems" << std::endl;
        for (EnginePlugin * plugin : _plugins) {
            plugin->registerSystems(*_game);
        }

        Log::out.info() << "[Engine::initialize] Plugins: postInitialize" << std::endl;
        for (EnginePlugin *plugin : _plugins) {
            plugin->postInitialize(*this);
        }

        Log::out.info() << "[Engine::initialize] initialize Game" << std::endl;
        _game->initialize();

        Log::out.info() << "[Engine::initialize] done" << std::endl;
        return true;
    }


    int Engine::run() {
        using namespace std::chrono;
        using clock = high_resolution_clock;

        _running = true;

        _actualFPS = _targetFPS;
        _actualUPS = _targetUPS;

        /** LOOP VARS **/
        // Calculate how many seconds each frame should take for our target fps.
        // Think of this as slots, where in each one at least one frame/update
        // should be done.
        duration<double> SPF = duration<double>(1.0 / _targetFPS);
        duration<double> SPU = duration<double>(1.0 / _targetUPS);
        nanoseconds SPU_ns = duration_cast<nanoseconds>(SPU);

        high_resolution_clock::time_point loopStartTime;
        high_resolution_clock::time_point lastLoopStartTime = clock::now();
        // time the last frame took.
        duration<double> dt(0);
        int timeLeft = 0;

        /** UPDATE VARS **/
        constexpr long MAX_UPDATES = 1 << 4;

        // How long do all updates in one frame take together
        high_resolution_clock::time_point nextUpdateTime(lastLoopStartTime);
        // How many SPFs we are behind execution e.g. slower than desired.
        duration<double> lag(0);
        duration<double> update_duration(0);
        // num of updates each frame
        short updatesPerRender = 0;

        /** RENDER VARS **/
        high_resolution_clock::time_point renderStartTime(lastLoopStartTime);
        duration<double> render_duration(0);
        duration<double> timeTilNextRender(0);

        /** FPS & UPS COUNTER **/
        high_resolution_clock::time_point lastSecond(lastLoopStartTime);
        int frames = 0;
        int updates = 0;
        high_resolution_clock::time_point fpsUpsTimeStamp;

        while (_running) {
            // calculate delta time
            loopStartTime = clock::now();
            dt = loopStartTime - lastLoopStartTime;
            lastLoopStartTime = loopStartTime;

            // UPDATE
            lag = loopStartTime - nextUpdateTime;
            updatesPerRender = 0;

            while (lag >= duration<double>::zero() && updatesPerRender < MAX_UPDATES) {
                UpdateOptions updateOptions(
                        static_cast<float>(1.0 / _targetUPS),
                        static_cast<float>(dt.count()));
                update(updateOptions);
                nextUpdateTime += SPU_ns;
                lag -= SPU_ns;
                ++updatesPerRender;
            }

            // lag is to great to be catched up
            if (lag >= SPU_ns) {
                std::cerr << "[Engine::run] Debug: update lag to great!" << std::endl;
                nextUpdateTime = loopStartTime - SPU_ns;
            }

            updates += updatesPerRender;
            update_duration = clock::now() - loopStartTime;

            // RENDER
            renderStartTime = clock::now();
            render();
            ++frames;
            render_duration = clock::now() - renderStartTime;

            // count fps
            fpsUpsTimeStamp = clock::now();
            if (fpsUpsTimeStamp >= lastSecond + seconds(1)) {
                duration<double> sPassed = fpsUpsTimeStamp - lastSecond;
                _actualFPS = frames / sPassed.count();
                _actualUPS = updates / sPassed.count();

                /*
                std::cout << "[Engine::run] updatesPerRender = " << updatesPerRender << std::endl;
                std::cout << "[Engine::run] updates          = " << updates << std::endl;
                std::cout << "[Engine::run] update_duration  = " << update_duration.count() << std::endl;
                std::cout << "[Engine::run] UPS              = " << _actualUPS << std::endl;
                std::cout << "[Engine::run] frames           = " << frames << std::endl;
                std::cout << "[Engine::run] render_duration  = " << render_duration.count() << std::endl;
                std::cout << "[Engine::run] FPS              = " << _actualFPS << std::endl << std::endl;
                //*/

                frames = 0;
                updates = 0;

                lastSecond = fpsUpsTimeStamp;
            }

            // Wait if your computer is faster than roadrunner to not kill it.
            timeTilNextRender = SPF - update_duration - render_duration; // this is just an estimation
            timeLeft = static_cast<int>(1000.0 * timeTilNextRender.count());
            /*
            std::cout << "rt " << timeTilNextRender.count() << std::endl;
            std::cout << "ut " << timeTilNextUpdate.count() <<  " ... " << lag.count() << " / " << SPU.count() << std::endl;
            //*/
            if (timeLeft > 0) {
                PAX::ThreadSleep(static_cast<unsigned int>(timeLeft));
            }
        }

        terminate();

        return 0;
    }


    void Engine::update(UpdateOptions & options) {
        _services.update(options);
        _game->update(options);
    }

    void Engine::render() {
        _renderer.render();
    }

    void Engine::stop() {
        _running = false;
    }

    Game *Engine::getGame() {
        return _game;
    }

    Renderer &Engine::getRenderer() {
        return _renderer;
    }

    double Engine::getFPS() {
        return _actualFPS;
    }

    double Engine::getUPS() {
        return _actualUPS;
    }

    Engine &Engine::Instance() {
        if (!instance)
            instance = new Engine();
        return *instance;
    }

    bool Engine::terminate() {
        _game->terminate();

        for (auto i = _plugins.rbegin(); i != _plugins.rend(); ++i) {
            (*i)->terminate(*this);
        }

        _services.terminate();
        return true;
    }
}