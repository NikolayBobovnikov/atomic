#include <string>
#include <iostream>
#include <cxxopts.hpp>
#include "cli_options.h"

using namespace std;

namespace {
  using std::string;
  static const string arg_input = "input";
  static const string arg_output = "output";
  static const string arg_config = "config";
  static const string arg_config_default_value = "pipeline.yml";
  static const string file_not_exist_prefix = "File not exist: ";
}

CLIOptions::CLIOptions(int argc, char* argv[])
{
  cxxopts::Options options("Pipeline", "Applies pipeline transformations of the input data.");

  // define available options
  options.add_options()
    ("i," + arg_input, "Path to file with input data for processing", cxxopts::value<string>()),
    ("o," + arg_output, "Path to output file with processed results", cxxopts::value<string>()),
    ("c," + arg_config, "Pipeline YAML configuration file", cxxopts::value<string>()->default_value(arg_config_default_value))
    ;

  // parse options
  auto cli_options = options.parse(argc, argv);

  // validate required options are specified
  try
  {
    input = cli_options[arg_input].as<string>();
    if (!filesystem::is_regular_file(input)) {
      throw invalid_argument(file_not_exist_prefix + input.string());
    }

    output = cli_options[arg_output].as<string>();
    if (!filesystem::is_regular_file(output)) {
      throw invalid_argument(file_not_exist_prefix + output.string());
    }

    config = cli_options[arg_config].as<string>();
    if (!filesystem::is_regular_file(output)) {
      throw invalid_argument(file_not_exist_prefix + config.string());
    }
  }
  catch (exception& e) {
    cout << "Error in command line arguments: " << e.what() << endl;
    
    // TODO
    //throw;
  }
}