#ifndef RC70_STRING
#define RC70_STRING

#include <iostream>
namespace ilrd
{
  #include <cstddef>
  // #include <cstdlib>

class RcString;

std::ostream& operator<<(std::ostream& os_, const RcString& string_);

class RcString
{
public:
    RcString(const char* str=""); //must not be NULL. Non-explicit on purpose
    RcString(const RcString& other_);
    ~RcString();

    RcString& operator=(const RcString& other_);
    char& operator[](size_t index);
    char operator[](size_t) const;
    std::size_t Length() const;
    bool IsShared();

    const char *Cstr() const;

private:
    char *m_str;
    // size_t *m_counter;

    // static void DestroyIMP();
    static char* CopyStringIMP(const char* other_);
    // static char* CopyRcStringIMP(const char* other_);

    void DecCounterIMP();
    void IncCounterIMP() const;
    size_t GetCounterIMP();
    void InitCounterIMP();

};

}
#endif //RC70_STRING
