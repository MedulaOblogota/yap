#ifndef RD70_SERIALIZER
#define RD70_SERIALIZER

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/core/demangle.hpp>

#include "factory.hpp"
// template<class Base, class DERIVED>
// boost::shared_ptr<Base> Create<DERIVED>(std::istream& is_)
// {
//   boost::shared_ptr<Base> base(new DERIVED());
//
//   is_ >> *base;
//
//   // make_shared<DERIVED>()
//
//   return base;
// }

// Base must have << and >> operator
// Base must have default Ctor

template<class Base>
class Deserializer
{
public:
  void Serialize(std::ostream&, const Base&);
  boost::shared_ptr<Base> Deserialize(std::istream&);

  template<class DERIVED>
  void Add();

private:
  // template <typename HANDLE, typename KEY, typename DATA, typename CREATOR>
  Factory<boost::shared_ptr<Base>, char *, std::istream&, boost::shared_ptr<Base> (*)(std::istream& is_)> m_factory;

  template<class DERIVED>
  boost::shared_ptr<Base> Create(std::istream& is_);
};

template<class Base>
void Deserializer<Base>::Serialize(std::ostream& os_, const Base& s_)
{
	// std::string buffer =
  os_ << boost::core::demangle(typeid(s_).name()) << "\n" << s_;
}

template<class Base>
template<class DERIVED>
void Deserializer<Base>::Add()
{
  m_factory.add(typeid(DERIVED).name(), Deserializer::Create<DERIVED>);
}

template<class Base>
boost::shared_ptr<Base> Deserializer<Base>::Deserialize(std::istream& os_)
{
  return m_factory.create(typeid(*this).name(), os_);
}

template<class Base>
template <class DERIVED>
boost::shared_ptr<Base> Deserializer<Base>::Create(std::istream& is_)
{
  boost::shared_ptr<Base> base(new DERIVED());

  is_ >> *base;

  return base;
}

#endif //RD70_SERIALIZER
