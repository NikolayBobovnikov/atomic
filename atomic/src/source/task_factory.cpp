#include <exception>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "task_factory.h"
#include "tasks/add.h"

using namespace std;

namespace
{
  using namespace Quant;

  unique_ptr<IDataTypeChecker> make_data_checker(const type_info &ti)
  {
    static const string type_not_supported_prfix = "Type is not supported: ";

    if (ti == typeid(int))
    {
      return make_unique<DataTypeChecker<int>>();
    }
    if (ti == typeid(size_t))
    {
      return make_unique<DataTypeChecker<size_t>>();
    }
    if (ti == typeid(float))
    {
      return make_unique<DataTypeChecker<float>>();
    }
    if (ti == typeid(double))
    {
      return make_unique<DataTypeChecker<double>>();
    }

    throw invalid_argument(type_not_supported_prfix + ti.name());
  }

  std::unique_ptr<IProcessor> make_task_processor(string task_name)
  {
    if (task_name == "add")
    {
      return make_unique<Tasks::Add>();
    }

    throw invalid_argument("Specified task is not supported: " + task_name);
  }
}

namespace Quant
{

  // template<class InputType, class OutputType>
  unique_ptr<Task> TaskFactory::Create(
      const type_info &input_type,
      const type_info &output_type,
      string task_name,
      TaskParameters task_params)
  {
    // convert to lowercase in place
    transform(task_name.begin(), task_name.end(), task_name.begin(), [](unsigned char c)
              { return tolower(c); });

    auto task = make_unique<Task>(input_type, output_type, task_name);
    auto processor = make_task_processor(task_name);
    processor->set_input_checker(make_data_checker(input_type));
    processor->set_output_checker(make_data_checker(output_type));

    // add parameters if applicable
    if (IParametrized *parametrized_task = dynamic_cast<IParametrized *>(processor.get()))
    {
      parametrized_task->set_parameters(task_params);
    }

    // set data processor to the task
    task->set_processor(move(processor));

    return task;
  }
}