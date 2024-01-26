#include "obj2pov.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace obj2pov {
    ObjFile::ObjFile(const std::string &InputPath)
    {
        std::ifstream fin(InputPath);

        if (!fin)
        {
            std::cout << "Couldn't open .obj file!" << std::endl;
            return;
        }

        std::stringstream ssm;
        ssm << fin.rdbuf();
        _Src = ssm.str();

        fin.close();
    }

    bool ObjFile::Convert(const std::string &OutputPath)
    {
        struct Vertex
        {
            float _Data[3];
        };

        std::vector<Vertex> vertices;

        std::ofstream fout(OutputPath, std::ios::trunc);

        std::string output, line;
        std::stringstream ssm(_Src);

        output.append("mesh {\n");

        while (std::getline(ssm, line))
        {
            if (ssm.eof())
                break;

            // NOTE: We only care about 'v x y z' & 'f v1 v2 v3'.
            if (line[0] == 'v' && line[1] == ' ')
            {
                std::stringstream vertSsm(line.substr(2));
                vertices.emplace_back();
                for (int i = 0; i < 3; i++)
                {
                    vertSsm >> vertices.back()._Data[i];
                }
            }
            else if (line[0] == 'f')
            {
                std::stringstream faceSsm(line.substr(2));
                std::stringstream coordSsm;
                coordSsm.precision(4);
                std::string tmp;
                std::string tmpCoord;
                int tmpVert;

                output.append("\ttriangle { ");

                for (int i = 0; i < 3; i++)
                {
                    faceSsm >> tmp;
                    auto slashPos = tmp.find('/');
                    if (slashPos == std::string::npos)
                        slashPos = tmp.size();
                    tmpVert = std::stoi(tmp.substr(0, slashPos)) - 1;
                    output.append("<");
                    for (int j = 0; j < 3; j++)
                    {
                        coordSsm << vertices[tmpVert]._Data[j];
                        coordSsm >> tmpCoord;

                        coordSsm.clear();

                        output.append(tmpCoord);
                        if (j < 2)
                            output.append(", ");
                    }
                    output.append(">");
                    if (i < 2)
                        output.append(", ");
                }
                output.append(" }\n");
            }
        }

        output.append("}\n");

        fout << output << std::flush;
        fout.close();
        return true;
    }
} // namespace obj2pov
