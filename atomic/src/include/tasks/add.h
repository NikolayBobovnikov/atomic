#include "task.h"

namespace Quant
{
    namespace Tasks
    {
        struct Add final : ProcessorBase
        {
            // Add(const std::type_info &input_type,
            //     const std::type_info &output_type,
            //     const std::string &name)
            //     : Task(input_type, output_type, name)
            // {
            // }

            virtual std::any process(std::any data) const override
            {
                return data + parameter;
            }

        private:
            std::any parameter;
        }
    }
}