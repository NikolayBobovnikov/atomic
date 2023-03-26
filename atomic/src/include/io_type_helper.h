#include <typeindex>
#include <string>
#include "io_types.h"

namespace Quant
{
    struct IOTypeHelper
    {
        static std::type_index parse_type_index(std::string s);
        static std::string to_string(data_t);
        static data_t from_string(std::type_index type, std::string &value);
    };
}