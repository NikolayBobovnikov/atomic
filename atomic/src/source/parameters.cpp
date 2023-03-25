#include "parameters.h"

namespace Quant
{
    void TaskParameters::add(data_t arg)
    {
        args.push_back(arg);
    }
    void TaskParameters::add_named(std::string name, data_t arg)
    {
        kwargs[name] = arg;
    }
}