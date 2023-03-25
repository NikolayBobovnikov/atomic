#include <filesystem>
#include "settings.h"

using namespace Quant;

struct PipelineSettingsLoader
{
  Settings::Pipeline Load(const std::filesystem::path &);
};