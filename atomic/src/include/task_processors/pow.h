#pragma once

#include <cmath>
#include "task_processor.h"

namespace Quant
{
    namespace Tasks
    {
        struct Power final : TaskProcessor
        {
            data_t process(data_t input_data) const override
            {
                return std::visit(overload{
                                      [&](auto input, auto value) -> data_t
                                      {
                                          // TODO: watch overthrow!
                                          return std::pow(input, value);
                                      },
                                  },
                                  input_data, m_exp);
            }

            void set_parameters(TaskParameters params) override
            {
                expect_n_arguments<1>(params);
                m_exp = params.args[0];
            }

        private:
            data_t m_exp;
        };
    }
}