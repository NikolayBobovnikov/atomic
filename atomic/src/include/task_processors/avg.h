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
                               [this](auto value) -> data_t
                               {
                                   // cycle write
                                   m_pos = m_pos < m_values.size() ? m_pos : 0;
                                   m_values[m_pos] = value;
                                   ++m_pos;
                                   return std::accumulate(m_values.begin(), m_values.end(), 0.0) / m_values.size();
                               },
                           },
                           input_data);

                // calculate sum of the buffer
                data_t sum_t = 0;
                for (const auto &v : m_values)
                {
                    sum_t = std::visit(overload{
                                           [](auto value, auto sum) -> data_t
                                           {
                                               return value + sum;
                                           },
                                       },
                                       v, sum_t);
                }

                // calculate average
                // std::visit(overload{
                //                [this](auto value) -> data_t
                //                {
                //                    // cycle write
                //                    m_pos = m_pos < m_values.size() ? m_pos : 0;
                //                    m_values[m_pos] = value;
                //                    ++m_pos;
                //                    return std::accumulate(m_values.begin(), m_values.end(), 0.0) / m_values.size();
                //                },
                //            },
                //            input_data);

                return sum_t;
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