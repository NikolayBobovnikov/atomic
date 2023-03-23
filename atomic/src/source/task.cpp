#include "task.h"

using namespace std;

namespace Quant
{
    Task::Task(const std::type_info &input_type, const std::type_info &output_type)
        : IProcessor(input_type, output_type)
    {
    }
}
