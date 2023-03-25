
#pragma once

#include "processor.h"
#include "parameters.h"

namespace Quant
{
    struct TaskProcessor : IProcessor
    {
        virtual ~TaskProcessor() = default;
        virtual void set_parameters(TaskParameters params){/* no parameters by default*/};
    };
}