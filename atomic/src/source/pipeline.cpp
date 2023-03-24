
#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <variant>
#include <typeinfo>
#include <typeindex>
#include <exception>
#include <string>
#include <algorithm>
#include "pipeline.h"
#include "task.h"
#include "task_factory.h"

using namespace std;
namespace
{

}
namespace Quant
{

  Pipeline::Pipeline(const std::type_info &input_type, const std::type_info &output_type)
      : ProcessorBase(input_type, output_type)
  {
  }

  data_t Pipeline::process(data_t data) const
  {
    // pass data by reference to the task with checking errors
    auto checked_transformation = [&data](const std::unique_ptr<Task>& task)
    {
      try
      {
        data = task->process(data);
      }
      catch (exception &e)
      {
        // catch, log, rethrow to be processed in pipeline
        return data_t("Error in task: " + task->name() + ". " + e.what());
      }

      return data;
    };

    // run pipeline
    try
    {
      for_each(cbegin(tasks), cend(tasks), checked_transformation);
    }
    catch (exception &e)
    {
      // return error message in case of errors
      return data_t(e.what());
    }

    return data;
  }

  void Pipeline::add(unique_ptr<Task> task)
  {
    auto input = input_type();

    // first task must have the same input type as pipeline
    if (tasks.size() == 0 && task->input_type() != input_type())
    {
      throw invalid_argument("Incompatible task input type. Expected ");
    }
    tasks.push_back(move(task));
  }

  void Pipeline::add(const std::type_info& input_type,
    const type_info& output_type,
    string task_name,
    TaskParameters task_params)
  {
    // first task must have the same input type as pipeline
    if (tasks.size() == 0 && this->input_type() != std::type_index(input_type))
    {
      throw invalid_argument("Incompatible task input type. Expected ");
    }

    auto task = TaskFactory::Create(input_type, output_type, task_name, task_params);
    tasks.push_back(move(task));
  }
}
