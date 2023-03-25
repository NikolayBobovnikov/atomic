
#pragma once

#include <string>
#include <stdexcept>
#include "processor.h"
#include "parameters.h"

namespace Quant
{
    struct TaskProcessor : IProcessor
    {
        virtual ~TaskProcessor() = default;
        virtual void set_parameters(TaskParameters params){/* no parameters by default*/};

        template <int N>
        static void expect_n_arguments(TaskParameters params)
        {
            static const std::string n = std::to_string(N);

            if (params.args.size() != N)
            {
                throw std::invalid_argument("Incorrect number of parameters, expected: " + n);
            }
        }
    };
}