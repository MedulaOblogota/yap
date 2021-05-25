#include <iostream>
#include <list>
#include <vector>

// template <typename IterT>
// struct iterator_traits<IterT*>
// {
//   typedef random_access_iterator_tag iterator_category;
// };

template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT& d, std::random_access_iterator_tag)
{
  iter += d;
}

template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT& d, std::bidirectional_iterator_tag)
{
  if (d > 0)
  {
    while (d--)
    {
      ++iter;
    }
  }
  else
  {
    while (d++)
    {
      --iter;
    }
  }
}

template<typename IterT, typename DistT>
void doAdvance(IterT& iter, DistT& d, std::input_iterator_tag)
{
  while (d--) ++iter;
}

template<typename IterT, typename DistT>
void Advance(IterT& iter, DistT& d)
{
  doAdvance(
    iter, d, typename std::iterator_traits<IterT>::iterator_category()
  );
}

int main()
{
  std::list<int> myList;
  std::vector<char> myVector;
  int first = 1;
  int second = 2;
  int third = 3;
  int fourth = 4;
  int fifth = 5;
  size_t distance = 0;

  myList.push_back(first);
  myList.push_back(second);
  myList.push_back(third);
  myList.push_back(fourth);
  myList.push_back(fifth);

  std::list<int>::iterator it = myList.begin();
  Advance(it, distance);
  std::cout << "List item: " << *it << std::endl;

  // num = 0;
  myVector.push_back('a');
  myVector.push_back('b');
  myVector.push_back('c');
  myVector.push_back('d');
  myVector.push_back('e');
  std::vector<char>::iterator vit = myVector.begin();

  distance = 0;
  Advance(vit, distance);

  std::cout << "vector size " << myVector.size() << std::endl;

  std::cout << "Vector item: " << *vit << std::endl;


}
