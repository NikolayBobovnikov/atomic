
#include <memory>
#include <iostream>
#include <vector>
#include <functional>
#include <any>
#include <typeinfo>
#include <typeindex>
#include <exception>
#include <string>
#include <algorithm>
#include "pipeline.h"
#include "task.h"

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

  std::any Pipeline::process(std::any data) const
  {
    // pass data by reference to the task with checking errors
    auto checked_transformation = [&data](const Task &task)
    {
      try
      {
        data = task.process(data);
      }
      catch (exception &e)
      {
        // catch, log, rethrow to be processed in pipeline
        return std::any("Error in task: " + task.name_str() + ". " + e.what());
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
      return std::any(e.what());
    }

    return data;
  }

  void Pipeline::add(Task task)
  {
    auto input = input_type();

    // first task must have the same input type as pipeline
    if (tasks.size() == 0 && task.input_type() != input_type())
    {
      throw invalid_argument("Incompatible task input type. Expected ");
    }
    tasks.push_back(std::move(task));
  }
}
