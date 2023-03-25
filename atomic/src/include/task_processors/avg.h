#pragma once

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <numeric>
#include "task_processor.h"

namespace Quant
{
    namespace Tasks
    {
        struct Avg final : TaskProcessor
        {
            data_t process(data_t input_data) const override
            {
                // write current data to the buffer
                std::visit(overload{
                               [&](auto value)
                               {
                                   // cycle write
                                   m_pos = m_pos < m_values.size() ? m_pos : 0;
                                   m_values[m_pos] = value;
                                   ++m_pos;
                               },
                           },
                           input_data);

                // calculate sum of the buffer
                data_t sum{0};
                for (const auto &v : m_values)
                {
                    std::visit(overload{
                                   [&sum](auto value, auto curr_sum)
                                   {
                                       sum = value + curr_sum;
                                   },
                               },
                               v, sum);
                }

                // calculate average
                return std::visit(overload{
                                      [this](auto sum_value) -> data_t
                                      {
                                          return sum_value / m_values.size();
                                      },
                                  },
                                  sum);
            }

            void set_parameters(TaskParameters params) override
            {
                expect_n_arguments<1>(params);

                size_t count;
                try
                {
                    count = std::get<int>(params.args[0]);
                }
                catch (...)
                {
                    try
                    {
                        count = std::get<size_t>(params.args[0]);
                    }
                    catch (...)
                    {
                        throw std::invalid_argument("Expected numeric value for the number of elements for averaging.");
                    }
                }

                m_values.resize(count, 0);
                m_pos = 0;
            }

        private:
            mutable size_t m_pos;                 // position of current value
            mutable std::vector<data_t> m_values; // place to store values
        };
    }
}