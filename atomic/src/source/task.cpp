#include <memory>
#include "task.h"
#include "task_processor.h"

namespace Quant
{
  using namespace std;

  Task::Task() = default;

  Task::Task(
      type_index input_type,
      type_index output_type,
      string name)
      : IOTypeInfo(input_type, output_type), m_name(move(name))
  {
  }

  Task::~Task() = default;

  data_t Task::process(data_t data) const
  {
    check_input(data);
    auto output = m_processor->process(data);
    check_output(output);
    return output;
  }

  void Task::set_processor(std::unique_ptr<TaskProcessor> processor)
  {
    m_processor = move(processor);
  }

  const std::string &Task::name() const
  {
    return m_name;
  }
}
