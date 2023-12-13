#include "receiver_harness.hh"
#include "wrapping_integers.hh"

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    try {
    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
