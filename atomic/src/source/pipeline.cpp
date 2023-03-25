
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

namespace Quant
{
  Pipeline::Pipeline() = default;
  Pipeline::Pipeline(const std::type_info &input_type, const std::type_info &output_type)
      : IOTypeInfo(input_type, output_type)
  {
  }
  Pipeline::~Pipeline() = default;

  void Pipeline::validate() const
  {
    if (tasks.size() == 0)
    {
      return;
    }

    // output type of first task must be equal to output type of pipeline
    const auto &task = *(tasks.back());
    if (get_out_type() != task.get_out_type())
    {
      static const string out_error_prefix = "Incompatible output type for task ";
      throw invalid_argument(out_error_prefix + task.name() + "Got: " + task.get_out_type().name() + ", expected: " + get_out_type().name());
    }
  }

  data_t Pipeline::process(data_t data) const
  {
    // if pipeline contains no tasks, return unmodified
    if (tasks.size() == 0)
    {
      return data;
    }

    // validate
    validate();

    // run pipeline
    // save results in place
    for_each(cbegin(tasks), cend(tasks), [&data](const auto &task)
             { data = task->process(data); });

    return data;
  }

  data_out_t Pipeline::process_ext(data_t data) const noexcept
  {
    data_out_t result;

    // run pipeline
    try
    {
      // return result of the pipeline by default
      result = variant_cast(process(data));
    }
    catch (exception &e)
    {
      // return error message in case of errors
      result = e.what();
    }

    return result;
  }

  void Pipeline::add_task(unique_ptr<Task> task)
  {
    static const string in_error_prefix = "Incompatible input type for task ";

    const auto &prev_type = tasks.size() == 0 ? get_in_type() : tasks.back()->get_in_type();

    // input type of first task must be equal to input type of pipeline
    if (task->get_in_type() != prev_type)
    {
      throw invalid_argument(in_error_prefix + task->name() + "Got: " + task->get_in_type().name() + ", expected: " + get_in_type().name());
    }

    tasks.push_back(move(task));
  }

  void Pipeline::add_task(const std::type_info &input_type,
                          const type_info &output_type,
                          string name,
                          TaskParameters parameters)
  {
    return add_task(TaskFactory::Create(input_type, output_type, name, parameters));
  }
}
