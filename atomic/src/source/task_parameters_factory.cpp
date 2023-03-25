#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>
#include "io_types.h"
#include "io_type_helper.h"
#include "task_parameters_factory.h"

using namespace std;

namespace
{
    using namespace Quant;
    data_t parse_data_t(string type, string value)
    {
        std::type_index t_index = IOTypeHelper::parse_type_index(type);

        if (t_index == typeid(int))
        {
            return stoi(value);
        }
        if (t_index == typeid(float))
        {
            return std::stof(value);
        }
        if (t_index == typeid(double))
        {
            return std::stod(value);
        }
        if (t_index == typeid(size_t))
        {
            std::stringstream sstream(value);
            size_t result;
            sstream >> result;
            return result;
        }

        throw invalid_argument("Couldn't parse argument: " + value);
    }
}

namespace Quant
{
    TaskParameters TaskParametersFactory::Create(Settings::Task s)
    {
        TaskParameters parameters;

        // fill args
        for (const auto &arg : s.args)
        {
            parameters.add(parse_data_t(arg.type, arg.value));
        }

        // fill keyword args
        for (const auto &kwarg : s.kwargs)
        {
            parameters.add_named(kwarg.name, parse_data_t(kwarg.type, kwarg.value));
        }

        return parameters;
    }
}