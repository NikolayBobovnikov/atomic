#include <stdexcept>
#include <io_type_helper.h>
#include "pipeline_factory.h"
#include "pipeline.h"

using namespace std;

namespace
{
    using namespace Quant;

}

namespace Quant
{
    using namespace std;
    PipelineFactory::~PipelineFactory() = default;

    unique_ptr<Pipeline> PipelineFactory::Create(PipelineSettings settings)
    {
        auto pipeline = make_unique<Pipeline>();
        pipeline->set_in_type(IOTypeHelper::parse_type_index(settings.input_type));
        pipeline->set_out_type(IOTypeHelper::parse_type_index(settings.output_type));

        return pipeline;
    }
}
