#pragma once

#include "data_types.h"
namespace Quant
{
  // main interface for the pipeline and tasks
  struct IProcessor
  {
    virtual data_t process(data_t) const = 0;
    virtual ~IProcessor() = default;
  };
}
