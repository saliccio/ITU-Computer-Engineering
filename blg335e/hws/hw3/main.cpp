#include <cstdlib>
#include "CompletelyFairScheduler.h"

int main(int argc, char** argv) {
    CompletelyFairScheduler cfs;
    cfs.simulate(argv[1], "output.txt");

    return EXIT_SUCCESS;
}