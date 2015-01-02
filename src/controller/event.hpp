#pragma once

#include <memory>

class event_manager;

class event
{
public:
    virtual ~event() = 0;
    virtual std::unique_ptr<event> next_event(event_manager& context);
    virtual std::unique_ptr<event> update(event_manager& context) = 0;
};

class start : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class init_chip : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class init_deal : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class bet_ante : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class exchange : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class raise : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class call : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class payoff : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class player_win : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class ai_win : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};

class end : public event
{
public:
    virtual std::unique_ptr<event> update(event_manager& context);
};
