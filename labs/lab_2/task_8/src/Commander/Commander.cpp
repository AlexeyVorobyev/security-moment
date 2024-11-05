#ifndef COMMANDER_H
#define COMMANDER_H

#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "fstream"
#include "set"

#include "Utils/Utils.cpp"
#include "TGModel/TGModel.cpp"
#include "TGIslandsGenerator/TGIslandsGenerator.cpp"
#include "../TGView/TGView.cpp"

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
        srand(time(0));
        std::cout << "started" << std::endl;

        this->loadInput();

        TGIslandsGenerator *islandsGenerator = new TGIslandsGenerator(this->model);

        auto islands = islandsGenerator
                ->generateIslands()
                ->getIslands();

        for (auto island: islands) {
            TGView* view = new TGView(&island);
            this->generateView(view);
        }
    };

private:
    struct ParamKeys {
        std::string inputFile;
        std::string outputFileFolder;
    };

    struct ParamValues {
        std::string inputFile;
        std::string outputFileFolder;
    };


    ParamKeys paramKeys = {"--in-file", "--out-file-dir"};
    ParamValues paramValues = {"./input.txt", "./output"};

    TGModel *model;

    void parseParam(const std::string &rawParam) {

        if (rawParam.find(this->paramKeys.inputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            this->paramValues.inputFile = value;
        }

        if (rawParam.find(this->paramKeys.outputFileFolder) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            this->paramValues.outputFileFolder = value;
        }
    };

    void loadInput() {
        std::ifstream inputFile;
        inputFile.open(this->paramValues.inputFile.c_str(), std::ios_base::in);

        if (!inputFile.is_open()) {
            throw std::invalid_argument("Error opening the " + this->paramValues.inputFile + " file!");
        }

        std::string rawObjectsLine;
        getline(inputFile, rawObjectsLine);

        std::vector <std::string> objects = Utils::splitString(rawObjectsLine, " ");

        fmt::print("Загружены объекты: {}\n", fmt::join(objects, " "));

        std::string rawSubjectsLine;
        getline(inputFile, rawSubjectsLine);

        std::vector <std::string> subjects = Utils::splitString(rawSubjectsLine, " ");

        fmt::print("Загружены субъекты: {}\n", fmt::join(subjects, " "));

        TGRelations relations;

        std::string rawRelationLine;

        getline(inputFile, rawRelationLine);

        while (getline(inputFile, rawRelationLine)) {

            std::vector <std::string> relation = Utils::splitString(rawRelationLine, " ");

            if (relation.size() != 3) {
                throw std::invalid_argument("Некорректный формат строки с описанием дуги прав");
            }

            std::string nodeFirst = relation[0];

            std::string nodeSecond = relation[1];

            std::string rights = relation[2];

            for (char right: rights) {

                TGRelation relation = {
                        nodeFirst,
                        nodeSecond,
                        static_cast<TGRightEnum>(right)
                };

                fmt::print(
                        "Загружено право {} узла {} над узлом {}\n",
                        right,
                        nodeFirst,
                        nodeSecond
                );

                relations.insert(relation);
            }
        }

        inputFile.close();

        std::set <std::string> objectsSet(objects.begin(), objects.end());
        std::set <std::string> subjectsSet(subjects.begin(), subjects.end());

        this->model = new TGModel(
                objectsSet,
                subjectsSet,
                relations
        );
    };

    void generateView(TGView* view) {
        std::ofstream outputFileFolder;
        outputFileFolder.open((this->paramValues.outputFileFolder + "/" + std::to_string(rand()) + ".txt").c_str(),
                              std::ios_base::out);

        if (!outputFileFolder.is_open()) {
            throw std::invalid_argument("Error opening the " + this->paramValues.outputFileFolder + " file!");
        }

        outputFileFolder << view->generateView()->getView();

        outputFileFolder.close();
    };
};


#endif //COMMANDER_H
