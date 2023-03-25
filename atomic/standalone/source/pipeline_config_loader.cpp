#include <exception>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "pipeline_config_loader.h"

using namespace std;

/*
- input type: float
- output type: int

- pipeline:
    - task:
        name: multiply
        output type: double
    - task:
        name : add
        args: [10.5]
    - task:
        name: complex task
        args: [10.4, 5]
        kwargs:
            - kwarg:
                name: strategy
                value: interpolation
            - kwarg:
                name: precision
                value: 0.01
*/

namespace
{
  // YAML settings keywords
  static const string input_type = "input type";
  static const string output_type = "output type";
  static const string pipeline = "pipeline";
  static const string task = "task";
  static const string args = "args";
  static const string kwargs = "kwargs";
  static const string name = "name";
  static const string value = "value";

  namespace
  {
    PipelineSettings load(const std::filesystem::path &path_to_config)
    {
      PipelineSettings settings;

      YAML::Node yaml = YAML::LoadFile(path_to_config.string());

      settings.input_type = yaml[input_type].as<string>();
      settings.output_type = yaml[output_type].as<string>();

      for (const auto &task : yaml[pipeline])
      {
        // add task
        settings.tasks.emplace_back(task[name].as<string>(), task[input_type].as<string>(), task[output_type].as<string>());
        auto &added_task = settings.tasks.back();

        // fill unnamed arguments
        for (const auto &targ : task[args])
        {
          added_task.args.push_back(targ.as<string>());
        }

        // fill named arguments
        for (const auto &tkwarg : task[args])
        {
          added_task.kwargs[tkwarg[name].as<string>()] = tkwarg[value].as<string>();
        }
      }

      return settings;
    }
  }
}

PipelineSettings PipelineSettingsLoader::Load(const std::filesystem::path &path_to_config)
{
  PipelineSettings settings;

  try
  {
    settings = load(path_to_config);
  }
  catch (exception &e)
  {
    cout << "Error in pipeline configuration settings: " << e.what() << endl;
    throw;
  }

  return settings;
}
