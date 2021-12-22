#include "artifact.h"

#include "../characters/character.h"

const Vector<artifact::artifact_info> artifact::artifact_infos = {
        {
                "PROTEIN",
                0,
                [](character* ch) {
                    if (ch->dead())
                        return;
                    static const int gain = 20;
                    ch->m_max_hp += gain;
                    if (ch->m_hp > 0)
                        ch->m_hp += gain;
                    ch->check_hp();
                },
                [](character* ch) {
                    if (ch->dead())
                        return;
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
                    if (ch->dead())
                        return;
                    static const int gain = 10;
                    ch->m_hp += gain;
                    ch->check_hp();
                },
                [](character* ch) {
                    if (ch->dead())
                        return;
                    static const int gain = 10;
                    ch->m_hp -= gain;
                    ch->check_hp();
                }
        },
        {
                "GOLDEN APPLE",
                2,
                [](character* ch) {
                    if (ch->dead())
                        return;
                    ch->m_hp = ch->max_hp();
                },
                [](character* ch) {
                    // do nothing
                }
        },
        {
                "KNIFE",
                3,
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

artifact::artifact(artifact_id id, geo::i_point coords) : entity(coords), m_id(id) {}

artifact::artifact_id artifact::id() const {
    return m_id;
}

void artifact::act(artifact* art, character* ch) {
    artifact_infos[art->m_id].m_action(ch);
}

void artifact::react(artifact* art, character* ch) {
    artifact_infos[art->m_id].m_reaction(ch);
}