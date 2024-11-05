#ifndef TGVIEW_H
#define TGVIEW_H

#include "string"
#include "vector"
#include "fmt/ranges.h"
#include "fmt/core.h"

#include "TGModel/TGModel.cpp"


class TGView {

public:
    TGView(TGModel *model) { this->model = model; };

    TGView *generateView() {
        TGObjects objects = this->model->getObjects();
        std::vector <std::string> objectsVector(objects.begin(), objects.end());

        std::string newView;

        newView += fmt::format("{}\n", fmt::join(objectsVector, " "));

        TGObjects subjects = this->model->getSubjects();
        std::vector <std::string> subjectsVector(subjects.begin(), subjects.end());

        newView += fmt::format("{}\n", fmt::join(subjectsVector, " "));

        TGRelations relations = this->model->getRelations();

        std::vector <TGRelation> relationsVector(relations.begin(), relations.end());

        for (auto relation: relationsVector) {
            newView += fmt::format("{} {} {}\n", relation.nodeFirst, relation.nodeSecond, char(relation.right));
        }

        this->view = newView;

        return this;
    };

    auto getView() { return view; };

private:
    TGModel *model;
    std::string view;

    std::string generateRights(TGRelations relations) {
        std::string rightsLine = "";

        for (TGRelation item : relations) {
            rightsLine+=char(item.right);
        }

        if (rightsLine.size() == 0) {
            rightsLine = "-";
        }

        return rightsLine;
    }
};


#endif //TGVIEW_H
