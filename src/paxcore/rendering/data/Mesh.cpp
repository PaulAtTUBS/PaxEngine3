//
// Created by Paul on 04.09.2018.
//

#include <paxcore/rendering/data/Mesh.h>
#include <paxutil/stdutils/CollectionUtils.h>

#include <iostream>

namespace PAX {
    const Mesh::AttributeName Mesh::Unspecified = -1;
    const Mesh::AttributeName Mesh::Vertices = 0;
    const Mesh::AttributeName Mesh::Normals = Mesh::Vertices + 1;
    const Mesh::AttributeName Mesh::UVs = Mesh::Normals + 1;
    const Mesh::AttributeName Mesh::Tangents = Mesh::UVs + 1;
    const Mesh::AttributeName Mesh::Bitangents = Mesh::Tangents + 1;

    Mesh::~Mesh() {

    }

    void Mesh::setName(const std::string &name) {
        _name = name;
    }

    const std::string& Mesh::getName() const {
        return _name;
    }

    void Mesh::addAttribName(PAX::Mesh::AttributeName name) {
        _attributeNames.emplace_back(name);
    }

    bool Mesh::hasAttribute(PAX::Mesh::AttributeName attribName) {
        return Util::vectorContains(_attributeNames, attribName);
    }

    int Mesh::getAttributeLocation(PAX::Mesh::AttributeName attribName) {
        for (int i = 0; i < _attributeNames.size(); ++i) {
            if (_attributeNames[i] == attribName)
                return i;
        }
        return -1;
    }

    void Mesh::upload() {
        _uploaded = true;
    }

    bool Mesh::isUploaded() {
        return _uploaded;
    }

    void Mesh::cacheUniformsFor(std::shared_ptr <PAX::Shader> &shader) {
        shader->cacheUniforms({
                                      "projection",
                                      "view",
                                      "modelview",
                                      "transposedInvModelView"
                              });
    }
}