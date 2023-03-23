#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include <functional>

namespace Quant
{
  template<class InputType, class OutputType>
  struct Task {
    virtual OutputType process(InputType value) = 0;
  };


  template<class InputType, class OutputType>
  struct Pipeline : Task<InputType, OutputType>
  {
    Pipeline();
    virtual OutputType process(InputType value) override {
      foreach(auto t : tasks) {
        t(0);
      }
    }

    std::vector < std::function<void(int)>> tasks;
  };

  template<class InputType, class OutputType> Pipeline<InputType, OutputType>::Pipeline() 
  {
    using std::cout;
    using std::endl;
    tasks.push_back([]() { cout << "Function called!" << endl; })
  };
}
