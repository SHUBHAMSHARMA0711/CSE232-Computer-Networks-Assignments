#include "byte_stream.hh"
#include <algorithm>

using namespace std;

ByteStream::ByteStream(const size_t capa)
{
	streamCapacity = capa;
}

size_t ByteStream::write(const string &data)
{
	if (error() || ended)
	{
		return 0;
	}

	size_t dataWritten = 0;
	size_t streamSizeBeforeNewData = remaining_capacity();

	for (size_t i = 0; i < (data.length() < streamSizeBeforeNewData ? data.length() : streamSizeBeforeNewData); ++i)
	{
		++written;
		++dataWritten;
		stream.emplace_back(data[i]);
	}

	return dataWritten;
}

string ByteStream::peek_output(const size_t len) const
{
	if (error())
	{
		return "";
	}

	string str = "";

	for (size_t i = 0; i < len; ++i)
	{
		str += stream[i];
	}

	return str;
}

void ByteStream::pop_output(const size_t len)
{
	if (error())
	{
		return;
	}

	if (len > stream.size() || len > streamCapacity)
	{
		set_error();
		return;
	}

	for (size_t i = 0; i < len && !stream.empty(); ++i)
	{
		stream.pop_front();
		++readd;
	}
}

std::string ByteStream::read(const size_t len)
{
	if (error())
	{
		return "";
	}

	if (len > stream.size() || len > streamCapacity)
	{
		set_error();
		return "";
	}

	string str = peek_output(len);
	pop_output(len);

	return str;
}

void ByteStream::end_input()
{
	ended = true;
}

bool ByteStream::input_ended() const
{
	return ended;
}

size_t ByteStream::buffer_size() const
{
	return stream.size();
}

bool ByteStream::buffer_empty() const
{
	return stream.empty();
}

bool ByteStream::eof() const
{
	return ended && stream.empty();
}

size_t ByteStream::bytes_written() const
{
	return written;
}

size_t ByteStream::bytes_read() const
{
	return readd;
}

size_t ByteStream::remaining_capacity() const
{
	return streamCapacity - stream.size();
}