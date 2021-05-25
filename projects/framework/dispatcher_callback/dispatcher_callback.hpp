#ifndef RD70_DISPATCHER_CALLBACK
#define RD70_DISPATCHER_CALLBACK

#include <list>

template <typename SUBJECT, typename DATA>
class Dispatcher
{
public:
    class CallBack;

    virtual ~Dispatcher();
    void Notify (const DATA& event_);
    void Register(CallBack *callback_);
    void UnRegister(CallBack *callback_);

private:
    List<CallBack *> m_subscribers;
};

template <typename SUBJECT, typename DATA>
class CallBack
{
public:
    CallBack(SUBJECT *subject_);
    virtual ~CallBack();

    friend class Dispatcher;
    virtual void Update(DATA &data_);

private:
    SUBJECT *m_subject;
};

template<typename SUBJECT, typename DATA>
void Dispatcher<SUBJECT, DATA>::Notify(const DATA& event_)
{
    for (std::list<CallBack *>::iterator it = m_subscribers.begin(); it != m_subscribers.end(); ++it)
    {
        (*it).Update(event_);
    }
}

template<typename SUBJECT, typename DATA>
void Dispatcher<SUBJECT, DATA>::Register(CallBack *callback_)
{
    m_subscribers.push_back(callback_);
}

template<typename SUBJECT, typename DATA>
void Dispatcher<SUBJECT, DATA>::UnRegister(CallBack *callback_)
{
    m_subscribers.remove(callback_);
}

template<typename SUBJECT, typename DATA>
CallBack<SUBJECT, DATA>::CallBack(SUBJECT *subject_)
    : m_subject(subject_)
{}

template<typename SUBJECT, typename DATA>
void CallBack<SUBJECT, DATA>::Update(DATA &data_)
{
    m_subject(data);
}

#endif // RD70_DISPATCHER_CALLBACK