#pragma once
#include "../cut.h"
#include "enum.h"
#include "surface.h"

/**
 * \defgroup gx2_registers Registers
 * \ingroup gx2
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GX2AAMaskReg GX2AAMaskReg;
typedef struct GX2AlphaTestReg GX2AlphaTestReg;
typedef struct GX2AlphaToMaskReg GX2AlphaToMaskReg;
typedef struct GX2BlendControlReg GX2BlendControlReg;
typedef struct GX2BlendConstantColorReg GX2BlendConstantColorReg;
typedef struct GX2ColorControlReg GX2ColorControlReg;
typedef struct GX2DepthStencilControlReg GX2DepthStencilControlReg;
typedef struct GX2StencilMaskReg GX2StencilMaskReg;
typedef struct GX2LineWidthReg GX2LineWidthReg;
typedef struct GX2PointSizeReg GX2PointSizeReg;
typedef struct GX2PointLimitsReg GX2PointLimitsReg;
typedef struct GX2PolygonControlReg GX2PolygonControlReg;
typedef struct GX2PolygonOffsetReg GX2PolygonOffsetReg;
typedef struct GX2ScissorReg GX2ScissorReg;
typedef struct GX2TargetChannelMaskReg GX2TargetChannelMaskReg;
typedef struct GX2ViewportReg GX2ViewportReg;

struct GX2AAMaskReg
{
    uint32_t pa_sc_aa_mask;
};
CUT_CHECK_OFFSET(GX2AAMaskReg, 0, pa_sc_aa_mask);
CUT_CHECK_SIZE(GX2AAMaskReg, 4);

struct GX2AlphaTestReg
{
    uint32_t sx_alpha_test_control;
    uint32_t sx_alpha_ref;
};
CUT_CHECK_OFFSET(GX2AlphaTestReg, 0, sx_alpha_test_control);
CUT_CHECK_OFFSET(GX2AlphaTestReg, 4, sx_alpha_ref);
CUT_CHECK_SIZE(GX2AlphaTestReg, 8);

struct GX2AlphaToMaskReg
{
    uint32_t db_alpha_to_mask;
};
CUT_CHECK_OFFSET(GX2AlphaToMaskReg, 0, db_alpha_to_mask);
CUT_CHECK_SIZE(GX2AlphaToMaskReg, 4);

struct GX2BlendControlReg
{
    GX2RenderTarget target;
    uint32_t cb_blend_control;
};
CUT_CHECK_OFFSET(GX2BlendControlReg, 0, target);
CUT_CHECK_OFFSET(GX2BlendControlReg, 4, cb_blend_control);
CUT_CHECK_SIZE(GX2BlendControlReg, 8);

struct GX2BlendConstantColorReg
{
    float red;
    float green;
    float blue;
    float alpha;
};
CUT_CHECK_OFFSET(GX2BlendConstantColorReg, 0x00, red);
CUT_CHECK_OFFSET(GX2BlendConstantColorReg, 0x04, green);
CUT_CHECK_OFFSET(GX2BlendConstantColorReg, 0x08, blue);
CUT_CHECK_OFFSET(GX2BlendConstantColorReg, 0x0c, alpha);
CUT_CHECK_SIZE(GX2BlendConstantColorReg, 0x10);

struct GX2ColorControlReg
{
    uint32_t cb_color_control;
};
CUT_CHECK_OFFSET(GX2ColorControlReg, 0x00, cb_color_control);
CUT_CHECK_SIZE(GX2ColorControlReg, 4);

struct GX2DepthStencilControlReg
{
    uint32_t db_depth_control;
};
CUT_CHECK_OFFSET(GX2DepthStencilControlReg, 0, db_depth_control);
CUT_CHECK_SIZE(GX2DepthStencilControlReg, 4);

struct GX2StencilMaskReg
{
    uint32_t db_stencilrefmask;
    uint32_t db_stencilrefmask_bf;
};
CUT_CHECK_OFFSET(GX2StencilMaskReg, 0, db_stencilrefmask);
CUT_CHECK_OFFSET(GX2StencilMaskReg, 4, db_stencilrefmask_bf);
CUT_CHECK_SIZE(GX2StencilMaskReg, 8);

struct GX2LineWidthReg
{
    uint32_t pa_su_line_cntl;
};
CUT_CHECK_OFFSET(GX2LineWidthReg, 0, pa_su_line_cntl);
CUT_CHECK_SIZE(GX2LineWidthReg, 4);

struct GX2PointSizeReg
{
    uint32_t pa_su_point_size;
};
CUT_CHECK_OFFSET(GX2PointSizeReg, 0, pa_su_point_size);
CUT_CHECK_SIZE(GX2PointSizeReg, 4);

struct GX2PointLimitsReg
{
    uint32_t pa_su_point_minmax;
};
CUT_CHECK_OFFSET(GX2PointLimitsReg, 0, pa_su_point_minmax);
CUT_CHECK_SIZE(GX2PointLimitsReg, 4);

struct GX2PolygonControlReg
{
    uint32_t pa_su_sc_mode_cntl;
};
CUT_CHECK_OFFSET(GX2PolygonControlReg, 0, pa_su_sc_mode_cntl);
CUT_CHECK_SIZE(GX2PolygonControlReg, 4);

struct GX2PolygonOffsetReg
{
    uint32_t pa_su_poly_offset_front_scale;
    uint32_t pa_su_poly_offset_front_offset;
    uint32_t pa_su_poly_offset_back_scale;
    uint32_t pa_su_poly_offset_back_offset;
    uint32_t pa_su_poly_offset_clamp;
};
CUT_CHECK_OFFSET(GX2PolygonOffsetReg, 0x00, pa_su_poly_offset_front_scale);
CUT_CHECK_OFFSET(GX2PolygonOffsetReg, 0x04, pa_su_poly_offset_front_offset);
CUT_CHECK_OFFSET(GX2PolygonOffsetReg, 0x08, pa_su_poly_offset_back_scale);
CUT_CHECK_OFFSET(GX2PolygonOffsetReg, 0x0C, pa_su_poly_offset_back_offset);
CUT_CHECK_OFFSET(GX2PolygonOffsetReg, 0x10, pa_su_poly_offset_clamp);
CUT_CHECK_SIZE(GX2PolygonOffsetReg, 20);

struct GX2ScissorReg
{
    uint32_t pa_sc_generic_scissor_tl;
    uint32_t pa_sc_generic_scissor_br;
};
CUT_CHECK_OFFSET(GX2ScissorReg, 0x00, pa_sc_generic_scissor_tl);
CUT_CHECK_OFFSET(GX2ScissorReg, 0x04, pa_sc_generic_scissor_br);
CUT_CHECK_SIZE(GX2ScissorReg, 8);

struct GX2TargetChannelMaskReg
{
    uint32_t cb_target_mask;
};
CUT_CHECK_OFFSET(GX2TargetChannelMaskReg, 0x00, cb_target_mask);
CUT_CHECK_SIZE(GX2TargetChannelMaskReg, 4);

struct GX2ViewportReg
{
    uint32_t pa_cl_vport_xscale;
    uint32_t pa_cl_vport_xoffset;
    uint32_t pa_cl_vport_yscale;
    uint32_t pa_cl_vport_yoffset;
    uint32_t pa_cl_vport_zscale;
    uint32_t pa_cl_vport_zoffset;
    uint32_t pa_cl_gb_vert_clip_adj;
    uint32_t pa_cl_gb_vert_disc_adj;
    uint32_t pa_cl_gb_horz_clip_adj;
    uint32_t pa_cl_gb_horz_disc_adj;
    uint32_t pa_sc_vport_zmin;
    uint32_t pa_sc_vport_zmax;
};
CUT_CHECK_OFFSET(GX2ViewportReg, 0x00, pa_cl_vport_xscale);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x04, pa_cl_vport_xoffset);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x08, pa_cl_vport_yscale);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x0C, pa_cl_vport_yoffset);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x10, pa_cl_vport_zscale);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x14, pa_cl_vport_zoffset);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x18, pa_cl_gb_vert_clip_adj);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x1C, pa_cl_gb_vert_disc_adj);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x20, pa_cl_gb_horz_clip_adj);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x24, pa_cl_gb_horz_disc_adj);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x28, pa_sc_vport_zmin);
CUT_CHECK_OFFSET(GX2ViewportReg, 0x2C, pa_sc_vport_zmax);
CUT_CHECK_SIZE(GX2ViewportReg, 48);

CUT_IMPORT void (*GX2SetAAMask)(uint8_t upperLeft, uint8_t upperRight, uint8_t lowerLeft, uint8_t lowerRight);

CUT_IMPORT void (*GX2InitAAMaskReg)(GX2AAMaskReg *reg, uint8_t upperLeft, uint8_t upperRight, uint8_t lowerLeft, uint8_t lowerRight);

CUT_IMPORT void (*GX2GetAAMaskReg)(GX2AAMaskReg *reg, uint8_t *upperLeft, uint8_t *upperRight, uint8_t *lowerLeft, uint8_t *lowerRight);

CUT_IMPORT void (*GX2SetAAMaskReg)(const GX2AAMaskReg *reg);

CUT_IMPORT void (*GX2SetAlphaTest)(BOOL alphaTest, GX2CompareFunction func, float ref);

CUT_IMPORT void (*GX2InitAlphaTestReg)(GX2AlphaTestReg *reg, BOOL alphaTest, GX2CompareFunction func, float ref);

CUT_IMPORT void (*GX2GetAlphaTestReg)(const GX2AlphaTestReg *reg, BOOL *alphaTest, GX2CompareFunction *func, float *ref);

CUT_IMPORT void (*GX2SetAlphaTestReg)(const GX2AlphaTestReg *reg);

CUT_IMPORT void (*GX2SetAlphaToMask)(BOOL alphaToMask, GX2AlphaToMaskMode mode);

CUT_IMPORT void (*GX2InitAlphaToMaskReg)(GX2AlphaToMaskReg *reg, BOOL alphaToMask, GX2AlphaToMaskMode mode);

CUT_IMPORT void (*GX2GetAlphaToMaskReg)(const GX2AlphaToMaskReg *reg, BOOL *alphaToMask, GX2AlphaToMaskMode *mode);

CUT_IMPORT void (*GX2SetAlphaToMaskReg)(const GX2AlphaToMaskReg *reg);

CUT_IMPORT void (*GX2SetBlendConstantColor)(float red, float green, float blue, float alpha);

CUT_IMPORT void (*GX2InitBlendConstantColorReg)(GX2BlendConstantColorReg *reg, float red, float green, float blue, float alpha);

CUT_IMPORT void (*GX2GetBlendConstantColorReg)(GX2BlendConstantColorReg *reg, float *red, float *green, float *blue, float *alpha);

CUT_IMPORT void (*GX2SetBlendConstantColorReg)(const GX2BlendConstantColorReg *reg);

CUT_IMPORT void (*GX2SetBlendControl)(GX2RenderTarget target, GX2BlendMode colorSrcBlend, GX2BlendMode colorDstBlend,
                                      GX2BlendCombineMode colorCombine, BOOL useAlphaBlend, GX2BlendMode alphaSrcBlend, GX2BlendMode alphaDstBlend,
                                      GX2BlendCombineMode alphaCombine);

CUT_IMPORT void (*GX2InitBlendControlReg)(GX2BlendControlReg *reg, GX2RenderTarget target, GX2BlendMode colorSrcBlend, GX2BlendMode colorDstBlend,
                                          GX2BlendCombineMode colorCombine, BOOL useAlphaBlend, GX2BlendMode alphaSrcBlend,
                                          GX2BlendMode alphaDstBlend, GX2BlendCombineMode alphaCombine);

CUT_IMPORT void (*GX2GetBlendControlReg)(GX2BlendControlReg *reg, GX2RenderTarget *target, GX2BlendMode *colorSrcBlend, GX2BlendMode *colorDstBlend,
                                         GX2BlendCombineMode *colorCombine, BOOL *useAlphaBlend, GX2BlendMode *alphaSrcBlend,
                                         GX2BlendMode *alphaDstBlend, GX2BlendCombineMode *alphaCombine);

CUT_IMPORT void (*GX2SetBlendControlReg)(const GX2BlendControlReg *reg);

CUT_IMPORT void (*GX2SetColorControl)(GX2LogicOp rop3, uint8_t targetBlendEnable, BOOL multiWriteEnable, BOOL colorWriteEnable);

CUT_IMPORT void (*GX2InitColorControlReg)(GX2ColorControlReg *reg, GX2LogicOp rop3, uint8_t targetBlendEnable, BOOL multiWriteEnable,
                                          BOOL colorWriteEnable);

CUT_IMPORT void (*GX2GetColorControlReg)(GX2ColorControlReg *reg, GX2LogicOp *rop3, uint8_t *targetBlendEnable, BOOL *multiWriteEnable,
                                         BOOL *colorWriteEnable);

CUT_IMPORT void (*GX2SetColorControlReg)(const GX2ColorControlReg *reg);

CUT_IMPORT void (*GX2SetDepthOnlyControl)(BOOL depthTest, BOOL depthWrite, GX2CompareFunction depthCompare);

CUT_IMPORT void (*GX2SetDepthStencilControl)(BOOL depthTest, BOOL depthWrite, GX2CompareFunction depthCompare, BOOL stencilTest, BOOL backfaceStencil,
                                             GX2CompareFunction frontStencilFunc, GX2StencilFunction frontStencilZPass,
                                             GX2StencilFunction frontStencilZFail, GX2StencilFunction frontStencilFail,
                                             GX2CompareFunction backStencilFunc, GX2StencilFunction backStencilZPass,
                                             GX2StencilFunction backStencilZFail, GX2StencilFunction backStencilFail);

CUT_IMPORT void (*GX2InitDepthStencilControlReg)(GX2DepthStencilControlReg *reg, BOOL depthTest, BOOL depthWrite, GX2CompareFunction depthCompare,
                                                 BOOL stencilTest, BOOL backfaceStencil, GX2CompareFunction frontStencilFunc,
                                                 GX2StencilFunction frontStencilZPass, GX2StencilFunction frontStencilZFail,
                                                 GX2StencilFunction frontStencilFail, GX2CompareFunction backStencilFunc,
                                                 GX2StencilFunction backStencilZPass, GX2StencilFunction backStencilZFail,
                                                 GX2StencilFunction backStencilFail);

CUT_IMPORT void (*GX2GetDepthStencilControlReg)(GX2DepthStencilControlReg *reg, BOOL *depthTest, BOOL *depthWrite, GX2CompareFunction *depthCompare,
                                                BOOL *stencilTest, BOOL *backfaceStencil, GX2CompareFunction *frontStencilFunc,
                                                GX2StencilFunction *frontStencilZPass, GX2StencilFunction *frontStencilZFail,
                                                GX2StencilFunction *frontStencilFail, GX2CompareFunction *backStencilFunc,
                                                GX2StencilFunction *backStencilZPass, GX2StencilFunction *backStencilZFail,
                                                GX2StencilFunction *backStencilFail);

CUT_IMPORT void (*GX2SetDepthStencilControlReg)(const GX2DepthStencilControlReg *reg);

CUT_IMPORT void (*GX2SetStencilMask)(uint8_t frontMask, uint8_t frontWriteMask, uint8_t frontRef, uint8_t backMask, uint8_t backWriteMask,
                                     uint8_t backRef);

CUT_IMPORT void (*GX2InitStencilMaskReg)(GX2StencilMaskReg *reg, uint8_t frontMask, uint8_t frontWriteMask, uint8_t frontRef, uint8_t backMask,
                                         uint8_t backWriteMask, uint8_t backRef);

CUT_IMPORT void (*GX2GetStencilMaskReg)(GX2StencilMaskReg *reg, uint8_t *frontMask, uint8_t *frontWriteMask, uint8_t *frontRef, uint8_t *backMask,
                                        uint8_t *backWriteMask, uint8_t *backRef);

CUT_IMPORT void (*GX2SetStencilMaskReg)(const GX2StencilMaskReg *reg);

CUT_IMPORT void (*GX2SetLineWidth)(float width);

CUT_IMPORT void (*GX2InitLineWidthReg)(GX2LineWidthReg *reg, float width);

CUT_IMPORT void (*GX2GetLineWidthReg)(GX2LineWidthReg *reg, float *width);

CUT_IMPORT void (*GX2SetLineWidthReg)(const GX2LineWidthReg *reg);

CUT_IMPORT void (*GX2SetPointSize)(float width, float height);

CUT_IMPORT void (*GX2InitPointSizeReg)(GX2PointSizeReg *reg, float width, float height);

CUT_IMPORT void (*GX2GetPointSizeReg)(GX2PointSizeReg *reg, float *width, float *height);

CUT_IMPORT void (*GX2SetPointSizeReg)(const GX2PointSizeReg *reg);

CUT_IMPORT void (*GX2SetPointLimits)(float min, float max);

CUT_IMPORT void (*GX2InitPointLimitsReg)(GX2PointLimitsReg *reg, float min, float max);

CUT_IMPORT void (*GX2GetPointLimitsReg)(GX2PointLimitsReg *reg, float *min, float *max);

CUT_IMPORT void (*GX2SetPointLimitsReg)(const GX2PointLimitsReg *reg);

CUT_IMPORT void (*GX2SetCullOnlyControl)(GX2FrontFace frontFace, BOOL cullFront, BOOL cullBack);

CUT_IMPORT void (*GX2SetPolygonControl)(GX2FrontFace frontFace, BOOL cullFront, BOOL cullBack, BOOL polyMode, GX2PolygonMode polyModeFront,
                                        GX2PolygonMode polyModeBack, BOOL polyOffsetFrontEnable, BOOL polyOffsetBackEnable,
                                        BOOL polyOffsetParaEnable);

CUT_IMPORT void (*GX2InitPolygonControlReg)(GX2PolygonControlReg *reg, GX2FrontFace frontFace, BOOL cullFront, BOOL cullBack, BOOL polyMode,
                                            GX2PolygonMode polyModeFront, GX2PolygonMode polyModeBack, BOOL polyOffsetFrontEnable,
                                            BOOL polyOffsetBackEnable, BOOL polyOffsetParaEnable);

CUT_IMPORT void (*GX2GetPolygonControlReg)(GX2PolygonControlReg *reg, GX2FrontFace *frontFace, BOOL *cullFront, BOOL *cullBack, BOOL *polyMode,
                                           GX2PolygonMode *polyModeFront, GX2PolygonMode *polyModeBack, BOOL *polyOffsetFrontEnable,
                                           BOOL *polyOffsetBackEnable, BOOL *polyOffsetParaEnable);

CUT_IMPORT void (*GX2SetPolygonControlReg)(const GX2PolygonControlReg *reg);

CUT_IMPORT void (*GX2SetPolygonOffset)(float frontOffset, float frontScale, float backOffset, float backScale, float clamp);

CUT_IMPORT void (*GX2InitPolygonOffsetReg)(GX2PolygonOffsetReg *reg, float frontOffset, float frontScale, float backOffset, float backScale,
                                           float clamp);

CUT_IMPORT void (*GX2GetPolygonOffsetReg)(GX2PolygonOffsetReg *reg, float *frontOffset, float *frontScale, float *backOffset, float *backScale,
                                          float *clamp);

CUT_IMPORT void (*GX2SetPolygonOffsetReg)(const GX2PolygonOffsetReg *reg);

CUT_IMPORT void (*GX2SetScissor)(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

CUT_IMPORT void (*GX2InitScissorReg)(GX2ScissorReg *reg, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

CUT_IMPORT void (*GX2GetScissorReg)(GX2ScissorReg *reg, uint32_t *x, uint32_t *y, uint32_t *width, uint32_t *height);

CUT_IMPORT void (*GX2SetScissorReg)(const GX2ScissorReg *reg);

CUT_IMPORT void (*GX2SetTargetChannelMasks)(GX2ChannelMask mask0, GX2ChannelMask mask1, GX2ChannelMask mask2, GX2ChannelMask mask3,
                                            GX2ChannelMask mask4, GX2ChannelMask mask5, GX2ChannelMask mask6, GX2ChannelMask mask7);

CUT_IMPORT void (*GX2InitTargetChannelMasksReg)(GX2TargetChannelMaskReg *reg, GX2ChannelMask mask0, GX2ChannelMask mask1, GX2ChannelMask mask2,
                                                GX2ChannelMask mask3, GX2ChannelMask mask4, GX2ChannelMask mask5, GX2ChannelMask mask6,
                                                GX2ChannelMask mask7);

CUT_IMPORT void (*GX2GetTargetChannelMasksReg)(GX2TargetChannelMaskReg *reg, GX2ChannelMask *mask0, GX2ChannelMask *mask1, GX2ChannelMask *mask2,
                                               GX2ChannelMask *mask3, GX2ChannelMask *mask4, GX2ChannelMask *mask5, GX2ChannelMask *mask6,
                                               GX2ChannelMask *mask7);

CUT_IMPORT void (*GX2SetTargetChannelMasksReg)(const GX2TargetChannelMaskReg *reg);

CUT_IMPORT void (*GX2SetViewport)(float x, float y, float width, float height, float nearZ, float farZ);

CUT_IMPORT void (*GX2InitViewportReg)(GX2ViewportReg *reg, float x, float y, float width, float height, float nearZ, float farZ);

CUT_IMPORT void (*GX2GetViewportReg)(GX2ViewportReg *reg, float *x, float *y, float *width, float *height, float *nearZ, float *farZ);

CUT_IMPORT void (*GX2SetViewportReg)(const GX2ViewportReg *reg);

CUT_IMPORT void (*GX2SetRasterizerClipControl)(BOOL rasterizer, BOOL zclipEnable);

CUT_IMPORT void (*GX2SetRasterizerClipControlEx)(BOOL rasterizer, BOOL zclipEnable, BOOL halfZ);

CUT_IMPORT void (*GX2SetRasterizerClipControlHalfZ)(BOOL rasterizer, BOOL zclipEnable, BOOL halfZ);

#ifdef __cplusplus
}
#endif

/** @} */
