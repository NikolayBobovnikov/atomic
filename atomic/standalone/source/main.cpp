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
#include "settings_loader.h"
#include "pipeline.h"
#include "pipeline_factory.h"

using namespace std;
using namespace Quant;

void test()
{
  // test
  Pipeline p(typeid(int), typeid(int));
  // test: multiply by 2 and add 0.5
  TaskParameters mul_param;
  TaskParameters add_param;
  mul_param.add(2);
  add_param.add(0.5);
  p.add_task(typeid(int), typeid(int), "multiply", mul_param);
  p.add_task(typeid(int), typeid(float), "add", add_param);

  auto res = p.process(1);
  cout << "result" << std::get<int>(res) << endl;
}

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
    PipelineSettingsLoader settings_loader;
    auto settings = settings_loader.Load(options.config);

    // 3. construct pipeline from the configuration object
    auto pipeline = PipelineFactory::Create(settings);

    // 4. process input data
  }
  catch (exception &e)
  {
    cout << e.what() << endl;

    // TODO:
    // cout << "Press any key to exit" << endl;
    // cin.get();

    // In case of exceptions return status code for failure
    return -1;
  }

  // OK
  return 0;
}
