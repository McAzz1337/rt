#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef _DEBUG

#define LOG(x) printf("%s:%i\t%s\n", __FILE__, __LINE__, x)
#define CALL(x) printf("%s:%i\t%s\n", __FILE__, __LINE__, #x); x

#elif

#define LOG(x)
#define CALL(x)

#endif




#endif // DEBUG_H
