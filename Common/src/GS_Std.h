#ifndef _GS_STD_H
#define _GS_STD_H

#include <assert.h>
#include <string>

//assert宏
#if defined(_DEBUG)
	
	#define  GS_ASSERT(expression) assert(expression)

#else
	#define  GS_ASSERT(expression)
#endif

//DLL
#ifdef __LINUX__
	#define EXPORT_T 

	#define IMPORT_T 
#endif

#ifdef _WIN32
#define EXPORT_T __declspec (dllexport)

#define IMPORT_T __declspec (dllimport)
#endif

#ifndef _T
#if defined( _UNICODE )
	#define _T(x) L##x
#else
    #define _T(x) x
#endif
#endif

//handle_close,
#define  CUSTOM_MASK (1 << 16)
#define INT_HIGH(x) (unsigned short)((x & 0xffff0000) >> 16)
#define INT_LOW(x)	(unsigned short)(x & 0x0000ffff)
#define MAKE_INT(high,low) (unsigned int )((high << 16) | (low & 0x0000ffff))

//////////////////////////////////////////////////////////////////////////
//类型重定义
namespace GS
{
	typedef unsigned short U_SHORT;

	typedef unsigned char  U_CHAR;

	typedef unsigned int   U_INT;

#if defined(_UNICODE)
	typedef wchar_t  TCHAR;
	typedef std::basic_string<char>   tstring;
#else
	typedef char     TCHAR;
	typedef std::basic_string<wchar_t> tstring;
#endif

	typedef unsigned int	ID;

	typedef unsigned int	SOCKET_ID;
}

#endif
