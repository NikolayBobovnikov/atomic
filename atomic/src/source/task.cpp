#include "task.h"

using namespace std;

namespace Quant
{
    Task::Task(
        const type_info &input_type,
        const type_info &output_type,
        function<any(any)> processor,
        const string &name)
        : ProcessorBase(input_type, output_type), m_processor(processor), m_name(name)
    {
    }

    any Task::process(any data) const
    {
        return m_processor(data);
    }

    const std::string &Task::name() const
    {
        return m_name;
    }
}
