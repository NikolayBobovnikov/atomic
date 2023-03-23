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
        name: square root
        output type: double
    - task:
        name : addition
        parameter: 10.5
    - task:
        name: complex task
        parameters:
            - parameter:
                name: strategy
                value: interpolation
            - parameter:
                name: precision
                value: 0.01
*/

namespace {
  static const string input_type = "input type";
  static const string output_type = "output type";
  static const string tasks = "tasks";
  static const string task = "task";
  static const string name = "name";
  static const string parameters = "parameters";
  static const string parameter = "parameter";
}

PipelineConfiguration PipelineConfigLoader::Load(const std::filesystem::path& path_to_config)
{
  PipelineConfiguration configuration;

  try {
    if (!filesystem::is_regular_file(path_to_config)) {
      throw invalid_argument("Configuration file does not exist");
    }

    YAML::Node config = YAML::LoadFile(path_to_config.string());

    if (config[input_type]) {
      std::cout << "Last logged in: " << config[input_type].as<string>() << endl;
    }
  }
  catch (exception& e) {
    cout << "Error in pipeline configuration settings: " << e.what() << endl;
    throw;
  }

  return configuration;
}
