//
// Created by Paul on 06.07.2017.
//

#ifndef PAXENGINE3_STRINGUTILS_H
#define PAXENGINE3_STRINGUTILS_H

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>

#define PAX_UTIL_STRING_EQUALS !strcmp
#define PAX_UTIL_STRING_NEQUALS strcmp

#define PAX_UTIL_BOOL_TO_YESNO(boolValue) boolValue ? "yes" : "no"

namespace PAX {
    namespace Util {
        // trim from start (in place)
        void ltrim(std::string &s);

        // trim from end (in place)
        void rtrim(std::string &s);

        // trim from both ends (in place)
        void trim(std::string &s);

        // trim from both ends (copying)
        std::string trimmed(std::string s);

        bool startsWith(const std::string& s, const std::string& prefix);

        bool endsWith(const std::string& s, const std::string& suffix);

        std::string getExtension(const std::string & path);

        void str_replace(std::string& string, const char& from, const char& to);
    }
}
#endif //PAXENGINE3_STRINGUTILS_H
