#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "../data/sela_frame.hpp"
#include "../file/sela_file.hpp"
#include "../file/wav_file.hpp"

namespace sela {
class Encoder {
private:
    void readFrames();
    void readFrames2();
    void processFrames(std::vector<data::SelaFrame>& encodedSelaFrames);
    // std::ifstream& ifStream;
    std::vector<char>& contents;
    file::WavFile wavFile;

public:
    // Encoder(std::ifstream& ifStream)
    //     : ifStream(ifStream)
    // {
    // }
    Encoder(std::vector<char>& contents)
        : contents(contents)
    {
    }
    file::SelaFile process();
    file::SelaFile process2();
};
}

#endif