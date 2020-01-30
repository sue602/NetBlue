/*
 * ByteArray.h
 *
 *  Created on: Jan 30, 2020
 *      Author: ltzd
 */

#pragma once
#ifndef _BYTE_ARRAY_
#define _BYTE_ARRAY_

#include <stdio.h>
#include <vector>
#include <string>
#include <memory.h>
#include <math.h>
using namespace std;

const unsigned int MAXMSGSIZE		= 16 * 1024;                    // 16K  单个网络消息最大长度,(超过极易导致物理服务器收发队列阻塞)
const unsigned int INCRSIZE			= 2 * 1024;                    // 2K  每次增量

class ByteArray
{
public:
	ByteArray(unsigned int mBufferSize = MAXMSGSIZE);
	virtual ~ByteArray();

	void print();
	void resize(unsigned int mLength);
	void reuse(){ m_nRdptr = 0; m_nWrPtr = 0;}
public:
	short readInt16();								// 从字节流读取16位整形
	unsigned short readUint16();      // 从字节流读取16位无符号整形

	int	readInt();									// 从字节流读取32位整形
	unsigned int readUint();						// 从字节流读取32位整形

	long long readInt64();							// 从字节流读取64位整形
	unsigned long long readUint64();				// 从字节流读取64位无符号整形

	short readShort();								// 从字节流读取短整形
	unsigned short readUshort();					// 从字节流读取无符号短整形

	long readLong();								// 从字节流读取长整形
	unsigned long readUlong();						// 从字节流读取无符号长整形

	char readChar();						// 从字节流读取字符
    char readByte();						// 从字节流读取字符
	unsigned char  readUchar();					// 从字节流读取无符号字符整数

	bool readBool();                     // 从字节流读取Bool值

	float readFloor();                    // 从字节流读取浮点数
	double readDouble();                   // 从字节流读取双精度数

	char * readString(char* info, unsigned int len); // 从字节流读取字符串
	std::string readString();                   // 从字节流读取字符串
	void writeInt(int);                  // 向字节流写32位整形
	void writeUint(unsigned int);        // 向字节流写32位无符号整形

    void * readStream(int &mLength);//往字节流读出数据
    void writeStream(void * mChars,int mLength);//向字节流写入数据
	void writeInt16(short);              // 向字节流写16位整形
	void writeUint16(unsigned short);              // 向字节流写16位无符号整形

	void writeInt64(long long);           // 向字节流写64位整形
	void writeUint64(unsigned long long); // 向字节流写64位无符号整形

	void writeShort(short);                // 向字节流写短整
	void writeUshort(unsigned short);              // 向字节流写无符号短整

	void writeLong(long);                  // 向字节流写长整
	void writeUlong(unsigned long);        // 向字节流写无符号长整

	void writeChar(char);                  // 向字节流写字符型
    void writeByte(char);                  // 向字节流写字符型
	void writeUchar(unsigned char);        // 向字节流写无符号字符型整数

	void writeBool(bool);                  // 向字节流写布尔型

	void writeFloat(float);                // 向字节流写浮点数
	void writeDouble(double);              // 向字节流写双精度数

	void writeString(const char* str);     // 向字节流写字符串
	void writeString(const std::string& str); // 向字节流写字符串

	int length() const;                    //字节流当前长度
	void setTag(int t);
	int getTag();
	void setCmdType(int _t);
	int getCmdType();
    void setStatus(char mStatus);
    char getStatus();
	void setAction(int mAction);
	int getAction();

public:
	char* base() const;//字节流内部实现
	char* end(void) const;
	char* rdPtr(void) const;
	char* wrPtr(void);
	void rdPtr(int n);
	void wrPtr(int n);
	unsigned int space();
	int copy(const char *buf, int n);
	void rdSkip(int mBytes); //skip read bytes

private:
	int mTag;
	int mCmdType;
    char mStatus;
	int mAction;

private:

    void * memcpy(void * dst, void const * src, size_t len)
    {
        char * pDst = (char *) dst;
        char const * pSrc = (char const *) src;

        while (len--)
        {
            *pDst++ = *pSrc++;
        }

        return (dst);
    }

	template<typename T> friend ByteArray& operator>>(ByteArray& msg, T& v)     //运算符重载
	{
		msg.Read(&v);
		return msg;
	}

	friend ByteArray& operator>>(ByteArray& msg, std::string& str)
	{
		str = msg.readString();
		return msg;
	}

	template<typename T> friend ByteArray& operator<<(ByteArray& msg, const T& v)
	{
		msg.Write(v);
		return msg;
	}

	friend ByteArray& operator<<(ByteArray& msg, const std::string& str)
	{
		msg.writeString(str);
		return msg;
	}

	template<typename T>
	T& Read(T* pVar,bool readonly=false)
	{
        this->memcpy((char*)(pVar),(char*)(m_pContent + m_nRdptr), sizeof(T));//to avoid EXC_ARM_DA_ALIGN error
		if(!readonly)//添加只读，不移指针支持，为了调试，Mike
			rdPtr(sizeof(T));
		return *pVar;
	}

	template<typename T>
	void Write(const T& value)
    {
        this->memcpy((char*)(m_pContent + m_nWrPtr),(char *)(&value), sizeof(T));//to avoid EXC_ARM_DA_ALIGN error
		wrPtr(sizeof(T));
	}

private:
	char* m_pContent;                               //字节流内容指针
	unsigned int  m_nTotalSize;                     //字节流允许大小
	int   m_nRdptr;                                 //读取位置
	int   m_nWrPtr;                                 //写入位置
};

#endif
