#ifndef RD70_STRING
#define RD70_STRING

namespace ilrd
{
#include <cstdlib>

class RdString;

std::ostream& operator<<(std::ostream& os_, const RdString& string_);

class RdString
{
public:
    RdString(const char* str=""); //must not be NULL. Non-explicit on purpose
    RdString(const RdString& other_);
    ~RdString();

    RdString& operator=(const RdString& other_);
    std::size_t Length() const;

    const char *Cstr() const;

private:
    char *m_str;

    // static void DestroyIMP();
    static char* CopyIMP(const char* other_);
    size_t DecCounter();
    size_t IncCounter();

};

}
#endif //RD70_STRING
