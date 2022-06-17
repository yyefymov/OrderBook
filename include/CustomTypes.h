#ifndef CUSTOMTYPES_H
#define CUSTOMTYPES_H

#include <string>

namespace CustomTypes
{
    struct timestamp
    {
        int tm_hour = 0;
        int tm_min = 0;
        int tm_sec = 0;
        int tm_usec = 0;

        std::string to_string()
        {
            std::string time_str = "";
            time_str += std::to_string(tm_hour) + ":";
            time_str += std::to_string(tm_min) + ":";
            time_str += std::to_string(tm_sec) + ".";
            time_str += std::to_string(tm_usec);

            return time_str;
        }
    };
}

#endif // CUSTOMTYPES_H
