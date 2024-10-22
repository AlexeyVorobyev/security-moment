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

        if (rawParam.find(paramKeys.inputFile)) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.inputFile = value;
        }

        if (rawParam.find(paramKeys.outputFile)) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.outputFile = value;
        }
    }

    void execute() const {
        std::ifstream inputFile(paramValues.inputFile);
        std::ofstream outputFile(paramValues.outputFile);

        if (!inputFile.is_open()) {
            std::cerr << "Error opening the " << paramValues.inputFile << " file!" << std::endl;
            return;
        }
        if (!outputFile.is_open()) {
            std::cerr << "Error opening the " << paramValues.outputFile << " file!" << std::endl;
            return;
        }

        std::string readLineData;

        while (getline(inputFile, readLineData)) {
            std::string compressedData = this->rleCompressor->compress(readLineData);
            outputFile << compressedData << std::endl;
        }

        inputFile.close();
        outputFile.close();
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

    RleCompressor *rleCompressor = new RleCompressor();
};


#endif //COMMANDER_H
