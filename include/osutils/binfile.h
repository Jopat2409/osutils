/***
 * File created to make reading binary data from files easier.
 * Provides methods to read most common types
*/
#ifndef _INTERNAL_BASEFILE_H
#define _INTERNAL_BASEFILE_H

#include <fstream>
#include <cstdint>
#include <string.h>
#include <intrin.h>
#include <iostream>

#include "type.h"

#define MAX_FILE_BUFFER 8192
#define FREE_STR(x) if(x) delete x;

typedef enum {
	LITTLE_ENDIAN = 0,
	BIG_ENDIAN = 1
} endianness_t;

class BinaryFile {
public:

	BinaryFile(endianness_t type = LITTLE_ENDIAN);
    ~BinaryFile();

    bool Open(const char* path);
	bool Open(std::string& path);
	void Close();


	static bool CheckPath(const char* path);
	void SetLastError(const char* error);
	const char* GetLastError();

	template <typename T>
	inline void LoadType(T& dest) {
		CheckSize(sizeof(T));
		dest = ReverseEndianness(*(T*)(this->inputStream + this->cPtr));
		this->cPtr += sizeof(T);
	}
	template <typename T>
	inline T LoadType() {
		CheckSize(sizeof(T));
		this->cPtr += sizeof(T);
		return ReverseEndianness(*(T*)(this->inputStream + this->cPtr - sizeof(T)));
	}

	unsigned long LoadULEB128();
    unsigned long LoadLEB128();
	void LoadString(char*& dest);

	void LoadIntDoublePair(Osu::int_double_t& dest);

protected:
	inline char* GetCurrentPtr() { return inputStream + cPtr; };
	//void LoadString(const char*& dest);
	//const char* LoadString();
	inline size_t GetReadBytes() { return readBytes; };
private:
	unsigned long cPtr{0};
	char* inputStream{nullptr};
	std::ifstream* inputFile{nullptr};
	size_t readBytes{ 0 };
	size_t initialSize{ 0 };
	bool isOpen{ false };

	endianness_t c_endianness;

	void LoadBytes(int byteOffset = 0);
	void CheckSize(size_t size);

	template <typename T>
	inline T ReverseEndianness(T val) {
		if (c_endianness == LITTLE_ENDIAN)
			return val;
		switch (sizeof(val)) {
		case 1:
			return val;
		case 2:
			return _byteswap_ushort(val);
		case 4:
			return _byteswap_ulong(val);
		case 8:
			return _byteswap_uint64(val);
		default:
			return val;
		}
	}

	const char* m_lastError;
};

inline BinaryFile::BinaryFile(endianness_t type)
{
    c_endianness = type;
}
inline BinaryFile::~BinaryFile()
{
    if(this->isOpen)
        this->Close();
}

inline bool BinaryFile::Open(const char* path)
{
    /***
     * Opens a binary file for reading. Loads the first bytes from the file as defined by
     * MAX_FILE_BUFFER (Should be 8192 bytes)
    */
    if(this->isOpen)
    {
        SetLastError("[WARNING] Binary file is already open");
        return false;
    }
    if(!CheckPath(path))
    {
        SetLastError("[ERROR] Path to file does not exist");
        return false;
    }
    // Load the file and read enough bytes to fit the input buffer
	this->inputFile = new std::ifstream(path, std::ios_base::in | std::ios_base::binary);
	this->LoadBytes();

	this->isOpen = true;
	return true;

}

inline bool BinaryFile::Open(std::string& path) {
	return Open(path.c_str());
}

inline void BinaryFile::Close()
{
    if (this->isOpen)
	{
		// delete input char buffer
		delete this->inputStream;
		// close input stream
		this->inputFile->close();
		delete this->inputFile;
		this->isOpen = false;
	}
}

