#include "obj2pov.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "[obj2pov] Usage: obj2pov <input_file_path> <output_file_path>" << std::endl;
        return 0;
    }
    obj2pov::ObjFile objFile(argv[1]);
    std::cout << "[obj2pov] Converting.." << std::endl;
    if (!objFile.Convert(argv[2]))
    {
        std::cout << "[obj2pov] File corrupted. Conversion terminated." << std::endl;
        return 0;
    }
    std::cout << "[obj2pov] Conversion successful." << std::endl;

    return 0;
}
