//
// Created by Bittner on 02/04/2019.
//

#include <paxopengl/OpenGLError.h>
#include <paxutil/macros/MacroIncludes.h>

namespace PAX {
    namespace OpenGL {
        void GLAPIENTRY
        GLErrorCallback( GLenum source,
                         GLenum type,
                         GLuint id,
                         GLenum severity,
                         GLsizei length,
                         const GLchar* message,
                         const void* userParam )
        {
            if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
                return;
            }

            std::string severityString;
            if (severity == GL_DEBUG_SEVERITY_LOW) {
                severityString = "low";
            } else if (severity == GL_DEBUG_SEVERITY_MEDIUM) {
                severityString = "medium";
            } else if (severity == GL_DEBUG_SEVERITY_HIGH) {
                severityString = "high";
            } else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
                severityString = "notification";
            } else {
                severityString = "unknown";
            }

            std::string typeString;
            switch (type) {
                case GL_DEBUG_TYPE_ERROR:
                    typeString = "ERROR";
                    break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                    typeString = "DEPRECATED_BEHAVIOR";
                    break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                    typeString = "UNDEFINED_BEHAVIOR";
                    break;
                case GL_DEBUG_TYPE_PORTABILITY:
                    typeString = "PORTABILITY";
                    break;
                case GL_DEBUG_TYPE_PERFORMANCE:
                    typeString = "PERFORMANCE";
                    break;
                case GL_DEBUG_TYPE_OTHER:
                    typeString = "OTHER";
                    break;
                default:
                    typeString = "(Unknown error type)";
                    break;
            }

            std::stringstream out;
            out << "[GLErrorCallback] " << typeString << ": " << message << " (Severity is " << severityString << ")";

#ifdef PAX_CRASH_ON_GLERROR
            PAX_THROW_RUNTIME_ERROR(out.str())
#else
            std::cerr << "[GLErrorCallback] " << out.str() << std::endl;
#endif
        }

        bool getGLError(const std::string & location)
        {
            while (auto err = glGetError()) {
#ifdef PAX_CRASH_ON_GLERROR
                PAX_THROW_RUNTIME_ERROR("OPENGL ERROR" << " in " << location << ": " << gluErrorString(err))
#else
                std::cerr << "OPENGL ERROR" << " in " << location << ": " << gluErrorString(err) << std::endl;
#endif
            }

            return true;
        }
    }
}