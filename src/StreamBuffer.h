#pragma once

#include <istream>
#include <cstdint>

#include "Buffer.h"

namespace Units
{
	class StreamBuffer : public Buffer
	{
	private:
		std::istream& is;
		char curr_char;

	public:
		StreamBuffer(std::istream& s) : is(s), curr_char(0) { curr_char = (char)is.get(); }
		~StreamBuffer() = default;

		char current() override { return curr_char; }
		char ahead  () override { char c = (char)is.peek(); return c != EOF ? c : EOF_MARK; }

		char advance(bool skipws = false) override
		{
			if(current() == EOF_MARK) return EOF_MARK;

			curr_char = (char)is.get();

			if(skipws)
			{
				while(curr_char == ' ')
					curr_char = (char)is.get();
			}

			return current();
		}
	};
}
