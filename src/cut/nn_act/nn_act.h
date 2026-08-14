#pragma once

#include "../cut.h"
#include "../nn/result.h"

#ifdef __cplusplus

namespace nn::act
{
    using PrincipalId = uint32_t;

    static constexpr size_t AccountIdSize = 17;

    struct ACTNexAuthenticationResult
    {
        char token[513];
        CUT_PADDING_BYTES(3);
        char password[65];
        CUT_PADDING_BYTES(3);
        char host[16];
        uint16_t port;
        CUT_PADDING_BYTES(2);
    };
    CUT_CHECK_OFFSET(ACTNexAuthenticationResult, 0x000, token);
    CUT_CHECK_OFFSET(ACTNexAuthenticationResult, 0x204, password);
    CUT_CHECK_OFFSET(ACTNexAuthenticationResult, 0x248, host);
    CUT_CHECK_OFFSET(ACTNexAuthenticationResult, 0x258, port);
    CUT_CHECK_SIZE(ACTNexAuthenticationResult, 0x25C);

    CUT_IMPORT Result (*Initialize)();

    CUT_IMPORT Result (*AcquireNexServiceToken)(ACTNexAuthenticationResult *result, uint32_t gameServerId);

    CUT_IMPORT Result (*GetAccountId)(char outAccountId[AccountIdSize]);

    CUT_IMPORT PrincipalId (*GetPrincipalId)();
} // namespace nn::act

#endif //__cplusplus
