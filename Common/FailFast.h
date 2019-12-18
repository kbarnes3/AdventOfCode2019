#pragma once
#include <intrin.h>

__declspec(noreturn)
inline void FAIL_FAST()
{
    __fastfail(1);
}
