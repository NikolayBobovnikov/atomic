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
#include <iostream>
#include <cxxopts.hpp>
#include <yaml-cpp/yaml.h>


int main(int argc, char *argv[])
{
    using namespace std;

    cxxopts::Options options("Pipeline", "Applies pipeline transformations of the input data.");

    // define available options
    options.add_options()
        //("d,debug", "Enable debugging") // a bool parameter
        //("i,integer", "Int param", cxxopts::value<int>())
        ("c,config", "Pipeline settings JSON configuration file", cxxopts::value<string>())
        ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
        ;

    // parse options
    auto result = options.parse(argc, argv);

    try{
        // get json pipeline config
        auto pipelint = result["config"].as<string>();
        cout << "Using settings " << pipelint << endl;
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    
    return 0;
}