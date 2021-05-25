#ifndef RD70_BITARRAY
#define RD70_BITARRAY

#include <algorithm> //std::equal std::transform
#include <numeric> //accumulate
#include <cstring> //memset
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
namespace ilrd
{

template <size_t N, typename WORD_SIZE = unsigned long>
class BitArray
{
    class BitProxy;
public:
    explicit BitArray(bool intState = false);
    // BitArray(const BitArray&); generated is enough
    // ~BitArray();
	//BitArray& operator=(const BitArray&);

    BitProxy& operator[](const size_t index);
    bool operator[](const size_t index) const;
    BitArray& operator&=(const BitArray&);
    BitArray& operator^=(const BitArray&);
    BitArray& operator|=(const BitArray&);
    bool operator!=(const BitArray&) const;
    bool operator==(const BitArray&) const;
	bool GetBit(const size_t) const;
	void SetBit(const size_t, bool);
    size_t CountOnBits() const;

    void Toogle();
    void Toogle(size_t);

    static const size_t WORD;

private:
	static const size_t BITSINBYTE = 8;
	static const size_t BITSINWORD = 8*sizeof(WORD_SIZE);
	static const size_t WORDSINARRAY = N/BITSINWORD + ((N%BITSINWORD)!=0);
	static const WORD_SIZE FIRSTBITINWORD =
                                static_cast<WORD_SIZE>(1) << (BITSINWORD - 1);
	WORD_SIZE m_array[WORDSINARRAY];

    static void ToogleWordIMP(WORD_SIZE&);
    static WORD_SIZE WordIntersectIMP(WORD_SIZE, WORD_SIZE);
    static WORD_SIZE WordXorIMP(WORD_SIZE, WORD_SIZE);
    static WORD_SIZE WordUnionIMP(WORD_SIZE, WORD_SIZE);
    static size_t CountBitonWordIMP(size_t, WORD_SIZE);


    class BitProxy
    {
    public:
        BitProxy(BitArray*, size_t);

        bool operator=(const BitArray&);
        bool operator=(const bool);
        operator bool();
    private:
        BitArray* m_bitArray;
        size_t m_index;
    };
};

template <size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>::BitArray(bool intState)
{
	WORD_SIZE initVal = (static_cast<WORD_SIZE>(intState))
						*(~static_cast<WORD_SIZE>(0));

    memset(m_array, initVal, WORDSINARRAY*sizeof(WORD_SIZE));
}

template <size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::GetBit(const size_t bitIndex) const
{//LSB is on the LEFT
	size_t arrIndex = bitIndex / BITSINWORD;
	size_t subIndex = bitIndex % BITSINWORD;

	return (*(m_array + arrIndex) & (FIRSTBITINWORD >> subIndex));
}

template <size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::SetBit(const size_t bitIndex, bool value)
{//LSB is on the LEFT
	size_t arrIndex = bitIndex / BITSINWORD;
	size_t subIndex = bitIndex % BITSINWORD;

    if (value)
    {
        *(m_array + arrIndex) |= (FIRSTBITINWORD  >> subIndex);
    }

    else
    {
        *(m_array + arrIndex) &= ~(FIRSTBITINWORD  >> subIndex);
    }
}

template <size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::operator[](const size_t bitIndex) const
{
	return(GetBit(bitIndex));
}

template <size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::Toogle()
{
	std::for_each(m_array, m_array + WORDSINARRAY, ToogleWordIMP);
}

template <size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::ToogleWordIMP(WORD_SIZE& word)
{
    word = ~word;
}

template <size_t N, typename WORD_SIZE>
void BitArray<N, WORD_SIZE>::Toogle(size_t index)
{
	(*this)[index] = (GetBit(index) == false);
}

template <size_t N, typename WORD_SIZE>
typename BitArray<N, WORD_SIZE>::BitProxy& BitArray<N, WORD_SIZE>::operator[](const size_t bitIndex)
{
	boost::shared_ptr<BitProxy> bP = boost::make_shared<BitProxy>(this, bitIndex);
    return (*bP);
}

template <size_t N, typename WORD_SIZE>
WORD_SIZE BitArray<N, WORD_SIZE>::WordIntersectIMP(WORD_SIZE w1, WORD_SIZE w2)
{
    return(w1&w2);
}

template <size_t N, typename WORD_SIZE>
WORD_SIZE BitArray<N, WORD_SIZE>::WordXorIMP(WORD_SIZE w1, WORD_SIZE w2)
{
    return(w1^w2);
}
template <size_t N, typename WORD_SIZE>
WORD_SIZE BitArray<N, WORD_SIZE>::WordUnionIMP(WORD_SIZE w1, WORD_SIZE w2)
{
    return(w1 | w2);
}

template <size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>& BitArray<N, WORD_SIZE>
                            ::operator&=(const BitArray& other)
{
    std::transform (m_array, m_array + WORDSINARRAY,
                other.m_array, m_array, WordIntersectIMP);

    return (*this);
}

template <size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>& BitArray<N, WORD_SIZE>
                            ::operator^=(const BitArray& other)
{
    std::transform (m_array, m_array + WORDSINARRAY,
                other.m_array, m_array, WordXorIMP);

    return (*this);
}

template <size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>& BitArray<N, WORD_SIZE>
                            ::operator|=(const BitArray& other)
{
    std::transform (m_array, m_array + WORDSINARRAY,
                other.m_array, m_array, WordUnionIMP);

    return (*this);
}

template <size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::operator==(const BitArray& other) const
{
    return (std::equal (m_array, m_array + WORDSINARRAY, other.m_array));
}

template <size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::operator!=(const BitArray& other) const
{
    return (!(*this == other));
}

template <size_t N, typename WORD_SIZE>
size_t BitArray<N, WORD_SIZE>::CountOnBits() const
{
    return std::accumulate(m_array, m_array + WORDSINARRAY, 0, CountBitonWordIMP);
}

template <size_t N, typename WORD_SIZE>
size_t BitArray<N, WORD_SIZE>::CountBitonWordIMP(size_t count ,WORD_SIZE word)
{
    static size_t comparisons = 0;
    size_t i = 0;
    size_t mask = FIRSTBITINWORD;

    while(i < BITSINWORD && comparisons < N)
    {
        count += ((word & mask) != 0);
        mask >>= 1;
        ++comparisons;
        ++i;
    }

    if (comparisons == N)
    {
        comparisons = 0;
    }

    return (count);
}


template <size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>::BitProxy::BitProxy(BitArray* bA, size_t index)
	:m_bitArray(bA), m_index(index)
{}

template <size_t N, typename WORD_SIZE>
BitArray<N, WORD_SIZE>::BitProxy::operator bool()
{
    return(m_bitArray->GetBit(m_index));
}

template <size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::BitProxy::operator=(const BitArray& other)
{//handles self assignment
    m_bitArray = other.m_bitArray;
    m_index = other.m_index;

    return((*m_bitArray)[m_index]);
}

template <size_t N, typename WORD_SIZE>
bool BitArray<N, WORD_SIZE>::BitProxy::operator=(const bool other)
{
    m_bitArray->SetBit(m_index, other);

    return((*m_bitArray)[m_index]);
}



}
#endif //RD70_BITARRAY
