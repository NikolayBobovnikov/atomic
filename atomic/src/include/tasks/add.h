#include "task.h"
#include <iostream>

namespace Quant
{
    namespace Tasks
    {
      template<class InputType, class OutputType>
      struct Add final : IProcessor, IParametrized
      {
        data_t process(data_t data) const override
        {
          // verify input data
          auto input = std::get<InputType>(data);
          OutputType out = 123;

          //// apply parameter
          //std::visit(overloaded{
          // [](int arg) {  out = arg + input; },
          // [](float arg) { out = arg + input; },
          // [](double arg) { out = arg + input; }
          //  }, m_parameter);

          //std::visit(
          //[](auto&& arg) {
          //  using T = std::decay_t<decltype(arg)>;
          //  if constexpr (std::is_same_v<T, int>)
          //  {
          //    out = input + std::get<int>(m_parameter);
          //  }
          //  else if constexpr (std::is_same_v<T, float>)
          //  {
          //    out = input + std::get<float>(m_parameter);
          //  }
          //  else if constexpr (std::is_same_v<T, double>)
          //  {
          //    out = input + std::get<double>(m_parameter);
          //  }
          //  else
          //  {
          //    throw std::invalid_argument("Input/output data type mismatch")
          //  }
          //},
          //m_parameter);

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