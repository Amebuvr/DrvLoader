#include "binded_str.h"

using namespace DrvLoaderCLR;

binded_str::~binded_str()
{
    if (data != NULL)
    {
        free(data);
        data = NULL;
    }
}
