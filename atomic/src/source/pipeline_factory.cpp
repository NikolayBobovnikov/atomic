#include <string>
#include <algorithm>
#include <stdexcept>
#include "pipeline_factory.h"
#include "pipeline.h"

using namespace std;

namespace
{
    using namespace Quant;

    std::type_index from_string(string s)
    {
        // convert to lowercase in place
        transform(s.begin(), s.end(), s.begin(), [](unsigned char c)
                  { return tolower(c); });

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

}

namespace Quant
{
    using namespace std;
    PipelineFactory::~PipelineFactory() = default;

    unique_ptr<Pipeline> PipelineFactory::Create(PipelineSettings settings)
    {
        auto pipeline = make_unique<Pipeline>();
        pipeline->set_in_type(from_string(settings.input_type));
        pipeline->set_out_type(from_string(settings.output_type));

        return pipeline;
    }
}
