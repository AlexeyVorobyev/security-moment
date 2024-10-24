#ifndef COMMANDER_H
#define COMMANDER_H

#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "fstream"
#include "set"

#include "splitString.cpp"
#include "HRUModel/HRUModel.cpp"

#include "fmt/ranges.h"
#include "fmt/core.h"

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
        }
    };


    void execute() {
        std::cout << "started" << std::endl;

        this->loadInput();
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
        std::string commandsFile;
        std::string outputFile;
    };

    struct ParamValues {
        std::string inputFile;
        std::string commandsFile;
        std::string outputFile;
    };

    ParamKeys paramKeys = {"--in-file", "--comm-file", "--out-file"};
    ParamValues paramValues = {"./input.txt", "./commands.txt", "./output.txt"};

    HRUModel *model;

    void parseParam(const std::string &rawParam) {

        if (rawParam.find(paramKeys.inputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.inputFile = value;
        }

        if (rawParam.find(paramKeys.commandsFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.commandsFile = value;
        }

        if (rawParam.find(paramKeys.outputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            paramValues.outputFile = value;
        }
    };

    void loadInput() {
        std::ifstream inputFile;
        inputFile.open(paramValues.inputFile.c_str(), std::ios_base::in);

        if (!inputFile.is_open()) {
            throw std::invalid_argument("Error opening the " + paramValues.inputFile + " file!");
        }

        std::string rawN;
        getline(inputFile, rawN);
        std::string rawM;
        getline(inputFile, rawM);

        unsigned int n = std::stoi(rawN);
        unsigned int m = std::stoi(rawM);

        fmt::print("Загружена матрица разрешений размерностью {}x{}\n", n, m);

        std::string rawObjectsLine;
        getline(inputFile, rawObjectsLine);
        getline(inputFile, rawObjectsLine);

        std::vector <std::string> objects = split(rawObjectsLine, " ");

        if (objects.size() != m) {
            throw std::invalid_argument("Количество объектов не соответствует размерности матрицы");
        }

        fmt::print("Загружены объекты: {}\n", fmt::join(objects, " "));

        std::vector <std::string> subjects;

        HRURelations relations;

        for (int i = 0; i < n; i++) {
            std::string rawSubjectsRightLine;
            getline(inputFile, rawSubjectsRightLine);

            std::vector <std::string> subjectWithRights = split(rawSubjectsRightLine, " ");

            if (subjectWithRights.size() != m + 1) {
                throw std::invalid_argument("Количество прав не соответствует размерности матрицы");
            }

            std::string subject = subjectWithRights[0];

            fmt::print("\nЗагружен субъект: {}\n", subject);

            subjects.push_back(subject);

            for (int j = 1; j < m + 1; j++) {

                std::string rights = subjectWithRights[j];

                for (char right: rights) {

                    if (right == '-') {
                        continue;
                    }

                    HRURelation relation = {
                            objects[j - 1],
                            subject,
                            static_cast<HRURightEnum>(right)
                    };

                    fmt::print(
                            "Загружено право {} субъекта {} над объектом {}\n",
                            right,
                            subject,
                            objects[j - 1]
                    );

                    relations.insert(relation);
                }
            }
        }

        inputFile.close();

        std::set <std::string> objectsSet(objects.begin(), objects.end());
        std::set <std::string> subjectsSet(subjects.begin(), subjects.end());

        this->model = new HRUModel(
                objectsSet,
                subjectsSet,
                relations
        );

    };
};


#endif //COMMANDER_H
