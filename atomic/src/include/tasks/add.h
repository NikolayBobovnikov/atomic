#include <any>
#include "task.h"

namespace Quant
{
    namespace Tasks
    {
        struct Add final : ProcessorBase
        {
            Add(const std::type_info &input_type,
                const std::type_info &output_type,
                std::string name,
                std::any parameter)
                : Task(input_type, output_type, name), m_parameter(parameter)
            {
            }

            virtual std::any process(std::any data) const override
            {
                return data + parameter;
            }

        private:
            std::any m_parameter;
        }
    }
}