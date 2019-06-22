//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_OPENGLNULLTEXTURELOADER_H
#define PAXENGINE3_OPENGLNULLTEXTURELOADER_H

#include <paxcore/rendering/data/Texture.h>
#include <paxutil/resources/ResourceLoader.h>
#include "../resource/OpenGLTexture2D.h"

namespace PAX {
    namespace OpenGL {
        class NullOpenGLTextureLoader : public ResourceLoader<Texture, Path> {
        private:
            // Cache texture here, so that it will never be deleted.
            std::shared_ptr<OpenGLTexture2D> _texture = nullptr;

        public:
            NullOpenGLTextureLoader();
            ~NullOpenGLTextureLoader() override;

            bool canLoad(Path path) const override;
            std::shared_ptr<Texture> load(Path path) override;
            std::shared_ptr<Texture> loadToOrGetFromResources(Resources & resources, const VariableHierarchy & parameters) override;
        };
    }
}

#endif //PAXENGINE3_OPENGLNULLTEXTURELOADER_H