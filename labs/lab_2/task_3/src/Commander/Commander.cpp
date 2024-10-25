#ifndef COMMANDER_H
#define COMMANDER_H

#include "string"
#include "map"
#include "vector"
#include "iostream"
#include "fstream"
#include "set"

#include "Utils/Utils.cpp"
#include "HRUModel/HRUModel.cpp"
#include "HRUView/HRUView.cpp"

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

        std::vector <Command> commands = this->loadCommands();

        for (Command command: commands) {
            this->executeCommand(command);
        }

        this->generateView();
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

    struct Command {
        std::string command;
        std::vector <std::string> args;
    };

    ParamKeys paramKeys = {"--in-file", "--com-file", "--out-file"};
    ParamValues paramValues = {"./input.txt", "./commands.txt", "./output.txt"};

    HRUModel *model;

    HRUView *view;

    void parseParam(const std::string &rawParam) {

        if (rawParam.find(this->paramKeys.inputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            this->paramValues.inputFile = value;
        }

        if (rawParam.find(this->paramKeys.commandsFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            this->paramValues.commandsFile = value;
        }

        if (rawParam.find(this->paramKeys.outputFile) == 0) {
            std::string value = rawParam.substr(
                    rawParam.find("=") + 1,
                    rawParam.length() - rawParam.find("=") - 1
            );

            this->paramValues.outputFile = value;
        }
    };

    void loadInput() {
        std::ifstream inputFile;
        inputFile.open(this->paramValues.inputFile.c_str(), std::ios_base::in);

        if (!inputFile.is_open()) {
            throw std::invalid_argument("Error opening the " + this->paramValues.inputFile + " file!");
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

        std::vector <std::string> objects = Utils::splitString(rawObjectsLine, " ");

        if (objects.size() != m) {
            throw std::invalid_argument("Количество объектов не соответствует размерности матрицы");
        }

        fmt::print("Загружены объекты: {}\n", fmt::join(objects, " "));

        std::vector <std::string> subjects;

        HRURelations relations;

        for (int i = 0; i < n; i++) {
            std::string rawSubjectsRightLine;
            getline(inputFile, rawSubjectsRightLine);

            std::vector <std::string> subjectWithRights = Utils::splitString(rawSubjectsRightLine, " ");

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

        this->view = new HRUView(this -> model);

    };

    std::vector <Command> loadCommands() {

        std::ifstream commandsFile;
        commandsFile.open(this->paramValues.commandsFile.c_str(), std::ios_base::in);

        if (!commandsFile.is_open()) {
            throw std::invalid_argument("Error opening the " + this->paramValues.commandsFile + " file!");
        }

        std::vector <Command> commands;

        std::string rawCommandLine;

        while (getline(commandsFile, rawCommandLine)) {

            std::vector <std::string> commandWithArgs = Utils::splitString(rawCommandLine, " ");

            std::vector <std::string> args(++commandWithArgs.begin(), commandWithArgs.end());

            Command command = {
                    commandWithArgs[0],
                    args
            };

            commands.push_back(command);
        }

        commandsFile.close();

        return commands;
    };

    void executeCommand(Command command) {

        std::map<std::string, int> caseMapping{
                {"cco", 1},
                {"ccs", 2},
                {"cdo", 3},
                {"cds", 4},
                {"cer", 5},
                {"cdr", 6},
        };

        switch (caseMapping[command.command]) {
            case 1:
                this->model->createObject(command.args[0]);
                break;
            case 2:
                this->model->createSubject(command.args[0]);
                break;
            case 3:
                this->model->destroyObject(command.args[0]);
                break;
            case 4:
                this->model->destroySubject(command.args[0]);
                break;
            case 5:
                this->model->createRelation(
                        command.args[0],
                        command.args[1],
                        static_cast<HRURightEnum>(command.args[2][0])
                );
                break;
            case 6:
                this->model->destroyRelation(
                        command.args[0],
                        command.args[1],
                        static_cast<HRURightEnum>(command.args[2][0])
                );
                break;
            default:
                throw std::invalid_argument("Такой команды не существует");
        }
    };

    void generateView() {
        std::ofstream outputFile;
        outputFile.open(this->paramValues.outputFile.c_str(), std::ios_base::out);

        if (!outputFile.is_open()) {
            throw std::invalid_argument("Error opening the " + this->paramValues.outputFile + " file!");
        }

        outputFile << this->view->generateView()->getView();

        outputFile.close();
    };
};


#endif //COMMANDER_H
