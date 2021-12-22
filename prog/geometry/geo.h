#ifndef GAME_GEO_H
#define GAME_GEO_H

#include "../../lib/containers/pair/Pair.h"

namespace geo {

    template <typename T>
    using point = Pair<T>;

    using i_point = point<int>;
}

#endif //GAME_GEO_H