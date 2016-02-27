/*! \brief Template to convert stuff to strings.
 */

#ifndef STRINGIFY_HH
#define STRINGIFY_HH 1

#include <sstream>

namespace stringify_internals
{
    template <typename T_>
    std::string real_stringify(const T_ & t)
    {
        std::ostringstream s;
        s << t;
        return s.str();
    }

    inline std::string real_stringify(const bool & t)
    {
        return t ? "true" : "false";
    }

    inline std::string real_stringify(const char * const t)
    {
        return std::string(t);
    }
}

template <typename T_>
inline std::string stringify(const T_ & t)
{
    return stringify_internals::real_stringify(t);
}

#endif
