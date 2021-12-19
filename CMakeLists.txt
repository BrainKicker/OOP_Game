cmake_minimum_required(VERSION 3.20)
project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game main.cpp lib/containers/list/list.h lib/containers/matrix/matrix.h lib/containers/pair/pair.h lib/containers/string/string.h lib/containers/string/string.cpp lib/containers/queue/queue.h lib/containers/vector/vector.h lib/containers/vector/vector_iterator.h lib/utils/memory_utils.h prog/entities/entity.cpp prog/entities/entity.h prog/entities/characters/character.cpp prog/entities/characters/character.h prog/entities/characters/player/player.cpp prog/entities/characters/player/player.h prog/entities/artifacts/artifact.cpp prog/entities/artifacts/artifact.h prog/entities/characters/enemies/enemy.cpp prog/entities/characters/enemies/enemy.h prog/field/field.cpp prog/field/field.h prog/geometry/geo.h prog/field/cell/cell.cpp prog/field/cell/cell.h lib/utils/data.h prog/adapters/sfml/sfml_adapter.cpp prog/adapters/sfml/sfml_adapter.h prog/field/action.h prog/field/direction.h prog/field/action.cpp prog/adapters/sfml/window/RenderWindow.cpp prog/adapters/sfml/window/RenderWindow.h lib/algorithm/comparator/comparator.h lib/algorithm/sorts/heapsort.h lib/algorithm/algorithm.h lib/utils/logger/logger.cpp lib/utils/logger/logger.h)

set(CMAKE_CXX_FLAGS "-lsfml-system -lsfml-window -lsfml-graphics -lpthread")