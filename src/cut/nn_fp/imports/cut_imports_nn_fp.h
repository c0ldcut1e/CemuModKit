#pragma once

#include "../nn_fp.h"

#ifdef __cplusplus

typedef struct ImportsNNFp
{
    nn::Result (*Initialize__Q2_2nn2fpFv)();
    nn::Result (*LoginAsync__Q2_2nn2fpFPFQ2_2nn6ResultPv_vPv)(void (*funcPtr)(nn::Result *result, void *userParam), void *userParam);
} ImportsNNFp;

#endif //__cplusplus
