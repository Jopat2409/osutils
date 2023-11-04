
#ifndef OSU_API_H
#define OSU_API_H

#ifdef OSUTILS_STATIC_DEFINE
#  define OSU_API
#  define OSUTILS_NO_EXPORT
#else
#  ifndef OSU_API
#    ifdef osutils_EXPORTS
        /* We are building this library */
#      define OSU_API __declspec(dllexport)
#    else
        /* We are using this library */
#      define OSU_API __declspec(dllimport)
#    endif
#  endif

#  ifndef OSUTILS_NO_EXPORT
#    define OSUTILS_NO_EXPORT 
#  endif
#endif

#ifndef OSUTILS_DEPRECATED
#  define OSUTILS_DEPRECATED __declspec(deprecated)
#endif

#ifndef OSUTILS_DEPRECATED_EXPORT
#  define OSUTILS_DEPRECATED_EXPORT OSU_API OSUTILS_DEPRECATED
#endif

#ifndef OSUTILS_DEPRECATED_NO_EXPORT
#  define OSUTILS_DEPRECATED_NO_EXPORT OSUTILS_NO_EXPORT OSUTILS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OSUTILS_NO_DEPRECATED
#    define OSUTILS_NO_DEPRECATED
#  endif
#endif

#endif /* OSU_API_H */
