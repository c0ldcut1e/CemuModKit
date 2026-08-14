#pragma once

#include "cut_imports_gx2_aperture.h"
#include "cut_imports_gx2_clear.h"
#include "cut_imports_gx2_context.h"
#include "cut_imports_gx2_debug.h"
#include "cut_imports_gx2_display.h"
#include "cut_imports_gx2_displaylist.h"
#include "cut_imports_gx2_draw.h"
#include "cut_imports_gx2_event.h"
#include "cut_imports_gx2_mem.h"
#include "cut_imports_gx2_registers.h"
#include "cut_imports_gx2_sampler.h"
#include "cut_imports_gx2_semaphore.h"
#include "cut_imports_gx2_shaders.h"
#include "cut_imports_gx2_state.h"
#include "cut_imports_gx2_surface.h"
#include "cut_imports_gx2_swap.h"
#include "cut_imports_gx2_temp.h"
#include "cut_imports_gx2_tessellation.h"
#include "cut_imports_gx2_texture.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ImportsGX2
{
    ImportsGX2Aperture aperture;
    ImportsGX2Clear clear;
    ImportsGX2Context context;
    ImportsGX2Debug debug;
    ImportsGX2Display display;
    ImportsGX2DisplayList displayList;
    ImportsGX2Draw draw;
    ImportsGX2Event event;
    ImportsGX2Mem mem;
    ImportsGX2Registers registers;
    ImportsGX2Sampler sampler;
    ImportsGX2Semaphore semaphore;
    ImportsGX2Shaders shaders;
    ImportsGX2State state;
    ImportsGX2Surface surface;
    ImportsGX2Swap swap;
    ImportsGX2Temp temp;
    ImportsGX2Tessellation tessellation;
    ImportsGX2Texture texture;
} ImportsGX2;

#ifdef __cplusplus
}
#endif
