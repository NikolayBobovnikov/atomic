#include <filesystem>
#include "settings.h"

using namespace Quant;

struct PipelineSettingsLoader
{
  PipelineSettings Load(const std::filesystem::path &);
};