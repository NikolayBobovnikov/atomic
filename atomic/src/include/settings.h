
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Quant
{
    struct TaskSettings
    {
        std::string name;
        std::string input_type;
        std::string output_type;
        std::vector<std::string> args;
        std::unordered_map<std::string, std::string> kwargs;
    };

    struct PipelineSettings
    {
        std::string input_type;
        std::string output_type;
        std::vector<TaskSettings> tasks;
    };
}
