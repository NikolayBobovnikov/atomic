#include "task.h"
#include <iostream>

namespace Quant
{
  namespace Tasks
  {
    struct Add final : IProcessor,
                       IParametrized,
                       IInOut
    {
      // TODO: move to builder function
      Add(std::unique_ptr<ICheckType> in, std::unique_ptr<ICheckType> out)
          : IInOut(std::move(in), std::move(out))
      {
      }

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