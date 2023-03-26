#include <iostream>
#include <exception>
#include <algorithm>
#include <unordered_map>
#include <string>
#include "io_type_helper.h"
#include "task_factory.h"
#include "task_parameters_factory.h"
#include "task_processors/add.h"
#include "task_processors/mul.h"
#include "task_processors/log.h"
#include "task_processors/pow.h"
#include "task_processors/avg.h"

using namespace std;

namespace
{
  using namespace Quant;

  void log(Settings::Task task)
  {
    cout << "Creating task " << task.name << endl
         << "input: " << task.input_type << endl
         << "output: " << task.output_type << endl
         << "arguments: [ ";

    for (const auto &s : task.args)
    {
      cout << s.value;
      cout << " ";
    }

    cout << "]" << endl;
  }

  unique_ptr<TaskProcessor> make_task_processor(string task_name)
  {
    if (task_name == "add")
    {
      return make_unique<Tasks::Add>();
    }
    if (task_name == "multiply" || task_name == "mul")
    {
      return make_unique<Tasks::Multiply>();
    }
    if (task_name == "pow")
    {
      return make_unique<Tasks::Power>();
    }
    if (task_name == "log")
    {
      return make_unique<Tasks::Log>();
    }
    if (task_name == "avg")
    {
      return make_unique<Tasks::Avg>();
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
    task->set_input_checker(input_type);
    task->set_output_checker(output_type);
    task->set_processor(move(task_processor));

    return task;
  }

  std::unique_ptr<Task> TaskFactory::Create(Settings::Task settings)
  {
    log(settings);
    return Create(IOTypeHelper::parse_type_index(settings.input_type),
                  IOTypeHelper::parse_type_index(settings.output_type),
                  settings.name,
                  TaskParametersFactory::Create(settings));
  }

  TaskFactory::~TaskFactory() = default;
}