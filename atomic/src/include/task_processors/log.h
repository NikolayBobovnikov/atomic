#pragma once

#include <cmath>
#include "task_processor.h"

namespace Quant
{
    namespace Tasks
    {
        struct Log final : TaskProcessor
        {
            data_t process(data_t input_data) const override
            {
                return std::visit(overload{
                                      [&](auto input, auto value) -> data_t
                                      {
                                          return std::log(input) / std::log(value);
                                      },
                                  },
                                  input_data, m_base);
            }

            void set_parameters(TaskParameters params) override
            {
                expect_n_arguments<1>(params);
                m_base = params.args[0];
            }

        private:
            data_t m_base;
        };
    }
}