// defines.h: interface for the Cdefines class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFINES_H__CE8DC853_F125_4758_A264_94CA9A9E5B5F__INCLUDED_)
#define AFX_DEFINES_H__CE8DC853_F125_4758_A264_94CA9A9E5B5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////////
#ifndef WIN32
#	ifdef _WIN32
#		define WIN32
#	endif
#endif

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#ifndef _WIN32_WINNT
#   define _WIN32_WINNT 0x400
#endif

#include <windows.h>
#include <direct.h>

#   ifdef _MSC_VER
//     '...' : forcing value to bool 'true' or 'false' (performance warning)
#      pragma warning( disable : 4800 )
//     ... identifier was truncated to '255' characters in the debug information
#      pragma warning( disable : 4786 )
//     'this' : used in base member initializer list
#      pragma warning( disable : 4355 )
//     class ... needs to have dll-interface to be used by clients of class ...
#      pragma warning( disable : 4251 )
//     ... : inherits ... via dominance
#      pragma warning( disable : 4250 )
//     non dll-interface class ... used as base for dll-interface class ...
#      pragma warning( disable : 4275 )
//      ...: decorated name length exceeded, name was truncated
#      pragma warning( disable : 4503 )  
#   endif

///////////////////////////////////////////////////////////////////////////////////
#else  //linux
///////////////////////////////////////////////////////////////////////////////////
typedef unsigned long       DWORD;
typedef int                 BOOL;

#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>			//mkdir, access
#include <dirent.h>			//DIR, dirent, opendir, readdir, closedir

#endif
///////////////////////////////////////////////////////////////////////////////////
//
// Endianness
//
// Most CPUs support only one endianness, with the notable exceptions
// of Itanium (IA64) and MIPS.
//
#if defined(__i386)     || defined(_M_IX86) || defined(__x86_64)  || \
    defined(_M_X64)     || defined(_M_IA64) || defined(__alpha__) || \
    defined(__MIPSEL__)
#   define UP_LITTLE_ENDIAN
#elif defined(__sparc) || defined(__sparc__) || defined(__hppa)      || \
    defined(__ppc__) || defined(__powerpc) || defined(_ARCH_COM) || \
    defined(__MIPSEB__)
#   define UP_BIG_ENDIAN
#else
#   error "Unknown architecture"
#endif

//
// 32 or 64 bit mode?
//
#if defined(__linux) && defined(__sparc__)
//
// We are a linux sparc, which forces 32 bit usr land, no matter 
// the architecture
//
#   define  UP_32
#elif defined(__sun) && (defined(__sparcv9) || defined(__x86_64))  || \
    defined(__linux) && defined(__x86_64)                        || \
    defined(__hppa) && defined(__LP64__)                         || \
    defined(_ARCH_COM) && defined(__64BIT__)                     || \
    defined(__alpha__)                                           || \
    defined(_WIN64)
#   define UP_64
#else
#   define UP_32
#endif
//
// Int64 typedef
//
#if defined(__BCPLUSPLUS__) || defined(_MSC_VER)
//
// On Windows, long is always 32-bit
//
typedef __int64 Int64;
#elif defined(UP_64)
typedef long Int64;
#else
typedef long long Int64;
#endif

//
// UP_INT64: macro for Int64 literal values
//
#if defined(__BCPLUSPLUS__) || defined(_MSC_VER)
#   define UP_INT64(n) n##i64
#elif defined(UP_64)
#   define UP_INT64(n) n##L
#else
#   define UP_INT64(n) n##LL
#endif
///////////////////////////////////////////////////////////////////////////////////

#ifndef ETHERTYPE_IP
# define ETHERTYPE_IP 0x0800
#endif

#ifndef ETHERTYPE_IPV6
# define ETHERTYPE_IPV6 0x86dd
#endif

///////////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_DEFINES_H__CE8DC853_F125_4758_A264_94CA9A9E5B5F__INCLUDED_)
