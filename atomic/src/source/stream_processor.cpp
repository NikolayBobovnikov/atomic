#include <fstream>
#include <string>
#include "io_type_helper.h"
#include "stream_processor.h"

using namespace std;
namespace Quant
{
    StreamProcessor::StreamProcessor(std::unique_ptr<Pipeline> p)
        : BatchProcessor(move(p))
    {
    }

    void StreamProcessor::batch_process(const filesystem::path &input_file, const filesystem::path &output_file) const
    {
        const auto &pipeline = get_pipeline();
        ifstream ifs(input_file.string());
        ofstream ofs(output_file.string());

        if (!ifs.is_open())
        {
            throw logic_error("Cannot open input file");
        }
        if (!ofs.is_open())
        {
            throw logic_error("Cannot create output file");
        }

        auto type = pipeline.get_in_type();
        string line;
        data_t input;
        data_t output;
        while (std::getline(ifs, line))
        {
            try
            {
                input = IOTypeHelper::from_string(type, line);
                output = pipeline.process(input);
                ofs << IOTypeHelper::to_string(output) << endl;
            }
            catch (exception &e)
            {
                // write to output and continue
                // pipeline.process_ext() for logging details
                ofs << e.what() << endl;
            }
        }
    }
}