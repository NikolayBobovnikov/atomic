#pragma once

#include "task.h"
#include <iostream>

namespace Quant
{
  namespace Tasks
  {
    struct Add final : TaskProcessor
    {
      data_t process(data_t input_data) const override
      {
        return std::visit(overload{
                              [](auto input, auto value) -> data_t
                              { return input + value; },
                          },
                          input_data, m_value);
      }

      void set_parameters(TaskParameters params) override
      {
        m_value = params.args[0];
      }

    private:
      data_t m_value;
    };
  }
}