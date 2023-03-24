#include "task.h"

using namespace std;

namespace Quant
{
    Task::Task(
        const type_info &input_type,
        const type_info &output_type,
        string name)
        : ProcessorBase(input_type, output_type), m_name(move(name))
    {
    }

    const std::string &Task::name() const
    {
        return m_name;
    }
}
