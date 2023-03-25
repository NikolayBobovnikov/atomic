#include <stdexcept>
#include <io_type_helper.h>
#include "pipeline_factory.h"
#include "pipeline.h"
#include "task_factory.h"

using namespace std;

namespace Quant
{
    using namespace std;

    PipelineFactory::~PipelineFactory() = default;

    unique_ptr<Pipeline> PipelineFactory::Create(Settings::Pipeline settings)
    {
        auto pipeline = make_unique<Pipeline>();
        pipeline->set_in_type(IOTypeHelper::parse_type_index(settings.input_type));
        pipeline->set_out_type(IOTypeHelper::parse_type_index(settings.output_type));

        for (const auto &task_settings : settings.tasks)
        {
            auto task = TaskFactory::Create(task_settings);
            pipeline->add_task(move(task));
        }

        return pipeline;
    }
}
