#ifndef HRUMODEL_H
#define HRUMODEL_H

#include "vector"
#include "set"
#include "string"
#include "iostream"
#include "HRURelation.cpp"
#include "copyIf.cpp"
#include "fmt/core.h"

typedef std::set <std::string> HRUObjects;

typedef std::set <std::string> HRUSubjects;

typedef std::set <HRURelation, HRURelationComparator> HRURelations;


class HRUModel {

public:

    HRUModel() = default;

    HRUModel(
            HRUObjects objects,
            HRUSubjects subjects
    ) {
        this->objects = objects;
        this->subjects = subjects;
    }

    HRUModel(
            HRUObjects objects,
            HRUSubjects subjects,
            HRURelations relations
    ) {
        this->objects = objects;
        this->subjects = subjects;
        this->relations = relations;
    }

    HRUModel *createObject(std::string objectKey) {
        if (this->objects.find(objectKey) != this->objects.end()) {
            throw std::invalid_argument("Объект с таким ключом уже существует");
        }

        this->objects.insert(objectKey);
        fmt::print("Объект с ключом {} добавлен в модель\n", objectKey);

        return this;
    }

    HRUModel *destroyObject(std::string objectKey) {
        if (this->objects.find(objectKey) == this->objects.end()) {
            throw std::invalid_argument("Объекта с таким ключом не существует");
        }

        this->objects.erase(objectKey);

        HRURelations clearedRelations;

        struct Condition {
            Condition(std::string compare) {
                this->compare = compare;
            }

            std::string compare;

            bool operator()(HRURelation relation) {
                return relation.object != this->compare;
            }
        };

        copyIf(
                this->relations.begin(),
                this->relations.end(),
                std::inserter(clearedRelations, clearedRelations.end()),
                Condition(objectKey)
        );

        this->relations = clearedRelations;

        fmt::print("Объект с ключом {} удалён из модели\n", objectKey);

        return this;
    }

    HRUModel *createSubject(std::string subjectKey) {
        if (this->subjects.find(subjectKey) != this->subjects.end()) {
            throw std::invalid_argument("Объект с таким ключом уже существует");
        }

        this->subjects.insert(subjectKey);
        fmt::print("Субъект с ключом {} добавлен в модель\n", subjectKey);

        return this;
    }

    HRUModel *destroySubject(std::string subjectKey) {
        if (this->subjects.find(subjectKey) == this->subjects.end()) {
            throw std::invalid_argument("Субъекта с таким ключом не существует");
        }

        this->subjects.erase(subjectKey);

        HRURelations clearedRelations;

        struct Condition {
            Condition(std::string compare) {
                this->compare = compare;
            }

            std::string compare;

            bool operator()(HRURelation relation) {
                return relation.subject != this->compare;
            }
        };

        copyIf(
                this->relations.begin(),
                this->relations.end(),
                std::inserter(clearedRelations, clearedRelations.end()),
                Condition(subjectKey)
        );

        this->relations = clearedRelations;

        fmt::print("Субъект с ключом {} удалён из модели\n", subjectKey);

        return this;
    }

    HRUModel *createRelation(
            std::string objectKey,
            std::string subjectKey,
            HRURightEnum rightKey
    ) {
        if (this->objects.find(objectKey) == this->objects.end()) {
            throw std::invalid_argument("Объекта с таким ключом не существует");
        }

        if (this->subjects.find(subjectKey) == this->subjects.end()) {
            throw std::invalid_argument("Субъекта с таким ключом не существует");
        }


        HRURelations relationsDuplicate;

        struct Condition {
            Condition(HRURelation compare) {
                this->compare = compare;
            }

            HRURelation compare;

            bool operator()(HRURelation relation) {
                return relation.subject == this->compare.subject
                       && relation.object == this->compare.object
                       && relation.right == this->compare.right;
            }
        };

        HRURelation newRelation = {
                objectKey,
                subjectKey,
                rightKey
        };

        copyIf(
                this->relations.begin(),
                this->relations.end(),
                std::inserter(relationsDuplicate, relationsDuplicate.end()),
                Condition(newRelation)
        );

        fmt::print("size: {}",relationsDuplicate.size());

        if (!relationsDuplicate.empty()) {
            throw std::invalid_argument("Такое право уже существует");
        }

        this->relations.insert(newRelation);

        fmt::print("size: {}",this->relations.size());

        fmt::print(
                "Право {} для субъекта {} над объектом {} добавлено в модель\n",
                char(rightKey),
                subjectKey,
                objectKey
        );

        return this;
    }

private:
    HRUObjects objects;
    HRUSubjects subjects;
    HRURelations relations;
};


#endif //HRUMODEL_H
