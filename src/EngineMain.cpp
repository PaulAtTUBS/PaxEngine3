//
// Created by Paul on 29.04.2017.
//

#include <easylogging++.h>

#include <test/ResourcesTest.h>
#include <test/trials/AllocatorConstructorTest.h>
#include <test/trials/InheritedTemplateTypeTest.h>
#include <test/EntityTest.h>
#include <demo/OpenGL/TerrainDemo.h>
#include <utility/reflection/TemplateTypeToString.h>
#include <demo/Platformer/PlatformerDemo.h>

#include "../include/EngineMain.h"

#include "../include/core/Engine.h"
#include "../include/sdl/SDLEngineSetup.h"

#include "../include/sdl/opengl/SDLOpenGLEngineSetup.h"

int PAX::Engine_Main(int argc, char *argv[]) {
    int exitcode = 0;

    EngineSetup *setup = new SDL::OpenGL::SDLOpenGLEngineSetup;
    Game *game = new Platformer::PlatformerDemo();

    Engine &engine = Engine::Instance();
    engine.initialize(setup, game);
    /*
    PAX::TEST::ENTITY::test();
    //*/
    exitcode = engine.run();

    return exitcode;
}