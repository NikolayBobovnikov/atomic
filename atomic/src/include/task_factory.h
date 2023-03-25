#pragma once

#include <memory>
#include <vector>
#include "parameters.h"
#include "settings.h"

namespace Quant
{
    struct Task;
    struct TaskFactory
    {
        // template<class InputType, class OutputType>
        static std::unique_ptr<Task> Create(
            std::type_index input_type,
            std::type_index output_type,
            std::string name,
            TaskParameters params);

        static std::unique_ptr<Task> Create(TaskSettings settings);
    };
}