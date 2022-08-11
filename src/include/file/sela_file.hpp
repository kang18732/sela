#ifndef _SELA_FILE_H_
#define _SELA_FILE_H_

#include "../data/sela_frame.hpp"
#include "../data/sela_header.hpp"

#include <fstream>

namespace file {
class SelaFile {
public:
    data::SelaHeader selaHeader;
    std::vector<data::SelaFrame> selaFrames;
    void readFromFile(std::ifstream& inputFile);
    void readFromVector(std::vector<char>& contents);
    void writeToFile(std::ofstream& outputFile);
    std::vector<char> writeToVector();
    SelaFile() {}
    SelaFile(uint32_t sampleRate, uint16_t bitsPerSample, uint8_t channels, std::vector<data::SelaFrame>&& selaFrames);
};
}

#endif