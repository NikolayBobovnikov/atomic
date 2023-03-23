#include <filesystem>
#include "pipeline_config.h"

struct PipelineConfigLoader {
  PipelineConfiguration Load(const std::filesystem::path&);
};