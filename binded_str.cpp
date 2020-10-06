#include "binded_str.h"

using namespace DrvLoader;

binded_str::~binded_str()
{
    if (data != NULL)
    {
        free(data);
        data = NULL;
    }
}
