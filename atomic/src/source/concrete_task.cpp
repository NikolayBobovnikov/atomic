
#include <functional>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <string>
#include "concrete_task.h"

using namespace std;
namespace Quant
{
    ConcreteTask::ConcreteTask(
        const type_info &input_type,
        const type_info &output_type,
        function<any(any)> processor,
        const string &name)
        : Task(input_type, output_type), m_processor(processor), m_name(name)
    {
    }

    any ConcreteTask::process(any data) const
    {
        return m_processor(data);
    }
}