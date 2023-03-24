#include <exception>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "task_factory.h"
#include "tasks/add.h"

using namespace std;

namespace Quant
{
  //template<class InputType, class OutputType>
  unique_ptr<Task> TaskFactory::Create(
    const type_info& input_type,
    const type_info& output_type,
    string task_name, 
    TaskParameters task_params)
  {
    // convert to lowercase in place
    transform(task_name.begin(), task_name.end(), task_name.begin(), [](unsigned char c) { return tolower(c); });
    
    // construct task
    auto task = make_unique<Task>(input_type, output_type, task_name);
    std::unique_ptr<IProcessor> processor;

    // construct specific data processor for the specified task name
    if (task_name == "add")
    {
      processor = make_unique<Tasks::Add<int, int>>();
    }
    else 
    {
      throw invalid_argument("Specified task is not supported: " + task_name);
    }

    // add parameters if applicable
    if (IParametrized* parametrized_task = dynamic_cast<IParametrized*>(processor.get()))
    {
      parametrized_task->set_parameters(task_params);
    }

    // set data processor to the task
    task->set_processor(make_unique<Tasks::Add<int, int>>());

    return task;
  }
}