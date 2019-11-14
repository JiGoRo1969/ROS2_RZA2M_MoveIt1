/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/ 
/*******************************************************************************
* Rev: 2.00
* Description : IO bitmask header
*******************************************************************************/

#ifndef DRW_IOBITMASK_H
#define DRW_IOBITMASK_H


/* ==== Mask values for IO registers ==== */

#define DRW_CONTROL_LIM1ENABLE                                                 (0x00000001u)
#define DRW_CONTROL_LIM1ENABLE_SHIFT                                           (0u)
#define DRW_CONTROL_LIM2ENABLE                                                 (0x00000002u)
#define DRW_CONTROL_LIM2ENABLE_SHIFT                                           (1u)
#define DRW_CONTROL_LIM3ENABLE                                                 (0x00000004u)
#define DRW_CONTROL_LIM3ENABLE_SHIFT                                           (2u)
#define DRW_CONTROL_LIM4ENABLE                                                 (0x00000008u)
#define DRW_CONTROL_LIM4ENABLE_SHIFT                                           (3u)
#define DRW_CONTROL_LIM5ENABLE                                                 (0x00000010u)
#define DRW_CONTROL_LIM5ENABLE_SHIFT                                           (4u)
#define DRW_CONTROL_LIM6ENABLE                                                 (0x00000020u)
#define DRW_CONTROL_LIM6ENABLE_SHIFT                                           (5u)
#define DRW_CONTROL_QUAD1ENABLE                                                (0x00000040u)
#define DRW_CONTROL_QUAD1ENABLE_SHIFT                                          (6u)
#define DRW_CONTROL_QUAD2ENABLE                                                (0x00000080u)
#define DRW_CONTROL_QUAD2ENABLE_SHIFT                                          (7u)
#define DRW_CONTROL_QUAD3ENABLE                                                (0x00000100u)
#define DRW_CONTROL_QUAD3ENABLE_SHIFT                                          (8u)
#define DRW_CONTROL_LIM1THRESHOLD                                              (0x00000200u)
#define DRW_CONTROL_LIM1THRESHOLD_SHIFT                                        (9u)
#define DRW_CONTROL_LIM2THRESHOLD                                              (0x00000400u)
#define DRW_CONTROL_LIM2THRESHOLD_SHIFT                                        (10u)
#define DRW_CONTROL_LIM3THRESHOLD                                              (0x00000800u)
#define DRW_CONTROL_LIM3THRESHOLD_SHIFT                                        (11u)
#define DRW_CONTROL_LIM4THRESHOLD                                              (0x00001000u)
#define DRW_CONTROL_LIM4THRESHOLD_SHIFT                                        (12u)
#define DRW_CONTROL_LIM5THRESHOLD                                              (0x00002000u)
#define DRW_CONTROL_LIM5THRESHOLD_SHIFT                                        (13u)
#define DRW_CONTROL_LIM6THRESHOLD                                              (0x00004000u)
#define DRW_CONTROL_LIM6THRESHOLD_SHIFT                                        (14u)
#define DRW_CONTROL_BAND1ENABLE                                                (0x00008000u)
#define DRW_CONTROL_BAND1ENABLE_SHIFT                                          (15u)
#define DRW_CONTROL_BAND2ENABLE                                                (0x00010000u)
#define DRW_CONTROL_BAND2ENABLE_SHIFT                                          (16u)
#define DRW_CONTROL_UNION12                                                    (0x00020000u)
#define DRW_CONTROL_UNION12_SHIFT                                              (17u)
#define DRW_CONTROL_UNION34                                                    (0x00040000u)
#define DRW_CONTROL_UNION34_SHIFT                                              (18u)
#define DRW_CONTROL_UNION56                                                    (0x00080000u)
#define DRW_CONTROL_UNION56_SHIFT                                              (19u)
#define DRW_CONTROL_UNIONAB                                                    (0x00100000u)
#define DRW_CONTROL_UNIONAB_SHIFT                                              (20u)
#define DRW_CONTROL_UNIONCD                                                    (0x00200000u)
#define DRW_CONTROL_UNIONCD_SHIFT                                              (21u)
#define DRW_CONTROL_SPANABORT                                                  (0x00400000u)
#define DRW_CONTROL_SPANABORT_SHIFT                                            (22u)
#define DRW_CONTROL_SPANSTORE                                                  (0x00800000u)
#define DRW_CONTROL_SPANSTORE_SHIFT                                            (23u)
#define DRW_CONTROL2_PATTERNENABLE                                             (0x00000001u)
#define DRW_CONTROL2_PATTERNENABLE_SHIFT                                       (0u)
#define DRW_CONTROL2_TEXTUREENABLE                                             (0x00000002u)
#define DRW_CONTROL2_TEXTUREENABLE_SHIFT                                       (1u)
#define DRW_CONTROL2_PATTERNSOURCEL5                                           (0x00000004u)
#define DRW_CONTROL2_PATTERNSOURCEL5_SHIFT                                     (2u)
#define DRW_CONTROL2_USEACB                                                    (0x00000008u)
#define DRW_CONTROL2_USEACB_SHIFT                                              (3u)
#define DRW_CONTROL2_READFORMAT_3_2                                            (0x00000030u)
#define DRW_CONTROL2_READFORMAT_3_2_SHIFT                                      (4u)
#define DRW_CONTROL2_BSFA                                                      (0x00000040u)
#define DRW_CONTROL2_BSFA_SHIFT                                                (6u)
#define DRW_CONTROL2_BDFA                                                      (0x00000080u)
#define DRW_CONTROL2_BDFA_SHIFT                                                (7u)
#define DRW_CONTROL2_WRITEFORMAT_2                                             (0x00000100u)
#define DRW_CONTROL2_WRITEFORMAT_2_SHIFT                                       (8u)
#define DRW_CONTROL2_BSF                                                       (0x00000200u)
#define DRW_CONTROL2_BSF_SHIFT                                                 (9u)
#define DRW_CONTROL2_BDF                                                       (0x00000400u)
#define DRW_CONTROL2_BDF_SHIFT                                                 (10u)
#define DRW_CONTROL2_BSI                                                       (0x00000800u)
#define DRW_CONTROL2_BSI_SHIFT                                                 (11u)
#define DRW_CONTROL2_BDI                                                       (0x00001000u)
#define DRW_CONTROL2_BDI_SHIFT                                                 (12u)
#define DRW_CONTROL2_BC2                                                       (0x00002000u)
#define DRW_CONTROL2_BC2_SHIFT                                                 (13u)
#define DRW_CONTROL2_TEXTURECLAMPX                                             (0x00004000u)
#define DRW_CONTROL2_TEXTURECLAMPX_SHIFT                                       (14u)
#define DRW_CONTROL2_TEXTURECLAMPY                                             (0x00008000u)
#define DRW_CONTROL2_TEXTURECLAMPY_SHIFT                                       (15u)
#define DRW_CONTROL2_TEXTUREFILTERX                                            (0x00010000u)
#define DRW_CONTROL2_TEXTUREFILTERX_SHIFT                                      (16u)
#define DRW_CONTROL2_TEXTUREFILTERY                                            (0x00020000u)
#define DRW_CONTROL2_TEXTUREFILTERY_SHIFT                                      (17u)
#define DRW_CONTROL2_READFORMAT_1_0                                            (0x000C0000u)
#define DRW_CONTROL2_READFORMAT_1_0_SHIFT                                      (18u)
#define DRW_CONTROL2_WRITEFORMAT_1_0                                           (0x00300000u)
#define DRW_CONTROL2_WRITEFORMAT_1_0_SHIFT                                     (20u)
#define DRW_CONTROL2_WRITEALPHA                                                (0x00C00000u)
#define DRW_CONTROL2_WRITEALPHA_SHIFT                                          (22u)
#define DRW_CONTROL2_RLEENABLE                                                 (0x01000000u)
#define DRW_CONTROL2_RLEENABLE_SHIFT                                           (24u)
#define DRW_CONTROL2_CLUTENABLE                                                (0x02000000u)
#define DRW_CONTROL2_CLUTENABLE_SHIFT                                          (25u)
#define DRW_CONTROL2_COLKEYENABLE                                              (0x04000000u)
#define DRW_CONTROL2_COLKEYENABLE_SHIFT                                        (26u)
#define DRW_CONTROL2_CLUTFORMAT                                                (0x08000000u)
#define DRW_CONTROL2_CLUTFORMAT_SHIFT                                          (27u)
#define DRW_CONTROL2_BSIA                                                      (0x10000000u)
#define DRW_CONTROL2_BSIA_SHIFT                                                (28u)
#define DRW_CONTROL2_BDIA                                                      (0x20000000u)
#define DRW_CONTROL2_BDIA_SHIFT                                                (29u)
#define DRW_CONTROL2_RLEPIXELWIDTH                                             (0xC0000000u)
#define DRW_CONTROL2_RLEPIXELWIDTH_SHIFT                                       (30u)
#define DRW_L1START_LSTART                                                     (0xFFFFFFFFu)
#define DRW_L1START_LSTART_SHIFT                                               (0u)
#define DRW_L2START_LSTART                                                     (0xFFFFFFFFu)
#define DRW_L2START_LSTART_SHIFT                                               (0u)
#define DRW_L3START_LSTART                                                     (0xFFFFFFFFu)
#define DRW_L3START_LSTART_SHIFT                                               (0u)
#define DRW_L4START_LSTART                                                     (0xFFFFFFFFu)
#define DRW_L4START_LSTART_SHIFT                                               (0u)
#define DRW_L5START_LSTART                                                     (0xFFFFFFFFu)
#define DRW_L5START_LSTART_SHIFT                                               (0u)
#define DRW_L6START_LSTART                                                     (0xFFFFFFFFu)
#define DRW_L6START_LSTART_SHIFT                                               (0u)
#define DRW_L1XADD_LXADD                                                       (0xFFFFFFFFu)
#define DRW_L1XADD_LXADD_SHIFT                                                 (0u)
#define DRW_L2XADD_LXADD                                                       (0xFFFFFFFFu)
#define DRW_L2XADD_LXADD_SHIFT                                                 (0u)
#define DRW_L3XADD_LXADD                                                       (0xFFFFFFFFu)
#define DRW_L3XADD_LXADD_SHIFT                                                 (0u)
#define DRW_L4XADD_LXADD                                                       (0xFFFFFFFFu)
#define DRW_L4XADD_LXADD_SHIFT                                                 (0u)
#define DRW_L5XADD_LXADD                                                       (0xFFFFFFFFu)
#define DRW_L5XADD_LXADD_SHIFT                                                 (0u)
#define DRW_L6XADD_LXADD                                                       (0xFFFFFFFFu)
#define DRW_L6XADD_LXADD_SHIFT                                                 (0u)
#define DRW_L1YADD_LYADD                                                       (0xFFFFFFFFu)
#define DRW_L1YADD_LYADD_SHIFT                                                 (0u)
#define DRW_L2YADD_LYADD                                                       (0xFFFFFFFFu)
#define DRW_L2YADD_LYADD_SHIFT                                                 (0u)
#define DRW_L3YADD_LYADD                                                       (0xFFFFFFFFu)
#define DRW_L3YADD_LYADD_SHIFT                                                 (0u)
#define DRW_L4YADD_LYADD                                                       (0xFFFFFFFFu)
#define DRW_L4YADD_LYADD_SHIFT                                                 (0u)
#define DRW_L5YADD_LYADD                                                       (0xFFFFFFFFu)
#define DRW_L5YADD_LYADD_SHIFT                                                 (0u)
#define DRW_L6YADD_LYADD                                                       (0xFFFFFFFFu)
#define DRW_L6YADD_LYADD_SHIFT                                                 (0u)
#define DRW_L1BAND_LBAND                                                       (0xFFFFFFFFu)
#define DRW_L1BAND_LBAND_SHIFT                                                 (0u)
#define DRW_L2BAND_LBAND                                                       (0xFFFFFFFFu)
#define DRW_L2BAND_LBAND_SHIFT                                                 (0u)
#define DRW_COLOR1_COLOR1B                                                     (0x000000FFu)
#define DRW_COLOR1_COLOR1B_SHIFT                                               (0u)
#define DRW_COLOR1_COLOR1G                                                     (0x0000FF00u)
#define DRW_COLOR1_COLOR1G_SHIFT                                               (8u)
#define DRW_COLOR1_COLOR1R                                                     (0x00FF0000u)
#define DRW_COLOR1_COLOR1R_SHIFT                                               (16u)
#define DRW_COLOR1_COLOR1A                                                     (0xFF000000u)
#define DRW_COLOR1_COLOR1A_SHIFT                                               (24u)
#define DRW_COLOR2_COLOR2B                                                     (0x000000FFu)
#define DRW_COLOR2_COLOR2B_SHIFT                                               (0u)
#define DRW_COLOR2_COLOR2G                                                     (0x0000FF00u)
#define DRW_COLOR2_COLOR2G_SHIFT                                               (8u)
#define DRW_COLOR2_COLOR2R                                                     (0x00FF0000u)
#define DRW_COLOR2_COLOR2R_SHIFT                                               (16u)
#define DRW_COLOR2_COLOR2A                                                     (0xFF000000u)
#define DRW_COLOR2_COLOR2A_SHIFT                                               (24u)
#define DRW_PATTERN_PATTERN                                                    (0x000000FFu)
#define DRW_PATTERN_PATTERN_SHIFT                                              (0u)
#define DRW_SIZE_SIZEX                                                         (0x0000FFFFu)
#define DRW_SIZE_SIZEX_SHIFT                                                   (0u)
#define DRW_SIZE_SIZEY                                                         (0xFFFF0000u)
#define DRW_SIZE_SIZEY_SHIFT                                                   (16u)
#define DRW_PITCH_PITCH                                                        (0x0000FFFFu)
#define DRW_PITCH_PITCH_SHIFT                                                  (0u)
#define DRW_PITCH_SSD                                                          (0xFFFF0000u)
#define DRW_PITCH_SSD_SHIFT                                                    (16u)
#define DRW_ORIGIN_ORIGIN                                                      (0xFFFFFFFFu)
#define DRW_ORIGIN_ORIGIN_SHIFT                                                (0u)
#define DRW_LUSTART_LUSTART                                                    (0xFFFFFFFFu)
#define DRW_LUSTART_LUSTART_SHIFT                                              (0u)
#define DRW_LUXADD_LUXADD                                                      (0xFFFFFFFFu)
#define DRW_LUXADD_LUXADD_SHIFT                                                (0u)
#define DRW_LUYADD_LUYADD                                                      (0xFFFFFFFFu)
#define DRW_LUYADD_LUYADD_SHIFT                                                (0u)
#define DRW_LVSTARTI_LVSTARTI                                                  (0xFFFFFFFFu)
#define DRW_LVSTARTI_LVSTARTI_SHIFT                                            (0u)
#define DRW_LVSTARTF_LVSTARTF                                                  (0x0000FFFFu)
#define DRW_LVSTARTF_LVSTARTF_SHIFT                                            (0u)
#define DRW_LVXADDI_LVXADDI                                                    (0xFFFFFFFFu)
#define DRW_LVXADDI_LVXADDI_SHIFT                                              (0u)
#define DRW_LVYADDI_LVYADDI                                                    (0xFFFFFFFFu)
#define DRW_LVYADDI_LVYADDI_SHIFT                                              (0u)
#define DRW_LVYXADDF_LVXADDF                                                   (0x0000FFFFu)
#define DRW_LVYXADDF_LVXADDF_SHIFT                                             (0u)
#define DRW_LVYXADDF_LVYADDF                                                   (0xFFFF0000u)
#define DRW_LVYXADDF_LVYADDF_SHIFT                                             (16u)
#define DRW_TEXPITCH_TEXPITCH                                                  (0x000007FFu)
#define DRW_TEXPITCH_TEXPITCH_SHIFT                                            (0u)
#define DRW_TEXMASK_TEXUMASK                                                   (0x000007FFu)
#define DRW_TEXMASK_TEXUMASK_SHIFT                                             (0u)
#define DRW_TEXMASK_TEXVMASK                                                   (0xFFFFF800u)
#define DRW_TEXMASK_TEXVMASK_SHIFT                                             (11u)
#define DRW_TEXORIGIN_TEXORIGIN                                                (0xFFFFFFFFu)
#define DRW_TEXORIGIN_TEXORIGIN_SHIFT                                          (0u)
#define DRW_IRQCTL_ENUMIRQEN                                                   (0x00000001u)
#define DRW_IRQCTL_ENUMIRQEN_SHIFT                                             (0u)
#define DRW_IRQCTL_DLISTIRQEN                                                  (0x00000002u)
#define DRW_IRQCTL_DLISTIRQEN_SHIFT                                            (1u)
#define DRW_IRQCTL_ENUMIRQCLR                                                  (0x00000004u)
#define DRW_IRQCTL_ENUMIRQCLR_SHIFT                                            (2u)
#define DRW_IRQCTL_DLISTIRQCLR                                                 (0x00000008u)
#define DRW_IRQCTL_DLISTIRQCLR_SHIFT                                           (3u)
#define DRW_IRQCTL_BUSIRQEN                                                    (0x00000010u)
#define DRW_IRQCTL_BUSIRQEN_SHIFT                                              (4u)
#define DRW_IRQCTL_BUSIRQCLR                                                   (0x00000020u)
#define DRW_IRQCTL_BUSIRQCLR_SHIFT                                             (5u)
#define DRW_CACHECTL_CENABLEFX                                                 (0x00000001u)
#define DRW_CACHECTL_CENABLEFX_SHIFT                                           (0u)
#define DRW_CACHECTL_CFLUSHFX                                                  (0x00000002u)
#define DRW_CACHECTL_CFLUSHFX_SHIFT                                            (1u)
#define DRW_CACHECTL_CENABLETX                                                 (0x00000004u)
#define DRW_CACHECTL_CENABLETX_SHIFT                                           (2u)
#define DRW_CACHECTL_CFLUSHTX                                                  (0x00000008u)
#define DRW_CACHECTL_CFLUSHTX_SHIFT                                            (3u)
#define DRW_DLISTSTART_DLISTSTART                                              (0xFFFFFFFFu)
#define DRW_DLISTSTART_DLISTSTART_SHIFT                                        (0u)
#define DRW_PERFCOUNT1_PERFCOUNT                                               (0xFFFFFFFFu)
#define DRW_PERFCOUNT1_PERFCOUNT_SHIFT                                         (0u)
#define DRW_PERFCOUNT2_PERFCOUNT                                               (0xFFFFFFFFu)
#define DRW_PERFCOUNT2_PERFCOUNT_SHIFT                                         (0u)
#define DRW_PERFTRIGGER_PERFTRIGGER1                                           (0x0000001Fu)
#define DRW_PERFTRIGGER_PERFTRIGGER1_SHIFT                                     (0u)
#define DRW_PERFTRIGGER_PERFTRIGGER2                                           (0x001F0000u)
#define DRW_PERFTRIGGER_PERFTRIGGER2_SHIFT                                     (16u)
#define DRW_TEXCLADDR_CLADDR                                                   (0x000000FFu)
#define DRW_TEXCLADDR_CLADDR_SHIFT                                             (0u)
#define DRW_TEXCLDATA_CLDATA                                                   (0xFFFFFFFFu)
#define DRW_TEXCLDATA_CLDATA_SHIFT                                             (0u)
#define DRW_TEXCLOFFSET_CLOFFSET                                               (0x000000FFu)
#define DRW_TEXCLOFFSET_CLOFFSET_SHIFT                                         (0u)
#define DRW_COLKEY_COLKEYB                                                     (0x000000FFu)
#define DRW_COLKEY_COLKEYB_SHIFT                                               (0u)
#define DRW_COLKEY_COLKEYG                                                     (0x0000FF00u)
#define DRW_COLKEY_COLKEYG_SHIFT                                               (8u)
#define DRW_COLKEY_COLKEYR                                                     (0x00FF0000u)
#define DRW_COLKEY_COLKEYR_SHIFT                                               (16u)

#endif
