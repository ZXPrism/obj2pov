#pragma once

#include <string>

namespace obj2pov {
    class ObjFile
    {
    public:
        ObjFile(const std::string &InputPath);
        bool Convert(const std::string &OutputPath);

    private:
        std::string _Src;
    };
} // namespace obj2pov
