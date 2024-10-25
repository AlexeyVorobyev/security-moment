#ifndef HRUVIEW_H
#define HRUVIEW_H

#include "string"
#include "vector"
#include "fmt/ranges.h"
#include "fmt/core.h"

#include "HRUModel/HRUModel.cpp"
#include "Utils/Utils.cpp"


class HRUView {

public:
    HRUView(HRUModel *model) { this->model = model; };

    HRUView *generateView() {
        HRUObjects objects = this->model->getObjects();
        std::vector <std::string> objectsVector(objects.begin(), objects.end());

        std::string newView;

        newView += fmt::format("   {}\n", fmt::join(objectsVector, " "));

        HRURelations relations = this->model->getRelations();

        auto predicateFactory = [](
                std::string subject,
                std::string object
        ) {

            auto predicate = [&](HRURelation relation) {
                return relation.object == object
                       && relation.subject == subject;
            };

            return predicate;
        };

        HRUSubjects subjects = this->model->getSubjects();
        std::vector <std::string> subjectsVector(subjects.begin(), subjects.end());

        for (std::string subject: subjectsVector) {

            std::string newLine = subject;

            for (std::string object: objectsVector) {

                HRURelations filteredRelations;

                Utils::copyIf(
                        relations.begin(),
                        relations.end(),
                        std::inserter(filteredRelations, filteredRelations.end()),
                        predicateFactory(subject, object)
                );

                newLine += (" " + this->generateRights(filteredRelations));
            }

            newView += fmt::format("{}\n", newLine);
        }

        this->view = newView;

        return this;
    };

    auto getView() { return view; };

private:
    HRUModel *model;
    std::string view;

    std::string generateRights(HRURelations relations) {
        std::string rightsLine = "";

        for (HRURelation item : relations) {
            rightsLine+=char(item.right);
        }

        if (rightsLine.size() == 0) {
            rightsLine = "-";
        }

        return rightsLine;
    }
};


#endif //HRUVIEW_H
