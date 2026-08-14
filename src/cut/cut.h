#pragma once

/*
 * cut : Cemu Toolchain
 * 1.0.0
*/

#define CUT_FORMAT_PRINTF(fmt, args) __attribute__((__format__(__printf__, fmt, args)))

#include "cut_rplwrap.h"
#include "cut_structsize.h"
#include "cut_types.h"
