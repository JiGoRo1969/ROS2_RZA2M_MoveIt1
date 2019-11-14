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

#ifndef VIN_IOBITMASK_H
#define VIN_IOBITMASK_H


/* ==== Mask values for IO registers ==== */

#define VIN_V0MC_ME                                                            (0x00000001u)
#define VIN_V0MC_ME_SHIFT                                                      (0u)
#define VIN_V0MC_BPS                                                           (0x00000002u)
#define VIN_V0MC_BPS_SHIFT                                                     (1u)
#define VIN_V0MC_IM                                                            (0x00000018u)
#define VIN_V0MC_IM_SHIFT                                                      (3u)
#define VIN_V0MC_EN                                                            (0x00000040u)
#define VIN_V0MC_EN_SHIFT                                                      (6u)
#define VIN_V0MC_DC                                                            (0x0000C000u)
#define VIN_V0MC_DC_SHIFT                                                      (14u)
#define VIN_V0MC_INF                                                           (0x00070000u)
#define VIN_V0MC_INF_SHIFT                                                     (16u)
#define VIN_V0MC_YCAL                                                          (0x00080000u)
#define VIN_V0MC_YCAL_SHIFT                                                    (19u)
#define VIN_V0MC_LUTE                                                          (0x00100000u)
#define VIN_V0MC_LUTE_SHIFT                                                    (20u)
#define VIN_V0MC_SCLE                                                          (0x04000000u)
#define VIN_V0MC_SCLE_SHIFT                                                    (26u)
#define VIN_V0MC_CLP                                                           (0x30000000u)
#define VIN_V0MC_CLP_SHIFT                                                     (28u)
#define VIN_V0MS_CA                                                            (0x00000001u)
#define VIN_V0MS_CA_SHIFT                                                      (0u)
#define VIN_V0MS_AV                                                            (0x00000002u)
#define VIN_V0MS_AV_SHIFT                                                      (1u)
#define VIN_V0MS_FS                                                            (0x00000004u)
#define VIN_V0MS_FS_SHIFT                                                      (2u)
#define VIN_V0MS_FBS                                                           (0x00000018u)
#define VIN_V0MS_FBS_SHIFT                                                     (3u)
#define VIN_V0FC_SC                                                            (0x00000001u)
#define VIN_V0FC_SC_SHIFT                                                      (0u)
#define VIN_V0FC_CC                                                            (0x00000002u)
#define VIN_V0FC_CC_SHIFT                                                      (1u)
#define VIN_V0SLPrC_SLPrC                                                      (0x000007FFu)
#define VIN_V0SLPrC_SLPrC_SHIFT                                                (0u)
#define VIN_V0ELPrC_ELPrC                                                      (0x000007FFu)
#define VIN_V0ELPrC_ELPrC_SHIFT                                                (0u)
#define VIN_V0SPPrC_SPPrC                                                      (0x000007FFu)
#define VIN_V0SPPrC_SPPrC_SHIFT                                                (0u)
#define VIN_V0EPPrC_EPPrC                                                      (0x000007FFu)
#define VIN_V0EPPrC_EPPrC_SHIFT                                                (0u)
#define VIN_V0CSI_IFMD_DES0                                                    (0x02000000u)
#define VIN_V0CSI_IFMD_DES0_SHIFT                                              (25u)
#define VIN_V0IS_IS                                                            (0x00001FF0u)
#define VIN_V0IS_IS_SHIFT                                                      (4u)
#define VIN_V0MB1_MB1                                                          (0xFFFFFF80u)
#define VIN_V0MB1_MB1_SHIFT                                                    (7u)
#define VIN_V0MB2_MB2                                                          (0xFFFFFF80u)
#define VIN_V0MB2_MB2_SHIFT                                                    (7u)
#define VIN_V0MB3_MB3                                                          (0xFFFFFF80u)
#define VIN_V0MB3_MB3_SHIFT                                                    (7u)
#define VIN_V0LC_LC                                                            (0x00000FFFu)
#define VIN_V0LC_LC_SHIFT                                                      (0u)
#define VIN_V0IE_FOE                                                           (0x00000001u)
#define VIN_V0IE_FOE_SHIFT                                                     (0u)
#define VIN_V0IE_EFE                                                           (0x00000002u)
#define VIN_V0IE_EFE_SHIFT                                                     (1u)
#define VIN_V0IE_SIE                                                           (0x00000004u)
#define VIN_V0IE_SIE_SHIFT                                                     (2u)
#define VIN_V0IE_FIE                                                           (0x00000010u)
#define VIN_V0IE_FIE_SHIFT                                                     (4u)
#define VIN_V0IE_VRE                                                           (0x00010000u)
#define VIN_V0IE_VRE_SHIFT                                                     (16u)
#define VIN_V0IE_VFE                                                           (0x00020000u)
#define VIN_V0IE_VFE_SHIFT                                                     (17u)
#define VIN_V0IE_FIE2                                                          (0x80000000u)
#define VIN_V0IE_FIE2_SHIFT                                                    (31u)
#define VIN_V0INTS_FOS                                                         (0x00000001u)
#define VIN_V0INTS_FOS_SHIFT                                                   (0u)
#define VIN_V0INTS_EFS                                                         (0x00000002u)
#define VIN_V0INTS_EFS_SHIFT                                                   (1u)
#define VIN_V0INTS_SIS                                                         (0x00000004u)
#define VIN_V0INTS_SIS_SHIFT                                                   (2u)
#define VIN_V0INTS_FIS                                                         (0x00000010u)
#define VIN_V0INTS_FIS_SHIFT                                                   (4u)
#define VIN_V0INTS_VRS                                                         (0x00010000u)
#define VIN_V0INTS_VRS_SHIFT                                                   (16u)
#define VIN_V0INTS_VFS                                                         (0x00020000u)
#define VIN_V0INTS_VFS_SHIFT                                                   (17u)
#define VIN_V0INTS_FIS2                                                        (0x80000000u)
#define VIN_V0INTS_FIS2_SHIFT                                                  (31u)
#define VIN_V0SI_SI                                                            (0x000007FFu)
#define VIN_V0SI_SI_SHIFT                                                      (0u)
#define VIN_V0DMR_DTMD                                                         (0x00000003u)
#define VIN_V0DMR_DTMD_SHIFT                                                   (0u)
#define VIN_V0DMR_ABIT                                                         (0x00000004u)
#define VIN_V0DMR_ABIT_SHIFT                                                   (2u)
#define VIN_V0DMR_BPSM                                                         (0x00000010u)
#define VIN_V0DMR_BPSM_SHIFT                                                   (4u)
#define VIN_V0DMR_EXRGB                                                        (0x00000100u)
#define VIN_V0DMR_EXRGB_SHIFT                                                  (8u)
#define VIN_V0DMR_YC_THR                                                       (0x00000800u)
#define VIN_V0DMR_YC_THR_SHIFT                                                 (11u)
#define VIN_V0DMR_YMODE                                                        (0x00007000u)
#define VIN_V0DMR_YMODE_SHIFT                                                  (12u)
#define VIN_V0DMR_EVA                                                          (0x00010000u)
#define VIN_V0DMR_EVA_SHIFT                                                    (16u)
#define VIN_V0DMR_A8BIT                                                        (0xFF000000u)
#define VIN_V0DMR_A8BIT_SHIFT                                                  (24u)
#define VIN_V0DMR2_HLV                                                         (0x000007FFu)
#define VIN_V0DMR2_HLV_SHIFT                                                   (0u)
#define VIN_V0DMR2_VLV                                                         (0x0000F000u)
#define VIN_V0DMR2_VLV_SHIFT                                                   (12u)
#define VIN_V0DMR2_FTEH                                                        (0x00010000u)
#define VIN_V0DMR2_FTEH_SHIFT                                                  (16u)
#define VIN_V0DMR2_FTEV                                                        (0x00020000u)
#define VIN_V0DMR2_FTEV_SHIFT                                                  (17u)
#define VIN_V0UVAOF_UVAOF                                                      (0xFFFFFF80u)
#define VIN_V0UVAOF_UVAOF_SHIFT                                                (7u)
#define VIN_V0CSCC1_CSUB                                                       (0x000000FFu)
#define VIN_V0CSCC1_CSUB_SHIFT                                                 (0u)
#define VIN_V0CSCC1_YSUB                                                       (0x0000FF00u)
#define VIN_V0CSCC1_YSUB_SHIFT                                                 (8u)
#define VIN_V0CSCC1_YMUL                                                       (0x03FF0000u)
#define VIN_V0CSCC1_YMUL_SHIFT                                                 (16u)
#define VIN_V0CSCC2_GCRMUL                                                     (0x000003FFu)
#define VIN_V0CSCC2_GCRMUL_SHIFT                                               (0u)
#define VIN_V0CSCC2_RCRMUL                                                     (0x03FF0000u)
#define VIN_V0CSCC2_RCRMUL_SHIFT                                               (16u)
#define VIN_V0CSCC3_BCBMUL                                                     (0x000003FFu)
#define VIN_V0CSCC3_BCBMUL_SHIFT                                               (0u)
#define VIN_V0CSCC3_GCBMUL                                                     (0x03FF0000u)
#define VIN_V0CSCC3_GCBMUL_SHIFT                                               (16u)
#define VIN_V0UDS_CTRL_NE_BCB                                                  (0x00010000u)
#define VIN_V0UDS_CTRL_NE_BCB_SHIFT                                            (16u)
#define VIN_V0UDS_CTRL_NE_GY                                                   (0x00020000u)
#define VIN_V0UDS_CTRL_NE_GY_SHIFT                                             (17u)
#define VIN_V0UDS_CTRL_NE_RCR                                                  (0x00040000u)
#define VIN_V0UDS_CTRL_NE_RCR_SHIFT                                            (18u)
#define VIN_V0UDS_CTRL_BC                                                      (0x00100000u)
#define VIN_V0UDS_CTRL_BC_SHIFT                                                (20u)
#define VIN_V0UDS_CTRL_AMD                                                     (0x40000000u)
#define VIN_V0UDS_CTRL_AMD_SHIFT                                               (30u)
#define VIN_V0UDS_SCALE_VFRAC                                                  (0x00000FFFu)
#define VIN_V0UDS_SCALE_VFRAC_SHIFT                                            (0u)
#define VIN_V0UDS_SCALE_VMANT                                                  (0x0000F000u)
#define VIN_V0UDS_SCALE_VMANT_SHIFT                                            (12u)
#define VIN_V0UDS_SCALE_HFRAC                                                  (0x0FFF0000u)
#define VIN_V0UDS_SCALE_HFRAC_SHIFT                                            (16u)
#define VIN_V0UDS_SCALE_HMANT                                                  (0xF0000000u)
#define VIN_V0UDS_SCALE_HMANT_SHIFT                                            (28u)
#define VIN_V0UDS_PASS_BWIDTH_BWIDTH_V                                         (0x0000007Fu)
#define VIN_V0UDS_PASS_BWIDTH_BWIDTH_V_SHIFT                                   (0u)
#define VIN_V0UDS_PASS_BWIDTH_BWIDTH_H                                         (0x007F0000u)
#define VIN_V0UDS_PASS_BWIDTH_BWIDTH_H_SHIFT                                   (16u)
#define VIN_V0UDS_CLIP_SIZE_CL_VSIZE                                           (0x00000FFFu)
#define VIN_V0UDS_CLIP_SIZE_CL_VSIZE_SHIFT                                     (0u)
#define VIN_V0UDS_CLIP_SIZE_CL_HSIZE                                           (0x0FFF0000u)
#define VIN_V0UDS_CLIP_SIZE_CL_HSIZE_SHIFT                                     (16u)
#define VIN_V0LUTP_LTCRPR                                                      (0x000003FFu)
#define VIN_V0LUTP_LTCRPR_SHIFT                                                (0u)
#define VIN_V0LUTP_LTCBPR                                                      (0x000FFC00u)
#define VIN_V0LUTP_LTCBPR_SHIFT                                                (10u)
#define VIN_V0LUTP_LTYPR                                                       (0x3FF00000u)
#define VIN_V0LUTP_LTYPR_SHIFT                                                 (20u)
#define VIN_V0LUTD_LTCRDT                                                      (0x000000FFu)
#define VIN_V0LUTD_LTCRDT_SHIFT                                                (0u)
#define VIN_V0LUTD_LTCBDT                                                      (0x0000FF00u)
#define VIN_V0LUTD_LTCBDT_SHIFT                                                (8u)
#define VIN_V0LUTD_LTYDT                                                       (0x00FF0000u)
#define VIN_V0LUTD_LTYDT_SHIFT                                                 (16u)
#define VIN_V0YCCR1_YCLRP                                                      (0x00001FFFu)
#define VIN_V0YCCR1_YCLRP_SHIFT                                                (0u)
#define VIN_V0YCCR2_YCLGP                                                      (0x00001FFFu)
#define VIN_V0YCCR2_YCLGP_SHIFT                                                (0u)
#define VIN_V0YCCR2_YCLBP                                                      (0x1FFF0000u)
#define VIN_V0YCCR2_YCLBP_SHIFT                                                (16u)
#define VIN_V0YCCR3_YCLAP                                                      (0x00000FFFu)
#define VIN_V0YCCR3_YCLAP_SHIFT                                                (0u)
#define VIN_V0YCCR3_YCLCEN                                                     (0x00010000u)
#define VIN_V0YCCR3_YCLCEN_SHIFT                                               (16u)
#define VIN_V0YCCR3_YCLHEN                                                     (0x00800000u)
#define VIN_V0YCCR3_YCLHEN_SHIFT                                               (23u)
#define VIN_V0YCCR3_YCLSFT                                                     (0x1F000000u)
#define VIN_V0YCCR3_YCLSFT_SHIFT                                               (24u)
#define VIN_V0YCCR3_YEXPEN                                                     (0x80000000u)
#define VIN_V0YCCR3_YEXPEN_SHIFT                                               (31u)
#define VIN_V0CBCCR1_CBCLRP                                                    (0x00001FFFu)
#define VIN_V0CBCCR1_CBCLRP_SHIFT                                              (0u)
#define VIN_V0CBCCR2_CBCLGP                                                    (0x00001FFFu)
#define VIN_V0CBCCR2_CBCLGP_SHIFT                                              (0u)
#define VIN_V0CBCCR2_CBCLBP                                                    (0x1FFF0000u)
#define VIN_V0CBCCR2_CBCLBP_SHIFT                                              (16u)
#define VIN_V0CBCCR3_CBCLAP                                                    (0x00000FFFu)
#define VIN_V0CBCCR3_CBCLAP_SHIFT                                              (0u)
#define VIN_V0CBCCR3_CBCLCEN                                                   (0x00010000u)
#define VIN_V0CBCCR3_CBCLCEN_SHIFT                                             (16u)
#define VIN_V0CBCCR3_CBCLHEN                                                   (0x00800000u)
#define VIN_V0CBCCR3_CBCLHEN_SHIFT                                             (23u)
#define VIN_V0CBCCR3_CBCLSFT                                                   (0x1F000000u)
#define VIN_V0CBCCR3_CBCLSFT_SHIFT                                             (24u)
#define VIN_V0CBCCR3_CBEXPEN                                                   (0x80000000u)
#define VIN_V0CBCCR3_CBEXPEN_SHIFT                                             (31u)
#define VIN_V0CRCCR1_CRCLRP                                                    (0x00001FFFu)
#define VIN_V0CRCCR1_CRCLRP_SHIFT                                              (0u)
#define VIN_V0CRCCR2_CRCLGP                                                    (0x00001FFFu)
#define VIN_V0CRCCR2_CRCLGP_SHIFT                                              (0u)
#define VIN_V0CRCCR2_CRCLBP                                                    (0x1FFF0000u)
#define VIN_V0CRCCR2_CRCLBP_SHIFT                                              (16u)
#define VIN_V0CRCCR3_CRCLAP                                                    (0x00000FFFu)
#define VIN_V0CRCCR3_CRCLAP_SHIFT                                              (0u)
#define VIN_V0CRCCR3_CRCLCEN                                                   (0x00010000u)
#define VIN_V0CRCCR3_CRCLCEN_SHIFT                                             (16u)
#define VIN_V0CRCCR3_CRCLHEN                                                   (0x00800000u)
#define VIN_V0CRCCR3_CRCLHEN_SHIFT                                             (23u)
#define VIN_V0CRCCR3_CRCLSFT                                                   (0x1F000000u)
#define VIN_V0CRCCR3_CRCLSFT_SHIFT                                             (24u)
#define VIN_V0CRCCR3_CREXPEN                                                   (0x80000000u)
#define VIN_V0CRCCR3_CREXPEN_SHIFT                                             (31u)
#define VIN_V0CSCE1_YMUL2                                                      (0x00003FFFu)
#define VIN_V0CSCE1_YMUL2_SHIFT                                                (0u)
#define VIN_V0CSCE2_CSUB2                                                      (0x00000FFFu)
#define VIN_V0CSCE2_CSUB2_SHIFT                                                (0u)
#define VIN_V0CSCE2_YSUB2                                                      (0x0FFF0000u)
#define VIN_V0CSCE2_YSUB2_SHIFT                                                (16u)
#define VIN_V0CSCE3_GCRMUL2                                                    (0x00003FFFu)
#define VIN_V0CSCE3_GCRMUL2_SHIFT                                              (0u)
#define VIN_V0CSCE3_RCRMUL2                                                    (0x3FFF0000u)
#define VIN_V0CSCE3_RCRMUL2_SHIFT                                              (16u)
#define VIN_V0CSCE4_BCBMUL2                                                    (0x00003FFFu)
#define VIN_V0CSCE4_BCBMUL2_SHIFT                                              (0u)
#define VIN_V0CSCE4_GCBMUL2                                                    (0x3FFF0000u)
#define VIN_V0CSCE4_GCBMUL2_SHIFT                                              (16u)

#endif
