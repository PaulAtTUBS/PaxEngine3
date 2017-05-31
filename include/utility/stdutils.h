//
// Created by Paul on 28.05.2017.
//

#ifndef PAXENGINE3_STDUTILS_H
#define PAXENGINE3_STDUTILS_H

#include <vector>
#include <algorithm>

namespace PAX {
    namespace Util {
        template<class T>
        inline bool removeFromVector(std::vector<T> *vector, const T element) {
            auto iter = std::find(vector->begin(), vector->end(), element);
            if (iter != vector->end()) {
                vector->erase(iter);
                return true;
            }
            return false;
        }
    }
}

#endif //PAXENGINE3_STDUTILS_H
