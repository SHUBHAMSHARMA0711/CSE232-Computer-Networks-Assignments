#include "tcp_receiver.hh"

#include <algorithm>

using namespace std;

void TCPReceiver::segment_received(const TCPSegment &seg)
{
    const TCPHeader head = seg.header();
    // ...

    if (head.syn)
    {
        _isn = head.seqno;
        _synReceived = true;
    }

    else if (head.fin)
    {
        _finReceived = true;
    }

    // --- Hint ------
    // convert the seqno into absolute seqno
    uint64_t checkpoint = _reassembler.ack_index();
    uint64_t abs_seqno = unwrap(head.seqno, _isn, checkpoint);
    uint64_t stream_idx = abs_seqno - _synReceived;
    // --- Hint ------

    _reassembler.push_substring(seg.payload().copy(), stream_idx, head.fin);
}

optional<WrappingInt32> TCPReceiver::ackno() const
{
    if (!_synReceived)
    {
        return {};
    }

    return _finReceived ? WrappingInt32(_isn) + stream_out().bytes_written() + 2 : WrappingInt32(_isn) + stream_out().bytes_written() + 1;
}

size_t TCPReceiver::window_size() const
{
    return stream_out().remaining_capacity();
}