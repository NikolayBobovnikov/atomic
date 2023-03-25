#pragma once

#include <memory>
#include <vector>
#include "parameters.h"
#include "settings.h"
#include "task.h"

namespace Quant
{
    // TODO: replace #include "task.h" with  forward decl
    // struct Task;
    struct TaskFactory
    {
        static std::unique_ptr<Task> Create(
            std::type_index input_type,
            std::type_index output_type,
            std::string name,
            TaskParameters params);

        static std::unique_ptr<Task> Create(TaskSettings settings);

        ~TaskFactory(); // define where pipml type is complete
    };
}