#ifndef HRUMODEL_H
#define HRUMODEL_H

#include "vector"
#include "set"
#include "string"
#include "iostream"
#include "Utils/Utils.cpp"
#include "fmt/core.h"
#include "algorithm"

#include "HRURelation.cpp"

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

        auto predicateFactory = [](std::string compare) {

            auto predicate = [&](HRURelation relation) {
                return relation.object != compare;
            };

            return predicate;
        };

        Utils::copyIf(
                this->relations.begin(),
                this->relations.end(),
                std::inserter(clearedRelations, clearedRelations.end()),
                predicateFactory(objectKey)
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

        auto predicateFactory = [](std::string compare) {

            auto predicate = [&](HRURelation relation) {
                return relation.subject != compare;
            };

            return predicate;
        };

        Utils::copyIf(
                this->relations.begin(),
                this->relations.end(),
                std::inserter(clearedRelations, clearedRelations.end()),
                predicateFactory(subjectKey)
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

        HRURelation newRelation = {
                objectKey,
                subjectKey,
                rightKey
        };

        auto predicateFactory = [](HRURelation a) {

            auto predicate = [&](HRURelation b) {
                return a.subject == b.subject
                       && a.object == b.object
                       && a.right == b.right;
            };

            return predicate;
        };

        auto it = std::find_if(
                this->relations.begin(),
                this->relations.end(),
                predicateFactory(newRelation)
        );

        if (it != this->relations.end()) {
            throw std::invalid_argument("Такое право уже существует");
        }

        this->relations.insert(newRelation);

        fmt::print(
                "Право {} для субъекта {} над объектом {} добавлено в модель\n",
                char(rightKey),
                subjectKey,
                objectKey
        );

        return this;
    }

    HRUModel *destroyRelation(
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

        HRURelation toDeleteRelation = {
                objectKey,
                subjectKey,
                rightKey
        };

        auto predicateFactory = [](HRURelation a) {

            auto predicate = [&](HRURelation b) {
                return a.subject == b.subject
                       && a.object == b.object
                       && a.right == b.right;
            };

            return predicate;
        };

        auto it = std::find_if(
                this->relations.begin(),
                this->relations.end(),
                predicateFactory(toDeleteRelation)
        );

        if (it == this->relations.end()) {
            throw std::invalid_argument("Такого права не существует");
        }

        this->relations.erase(it);

        fmt::print(
                "Право {} для субъекта {} над объектом {} удалено из модели\n",
                char(rightKey),
                subjectKey,
                objectKey
        );

        return this;
    }

    auto getObjects() { return objects; };

    auto getSubjects() { return subjects; };

    auto getRelations()  { return relations; };

private:
    HRUObjects objects;
    HRUSubjects subjects;
    HRURelations relations;

};


#endif //HRUMODEL_H
