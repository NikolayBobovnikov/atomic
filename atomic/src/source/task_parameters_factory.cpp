#include <algorithm>
#include <string>
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
        return IOTypeHelper::from_string(t_index, value);
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