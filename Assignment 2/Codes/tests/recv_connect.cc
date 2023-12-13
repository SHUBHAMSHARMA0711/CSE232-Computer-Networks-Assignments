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
        // auto rd = get_random_generator();

        {
            TCPReceiverTestHarness test{4000};
            test.execute(ExpectWindow{4000});
            test.execute(ExpectAckno{std::optional<WrappingInt32>{}});
            test.execute(ExpectUnassembledBytes{0});
            test.execute(ExpectTotalAssembledBytes{0});
            test.execute(SegmentArrives{}.with_syn().with_seqno(0).with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{1}});
            test.execute(ExpectUnassembledBytes{0});
            test.execute(ExpectTotalAssembledBytes{0});
        }

        {
            TCPReceiverTestHarness test{5435};
            test.execute(ExpectAckno{std::optional<WrappingInt32>{}});
            test.execute(ExpectUnassembledBytes{0});
            test.execute(ExpectTotalAssembledBytes{0});
            test.execute(SegmentArrives{}.with_syn().with_seqno(89347598).with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{89347599}});
            test.execute(ExpectUnassembledBytes{0});
            test.execute(ExpectTotalAssembledBytes{0});
        }

    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
