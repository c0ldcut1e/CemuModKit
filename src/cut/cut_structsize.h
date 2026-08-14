#pragma once

#include <assert.h>
#include <stddef.h>

// Ensure structs are correct size & offsets
#define CUT_CHECK_SIZE(Type, Size) static_assert(sizeof(Type) == Size, #Type " must be " #Size " bytes")
#define CUT_CHECK_OFFSET(Type, Offset, Field)                                                                                                        \
    static_assert(offsetof(Type, Field) == Offset, #Type "::" #Field " must be at "                                                                  \
                                                         "offset " #Offset)

// Workaround weird macro concat ## behaviour
#define CUT_PP_CAT(a, b)        CUT_PP_CAT_I(a, b)
#define CUT_PP_CAT_I(a, b)      CUT_PP_CAT_II(~, a##b)
#define CUT_PP_CAT_II(p, res)   res

// Allow us to easily add UNKNOWN / PADDING bytes into our structs,
// generates unique variable names using __COUNTER__
#define CUT_UNKNOWN_BYTES(Size) char CUT_PP_CAT(__unk, __COUNTER__)[Size]
#define CUT_PADDING_BYTES(Size) CUT_UNKNOWN_BYTES(Size)

// Unknown struct size
#define CUT_UNKNOWN_SIZE(x)

// Marks a struct as packed
#define CUT_PACKED     __attribute__((__packed__))

// Sets alignment for a struct
#define CUT_ALIGNAS(x) __attribute__((__aligned__(x)))
