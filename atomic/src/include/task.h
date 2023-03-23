#pragma once

#include <string>
#include "processor.h"

namespace Quant
{
    struct Task : IProcessor
    {
    public:
        ~Task() = default;
        virtual const std::string &name() const = 0;

    protected:
        Task(const std::type_info &input_type, const std::type_info &output_type);
    };
}
