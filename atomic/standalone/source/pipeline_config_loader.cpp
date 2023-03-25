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
    using namespace Quant::Settings;

    void match_type(const YAML::Node &node)
    {
      switch (node.Type())
      {
      case YAML::NodeType::Null:
      {
        break;
      }
      case YAML::NodeType::Scalar:
      {
        break;
      }
      case YAML::NodeType::Sequence:
      {
        for (auto s : task)
        {
          auto a = s;
        }
        break;
      }
      case YAML::NodeType::Map:
      {
        for (auto n : node)
        {
          auto first = n.first;
          auto second = n.second;
          auto key = first.as<string>();
          // auto s2 = second.as<string>();
        }
        break;
      }
      }
    }

    Pipeline load(const std::filesystem::path &path_to_config)
    {
      Pipeline settings;

      YAML::Node yaml = YAML::LoadFile(path_to_config.string());

      // auto node = yaml[input_type];
      // auto type = node.Type();
      // cout << node.Type() << endl;

      settings.input_type = yaml[input_type].as<std::string>();
      settings.output_type = yaml[output_type].as<std::string>();

      for (const auto &task : yaml[pipeline])
      {
        Task task_settings;
        match_type(task);

        task_settings.name = task[name].as<string>();
        task_settings.input_type = task[input_type].as<string>();
        task_settings.output_type = task[output_type].as<string>();

        // fill unnamed arguments
        for (const auto &targ : task[args])
        {
          task_settings.args.push_back({targ[type].as<string>(), targ[value].as<string>()});
        }

        // fill named arguments
        for (const auto &tkwarg : task[kwargs])
        {
          // task_settings.kwargs[tkwarg[name].as<string>()] = {tkwarg[type].as<string>(), tkwarg[value].as<string>()};
        }

        settings.tasks.push_back(task_settings);
      }

      return settings;
    }
  }
}

Pipeline PipelineSettingsLoader::Load(const std::filesystem::path &path_to_config)
{
  Pipeline settings;

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
