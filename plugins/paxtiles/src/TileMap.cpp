//
// Created by paul on 03.01.19.
//

#include "paxtiles/TileMap.h"
#include <paxutil/lib/GlmIncludes.h>

#include <vector>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/factory/MeshFactory.h>

namespace PAX {
    namespace Tiles {
        TileMap::TileMap() = default;

        void TileMap::createMesh(const std::vector<std::vector<Tile>> & tiles) {
            std::vector<glm::vec2>  vertices;
            std::vector<glm::ivec3> faces;
            std::vector<int> tileSheetIds;
            std::vector<glm::vec2>  uv;

            glm::vec3 vertexOffset = -glm::vec3(columns, rows, 0) / 2.f;
            glm::vec3 flipY = {1, -1, 1};

            // use vec2 to cast to float
            glm::vec2 spriteSheetSize = spriteSheet->getDimensions();
            glm::vec2 uvTileSize = 1.f / spriteSheetSize;

            // Order of tiles:
            //
            // >>>>>
            // >>>>>
            // >>>>>
            //
            int index = 0;
            for (unsigned long row = 0; row < rows; ++row) {
                for (unsigned long column = 0; column < columns; ++column) {
                    const Tile & currentTile = tiles[row][column];

                    // We have lots of vertex duplicates here, but this is necessary due to the need
                    // for different UV coords.
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column    , row    , 0)));
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column    , row + 1, 0)));
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column + 1, row + 1, 0)));
                    vertices.emplace_back(flipY * (vertexOffset + glm::vec3(column + 1, row    , 0)));

                    faces.emplace_back(glm::ivec3(index, index + 2, index + 1));
                    faces.emplace_back(glm::ivec3(index, index + 3, index + 2));

                    float uvX = static_cast<float>(currentTile.textureColumn) * uvTileSize.x;
                    float uvY = static_cast<float>(currentTile.textureRow)    * uvTileSize.y;
                    uv.emplace_back(glm::vec2(uvX               , uvY));
                    uv.emplace_back(glm::vec2(uvX               , uvY + uvTileSize.y));
                    uv.emplace_back(glm::vec2(uvX + uvTileSize.x, uvY + uvTileSize.y));
                    uv.emplace_back(glm::vec2(uvX + uvTileSize.x, uvY));

                    tileSheetIds.emplace_back(0);
                    tileSheetIds.emplace_back(0);
                    tileSheetIds.emplace_back(0);
                    tileSheetIds.emplace_back(0);

                    index += 4;
                }
            }

            MeshFactory* meshFactory = Services::GetFactoryService().get<MeshFactory>();
            PAX_assertNotNull(meshFactory, "MeshFactory can't be null!");
            mesh = meshFactory->create(vertices, faces);
            PAX_assertNotNull(mesh, "Mesh can't be null!");
            mesh->addAttribute(Mesh::UVs, uv);
            mesh->addAttribute(Mesh::Unspecified, tileSheetIds);
            mesh->upload();
        }

        void TileMap::create(const std::vector<std::vector<Tile>> & tiles, const std::shared_ptr<SpriteSheet> & spriteSheet) {
            this->rows    = static_cast<unsigned long>(tiles.size());
            this->columns = static_cast<unsigned long>(tiles.at(0).size());
            this->spriteSheet = spriteSheet;
            createMesh(tiles);
        }

        const std::shared_ptr<SpriteSheet> TileMap::getSpriteSheet() const {
            return spriteSheet;
        }

        const std::shared_ptr<Mesh>& TileMap::getMesh() const {
            return mesh;
        }

        unsigned long TileMap::getColumns() const {
            return columns;
        }

        unsigned long TileMap::getRows() const {
            return rows;
        }
    }
}