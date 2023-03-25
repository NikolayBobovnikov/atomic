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
  static const string type = "type";
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
        TaskSettings task_settings;
        task_settings.name = task[name].as<string>();
        task_settings.input_type = task[input_type].as<string>();
        task_settings.output_type = task[output_type].as<string>();

        // fill unnamed arguments
        for (const auto &targ : task[args])
        {
          task_settings.args.push_back({targ[type].as<string>(), targ[value].as<string>()});
        }

        // fill named arguments
        for (const auto &tkwarg : task[args])
        {
          task_settings.kwargs[tkwarg[name].as<string>()] = {tkwarg[type].as<string>(), tkwarg[value].as<string>()};
        }

        settings.tasks.push_back(task_settings);
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
