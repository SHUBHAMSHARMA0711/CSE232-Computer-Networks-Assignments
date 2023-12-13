#include "byte_stream.hh"
#include "byte_stream_test_harness.hh"
#include "util.hh"

#include <exception>
#include <iostream>

using namespace std;

int main() {
    try {

    } catch (const exception &e) {
        cerr << "Exception: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
