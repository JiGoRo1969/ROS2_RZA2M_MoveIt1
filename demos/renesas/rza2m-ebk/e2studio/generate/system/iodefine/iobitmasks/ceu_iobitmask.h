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

#ifndef CEU_IOBITMASK_H
#define CEU_IOBITMASK_H


/* ==== Mask values for IO registers ==== */

#define CEU_CAPSR_CE                                                           (0x00000001u)
#define CEU_CAPSR_CE_SHIFT                                                     (0u)
#define CEU_CAPSR_CPKIL                                                        (0x00010000u)
#define CEU_CAPSR_CPKIL_SHIFT                                                  (16u)
#define CEU_CAPCR_CTNCP                                                        (0x00010000u)
#define CEU_CAPCR_CTNCP_SHIFT                                                  (16u)
#define CEU_CAPCR_MTCM                                                         (0x00300000u)
#define CEU_CAPCR_MTCM_SHIFT                                                   (20u)
#define CEU_CAPCR_FDRP                                                         (0xFF000000u)
#define CEU_CAPCR_FDRP_SHIFT                                                   (24u)
#define CEU_CAMCR_HDPOL                                                        (0x00000001u)
#define CEU_CAMCR_HDPOL_SHIFT                                                  (0u)
#define CEU_CAMCR_VDPOL                                                        (0x00000002u)
#define CEU_CAMCR_VDPOL_SHIFT                                                  (1u)
#define CEU_CAMCR_JPG                                                          (0x00000030u)
#define CEU_CAMCR_JPG_SHIFT                                                    (4u)
#define CEU_CAMCR_DTARY                                                        (0x00000300u)
#define CEU_CAMCR_DTARY_SHIFT                                                  (8u)
#define CEU_CAMCR_DTIF                                                         (0x00001000u)
#define CEU_CAMCR_DTIF_SHIFT                                                   (12u)
#define CEU_CAMCR_FLDPOL                                                       (0x00010000u)
#define CEU_CAMCR_FLDPOL_SHIFT                                                 (16u)
#define CEU_CAMCR_DSEL                                                         (0x01000000u)
#define CEU_CAMCR_DSEL_SHIFT                                                   (24u)
#define CEU_CAMCR_FLDSEL                                                       (0x02000000u)
#define CEU_CAMCR_FLDSEL_SHIFT                                                 (25u)
#define CEU_CAMCR_HDSEL                                                        (0x04000000u)
#define CEU_CAMCR_HDSEL_SHIFT                                                  (26u)
#define CEU_CAMCR_VDSEL                                                        (0x08000000u)
#define CEU_CAMCR_VDSEL_SHIFT                                                  (27u)
#define CEU_CMCYR_HCYL                                                         (0x00003FFFu)
#define CEU_CMCYR_HCYL_SHIFT                                                   (0u)
#define CEU_CMCYR_VCYL                                                         (0x3FFF0000u)
#define CEU_CMCYR_VCYL_SHIFT                                                   (16u)
#define CEU_CAMOR_A_HOFST                                                      (0x00001FFFu)
#define CEU_CAMOR_A_HOFST_SHIFT                                                (0u)
#define CEU_CAMOR_A_VOFST                                                      (0x0FFF0000u)
#define CEU_CAMOR_A_VOFST_SHIFT                                                (16u)
#define CEU_CAPWR_A_HWDTH                                                      (0x00001FFFu)
#define CEU_CAPWR_A_HWDTH_SHIFT                                                (0u)
#define CEU_CAPWR_A_VWDTH                                                      (0x0FFF0000u)
#define CEU_CAPWR_A_VWDTH_SHIFT                                                (16u)
#define CEU_CAIFR_FCI                                                          (0x00000003u)
#define CEU_CAIFR_FCI_SHIFT                                                    (0u)
#define CEU_CAIFR_CIM                                                          (0x00000010u)
#define CEU_CAIFR_CIM_SHIFT                                                    (4u)
#define CEU_CAIFR_IFS                                                          (0x00000100u)
#define CEU_CAIFR_IFS_SHIFT                                                    (8u)
#define CEU_CRCNTR_RC                                                          (0x00000001u)
#define CEU_CRCNTR_RC_SHIFT                                                    (0u)
#define CEU_CRCNTR_RS                                                          (0x00000002u)
#define CEU_CRCNTR_RS_SHIFT                                                    (1u)
#define CEU_CRCNTR_RVS                                                         (0x00000010u)
#define CEU_CRCNTR_RVS_SHIFT                                                   (4u)
#define CEU_CRCMPR_RA                                                          (0x00000001u)
#define CEU_CRCMPR_RA_SHIFT                                                    (0u)
#define CEU_CFLCR_A_HFRAC                                                      (0x00000FFFu)
#define CEU_CFLCR_A_HFRAC_SHIFT                                                (0u)
#define CEU_CFLCR_A_HMANT                                                      (0x0000F000u)
#define CEU_CFLCR_A_HMANT_SHIFT                                                (12u)
#define CEU_CFLCR_A_VFRAC                                                      (0x0FFF0000u)
#define CEU_CFLCR_A_VFRAC_SHIFT                                                (16u)
#define CEU_CFLCR_A_VMANT                                                      (0xF0000000u)
#define CEU_CFLCR_A_VMANT_SHIFT                                                (28u)
#define CEU_CFSZR_A_HFCLP                                                      (0x00000FFFu)
#define CEU_CFSZR_A_HFCLP_SHIFT                                                (0u)
#define CEU_CFSZR_A_VFCLP                                                      (0x0FFF0000u)
#define CEU_CFSZR_A_VFCLP_SHIFT                                                (16u)
#define CEU_CDWDR_A_CHDW                                                       (0x00001FFFu)
#define CEU_CDWDR_A_CHDW_SHIFT                                                 (0u)
#define CEU_CDAYR_A_CAYR                                                       (0xFFFFFFFFu)
#define CEU_CDAYR_A_CAYR_SHIFT                                                 (0u)
#define CEU_CDACR_A_CACR                                                       (0xFFFFFFFFu)
#define CEU_CDACR_A_CACR_SHIFT                                                 (0u)
#define CEU_CDBYR_A_CBYR                                                       (0xFFFFFFFFu)
#define CEU_CDBYR_A_CBYR_SHIFT                                                 (0u)
#define CEU_CDBCR_A_CBCR                                                       (0xFFFFFFFFu)
#define CEU_CDBCR_A_CBCR_SHIFT                                                 (0u)
#define CEU_CBDSR_A_CBVS                                                       (0x007FFFFFu)
#define CEU_CBDSR_A_CBVS_SHIFT                                                 (0u)
#define CEU_CFWCR_FWE                                                          (0x00000001u)
#define CEU_CFWCR_FWE_SHIFT                                                    (0u)
#define CEU_CFWCR_FWV                                                          (0xFFFFFFE0u)
#define CEU_CFWCR_FWV_SHIFT                                                    (5u)
#define CEU_CLFCR_A_LPF                                                        (0x00000001u)
#define CEU_CLFCR_A_LPF_SHIFT                                                  (0u)
#define CEU_CDOCR_A_COBS                                                       (0x00000001u)
#define CEU_CDOCR_A_COBS_SHIFT                                                 (0u)
#define CEU_CDOCR_A_COWS                                                       (0x00000002u)
#define CEU_CDOCR_A_COWS_SHIFT                                                 (1u)
#define CEU_CDOCR_A_COLS                                                       (0x00000004u)
#define CEU_CDOCR_A_COLS_SHIFT                                                 (2u)
#define CEU_CDOCR_A_CDS                                                        (0x00000010u)
#define CEU_CDOCR_A_CDS_SHIFT                                                  (4u)
#define CEU_CDOCR_A_CBE                                                        (0x00010000u)
#define CEU_CDOCR_A_CBE_SHIFT                                                  (16u)
#define CEU_CEIER_CPEIE                                                        (0x00000001u)
#define CEU_CEIER_CPEIE_SHIFT                                                  (0u)
#define CEU_CEIER_CFEIE                                                        (0x00000002u)
#define CEU_CEIER_CFEIE_SHIFT                                                  (1u)
#define CEU_CEIER_IGRWIE                                                       (0x00000010u)
#define CEU_CEIER_IGRWIE_SHIFT                                                 (4u)
#define CEU_CEIER_HDIE                                                         (0x00000100u)
#define CEU_CEIER_HDIE_SHIFT                                                   (8u)
#define CEU_CEIER_VDIE                                                         (0x00000200u)
#define CEU_CEIER_VDIE_SHIFT                                                   (9u)
#define CEU_CEIER_CPBE1IE                                                      (0x00001000u)
#define CEU_CEIER_CPBE1IE_SHIFT                                                (12u)
#define CEU_CEIER_CPBE2IE                                                      (0x00002000u)
#define CEU_CEIER_CPBE2IE_SHIFT                                                (13u)
#define CEU_CEIER_CPBE3IE                                                      (0x00004000u)
#define CEU_CEIER_CPBE3IE_SHIFT                                                (14u)
#define CEU_CEIER_CPBE4IE                                                      (0x00008000u)
#define CEU_CEIER_CPBE4IE_SHIFT                                                (15u)
#define CEU_CEIER_CDTOFIE                                                      (0x00010000u)
#define CEU_CEIER_CDTOFIE_SHIFT                                                (16u)
#define CEU_CEIER_IGHSIE                                                       (0x00020000u)
#define CEU_CEIER_IGHSIE_SHIFT                                                 (17u)
#define CEU_CEIER_IGVSIE                                                       (0x00040000u)
#define CEU_CEIER_IGVSIE_SHIFT                                                 (18u)
#define CEU_CEIER_VBPIE                                                        (0x00100000u)
#define CEU_CEIER_VBPIE_SHIFT                                                  (20u)
#define CEU_CEIER_FWFIE                                                        (0x00800000u)
#define CEU_CEIER_FWFIE_SHIFT                                                  (23u)
#define CEU_CEIER_NHDIE                                                        (0x01000000u)
#define CEU_CEIER_NHDIE_SHIFT                                                  (24u)
#define CEU_CEIER_NVDIE                                                        (0x02000000u)
#define CEU_CEIER_NVDIE_SHIFT                                                  (25u)
#define CEU_CETCR_CPE                                                          (0x00000001u)
#define CEU_CETCR_CPE_SHIFT                                                    (0u)
#define CEU_CETCR_CFE                                                          (0x00000002u)
#define CEU_CETCR_CFE_SHIFT                                                    (1u)
#define CEU_CETCR_IGRW                                                         (0x00000010u)
#define CEU_CETCR_IGRW_SHIFT                                                   (4u)
#define CEU_CETCR_HD                                                           (0x00000100u)
#define CEU_CETCR_HD_SHIFT                                                     (8u)
#define CEU_CETCR_VD                                                           (0x00000200u)
#define CEU_CETCR_VD_SHIFT                                                     (9u)
#define CEU_CETCR_CPBE1                                                        (0x00001000u)
#define CEU_CETCR_CPBE1_SHIFT                                                  (12u)
#define CEU_CETCR_CPBE2                                                        (0x00002000u)
#define CEU_CETCR_CPBE2_SHIFT                                                  (13u)
#define CEU_CETCR_CPBE3                                                        (0x00004000u)
#define CEU_CETCR_CPBE3_SHIFT                                                  (14u)
#define CEU_CETCR_CPBE4                                                        (0x00008000u)
#define CEU_CETCR_CPBE4_SHIFT                                                  (15u)
#define CEU_CETCR_CDTOF                                                        (0x00010000u)
#define CEU_CETCR_CDTOF_SHIFT                                                  (16u)
#define CEU_CETCR_IGHS                                                         (0x00020000u)
#define CEU_CETCR_IGHS_SHIFT                                                   (17u)
#define CEU_CETCR_IGVS                                                         (0x00040000u)
#define CEU_CETCR_IGVS_SHIFT                                                   (18u)
#define CEU_CETCR_VBP                                                          (0x00100000u)
#define CEU_CETCR_VBP_SHIFT                                                    (20u)
#define CEU_CETCR_FWF                                                          (0x00800000u)
#define CEU_CETCR_FWF_SHIFT                                                    (23u)
#define CEU_CETCR_NHD                                                          (0x01000000u)
#define CEU_CETCR_NHD_SHIFT                                                    (24u)
#define CEU_CETCR_NVD                                                          (0x02000000u)
#define CEU_CETCR_NVD_SHIFT                                                    (25u)
#define CEU_CSTSR_CPTON                                                        (0x00000001u)
#define CEU_CSTSR_CPTON_SHIFT                                                  (0u)
#define CEU_CSTSR_CPFLD                                                        (0x00010000u)
#define CEU_CSTSR_CPFLD_SHIFT                                                  (16u)
#define CEU_CSTSR_CRST                                                         (0x01000000u)
#define CEU_CSTSR_CRST_SHIFT                                                   (24u)
#define CEU_CDSSR_CDSS                                                         (0xFFFFFFFFu)
#define CEU_CDSSR_CDSS_SHIFT                                                   (0u)
#define CEU_CDAYR2_A_CAYR2                                                     (0xFFFFFFFFu)
#define CEU_CDAYR2_A_CAYR2_SHIFT                                               (0u)
#define CEU_CDACR2_A_CACR2                                                     (0xFFFFFFFFu)
#define CEU_CDACR2_A_CACR2_SHIFT                                               (0u)
#define CEU_CDBYR2_A_CBYR2                                                     (0xFFFFFFFFu)
#define CEU_CDBYR2_A_CBYR2_SHIFT                                               (0u)
#define CEU_CDBCR2_A_CBCR2                                                     (0xFFFFFFFFu)
#define CEU_CDBCR2_A_CBCR2_SHIFT                                               (0u)
#define CEU_CAMOR_B_HOFST                                                      (0x00001FFFu)
#define CEU_CAMOR_B_HOFST_SHIFT                                                (0u)
#define CEU_CAMOR_B_VOFST                                                      (0x0FFF0000u)
#define CEU_CAMOR_B_VOFST_SHIFT                                                (16u)
#define CEU_CAPWR_B_HWDTH                                                      (0x00001FFFu)
#define CEU_CAPWR_B_HWDTH_SHIFT                                                (0u)
#define CEU_CAPWR_B_VWDTH                                                      (0x0FFF0000u)
#define CEU_CAPWR_B_VWDTH_SHIFT                                                (16u)
#define CEU_CFLCR_B_HFRAC                                                      (0x00000FFFu)
#define CEU_CFLCR_B_HFRAC_SHIFT                                                (0u)
#define CEU_CFLCR_B_HMANT                                                      (0x0000F000u)
#define CEU_CFLCR_B_HMANT_SHIFT                                                (12u)
#define CEU_CFLCR_B_VFRAC                                                      (0x0FFF0000u)
#define CEU_CFLCR_B_VFRAC_SHIFT                                                (16u)
#define CEU_CFLCR_B_VMANT                                                      (0xF0000000u)
#define CEU_CFLCR_B_VMANT_SHIFT                                                (28u)
#define CEU_CFSZR_B_HFCLP                                                      (0x00000FFFu)
#define CEU_CFSZR_B_HFCLP_SHIFT                                                (0u)
#define CEU_CFSZR_B_VFCLP                                                      (0x0FFF0000u)
#define CEU_CFSZR_B_VFCLP_SHIFT                                                (16u)
#define CEU_CDWDR_B_CHDW                                                       (0x00001FFFu)
#define CEU_CDWDR_B_CHDW_SHIFT                                                 (0u)
#define CEU_CDAYR_B_CAYR                                                       (0xFFFFFFFFu)
#define CEU_CDAYR_B_CAYR_SHIFT                                                 (0u)
#define CEU_CDACR_B_CACR                                                       (0xFFFFFFFFu)
#define CEU_CDACR_B_CACR_SHIFT                                                 (0u)
#define CEU_CDBYR_B_CBYR                                                       (0xFFFFFFFFu)
#define CEU_CDBYR_B_CBYR_SHIFT                                                 (0u)
#define CEU_CDBCR_B_CBCR                                                       (0xFFFFFFFFu)
#define CEU_CDBCR_B_CBCR_SHIFT                                                 (0u)
#define CEU_CBDSR_B_CBVS                                                       (0x007FFFFFu)
#define CEU_CBDSR_B_CBVS_SHIFT                                                 (0u)
#define CEU_CLFCR_B_LPF                                                        (0x00000001u)
#define CEU_CLFCR_B_LPF_SHIFT                                                  (0u)
#define CEU_CDOCR_B_COBS                                                       (0x00000001u)
#define CEU_CDOCR_B_COBS_SHIFT                                                 (0u)
#define CEU_CDOCR_B_COWS                                                       (0x00000002u)
#define CEU_CDOCR_B_COWS_SHIFT                                                 (1u)
#define CEU_CDOCR_B_COLS                                                       (0x00000004u)
#define CEU_CDOCR_B_COLS_SHIFT                                                 (2u)
#define CEU_CDOCR_B_CDS                                                        (0x00000010u)
#define CEU_CDOCR_B_CDS_SHIFT                                                  (4u)
#define CEU_CDOCR_B_CBE                                                        (0x00010000u)
#define CEU_CDOCR_B_CBE_SHIFT                                                  (16u)
#define CEU_CDAYR2_B_CAYR2                                                     (0xFFFFFFFFu)
#define CEU_CDAYR2_B_CAYR2_SHIFT                                               (0u)
#define CEU_CDACR2_B_CACR2                                                     (0xFFFFFFFFu)
#define CEU_CDACR2_B_CACR2_SHIFT                                               (0u)
#define CEU_CDBYR2_B_CBYR2                                                     (0xFFFFFFFFu)
#define CEU_CDBYR2_B_CBYR2_SHIFT                                               (0u)
#define CEU_CDBCR2_B_CBCR2                                                     (0xFFFFFFFFu)
#define CEU_CDBCR2_B_CBCR2_SHIFT                                               (0u)
#define CEU_CAMOR_M_HOFST                                                      (0x00001FFFu)
#define CEU_CAMOR_M_HOFST_SHIFT                                                (0u)
#define CEU_CAMOR_M_VOFST                                                      (0x0FFF0000u)
#define CEU_CAMOR_M_VOFST_SHIFT                                                (16u)
#define CEU_CAPWR_M_HWDTH                                                      (0x00001FFFu)
#define CEU_CAPWR_M_HWDTH_SHIFT                                                (0u)
#define CEU_CAPWR_M_VWDTH                                                      (0x0FFF0000u)
#define CEU_CAPWR_M_VWDTH_SHIFT                                                (16u)
#define CEU_CFLCR_M_HFRAC                                                      (0x00000FFFu)
#define CEU_CFLCR_M_HFRAC_SHIFT                                                (0u)
#define CEU_CFLCR_M_HMANT                                                      (0x0000F000u)
#define CEU_CFLCR_M_HMANT_SHIFT                                                (12u)
#define CEU_CFLCR_M_VFRAC                                                      (0x0FFF0000u)
#define CEU_CFLCR_M_VFRAC_SHIFT                                                (16u)
#define CEU_CFLCR_M_VMANT                                                      (0xF0000000u)
#define CEU_CFLCR_M_VMANT_SHIFT                                                (28u)
#define CEU_CFSZR_M_HFCLP                                                      (0x00000FFFu)
#define CEU_CFSZR_M_HFCLP_SHIFT                                                (0u)
#define CEU_CFSZR_M_VFCLP                                                      (0x0FFF0000u)
#define CEU_CFSZR_M_VFCLP_SHIFT                                                (16u)
#define CEU_CDWDR_M_CHDW                                                       (0x00001FFFu)
#define CEU_CDWDR_M_CHDW_SHIFT                                                 (0u)
#define CEU_CDAYR_M_CAYR                                                       (0xFFFFFFFFu)
#define CEU_CDAYR_M_CAYR_SHIFT                                                 (0u)
#define CEU_CDACR_M_CACR                                                       (0xFFFFFFFFu)
#define CEU_CDACR_M_CACR_SHIFT                                                 (0u)
#define CEU_CDBYR_M_CBYR                                                       (0xFFFFFFFFu)
#define CEU_CDBYR_M_CBYR_SHIFT                                                 (0u)
#define CEU_CDBCR_M_CBCR                                                       (0xFFFFFFFFu)
#define CEU_CDBCR_M_CBCR_SHIFT                                                 (0u)
#define CEU_CBDSR_M_CBVS                                                       (0x007FFFFFu)
#define CEU_CBDSR_M_CBVS_SHIFT                                                 (0u)
#define CEU_CLFCR_M_LPF                                                        (0x00000001u)
#define CEU_CLFCR_M_LPF_SHIFT                                                  (0u)
#define CEU_CDOCR_M_COBS                                                       (0x00000001u)
#define CEU_CDOCR_M_COBS_SHIFT                                                 (0u)
#define CEU_CDOCR_M_COWS                                                       (0x00000002u)
#define CEU_CDOCR_M_COWS_SHIFT                                                 (1u)
#define CEU_CDOCR_M_COLS                                                       (0x00000004u)
#define CEU_CDOCR_M_COLS_SHIFT                                                 (2u)
#define CEU_CDOCR_M_CDS                                                        (0x00000010u)
#define CEU_CDOCR_M_CDS_SHIFT                                                  (4u)
#define CEU_CDOCR_M_CBE                                                        (0x00010000u)
#define CEU_CDOCR_M_CBE_SHIFT                                                  (16u)
#define CEU_CDAYR2_M_CAYR2                                                     (0xFFFFFFFFu)
#define CEU_CDAYR2_M_CAYR2_SHIFT                                               (0u)
#define CEU_CDACR2_M_CACR2                                                     (0xFFFFFFFFu)
#define CEU_CDACR2_M_CACR2_SHIFT                                               (0u)
#define CEU_CDBYR2_M_CBYR2                                                     (0xFFFFFFFFu)
#define CEU_CDBYR2_M_CBYR2_SHIFT                                               (0u)
#define CEU_CDBCR2_M_CBCR2                                                     (0xFFFFFFFFu)
#define CEU_CDBCR2_M_CBCR2_SHIFT                                               (0u)

#endif
