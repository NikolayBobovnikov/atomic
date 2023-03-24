#include <memory>
#include <vector>
#include "task.h"

namespace Quant
{
    struct TaskFactory
    {
        //template<class InputType, class OutputType>
        static std::unique_ptr<Task> Create(
          const std::type_info& input_type,
          const std::type_info& output_type,
          std::string name, 
          TaskParameters params);

    };
}