#pragma once

#include "../nn_act.h"

#ifdef __cplusplus

typedef struct ImportsNNAct
{
    nn::Result (*Initialize__Q2_2nn3actFv)();
    nn::Result (*AcquireNexServiceToken__Q2_2nn3actFP26ACTNexAuthenticationResultUi)(nn::act::ACTNexAuthenticationResult *result,
                                                                                     uint32_t gameServerId);
    nn::Result (*GetAccountId__Q2_2nn3actFPc)(char outAccountId[nn::act::AccountIdSize]);
    nn::act::PrincipalId (*GetPrincipalId__Q2_2nn3actFv)();
} ImportsNNAct;

#endif //__cplusplus
