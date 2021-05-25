#include <cstdlib>    //size_t
#include <iostream>   //std
#include <cstring>    //strlen
#include <algorithm>  //std::equal

template <std::size_t N, typename WORD_SIZE = unsigned long>
class BitArray
{
  class BitProxy;
public:
  explicit BitArray(bool init_val = false);//
  //generated CCtor and Dtor sufficient
	//generated Assignment Operator sufficient

  BitProxy operator[](size_t index);//
  bool operator[](size_t index)const;//invalid index results in undefined behavior //

  bool operator==(const BitArray&)const;//
	bool operator!=(const BitArray&)const;//

	bool Get(size_t index)const;//
	void Set(bool, size_t);//

	void Toggle(size_t);//
	void Toggle();//
	size_t Count()const;//

	BitArray& operator&=(const BitArray&);
	BitArray& operator|=(const BitArray&);
	BitArray& operator^=(const BitArray&);

private:
  class BitProxy
	{
	public:
		explicit BitProxy(BitArray*, size_t);//

		bool operator=(const BitProxy&);//
		bool operator=(const bool b);//
		operator bool();//

	private:
		BitArray* m_bitarray;
		size_t m_index;
	};
	// WORD_SIZE[(1+((N-1) % sizeof(WORD_SIZE)) * BITS_IN_BYTE] m_array;
  static const size_t BITS_IN_BYTE = 8;
  static const size_t LENGTH =  1 + (N - 1) / (sizeof(WORD_SIZE) * BITS_IN_BYTE);
  static const size_t TAIL = LENGTH * (sizeof(WORD_SIZE) * BITS_IN_BYTE) - N;

  WORD_SIZE m_array[LENGTH];
  size_t GetMainIndexIMP(size_t) const;//
  size_t GetSecondaryIndexIMP(size_t)const;//

  class WordIntersectIMP
  {
  public:
    WORD_SIZE operator()(WORD_SIZE, WORD_SIZE);
  };

  class WordXorIMP
  {
  public:
    WORD_SIZE operator()(WORD_SIZE, WORD_SIZE);
  };

  class WordUnionIMP
  {
  public:
    WORD_SIZE operator()(WORD_SIZE, WORD_SIZE);
  };
};

template<std::size_t N, class WORD_SIZE>
size_t BitArray<N, WORD_SIZE>::GetMainIndexIMP(size_t index)const
{
    return index / (sizeof(WORD_SIZE) * BITS_IN_BYTE);
}

template<std::size_t N, class WORD_SIZE>
size_t BitArray<N, WORD_SIZE>::GetSecondaryIndexIMP(size_t index)const
{
  return index % (sizeof(WORD_SIZE) * BITS_IN_BYTE);
}

template <std::size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>::BitArray(bool init_val)
{
  char initial = static_cast<char>(init_val) * (~static_cast<char>(0));

  memset(m_array, initial, LENGTH * sizeof(WORD_SIZE));
}

template <std::size_t N, typename WORD_SIZE>
typename BitArray<N, WORD_SIZE>::BitProxy BitArray<N, WORD_SIZE>::operator[](size_t index)
{
  BitArray<N, WORD_SIZE>::BitProxy bp(this, index);

  return bp;
}

template <std::size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::operator[](size_t index)const
{
  size_t main_index = GetMainIndexIMP(index);
  size_t sec_index = GetSecondaryIndexIMP(index);

  WORD_SIZE mask = 0x01 << sec_index;

  return (m_array[main_index] & mask == mask);
}

template <std::size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::operator==(const BitArray& other_)const
{
  bool first = (std::equal(m_array, m_array + (N / (sizeof(WORD_SIZE) * BITS_IN_BYTE)), other_.m_array));
  WORD_SIZE mask = 0x01;
  size_t remainder = N % (sizeof(WORD_SIZE) * BITS_IN_BYTE);

  for (size_t i = 0; i < remainder; ++i)
  {
    if ((m_array[LENGTH -1 ] & mask) != (other_.m_array[LENGTH - 1] & mask))
    {
      return false;
    }
    mask <<= 1;
  }

  return first;
}

template <std::size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::operator!=(const BitArray& other_)const
{
  return (!(*this == other_));
}

