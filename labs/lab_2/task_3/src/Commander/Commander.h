#ifndef COMMANDER_H
#define COMMANDER_H

#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "fstream"

/**
 * Класс, описывающий логику обработки CLI команд
 * */
class Commander {

public:
    Commander(int argc, char **argv) {

        for (int i = 0; i < argc; i++) {
            if (argv[i] == nullptr) {
                continue;
            }

            std::string rawParam = std::string(argv[i]);

            this->parseParam(rawParam);
        };
    };

    void parseParam(const std::string &rawParam) {

        if (rawParam.find(paramKeys.inputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.inputFile = value;
        }

        if (rawParam.find(paramKeys.outputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.outputFile = value;
        }
    }

    void execute() const {
        std::cout<<"test"<<std::endl;
//        std::ifstream inputFile;
//        inputFile.open(paramValues.inputFile.c_str(), std::ios_base::in);
//
//        if (!inputFile.is_open()) {
//            std::cerr << "Error opening the " << paramValues.inputFile << " file!" << std::endl;
//            return;
//        }
//
//        std::string readLineData;
//
//        std::vector<std::string> compressedData;
//
//        while (getline(inputFile, readLineData)) {
//            std::string compressedLine = this->rleCompressor->compress(readLineData);
//            compressedData.push_back(compressedLine);
//        }
//
//        inputFile.close();
//
//        std::ofstream outputFile;
//        outputFile.open(paramValues.outputFile.c_str(), std::ios_base::out | std::ios_base::binary);
//
//
//        if (!outputFile.is_open()) {
//            std::cerr << "Error opening the " << paramValues.outputFile << " file!" << std::endl;
//            return;
//        }
//
//
//        for (const std::string& item : compressedData) {
//            outputFile << item.c_str() << std::endl;
//        }
//
//
//        outputFile.flush();
//
//        outputFile.close();
   };

private:
    struct ParamKeys {
        std::string inputFile;
        std::string outputFile;
    };

    struct ParamValues {
        std::string inputFile;
        std::string outputFile;
    };

    ParamKeys paramKeys = {"--in-file", "--out-file"};
    ParamValues paramValues = {"./input.txt", "./output.txt"};

//    RleCompressor *rleCompressor = new RleCompressor();
};


#endif //COMMANDER_H
