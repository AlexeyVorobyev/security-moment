#include "Commander/Commander.cpp"

int main(int argc, char **argv) {

    auto* commander = new Commander(argc, argv);

    commander->execute();

    return -1;
}
