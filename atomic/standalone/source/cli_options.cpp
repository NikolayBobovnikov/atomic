#include <string>
#include <iostream>
#include <cxxopts.hpp>
#include "cli_options.h"

using namespace std;

namespace
{
  using std::string;
  using namespace std::filesystem;

  static const string arg_input = "input";
  static const string arg_output = "output";
  static const string arg_config = "config";
  static const string arg_input_default_value = "input.txt";
  static const string arg_output_default_value = "output.txt";
  static const string arg_config_default_value = "pipeline.yml";
  static const string file_not_exist_prefix = "File not exist: ";

  filesystem::path check(string file, char *argv[])
  {
    if (!filesystem::is_regular_file(file))
    {
      // first argv[] is path to executable, get path to parent directory containing it
      auto fullPath = filesystem::path(argv[0]).parent_path();
      fullPath /= file;

      if (filesystem::is_regular_file(fullPath))
      {
        return fullPath;
      }
      else
      {
        throw invalid_argument(file_not_exist_prefix + file);
      }
    }

    return file;
  }

  void print_options_dbg(int argc, char *argv[])
  {
    cout << "Options for parsing: " << endl;
    for (int i = 0; i < argc; ++i)
    {
      cout << argv[i] << endl;
    }
  }

  void log(const CLIOptions &options)
  {
    cout << "Input file: " << options.input << endl;
    cout << "Output file: " << options.output << endl;
    cout << "Using pipeline settings: " << options.config << endl;
  }
}

CLIOptions::CLIOptions(int argc, char *argv[])
{
  // TODO remove
  print_options_dbg(argc, argv);

  cxxopts::Options options("Pipeline", "Applies pipeline transformations of the input data.");
  options.allow_unrecognised_options();

  // define available options
  options.add_options()("c,config", "Path to YAML configuration file", cxxopts::value<string>()->default_value(arg_config_default_value));
  options.add_options()("i,input", "Path to input file", cxxopts::value<string>()->default_value(arg_input_default_value));
  options.add_options()("o,output", "Path to output file", cxxopts::value<string>()->default_value(arg_output_default_value));

  // validate required options are specified
  try
  {
    // parse options
    auto cli_options = options.parse(argc, argv);

    // if specified parameter is not a full path to an existing file, try to check in the current dir
    input = check(cli_options[arg_input].as<string>(), argv);
    config = check(cli_options[arg_config].as<string>(), argv);

    // output file is created and thus no need to check its existence
    output = cli_options[arg_output].as<string>();
  }
  catch (exception &e)
  {
    cout << "Error in command line arguments: " << e.what() << endl;
    throw;
  }

  log(*this);
}