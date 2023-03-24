#include "task.h"
#include <iostream>

namespace Quant
{
  namespace Tasks
  {
    struct LightItem
    {
    };
    struct HeavyItem
    {
    };

    template <class InputType, class OutputType>
    struct Add final : IProcessor, IParametrized
    {
      data_t process(data_t data) const override
      {
        // verify input data type
        InputType in = std::get<InputType>(data);
        OutputType out = std::visit(overload{
                                        [](const std::string &s) -> OutputType
                                        { return OutputType(); },
                                        [in](auto param_value) -> OutputType
                                        { return param_value + in; },
                                    },
                                    m_parameter);

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