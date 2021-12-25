#ifndef GAME_ABSTRACT_EVENT_GETTER_H
#define GAME_ABSTRACT_EVENT_GETTER_H

template <typename event_type>
class abstract_event_getter {
public:
    virtual ~abstract_event_getter() = default;
    virtual event_type poll_event() = 0;
    virtual event_type wait_event() = 0;
};

#endif //GAME_ABSTRACT_EVENT_GETTER_H