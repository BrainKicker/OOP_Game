#ifndef GAME_ARTIFACT_H
#define GAME_ARTIFACT_H

#include <functional>

#include "../../../lib/containers/vector/vector.h"
#include "../../../lib/utils/data.h"

#include "../entity.h"

class character; // pre-declaration

class artifact : public entity {

public:

    using artifact_action = std::function<void(character*)>;

    enum artifact_ids {
        PROTEIN = 0,
        APPLE,
        KNIFE,

        COUNT
    };

    struct artifact_info {
        const char* m_name;
        int m_id;
        artifact_action m_action;
        artifact_action m_reaction;
    };

private:

    static const vector<artifact_info> artifact_infos;

    int m_id;

public:

    artifact(int id);

    int id();

    static void act(artifact* art, character* ch);
    static void react(artifact* art, character* ch);
};

#endif //GAME_ARTIFACT_H