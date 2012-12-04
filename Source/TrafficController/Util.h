/*
 * Contains cross-platform ulity functions
 */

#ifndef TC_UTIL_H
#define TC_UTIL_H

// Preprocessor, checking for multiple defines (add as wanted!)
#if (defined _WIN32 || defined _WIN64)
  #define TC_WINDOWS 1
#elif (defined __linux  || defined __linux__ || defined __gnu_linux__)
  #define TC_LINUX 1
#else
  #error "Unknown Platform!"
#endif


/*
 * Generic sleep function in miliseconds
 */
inline void TC_Sleep( unsigned int t)
{
#if TC_WINDOWS
    Sleep( t);
#elif TC_LINUX
    usleep( t * 1000);
#endif
}

/*
 * Get time function TODO actually do it
 */


#endif // TC_UTIL_H
