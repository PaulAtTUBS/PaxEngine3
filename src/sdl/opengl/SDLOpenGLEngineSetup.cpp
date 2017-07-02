//
// Created by Paul on 02.07.2017.
//

#include "../../../include/sdl/opengl/SDLOpenGLEngineSetup.h"
#include "../../../include/opengl/OpenGLRenderFactory.h"
#include "../../../include/sdl/opengl/SDLOpenGLWindow.h"

namespace PAX {
    namespace SDL {
        namespace OpenGL {
            Window* SDLOpenGLEngineSetup::createWindow() {
                return new SDLOpenGLWindow();
            }

            RenderFactory * SDLOpenGLEngineSetup::createRenderFactory() {
                return new PAX::OpenGL::OpenGLRenderFactory();
            }
        }
    }
}