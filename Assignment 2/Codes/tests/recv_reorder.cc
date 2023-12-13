#include "receiver_harness.hh"
#include "util.hh"
#include "wrapping_integers.hh"

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
    try {
        auto rd = get_random_generator();

        // An in-window, but later segment
        {
            uint32_t isn = uniform_int_distribution<uint32_t>{0, UINT32_MAX}(rd);
            TCPReceiverTestHarness test{2358};
            test.execute(SegmentArrives{}.with_syn().with_seqno(isn).with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 1}});
            test.execute(
                SegmentArrives{}.with_seqno(isn + 10).with_data("abcd").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 1}});
            test.execute(ExpectBytes{""});
            test.execute(ExpectUnassembledBytes{4});
            test.execute(ExpectTotalAssembledBytes{0});
        }

        // Many gaps, then filled bit by bit.
        {
            uint32_t isn = uniform_int_distribution<uint32_t>{0, UINT32_MAX}(rd);
            TCPReceiverTestHarness test{2358};
            test.execute(SegmentArrives{}.with_syn().with_seqno(isn).with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 1}});
            test.execute(SegmentArrives{}.with_seqno(isn + 5).with_data("e").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 1}});
            test.execute(ExpectBytes{""});
            test.execute(ExpectUnassembledBytes{1});
            test.execute(ExpectTotalAssembledBytes{0});
            test.execute(SegmentArrives{}.with_seqno(isn + 7).with_data("g").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 1}});
            test.execute(ExpectBytes{""});
            test.execute(ExpectUnassembledBytes{2});
            test.execute(ExpectTotalAssembledBytes{0});
            test.execute(SegmentArrives{}.with_seqno(isn + 3).with_data("c").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 1}});
            test.execute(ExpectBytes{""});
            test.execute(ExpectUnassembledBytes{3});
            test.execute(ExpectTotalAssembledBytes{0});
            test.execute(SegmentArrives{}.with_seqno(isn + 1).with_data("ab").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectAckno{WrappingInt32{isn + 4}});
            test.execute(ExpectBytes{"abc"});
            test.execute(ExpectUnassembledBytes{2});
            test.execute(ExpectTotalAssembledBytes{3});
            test.execute(SegmentArrives{}.with_seqno(isn + 6).with_data("f").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectUnassembledBytes{3});
            test.execute(ExpectTotalAssembledBytes{3});
            test.execute(ExpectBytes{""});
            test.execute(SegmentArrives{}.with_seqno(isn + 4).with_data("d").with_result(SegmentArrives::Result::OK));
            test.execute(ExpectUnassembledBytes{0});
            test.execute(ExpectTotalAssembledBytes{7});
            test.execute(ExpectBytes{"defg"});
        }

    } catch (const exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    return EXIT_SUCCESS;
}
