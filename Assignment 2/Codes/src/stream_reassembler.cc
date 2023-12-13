#include "stream_reassembler.hh"

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity)
{
    bufferCapacity = capacity;
}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof)
{
    size_t len = data.size();

    if (_output.remaining_capacity() == 0)
    {
        return;
    }

    else if (index == ack_index())
    {
        size_t i = 0;
        size_t indexx = index;
        if (_output.remaining_capacity() >= len)
        {
            while (i < len)
            {
                buffer.erase(indexx);
                _output.write(string(1, data[i]));
                ++i;
                ++indexx;
                ++acknowledgementIndex;
            }
        }

        else
        {
            size_t currentCapacity = _output.remaining_capacity();
            while (i < currentCapacity)
            {
                buffer.erase(indexx);
                _output.write(string(1, data[i]));
                ++i;
                ++indexx;
                ++acknowledgementIndex;
            }
        }

        if (eof)
        {
            _output.end_input();
        }
    }

    else if (index + len > ack_index() && index < ack_index())
    {
        bool lastByte = false;
        size_t i = ack_index() - index - 1;
        while (i < len)
        {
            lastByte = checkAndInsert(data, index, eof, lastByte, i, len);
            ++i;
        }
    }

    else
    {
        pushToBuffer(data, index, eof, len);
    }

    checkBuffer();
}

size_t StreamReassembler::unassembled_bytes() const
{
    return buffer.size();
}

bool StreamReassembler::empty() const
{
    return buffer.empty();
}

size_t StreamReassembler::ack_index() const
{
    return acknowledgementIndex;
}

void StreamReassembler::checkBuffer()
{
    while (!empty() && buffer.find(ack_index()) != buffer.end())
    {
        if (_output.remaining_capacity() > 0)
        {
            auto it = buffer.find(ack_index());
            _output.write(string(1, buffer.find(ack_index())->second.first));
            ++acknowledgementIndex;
            buffer.erase(it);

            if (it->second.second)
            {
                _output.end_input();
            }
        }

        else
        {
            break;
        }
    }
}

void StreamReassembler::pushToBuffer(const string &data, const size_t index, const bool eof, const size_t len)
{
    size_t i = 0;
    bool lastByte = false;
    if (_output.remaining_capacity() >= len)
    {
        while (i < len)
        {
            lastByte = checkAndInsert(data, index, eof, lastByte, i, len);
            ++i;
        }
    }

    else
    {
        while (i < _output.remaining_capacity())
        {
            lastByte = checkAndInsert(data, index, eof, lastByte, i, len);
            ++i;
        }
    }
}

bool StreamReassembler::checkAndInsert(const std::string &data, const size_t index, const bool eof, const bool lastByte, const size_t i, const size_t len)
{
    size_t indexx = i + index;
    if (lastByte || len == 1)
    {
        buffer.insert(make_pair(indexx, make_pair(data[i], eof))).second;
    }

    else
    {
        buffer.insert(make_pair(indexx, make_pair(data[i], false))).second;

        if (len - 2 == i)
        {
            return true;
        }
    }

    return false;
}