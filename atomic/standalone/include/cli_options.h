#include <filesystem>

struct CLIOptions {

  CLIOptions(int argc, char* argv[]);

  std::filesystem::path input;
  std::filesystem::path output;
  std::filesystem::path config;
};
