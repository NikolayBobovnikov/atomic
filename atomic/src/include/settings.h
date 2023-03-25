
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Quant
{
    struct TaskArgument
    {
        std::string type;
        std::string value;
    };
    struct TaskSettings
    {
        std::string name;
        std::string input_type;
        std::string output_type;
        std::vector<TaskArgument> args;
        std::unordered_map<std::string, TaskArgument> kwargs;
    };

    struct PipelineSettings
    {
        std::string input_type;
        std::string output_type;
        std::vector<TaskSettings> tasks;
    };
}
