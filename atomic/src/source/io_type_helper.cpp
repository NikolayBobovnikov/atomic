#include <algorithm>
#include <sstream>
#include <stdexcept>
#include "io_type_helper.h"

namespace Quant
{
    using namespace std;

    type_index IOTypeHelper::parse_type_index(string s)
    {
        // convert to lowercase in place
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                  { return tolower(c); });

        if (s.empty() || s == "void")
        {
            // if not defined
            return typeid(void);
        }
        if (s == "int")
        {
            return typeid(int);
        }
        if (s == "size_t")
        {
            return typeid(size_t);
        }
        if (s == "float")
        {
            return typeid(float);
        }
        if (s == "double")
        {
            return typeid(double);
        }

        throw invalid_argument("Type is not supported: " + s);
    }

    string IOTypeHelper::to_string(data_t data)
    {
        return visit(overload{
                         [](auto value) -> string
                         { return std::to_string(value); },
                     },
                     data);
    }

    data_t IOTypeHelper::from_string(std::type_index type, std::string &value)
    {
        if (type == typeid(int))
        {
            return stoi(value);
        }
        if (type == typeid(float))
        {
            return std::stof(value);
        }
        if (type == typeid(double))
        {
            return std::stod(value);
        }
        if (type == typeid(size_t))
        {
            std::stringstream sstream(value);
            size_t result;
            sstream >> result;
            return result;
        }

        throw invalid_argument("Couldn't parse input: " + value + ", type: " + type.name());
    }
}
