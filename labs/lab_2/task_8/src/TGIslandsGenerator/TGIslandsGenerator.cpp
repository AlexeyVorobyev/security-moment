#ifndef TGISLANDSGENERATOR_H
#define TGISLANDSGENERATOR_H

#include "TGModel/TGModel.cpp"
#include "./Utils/Utils.cpp"
#include <algorithm>

#include "fmt/ranges.h"
#include "fmt/core.h"

class TGIslandsGenerator {
public:
    TGIslandsGenerator(TGModel *model) { this->model = model; };

    TGIslandsGenerator *generateIslands() {

        auto clearedRelations = this->cleanRelations();

        auto discoveredRelationsArray = this->removeDuplicates(this->generateDiscoveredRelations(clearedRelations));

        for (auto disRelations: discoveredRelationsArray) {

            std::set<std::string> emptySet;

            auto model = new TGModel(
                    emptySet,
                    emptySet,
                    disRelations
            );

            islands.push_back(*model);
        }

        return this;
    };

    auto getIslands() { return this->islands; };

private:
    TGModel *model;
    std::vector <TGModel> islands;

    std::vector<TGRelations> removeDuplicates(std::vector<TGRelations> relationsArr) {
        std::set<std::set<std::string>> set;

        std::vector<TGRelations> relationsArrNew;

        for (auto relations: relationsArr) {
            auto nod = this->getNodesFromRelations(relations);
            if (set.find(nod) == set.end()) {
                set.insert(nod);
                relationsArrNew.push_back(relations);
            }
        }

        return relationsArrNew;
    }

    std::set<std::string> getNodesFromRelations(TGRelations relations) {
        std::set<std::string> set;

        for (auto relation: relations) {
            set.insert(relation.nodeFirst);
            set.insert(relation.nodeSecond);
        }

        return set;
    }

    std::vector<TGRelations> generateDiscoveredRelations(TGRelations clearedRelations) {

        std::vector <TGRelations> discoveredRelationsArray;

        TGSubjects subjects = this->model->getSubjects();

        auto predicateFactory = [](std::vector <std::string> toCompareVector) {
            auto predicate = [&](TGRelation relation) {
                return std::find(toCompareVector.begin(), toCompareVector.end(), relation.nodeFirst) !=
                       toCompareVector.end()
                       || std::find(toCompareVector.begin(), toCompareVector.end(), relation.nodeSecond) !=
                          toCompareVector.end();
            };

            return predicate;
        };

        for (auto subject: subjects) {
            auto nodes = this->dfs(subject, clearedRelations);

            fmt::print("Узлы: {}\n", fmt::join(nodes, " "));

            TGRelations disRelations;

            Utils::copyIf(
                    clearedRelations.begin(),
                    clearedRelations.end(),
                    std::inserter(disRelations, disRelations.end()),
                    predicateFactory(nodes)
            );

            discoveredRelationsArray.push_back(disRelations);
        }

        return discoveredRelationsArray;
    }

    std::vector <std::string> dfs(
            std::string node,
            TGRelations clearedRelations,
            std::vector <std::string> visitedNodes = {}
    ) {

        auto predicate = [&](TGRelation relation) {
            return (relation.nodeFirst == node
                   && std::find(visitedNodes.begin(), visitedNodes.end(), relation.nodeFirst) == visitedNodes.end())
                   || (relation.nodeSecond == node
                      && std::find(visitedNodes.begin(), visitedNodes.end(), relation.nodeSecond) == visitedNodes.end());
        };

        auto it = std::find_if(
                clearedRelations.begin(),
                clearedRelations.end(),
                predicate
        );

        if (it == clearedRelations.end()) {
            return visitedNodes;
        }

        visitedNodes.push_back(node);

        if (it->nodeFirst == node) {
            return dfs(it->nodeSecond, clearedRelations, visitedNodes);
        } else {
            return dfs(it->nodeFirst, clearedRelations, visitedNodes);
        }
    }

    TGRelations cleanRelations() {

        auto subjects = this->model->getSubjects();

        auto relations = this->model->getRelations();

        TGRelations clearedRelations;

        auto predicate = [&](TGRelation relation) {
            return subjects.find(relation.nodeFirst) != subjects.end()
                   && subjects.find(relation.nodeSecond) != subjects.end()
                   && relation.right != TGRightEnum::ABSTRACT_RIGHT;
        };

        Utils::copyIf(
                relations.begin(),
                relations.end(),
                std::inserter(clearedRelations, clearedRelations.end()),
                predicate
        );

        return clearedRelations;
    }
};


#endif //TGISLANDSGENERATOR_H
