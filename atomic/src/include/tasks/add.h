#include "task.h"
#include <iostream>

namespace Quant
{
    namespace Tasks
    {
      struct LightItem {};
      struct HeavyItem {};


      template<class InputType, class OutputType>
      struct Add final : IProcessor, IParametrized
      {
        data_t process(data_t data) const override
        {
          InputType in = std::get<InputType>(data);
          OutputType out;

          //std::visit(overload{
          //  //[](LightItem&, LightItem&) { },
          //  //[](LightItem&, HeavyItem&) { },
          //  //[](HeavyItem&, LightItem&) { },
          //  [](auto a, auto b) { return a + b; },
          //}, data, m_parameter);

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