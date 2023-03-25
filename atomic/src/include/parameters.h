#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "io_types.h"

namespace Quant
{
    struct TaskParameters
    {
        void add(data_t arg);
        void add_named(std::string name, data_t arg);

        std::vector<data_t> args;
        std::unordered_map<std::string, data_t> kwargs;
    };
}