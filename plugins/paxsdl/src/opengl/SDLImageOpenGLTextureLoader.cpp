//
// Created by Paul on 04.11.2017.
//

#include "paxsdl/opengl/SDLImageOpenGLTextureLoader.h"
#include "paxopengl/resource/OpenGLTexture2D.h"

#ifdef PAX_WITH_SDLIMAGE
#include <SDL2/SDL_image.h>
#endif

#include <easylogging++.h>
#include <paxutil/io/FileTypeChecker.h>
#include <assert.h>

namespace PAX {
    namespace OpenGL {
        SDLImageOpenGLTextureLoader::SDLImageOpenGLTextureLoader() {

        }

        SDLImageOpenGLTextureLoader::~SDLImageOpenGLTextureLoader() {

        }

        bool PAX::OpenGL::SDLImageOpenGLTextureLoader::canLoad(Path path) const {
            Util::FileTypeChecker formats({
                    "BMP", "GIF", "JPEG", "LBM", "PCX", "PNG", "PNM", "SVG", "TGA", "TIFF", "WEBP", "XCF", "XPM", "XV"
            });

            return formats.check(path.toString());
        }

        std::shared_ptr<PAX::Texture> PAX::OpenGL::SDLImageOpenGLTextureLoader::load(Path path) {
#ifdef PAX_WITH_SDLIMAGE
            SDL_Surface* tex = NULL;

            int flags = IMG_INIT_JPG | IMG_INIT_PNG;
            int initted = IMG_Init(flags);
            if((initted & flags) != flags) {
                LOG(ERROR) << "could not init SDL_Image: " << IMG_GetError();
            }

            if((tex = IMG_Load(path.c_str())) == NULL) {
                LOG(ERROR) << "Loading texture " << path << " failed in SDLImageOpenGLTextureLoader.";
            }

            GLuint id;
            glGenTextures(1, &id);

            OpenGLTexture2D *ogltexture = new OpenGLTexture2D(id, tex->w, tex->h);

            ogltexture->bind();

            int Mode = GL_RGB;
            if(tex->format->BytesPerPixel == 4) {
                Mode = GL_RGBA;
            }
            glPixelStorei(GL_UNPACK_ALIGNMENT, 8);
            glTexImage2D(GL_TEXTURE_2D, 0, Mode, ogltexture->getWidth(), ogltexture->getHeight(), 0, Mode, GL_UNSIGNED_BYTE, tex->pixels);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            ogltexture->unbind();

            SDL_FreeSurface(tex);

            return std::shared_ptr<OpenGLTexture2D>(ogltexture, [](OpenGLTexture2D* tex){
                GLuint texId = tex->getID();
                glDeleteTextures(1, &texId);
                delete tex;
            });
#else
            assert(false);
            return nullptr;
#endif
        }
    }
}