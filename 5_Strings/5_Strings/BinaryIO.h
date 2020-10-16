#pragma once;
#include <fstream>
#include <string>
#include <stdexcept>

namespace BinaryIO
{
	class file_didnt_exist : std::logic_error
	{
	public:
		file_didnt_exist(const char* s) : std::logic_error(s){}
	};

	class BinaryInput
	{
	private:
		std::ifstream input;
		char byteBuffer;
		unsigned long long bitCount = 0;
		bool endFlag = 0;
	public:
		BinaryInput(std::string file)
			:input(file, std::ios::binary)
		{
			if (!input) throw file_didnt_exist("havn't file");
		}

		~BinaryInput()
		{
			close();
		}

		void close() 
		{
			endFlag = 1;
			bitCount = 0;
			input.close();
		}

		bool isEnd()
		{
			return endFlag;
		}

		char readChar()
		{
			char c = 0;
			for (int i = 6; i >= 0; --i)
				c |= readBit() << i;
			return c;
		}

		unsigned char readUChar()
		{
			unsigned char c = 0;
			for (int i = 7; i >= 0; --i)
				c |= readBit() << i;
			return c;
		}

		unsigned readUInt() {
			unsigned c = 0;
			for (int i = 31; i >= 0; --i)
				c |= readBit() << i;
			return c;
		}

		char readByte()
		{
			if (bitCount % 8 == 0) {
				if (!input.read(&byteBuffer, 1)) endFlag = true;
				bitCount += 8;
			}
			else {
				bitCount += 8 - bitCount % 8;
			}
			return byteBuffer;
		}

		bool readBit()
		{
			if (bitCount % 8 == 0)
				if (!input.read(&byteBuffer, 1))
					endFlag = true;
			return (byteBuffer & (1 << (7 - bitCount++ % 8))) != 0;
		}

		operator bool() const
		{
			return !endFlag;
		}

		BinaryInput& operator>>(char& c)
		{
			c = readByte();
			return *this;
		}

		BinaryInput& operator>>(bool& c)
		{
			c = readBit();
			return *this;
		}
	};

	class BinaryOutput
	{
	private:
		std::ofstream output;
		char byteBuffer = 0;
		unsigned long long bitCount = 0;
	public:
		BinaryOutput(std::string file)
			:output(file, std::ios::binary)
		{
			if (!output) throw file_didnt_exist("havn't file");
		}

		~BinaryOutput()
		{
			close();
		}

		void close()
		{
			if (bitCount % 8 != 0)
				output.write(&byteBuffer, 1);
			bitCount = 0;
			output.close();
		}

		void writeChar(char byte)
		{
			for (int i = 6; i >= 0; --i)
				writeBit(byte & (1 << i));
		}

		void writeUChar(unsigned char byte)
		{
			for (int i = 7; i >= 0; --i)
				writeBit(byte & (1 << i));
		}

		void writeUInt(unsigned ui)
		{
			for (int i = 31; i >= 0; --i)
				writeBit(ui & (1 << i));
		}

		void writeByte(char byte)
		{
			if (bitCount % 8 != 0) {
				output.write(&byteBuffer, 1);
				byteBuffer = 0;
				bitCount += 8 - bitCount % 8;
			}
			output.write(&byte, 1);
		}

		void writeBit(bool bit)
		{
			byteBuffer |= bit << (7 - bitCount++ % 8);
			if (bitCount % 8 == 0) {
				output.write(&byteBuffer, 1);
				byteBuffer = 0;
			}
		}

		BinaryOutput& operator << (char c)
		{
			writeByte(c);
			return *this;
		}

		BinaryOutput& operator << (bool b)
		{
			writeBit(b);
			return *this;
		}

	};

}