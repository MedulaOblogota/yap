#ifndef RD70_SCOPEDLOCK
#define RD70_SCOPEDLOCK

template<class T, void (*Lock)(T&), void (*Unlock)(T&)>
class ScopedLock
{
public:
  explicit ScopedLock(T&);
  ~ScopedLock();

private:
  T& m_obj;
};

template<class T, void (*Lock)(T&), void (*Unlock)(T&)>
ScopedLock<T, Lock, Unlock>::ScopedLock(T& obj_)
	: m_obj(obj_)
{
	Lock(m_obj);
}

template<class T, void (*Lock)(T&), void (*Unlock)(T&)>
ScopedLock<T, Lock, Unlock>::~ScopedLock()
{
	Unlock(m_obj);
}

#endif //RD70_SCOPEDLOCK
