//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PATH_H
#define PAXENGINE3_PATH_H

#include <string>
#include <paxutil/StringUtils.h>

namespace PAX {
    class Path {
    public:
        static constexpr char PathSeparator_Win = '\\';
        static constexpr char PathSeparator_Unix = '/';
        static constexpr char PathSeparator =
#ifdef PAX_OS_WIN
                PathSeparator_Win;
#else
                PathSeparator_Unix;
#endif

    private:
        std::string _path;

    public:
        Path(const char* path);
        Path(const std::string& path);
        Path(const Path& other);

        /// A Path is considered to be a file, if it contains a dot, indicating a file ending, after the last slash/backslash.
        bool isFile() const;
        bool isDirectory() const;
        bool isAbsolute() const;
        Path getDirectory() const;

        static void convertToCurrentPlatform(std::string & path);
        static void convertToWin(std::string & path);
        static void convertToUnix(std::string & path);
        static void simplify(std::string & path);
        static bool isAbsolute(const std::string & path);

        bool operator==(const Path& other) const;
        operator const char*() const;
        operator std::string() const;

        const char* c_str() const;
        const std::string& toString() const;
    };
}

std::ostream& operator<<(std::ostream& os, const PAX::Path & p);

#endif //PAXENGINE3_PATH_H
