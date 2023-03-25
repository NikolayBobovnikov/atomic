
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Quant
{
    namespace Settings
    {
        struct Arg
        {
            std::string type;
            std::string value;
        };
        struct KWArg
        {
            std::string name;
            std::string type;
            std::string value;
        };
        struct Task
        {
            std::string name;
            std::string input_type;
            std::string output_type;
            std::vector<Arg> args;
            std::vector<KWArg> kwargs;
        };

        struct Pipeline
        {
            std::string input_type;
            std::string output_type;
            std::vector<Task> tasks;
        };
    }

}
