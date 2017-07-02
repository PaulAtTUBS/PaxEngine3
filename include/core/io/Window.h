//
// Created by Gordon on 16.05.2017.
//

#ifndef PAXENGINE3_WINDOW_H
#define PAXENGINE3_WINDOW_H

#include <string>
#include <glm/glm.hpp>

namespace PAX {
    class Window {
        bool _fullscreen;

    public:
        virtual bool create(std::string title, int width, int height) = 0;
        virtual glm::vec2 getResolution() = 0;

        virtual void setFullscreen(bool fullscreen);
        bool isFullscreen();
    };
}

#endif //PAXENGINE3_WINDOW_H
