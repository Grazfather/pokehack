#ifndef POKEHACK_CONFIG_H
#define POKEHACK_CONFIG_H

//define cross platform attribute macros
#if defined(_MSC_VER)
    #define POKEHACK_EXPORT         __declspec(dllexport)
    #define POKEHACK_IMPORT         __declspec(dllimport)
    #define POKEHACK_INLINE         __forceinline
    #define POKEHACK_DEPRECATED     __declspec(deprecated)
    #define POKEHACK_ALIGNED(x)     __declspec(align(x))
#elif defined(__GNUG__) && __GNUG__ >= 4
    #define POKEHACK_EXPORT         __attribute__((visibility("default")))
    #define POKEHACK_IMPORT         __attribute__((visibility("default")))
    #define POKEHACK_INLINE         inline __attribute__((always_inline))
    #define POKEHACK_DEPRECATED     __attribute__((deprecated))
    #define POKEHACK_ALIGNED(x)     __attribute__((aligned(x)))
#else
    #define POKEHACK_EXPORT
    #define POKEHACK_IMPORT
    #define POKEHACK_INLINE         inline
    #define POKEHACK_DEPRECATED
    #define POKEHACK_ALIGNED(x)
#endif

// Define API declaration macro
#ifdef POKEHACK_DLL_EXPORTS
    #define POKEHACK_API POKEHACK_EXPORT
#else
    #define POKEHACK_API POKEHACK_IMPORT
#endif // POKEHACK_DLL_EXPORTS

#endif /* POKEHACK_CONFIG_H */