template <std::size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::Get(size_t index)const
{
  size_t main_index = GetMainIndexIMP(index);
  size_t sec_index = GetSecondaryIndexIMP(index);
  WORD_SIZE mask = 0x01 << sec_index;

  return ((m_array[main_index] & mask) == mask);
}

template <std::size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::Set(bool value, size_t index)
{
  size_t main_index = GetMainIndexIMP(index);
  size_t sec_index = GetSecondaryIndexIMP(index);

  WORD_SIZE mask = (value == true) << sec_index;

  m_array[main_index] = m_array[main_index] & ~mask;
  m_array[main_index] = (mask | m_array[main_index]);
}

template <std::size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::Toggle(size_t index)
{
  size_t main_index = GetMainIndexIMP(index);
  size_t sec_index = GetSecondaryIndexIMP(index);

  WORD_SIZE mask = 0x01 << sec_index;

  m_array[main_index] = m_array[main_index] ^ mask;
}

template <std::size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::Toggle()
{
  size_t i = 0;

  for (i = 0; i < LENGTH; ++i)
  {
    m_array[i] = ~m_array[i];
  }
}

template <std::size_t N, typename WORD_SIZE>
size_t BitArray<N, WORD_SIZE>::Count()const
{
  size_t counter = 0;
  WORD_SIZE mask = 0x01;

  for (size_t i = 0; i < (N / (sizeof(WORD_SIZE) * BITS_IN_BYTE)); ++i )
  {
    mask = 0x01;

    for (size_t j = 0; j < (sizeof(WORD_SIZE) * BITS_IN_BYTE); ++j)
    {
      if ((m_array[i] & (mask << j)) == (mask << j))
      {
        ++counter;
      }
    }
  }

  size_t remainder = N % (sizeof(WORD_SIZE) * BITS_IN_BYTE);
  mask = 0x01;

  for (size_t i = 0; i < remainder; ++i)
  {
    if ((m_array[LENGTH -1 ] & mask) == mask)
    {
      ++counter;
    }
    mask <<= 1;
  }

  return counter;
}

template <std::size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>& BitArray<N, WORD_SIZE>::operator&=(const BitArray& other_)
{
  std::transform (m_array, m_array + LENGTH,
              other_.m_array, m_array, WordIntersectIMP());

  return (*this);
}

template <std::size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>& BitArray<N, WORD_SIZE>::operator|=(const BitArray& other_)
{
  std::transform (m_array, m_array + LENGTH,
              other_.m_array, m_array, WordUnionIMP());

  return (*this);
}

template <std::size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>& BitArray<N, WORD_SIZE>::operator^=(const BitArray& other_)
{
  std::transform (m_array, m_array + LENGTH,
              other_.m_array, m_array, WordXorIMP());

  return (*this);
}

template <size_t N, typename WORD_SIZE>
WORD_SIZE BitArray<N, WORD_SIZE>::WordIntersectIMP::operator()(WORD_SIZE w1, WORD_SIZE w2)
{
    return(w1&w2);
}

template <size_t N, typename WORD_SIZE>
WORD_SIZE BitArray<N, WORD_SIZE>::WordXorIMP::operator()(WORD_SIZE w1, WORD_SIZE w2)
{
    return(w1^w2);
}

template <size_t N, typename WORD_SIZE>
WORD_SIZE BitArray<N, WORD_SIZE>::WordUnionIMP::operator()(WORD_SIZE w1, WORD_SIZE w2)
{
    return(w1|w2);
}

template<std::size_t N, class WORD_SIZE>
BitArray<N, WORD_SIZE>::BitProxy::BitProxy(BitArray* bitarray, size_t index)
  : m_bitarray(bitarray), m_index(index)
{}

template<std::size_t N, class WORD_SIZE>
bool BitArray<N, WORD_SIZE>::BitProxy::operator=(const BitProxy& bitproxy)
{
  bool value = bitproxy.m_bitarray->Get(bitproxy.m_index);
  m_bitarray->Set(value, m_index);

  return value;
}

template<std::size_t N, class WORD_SIZE>
bool BitArray<N, WORD_SIZE>::BitProxy::operator=(const bool b)
{
  size_t index = this->m_index;

  m_bitarray->Set(b, index);
  return b;
}

template<std::size_t N, class WORD_SIZE>
BitArray<N, WORD_SIZE>::BitProxy::operator bool()
{
  return (m_bitarray->Get(m_index) == true);
}
