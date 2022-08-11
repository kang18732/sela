#include <fstream>
#include <iostream>

#include "include/data/exception.hpp"
#include "include/file/wav_file.hpp"
#include "include/rice.hpp"
#include "include/sela/decoder.hpp"
#include "include/sela/encoder.hpp"
#include "include/sela/player.hpp"

#include <emscripten/bind.h>

using namespace emscripten;

void print(std::string& data)
{
    std::cout << data << std::endl;
}

void printUsage(const std::string &programName)
{
    std::string usageString = "";
    usageString += "Usage: \n\n";
    usageString += "Encoding a file:\n";
    usageString += programName + " -e path/to/input.wav path/to/output.sela\n\n";
    usageString += "Decoding a file:\n";
    usageString += programName + " -d path/to/input.sela path/to/output.wav\n\n";
    usageString += "Playing a file:\n";
    usageString += programName + " -p path/to/input.sela";
    print(usageString);
}

// void encodeFile(std::ifstream &inputFile, std::ofstream &outputFile)
// {
//     sela::Encoder encoder = sela::Encoder(inputFile);
//     file::SelaFile selaFile = encoder.process();
//     selaFile.writeToFile(outputFile);
// }

std::vector<char> encodeWithSela(val blob)
{
    std::vector<char> contents = vecFromJSArray<char>(blob);
    // std::vector<char> contents = convertJSArrayToNumberVector<char>(blob);
    sela::Encoder encoder = sela::Encoder(contents);
    file::SelaFile selaFile = encoder.process2();
    return selaFile.writeToVector();
}

// void decodeFile(std::ifstream &inputFile, std::ofstream &outputFile)
// {
//     sela::Decoder decoder = sela::Decoder(inputFile);
//     file::WavFile wavFile = decoder.process();
//     wavFile.writeToFile(outputFile);
// }

std::vector<char> decodeWithSela(val blob)
{
    std::vector<char> contents = vecFromJSArray<char>(blob);
    // std::vector<char> contents = convertJSArrayToNumberVector<char>(blob);
    sela::Decoder decoder = sela::Decoder(contents);
    file::WavFile wavFile = decoder.process2();
    return wavFile.writeToVector();
}

// void playFile(std::ifstream &inputFile)
// {
//     sela::Decoder* decoder = new sela::Decoder(inputFile);
//     file::WavFile wavFile = decoder->process();
//     delete decoder;

//     sela::Player player;
//     player.play(wavFile);
// }

EMSCRIPTEN_BINDINGS(module) {
    function("encodeWithSela", &encodeWithSela);
    function("decodeWithSela", &decodeWithSela);

    register_vector<char>("vector<char>");
}

// int main(int argc, char **argv)
// {
//     std::string header = "SimplE Lossless Audio v2. Released under MIT license";
//     print(header);
//     std::string programName = std::string(argv[0]);
//     if (argc < 2)
//     {
//         printUsage(programName);
//     }
//     else
//     {
//         try
//         {
//             std::string secondArg = std::string(argv[1]);
//             if (secondArg == "-e" && argc == 4)
//             {
//                 std::ifstream inputFile(argv[2], std::ios::binary);
//                 std::ofstream outputFile(argv[3], std::ios::binary);

//                 std::string str = "Encoding: " + std::string(argv[2]);
//                 print(str);

//                 encodeFile(inputFile, outputFile);
//             }
//             else if (secondArg == "-d" && argc == 4)
//             {
//                 std::ifstream inputFile(argv[2], std::ios::binary);
//                 std::ofstream outputFile(argv[3], std::ios::binary);

//                 std::string str = "Decoding: " + std::string(argv[2]);
//                 print(str);

//                 decodeFile(inputFile, outputFile);
//             }
//             else if (secondArg == "-p" && argc == 3)
//             {
//                 std::ifstream inputFile(argv[2], std::ios::binary);

//                 std::string str = "Playing: " + std::string(argv[2]);
//                 print(str);

//                 playFile(inputFile);
//             }
//             else
//             {
//                 printUsage(programName);
//             }
//         }
//         catch (data::Exception exception)
//         {
//             std::cerr << exception.exceptionMessage << std::endl;
//             return 1;
//         }
//     }
//     return 0;
// }