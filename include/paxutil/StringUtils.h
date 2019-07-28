//
// Created by Paul on 06.07.2017.
//

#ifndef PAXENGINE3_STRINGUTILS_H
#define PAXENGINE3_STRINGUTILS_H

#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <locale>
#include <glm/detail/qualifier.hpp>

//#define PAX_UTIL_STRING_EQUALS !strcmp
#define PAX_UTIL_STRING_NEQUALS strcmp

//#define PAX_UTIL_BOOL_TO_YESNO(boolValue) boolValue ? "yes" : "no"

namespace PAX {
    /// Convert the string *str* to T.
    template<class T>
    class TryParser {
    public:
        [[nodiscard]] static T tryParse(const std::string & str) {
            return str;
        }
    };

    namespace String {
        void toLower(std::string & str);
        void toUpper(std::string & str);

        /// trim from start (in place)
        void ltrim(std::string &s);

        /// trim from end (in place)
        void rtrim(std::string &s);

        /// trim from both ends (in place)
        void trim(std::string &s);

        /// trim from both ends (copying)
        std::string trimmed(std::string s);

        bool startsWith(const std::string &s, const std::string &prefix);
        bool endsWith(const std::string &s, const std::string &suffix);

        /// Split the given *subject* string at occurences of *separator*.
        std::vector<std::string> split(char separator, const std::string &subject, bool keepEmptySubstrings = true);

        std::string getExtension(const std::string &path);

        void replace(std::string &string, const char &from, const char &to);

        template<typename T>
        T tryParse(const std::string &str) {
            return TryParser<T>::tryParse(str);
        }
    }

#define PAX_SPECIALIZE_TRYPARSER_HEADER(type) \
            template<> \
            class TryParser<type> { \
            public: \
                [[nodiscard]] static type tryParse(const std::string & str); \
            };

    PAX_SPECIALIZE_TRYPARSER_HEADER(bool)
    PAX_SPECIALIZE_TRYPARSER_HEADER(int)
    PAX_SPECIALIZE_TRYPARSER_HEADER(unsigned int)
    PAX_SPECIALIZE_TRYPARSER_HEADER(unsigned long)
    PAX_SPECIALIZE_TRYPARSER_HEADER(float)
    PAX_SPECIALIZE_TRYPARSER_HEADER(double)

    template<glm::length_t L, typename T, glm::qualifier Q>
    class TryParser<glm::vec<L, T, Q>> {
    public:
        static glm::vec<L, T, Q> tryParse(const std::string &str) {
            glm::vec<L, T, Q> ret(0);
            const size_t strlen = str.length();

            if (
                    (str[0] == '(' && str[strlen-1] == ')')
                    || (str[0] == '[' && str[strlen-1] == ']')
                    ) {
                std::string liststr = str.substr(1, strlen - 2);
                std::vector<std::string> numbers = String::split(',', liststr, false);

                for (glm::length_t i = 0; i < L && i < numbers.size(); ++i)
                    ret[i] = String::tryParse<T>(numbers[i]);
            }

            return ret;
        }
    };
}
#endif //PAXENGINE3_STRINGUTILS_H
