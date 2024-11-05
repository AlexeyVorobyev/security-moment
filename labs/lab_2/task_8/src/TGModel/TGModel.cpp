#ifndef TGMODEL_H
#define TGMODEL_H

#include "vector"
#include "set"
#include "string"

#include "TGRelation.cpp"

typedef std::set <std::string> TGObjects;

typedef std::set <std::string> TGSubjects;

typedef std::set <TGRelation, TGRelationComparator> TGRelations;


class TGModel {

public:

    TGModel() = default;

    TGModel(
            TGObjects objects,
            TGSubjects subjects
    ) {
        this->objects = objects;
        this->subjects = subjects;
    }

    TGModel(
            TGObjects objects,
            TGSubjects subjects,
            TGRelations relations
    ) {
        this->objects = objects;
        this->subjects = subjects;
        this->relations = relations;
    }

    auto getObjects() { return objects; };

    auto getSubjects() { return subjects; };

    auto getRelations()  { return relations; };

private:
    TGObjects objects;
    TGSubjects subjects;
    TGRelations relations;

};


#endif //TGMODEL_H
