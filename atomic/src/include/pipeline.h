#pragma once

#include <memory>

namespace Quant
{
  /*

  settings.json

  C++ functors for callable/pluggable items

  */

  struct Pipeline
  {
    virtual void run() = 0;
  };
}
