#include <memory>
#include "task.h"

using namespace std;

namespace Quant
{
  Task::Task(
      const type_info &input_type,
      const type_info &output_type,
      string name)
      : DataTypeInfo(input_type, output_type), m_name(move(name))
  {
  }

  data_t Task::process(data_t data) const
  {
    return m_processor->process(data);
  }

  void Task::set_processor(std::unique_ptr<IProcessor> processor)
  {
    m_processor = move(processor);
  }

  const std::string &Task::name() const
  {
    return m_name;
  }
}
