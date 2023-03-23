/*
inputs:
- json file with pipeline settings
    - one for all runs.
    - default search folder: current directory
    - optional: may specify location
- required: input file
- optional: output file.
    - if not specified, use default name with timestamp
*/

#include <string>
#include <string_view>
#include <iostream>
#include <filesystem>
#include "cli_options.h"
#include "pipeline_config_loader.h"

using namespace std;

int main(int argc, char *argv[])
{
  try
  {
    // 1. parse CLI options
    CLIOptions options(argc, argv);
    cout << "Input file: " << options.input << endl;
    cout << "Output file: " << options.output << endl;
    cout << "Using pipeline settings: " << options.config << endl;

    // 2. parse pipeline configuration settings
    PipelineConfigLoader config_loader;
    auto configuration = config_loader.Load(options.config);

    // 3. construct pipeline from the configuration object

    // 4. process input data
  }
  catch (exception&) {
    cout << "Press any key to exit" << endl;
    cin.get();

    // In case of exceptions return status code for failure
    return -1;
  }

  // OK
  return 0;
}

