//============================================================================
// Name        : ByteArray.cpp
// Author      : Su YinXiang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ByteArray.h"

char writer[MAXMSGSIZE] = "\0";

ByteArray::ByteArray(unsigned int mBufferSize):
		mCmdType(0),
		mStatus(0),
		mAction(0)
{
	m_pContent = new char[mBufferSize];
	memset(m_pContent, 0, mBufferSize);
	m_nTotalSize = mBufferSize;
	m_nRdptr = 0;
	m_nWrPtr = 0;
	mTag = -1;
}

ByteArray::~ByteArray()
{
    delete[] m_pContent;
}

void ByteArray::print()
{
	unsigned short *p = (unsigned short*)(rdPtr() + 2);
	printf("ByteArray:%d\n", p[0]);
}

void ByteArray::resize(unsigned int mLength)
{
	int tmpLength = this->length();
	char *tmpContent = m_pContent;

	m_nTotalSize  += INCRSIZE ;
	while (m_nTotalSize < mLength) {
		m_nTotalSize += INCRSIZE;
	}

	m_pContent = new char[m_nTotalSize];
	memset(m_pContent,0,m_nTotalSize);
	this->memcpy(m_pContent, tmpContent, tmpLength);

	delete[] tmpContent;
	tmpContent = NULL;
}

char* ByteArray::base() const
{
	return m_pContent;
}

char* ByteArray::end(void) const
{
	return m_pContent + m_nTotalSize;
}

char* ByteArray::rdPtr(void) const
{
	return m_pContent + m_nRdptr;
}

void ByteArray::rdPtr(int n)
{
	m_nRdptr +=n;
}

char* ByteArray::wrPtr(void)
{
	return base() + m_nWrPtr;
}

void ByteArray::wrPtr(int n)
{
	m_nWrPtr += n;
}

unsigned int ByteArray::space()
{
	return m_nTotalSize - m_nWrPtr;
}

int ByteArray::length() const
{
	return m_nWrPtr - m_nRdptr;
}

int   ByteArray::copy(const char *buf, int n)
{
	int len = this->space();

	if(len < n)
	{
		this->resize(n);
	}

	this->memcpy(this->wrPtr(), buf, n);
	this->wrPtr(n);
	return 0;

}

void ByteArray::rdSkip(int mBytes)
{
	rdPtr(mBytes);
}

short ByteArray::readInt16()
{
	short w = 0;
	Read(&w);
	return w;
}

unsigned short ByteArray::readUint16()
{
	unsigned short w = 0;
	Read(&w);
	return w;
}

int ByteArray::readInt()
{
	int w = 0;
	Read(&w);
	return w;
}

unsigned int ByteArray::readUint()
{
	unsigned int w = 0;
	Read(&w);
	return w;
}

long long ByteArray::readInt64()
{
	long long w = 0;
	Read(&w);
	return w;
}

unsigned long long ByteArray::readUint64()
{
	unsigned long long w = 0;
	Read(&w);
	return w;
}

short ByteArray::readShort()
{
	short w = 0;
	Read(&w);
	return w;
}

unsigned short ByteArray::readUshort()
{
	unsigned short w = 0;
	Read(&w);
	return w;
}

long ByteArray::readLong()
{
	long w = 0;
	Read(&w);
	return w;
}

unsigned long ByteArray::readUlong()
{
	unsigned long w = 0;
	Read(&w);
	return w;
}

char ByteArray::readChar()
{
	char w = 0;
	Read(&w);
	return w;
}

char ByteArray::readByte()
{
	char w = 0;
	Read(&w);
	return w;
}

unsigned char ByteArray::readUchar()
{
	unsigned char w = 0;
	Read(&w);
	return w;
}

bool ByteArray::readBool()
{
	bool w = 0;
	Read(&w);
	return w;
}

float ByteArray::readFloor()
{
	float w = 0;
	Read(&w);
	return w;
}

double ByteArray::readDouble()
{
	double w = 0;
	Read(&w);
	return w;
}

char* ByteArray::readString(char* info, unsigned int len)
{
	char* result = (char*)(this->memcpy(info, rdPtr(), len));
	rdPtr(len);
	return result;
}

std::string ByteArray::readString()
{
	unsigned short len = readUint16();
	std::string strValue(rdPtr(), len);
	rdPtr(len);
	return strValue;
}

void ByteArray::writeInt(int value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(int);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeUint(unsigned int value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(unsigned int);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void * ByteArray::readStream(int &mLength)
{
	mLength = readInt();
    void * readPtr = this->rdPtr();
    rdPtr(mLength);
    return readPtr;
}

void ByteArray::writeStream(void * mChars,int mLength)
{
    unsigned int len = this->space();
    unsigned int n = mLength + sizeof(int);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

    writeInt(mLength);
    copy((const char*)mChars, mLength);
}

void ByteArray::writeInt16(short value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(short);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeUint16(unsigned short value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(unsigned short);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeInt64(long long value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(long long);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeUint64(unsigned long long value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(unsigned long long);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeShort(short value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(short);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeUshort(unsigned short value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(unsigned short);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeLong(long value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(long);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeUlong(unsigned long value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(unsigned long);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeChar(char value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(char);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeByte(char value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(char);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeUchar(unsigned char value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(unsigned char);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeBool(bool value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(bool);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeFloat(float value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(float);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void ByteArray::writeDouble(double value)
{
    unsigned int len = this->space();
    unsigned int n = sizeof(double);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}

	Write(value);
}

void  ByteArray::writeString(const char* str)
{
	writeString(std::string(str));
}

void  ByteArray::writeString(const std::string& str)
{
    unsigned int len = this->space();
    unsigned int n = str.length() + sizeof(unsigned short);
	if(len < n)
	{
		this->resize(n + m_nTotalSize);
	}
	writeUint16(static_cast<unsigned short>(str.length()));
	copy(str.data(), str.length());
}

void ByteArray::setTag(int t)
{
	mTag = t;
}

int  ByteArray::getTag()
{
	return mTag;
}
void ByteArray::setCmdType(int _t)
{
	mCmdType = _t;
}

int ByteArray::getCmdType()
{
	return mCmdType;
}

void ByteArray::setStatus(char status)
{
	mStatus = status;
}

char ByteArray::getStatus()
{
	return  mStatus;
}

void ByteArray::setAction(int action)
{
	mAction = action ;
}

int  ByteArray::getAction()
{
	return mAction;
}