inline bool BinaryFile::CheckPath(const char* path)
{
    /***
     * Checks that a given path leads to an actual file
     * Returns true if the file exists, else returns false
    */
    if (FILE* f = fopen(path, "r"))
    {
		fclose(f);
		return true;
	}
	return false;
}

inline void BinaryFile::SetLastError(const char* error)
{
    m_lastError = error;
};
inline const char* BinaryFile::GetLastError()
{
    return m_lastError;
};

inline unsigned long BinaryFile::LoadULEB128()
{
	/* unsigned long total = 0;
	int currentShift = 0;
	char currentByte = 0;
	do {
		LoadType<char>(currentByte);
		total |= (currentByte & ~(1 << 7)) << currentShift;
		currentShift += 7;
	} while (currentByte & (1 << 7));
	return total; */
	unsigned long dest = 0;
	int shift = 0;
	int count = 0;
	while (1) {
		Osu::byte_t tempByte;
		LoadType<Osu::byte_t>(tempByte);
		dest |= (tempByte & 0x7f) << shift;
		if (!(tempByte & 0x80)) break;
		shift += 7;
	}
	return dest;
}

inline unsigned long BinaryFile::LoadLEB128()
{
    // TODO: implement please :D
    return 0;
}

inline void BinaryFile::LoadString(char*& dest)
{
	Osu::byte_t present;
	LoadType<Osu::byte_t>(present);
	if(present == OSU_STRING_PRESENT_BYTE)
	{
		unsigned long stringLength = LoadULEB128();
		CheckSize(stringLength);
		dest = new char[stringLength + 1]();
		memcpy_s(dest, stringLength + 1, this->inputStream + this->cPtr, stringLength);
		this->cPtr += stringLength;
	}
	else{
		dest = nullptr;
	}

}

inline void BinaryFile::LoadBytes(int byteOffset)
{
    // if initial size has not yet been determined
	if (!this->initialSize)
	{
		// go to end of file, get bytes and then set initial size
		this->inputFile->seekg(0, std::ios::end);
		size_t sizeLeft = this->inputFile->tellg();
		this->inputFile->seekg(0, std::ios::beg);
		this->initialSize = sizeLeft;
		// initialise input stream
		this->inputStream = new char[MAX_FILE_BUFFER]();
	}
	// bytes left in file
	size_t bytesLeft = this->initialSize - this->readBytes;
	// accounting for byte offset meaning slightly less bytes can be read
	size_t maxBufferSize = MAX_FILE_BUFFER - byteOffset;
	// set the length to read to either MAX_FILE_BUFFER - offset or simply to the amount of bytes left
	size_t length = maxBufferSize * (maxBufferSize <= bytesLeft) + bytesLeft * (bytesLeft < maxBufferSize);
	// read amount of bytes and add to length
	this->inputFile->read(&this->inputStream[byteOffset], length);
	this->readBytes += length;
}

inline void BinaryFile::CheckSize(size_t size)
{
    // bytes left in current buffer
	unsigned long bytesLeft = MAX_FILE_BUFFER - this->cPtr;
	// if there are less bytes left than bytes in object
	if (bytesLeft < size)
	{
		memcpy_s(this->inputStream, bytesLeft, &this->inputStream[this->cPtr], bytesLeft);
		// set cPtr to 0 and load bytes from the byte offset
		this->cPtr = 0;
		this->LoadBytes(bytesLeft);
	}
}

inline void BinaryFile::LoadIntDoublePair(Osu::int_double_t& dest)
{
	Osu::int_t numIntDoublePairs = LoadType<Osu::int_t>();
	for(int i = 0; i < numIntDoublePairs; i++)
	{
		Osu::byte_t checkByte;
		LoadType<Osu::byte_t>(checkByte);
		Osu::int_t modCombo = LoadType<Osu::int_t>();
		LoadType<Osu::byte_t>(checkByte);
		Osu::double_t starRating = LoadType<Osu::double_t>();
		dest[modCombo] = starRating;
	}
}

#endif
