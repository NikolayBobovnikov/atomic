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
    data_t parse_data_t(TaskArgument arg)
    {
        std::type_index t_index = IOTypeHelper::parse_type_index(arg.type);

        if (t_index == typeid(int))
        {
            return stoi(arg.value);
        }
        if (t_index == typeid(float))
        {
            return std::stof(arg.value);
        }
        if (t_index == typeid(double))
        {
            return std::stod(arg.value);
        }
        if (t_index == typeid(size_t))
        {
            std::stringstream sstream(arg.value);
            size_t result;
            sstream >> result;
            return result;
        }

        throw invalid_argument("Couldn't parse argument: " + arg.value);
    }
}

namespace Quant
{
    TaskParameters TaskParametersFactory::Create(TaskSettings s)
    {
        TaskParameters parameters;

        // fill args
        for (const auto &arg : s.args)
        {
            parameters.add(parse_data_t(arg));
        }

        // fill keyword args
        for (const auto &[key, value] : s.kwargs)
        {
            parameters.add_named(key, parse_data_t(value));
        }

        return parameters;
    }
}