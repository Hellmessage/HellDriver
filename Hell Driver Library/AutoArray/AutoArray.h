#ifndef __HELL_AUTOARRAY_HEADER__
#define __HELL_AUTOARRAY_HEADER__


#include <stdio.h>

typedef struct _string_set {
    char* buf;
    int size;
    int length;
    int* index;
} StringSet;
typedef StringSet* PSTRINGSET;





#endif // !__HELL_AUTOARRAY_HEADER__
