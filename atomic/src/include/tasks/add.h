#include "task.h"
#include <iostream>

namespace Quant
{
  namespace Tasks
  {
    struct Add final : TaskProcessorBase
    {
      data_t process(data_t data) const override
      {
        // TODO: move to outer class
        // verify input data type
        check_input(data);

        // TODO: leave in this (strategy) class, define interface
        data_t out = std::visit(overload{
                                    [](auto input, auto param_value) -> data_t
                                    { return input + param_value; },
                                },
                                data, m_parameter);

        // TODO: move to base class
        check_output(out);
        return out;
      }

      void set_parameters(TaskParameters params) override
      {
        m_parameter = params.args[0];
      }

    private:
      data_t m_parameter;
    };
  }
}