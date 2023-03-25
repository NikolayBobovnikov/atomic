#include "settings.h"

namespace Quant
{
    TaskSettings::TaskSettings(std::string &&_name,
                               std::string &&_input_type,
                               std::string &&_output_type)
        : name(_name), input_type(_input_type), output_type(_output_type)
    {
    }

}