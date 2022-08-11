#ifndef _DECODER_H_
#define _DECODER_H_

#include "../file/sela_file.hpp"
#include "../file/wav_file.hpp"
#include "../data/wav_frame.hpp"

namespace sela {
class Decoder {
private:
    void readFrames();
    void readFrames2();
    void processFrames(std::vector<data::WavFrame>& decodedWavFrames);
    // std::ifstream& ifStream;
    std::vector<char>& contents;
    file::SelaFile selaFile;

public:
    // explicit Decoder(std::ifstream& ifStream)
    //     : ifStream(ifStream)
    // {
    // }
    Decoder(std::vector<char>& contents)
        : contents(contents)
    {
    }
    file::WavFile process();
    file::WavFile process2();
};
}

#endif