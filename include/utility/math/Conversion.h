//
// Created by bittner on 11/20/17.
//

#ifndef PAXENGINE3_CONVERSION_H
#define PAXENGINE3_CONVERSION_H

#include <assert.h>

namespace PAX {
    namespace Util {
        namespace Conversion {
            int coordinatesToIndex(int w, int h, int x, int y) {
                assert(x < w);
                assert(y < h);
                return (w*y)+x;
            }
        }
    }
}

#endif //PAXENGINE3_CONVERSION_H
