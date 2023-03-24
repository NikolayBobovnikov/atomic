#include "task.h"

using namespace std;

namespace Quant
{
    Task::Task(
        const type_info &input_type,
        const type_info &output_type,
        const string &name)
        : ProcessorBase(input_type, output_type), m_name(name)
    {
    }

    const std::string &Task::name_str() const
    {
        return m_name;
    }
    std::any Task::process(std::any data) const
    {
        return m_processor(data);
    }
}
