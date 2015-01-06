#pragma once

#include <memory>

class event_manager;

namespace event
{
    class event                 // Stateパターンを使ってみる
    {
    public:
        virtual ~event() = 0;
        virtual std::unique_ptr<event> next_event(event_manager& context);

    private:
        virtual std::unique_ptr<event> update(event_manager& context) = 0;
    };

    class start : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class new_deal : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class bet_ante : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class exchange : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class raise : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class call : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class payoff : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class player_win : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class ai_win : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };

    class end : public event
    {
    private:
        virtual std::unique_ptr<event> update(event_manager& context);
    };
}
