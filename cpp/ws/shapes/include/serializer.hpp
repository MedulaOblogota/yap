#ifndef RD70_SERIALIZER
#define RD70_SERIALIZER

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/core/demangle.hpp>
#include <boost/make_shared.hpp>

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
  Factory<boost::shared_ptr<Base>, std::string, std::istream&,  boost::shared_ptr<Base> (*)(std::istream&)> m_factory;

  template<class DERIVED>
  static boost::shared_ptr<Base> Create(std::istream& is_);
};

template<class Base>
void Deserializer<Base>::Serialize(std::ostream& os_, const Base& s_)
{
  os_ << typeid(s_).name() << "\n" << s_;
}

template<class Base>
template<class DERIVED>
void Deserializer<Base>::Add()
{
  m_factory.add(typeid(DERIVED).name(), Create<DERIVED>);
}

template<class Base>
boost::shared_ptr<Base> Deserializer<Base>::Deserialize(std::istream& os_)
{
  std::string line;
  getline(os_, line);
  std::cout << line <<std::endl;
  return m_factory.create(line, os_);
}

template<class Base>
template <class DERIVED>
boost::shared_ptr<Base> Deserializer<Base>::Create(std::istream& is_)
{
  boost::shared_ptr<DERIVED> new_shape = boost::make_shared<DERIVED>(); //WHAT IS make_shared???

  is_ >> *new_shape;

  return new_shape;
}

#endif //RD70_SERIALIZER
