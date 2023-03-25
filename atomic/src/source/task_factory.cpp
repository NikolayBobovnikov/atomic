#include <exception>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "io_type_helper.h"
#include "task_factory.h"
#include "task_parameters_factory.h"
#include "task_processors/add.h"
#include "task_processors/multiply.h"

using namespace std;

namespace
{
  using namespace Quant;

  unique_ptr<IDataTypeChecker> make_data_checker(type_index ti)
  {
    static const string type_not_supported_prfix = "Type is not supported: ";

    if (ti == type_index(typeid(int)))
    {
      return make_unique<DataTypeChecker<int>>();
    }
    if (ti == type_index(typeid(size_t)))
    {
      return make_unique<DataTypeChecker<size_t>>();
    }
    if (ti == type_index(typeid(float)))
    {
      return make_unique<DataTypeChecker<float>>();
    }
    if (ti == type_index(typeid(double)))
    {
      return make_unique<DataTypeChecker<double>>();
    }

    throw invalid_argument(type_not_supported_prfix + ti.name());
  }

  unique_ptr<TaskProcessor> make_task_processor(string task_name)
  {
    if (task_name == "add")
    {
      return make_unique<Tasks::Add>();
    }
    if (task_name == "multiply")
    {
      return make_unique<Tasks::Multiply>();
    }

    throw invalid_argument("Specified task is not supported: " + task_name);
  }
}

namespace Quant
{
  // template<class InputType, class OutputType>
  unique_ptr<Task> TaskFactory::Create(
      type_index input_type,
      type_index output_type,
      string task_name,
      TaskParameters task_params)
  {
    // convert to lowercase in place
    transform(task_name.begin(), task_name.end(), task_name.begin(), [](unsigned char c)
              { return tolower(c); });

    auto task_processor = make_task_processor(task_name);
    task_processor->set_parameters(task_params);

    auto task = make_unique<Task>(input_type, output_type, task_name);
    task->set_input_checker(make_data_checker(input_type));
    task->set_output_checker(make_data_checker(output_type));
    task->set_processor(move(task_processor));

    return task;
  }

  std::unique_ptr<Task> TaskFactory::Create(TaskSettings settings)
  {
    auto taks_parameters = TaskParametersFactory::Create(settings);

    return Create(IOTypeHelper::parse_type_index(settings.input_type),
                  IOTypeHelper::parse_type_index(settings.output_type),
                  settings.name,
                  taks_parameters);
  }
}