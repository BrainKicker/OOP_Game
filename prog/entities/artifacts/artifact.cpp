#include "artifact.h"

#include "../characters/character.h"

const vector<artifact::artifact_info> artifact::artifact_infos = {
        {
                "PROTEIN",
                0,
                [](character* ch) {
                    static const int gain = 20;
                    ch->m_max_hp += gain;
                    if (ch->m_hp > 0)
                        ch->m_hp += gain;
                    ch->check_hp();
                },
                [](character* ch) {
                    static const int gain = 20;
                    ch->m_max_hp -= gain;
                    ch->m_hp -= gain;
                    ch->check_max_hp();
                    ch->check_hp();
                }
        },
        {
                "APPLE",
                1,
                [](character* ch) {
                    static const int gain = 10;
                    ch->m_hp += gain;
                    ch->check_hp();
                },
                [](character* ch) {
                    static const int gain = 10;
                    ch->m_hp -= gain;
                    ch->check_hp();
                }
        },
        {
                "KNIFE",
                2,
                [](character* ch) {
                    static const int gain = 10;
                    ch->m_damage += gain;
                },
                [](character* ch) {
                    static const int gain = 10;
                    ch->m_damage -= gain;
                    ch->check_damage();
                }
        }
};

artifact::artifact(int id) : entity(ARTIFACT), m_id(id) {}

int artifact::id() {
    return m_id;
}

void artifact::act(artifact* art, character* ch) {
    artifact_infos[art->m_id].m_action(ch);
}

void artifact::react(artifact* art, character* ch) {
    artifact_infos[art->m_id].m_reaction(ch);
}