#include "HRUModel/HRUModel.cpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE( "initialization does work", "[HRUModel]" ) {
    auto* model = new HRUModel();
}

TEST_CASE( "Add object to model", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model->createObject("1");
}

TEST_CASE( "Add existing object to model", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model->createObject("1");

    try {
        model->createObject("1");
    } catch (std::invalid_argument error) {
    }
}

TEST_CASE( "Destroy not existing object", "[HRUModel]" ) {
    auto* model = new HRUModel();

    try {
        model->destroyObject("2");
    } catch (std::invalid_argument error) {
    }
}

TEST_CASE( "Destroy existing object", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model->createObject("1");

    model->destroyObject("1");
}

TEST_CASE( "Add subject to model", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model->createSubject("1");
}

TEST_CASE( "Add existing Subject to model", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model->createSubject("1");

    try {
        model->createSubject("1");
    } catch (std::invalid_argument error) {
    }
}

TEST_CASE( "Destroy not existing Subject", "[HRUModel]" ) {
    auto* model = new HRUModel();

    try {
        model->destroySubject("2");
    } catch (std::invalid_argument error) {
    }
}

TEST_CASE( "Destroy existing Subject", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model->createSubject("1");

    model->destroySubject("1");
}

TEST_CASE( "Add relations to model", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model
        ->createObject("file_1")
        ->createSubject("alex_1")
        ->createRelation(
            "file_1",
            "alex_1",
            HRURightEnum::READ
        )
        ->createObject("file")
        ->createSubject("alex")
        ->createRelation(
            "file",
            "alex",
            HRURightEnum::READ
        )
        ->createRelation(
            "file",
            "alex",
            HRURightEnum::WRITE
        );
}

TEST_CASE( "Add existing relation to model", "[HRUModel]" ) {
    auto* model = new HRUModel();

    model
    ->createObject("file_1")
    ->createSubject("alex_1")
    ->createRelation(
        "file_1",
        "alex_1",
        HRURightEnum::READ
    )
    ->createObject("file")
    ->createSubject("alex")
    ->createRelation(
        "file",
        "alex",
        HRURightEnum::READ
    )
    ->createRelation(
        "file",
        "alex",
        HRURightEnum::WRITE
    );

    try {
        model->createRelation(
            "file",
            "alex",
            HRURightEnum::WRITE
        );
    } catch (std::invalid_argument error) {
    }
}