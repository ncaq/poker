#pragma once

#include <memory>

class event_observer;

class event
{
public:
    virtual ~event() = 0;
    virtual std::unique_ptr<event> next_event(event_observer& context) = 0;
};

class init_chip : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class init_deal : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class ante : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class exchange : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class raise : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class call : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class payoff : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};

class end : public event
{
public:
    virtual std::unique_ptr<event> next_event(event_observer& context);
};
