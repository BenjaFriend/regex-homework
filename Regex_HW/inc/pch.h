#pragma once

/// <summary>
/// Precompiled header for this program with common libraries/defines that are used
/// </summary>
/// <author>Ben Hoffman ( bah8892@rit.edu )</author>

#include <iostream>
#include <regex>
#include <string>
#include <assert.h>
#include <stdlib.h>  
#include <unordered_map>

/**************************************************************/
/* Platform specifications                                    */
/**************************************************************/
#if defined( _WIN32 ) || defined ( _WIN64 )

typedef std::wstring                FileName;
#define FORCE_INLINE                __forceinline
#define R_UNUSED

#else 

#define FORCE_INLINE                inline
#define R_UNUSED                    __attribute__ ((unused))

#endif

/**************************************************************/
/* Debug Macros                                               */
/**************************************************************/
#if defined( _DEBUG ) || defined ( DEBUG )

#if defined( _WIN32 ) || defined ( _WIN64 )

#define _CRTDBG_MAP_ALLOC   // memory leak detection
#include <crtdbg.h> 

// Debug new macro for tracking exactly where the leaks are
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define new DEBUG_NEW 

#endif  // _WIN32 || _WIN64

#else 

// Define DEBUG_NEW as just new
#define DEBUG_NEW new

#endif  // _DEBUG || DEBUG

/**************************************************************/
/* Util Macros                                                */
/**************************************************************/
#define SAFE_DELETE( obj ) if( obj != nullptr ){ delete obj; obj = nullptr; }  