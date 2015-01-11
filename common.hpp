#ifndef COMMON_HPP
#define COMMON_HPP

//
//
//
#define STR_TO_INT(cstr) strtol((cstr), 0, 10)
#define CHAR_TO_INT(chr) ((chr) - 48)

//
//
//
#define MAKE_NONCOPYABLE(name) \
    name(const name&); \
    name& operator = (const name&)

//
//
//
#define MAKE_SINGLETON(name)                    \
    MAKE_NONCOPYABLE(name);                     \
public:                                         \
static name& instance() {                       \
    static name ref;                            \
    return ref;                                 \
}                                               \
private:                                        \

typedef const char*   cstr;
typedef unsigned char byte;

#endif // COMMON_HPP
