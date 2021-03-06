#pragma once
#include "windows.h"
#include "vcclr.h"

namespace DrvLoader
{
    using namespace System;

    ref class binded_str
    {
        PWSTR data;
        String^ data_str;

    public:
        binded_str()
        {
            data = NULL;
        };
        ~binded_str();

        operator String ^ () { return data_str; }
        operator PWSTR() { return data; }

        binded_str^ operator=(String^ source)
        {
            data_str = source;
            this->~binded_str();
            pin_ptr<const WCHAR> s = PtrToStringChars(source);
            size_t len = wcslen(s) + 1;
            data = (PWSTR)malloc(len * sizeof(WCHAR));
            if (data != NULL)
            {
                wcscpy_s(data, len, s);
            }
            return this;
        }

        property size_t Length
        {
            size_t get()
            {
                if (data != NULL)
                {
                    return wcslen(data);
                }
                else
                {
                    return 0;
                }
            }
        }
    };
} // namespace DrvLoader
