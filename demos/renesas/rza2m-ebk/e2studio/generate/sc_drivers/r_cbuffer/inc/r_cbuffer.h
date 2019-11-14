/******************************************************************************
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
*******************************************************************************
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
* Portions copyright (C) 2011  Swarm Systems Limited. All rights reserved.
*******************************************************************************
* File Name    : r_cbuffer.h
* Version      : 1.01
* Device(s)    : Renesas
* Tool-Chain   : GNUARM-NONE-EABI v14.02
* OS           : None
* H/W Platform : EBK
* Description  : Circular Buffering Routines
*******************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 05.08.2010 1.00    First Release
*              : 10.11.2010 1.01    Added cbClear function
******************************************************************************/

/******************************************************************************
/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

#include "r_typedefs.h"
#include "malloc.h"

#ifndef CBUFFER_H
#define CBUFFER_H

/******************************************************************************
Typedef definitions
******************************************************************************/

/* Hide the structure of the circular buffer to prevent access to the members
   directly. This is called encapsulation. */
typedef struct _CBUFF *PCBUFF;

/******************************************************************************
Function Prototypes
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Function Name: cbCreate
* Description  : Function to create a circular buffer
* Arguments    : IN  memType - The type of memory to use
*              : IN  stBufferSize - The size of the circular buffer required
* Return Value : Pointer to the circular buffer or NULL on failure
******************************************************************************/

extern  PCBUFF cbCreate(size_t stBufferSize);

/******************************************************************************
* Function Name: cbDestroy
* Description  : Function to destroy a circular buffer
* Arguments    : IN  memType - The type of memory to use
*                IN  pcBuffer - Pointer to the buffer to destroy
* Return Value : N/A
******************************************************************************/

extern  void cbDestroy(PCBUFF pcBuffer);

/******************************************************************************
Function Name: cbPut
Description:   Put a uint8_t in the Buffer
Arguments:     IN  pBuffer - pointer to the circular buffer
               IN  byData - The data to put
Return value:  true if the byte was entered into the buffer
******************************************************************************/

extern  _Bool cbPut(PCBUFF pcBuffer, uint8_t byData);

/******************************************************************************
Function Name: cbGet
Description:   Get a byte from the Buffer
Arguments:     IN  pcBuffer - pointer to the circular buffer
               OUT pbyData - pointer to the destination byte of data
Return value:  true if a byte was retrieved
******************************************************************************/

extern  _Bool cbGet(PCBUFF pcBuffer, uint8_t *pbyData);

/******************************************************************************
Function Name: cbUsed
Description:   Function to return the number of bytes in the buffer
Arguments:     IN  pBuffer - Pointer to the buffer
Return value:  The number of bytes in the buffer
******************************************************************************/

extern  size_t cbUsed(PCBUFF pBuffer);

/******************************************************************************
* Function Name: cbFree
* Description  : Function to return the number of free space in the buffer
* Arguments    : IN  pBuffer - Pointer to the buffer
* Return Value : The number of bytes that can be put in the buffer
******************************************************************************/

extern  size_t cbFree(PCBUFF pBuffer);

/******************************************************************************
* Function Name: cbFull
* Description  : Function to return true when the buffer is full
* Arguments    : IN  pBuffer - Pointer to the buffer
* Return Value : true if the buffer is full
******************************************************************************/

extern  _Bool cbFull(PCBUFF pcBuffer);

/*****************************************************************************
* Function Name: cbClear
* Description  : Function to clear the buffer
* Arguments    : IN  pcBuffer - Pointer to the buffer to clear
* Return Value : 
******************************************************************************/

extern  void cbClear(PCBUFF pcBuffer);

/******************************************************************************
* Function Name: cbGetPacket
* Description  : Function to get data from the buffer but not check it out
*                cbUsed should be called before calls to this function to
*                ensure that there is sufficient data in the buffer
* Arguments    : IN  pBuffer - pointer to the IO buffer to get the data from
*                IN  stPacketLength - the length of data to read from the 
*                                     buffer
*                IN  pDest - the destination address
* Return Value : none
******************************************************************************/

extern  void cbGetPacket(PCBUFF pcBuffer, size_t stPacketLength, void *pDest);

/******************************************************************************
* Function Name: cbCheckOut
* Description  : Function to check the data out of the data following a call to
*                cbGetPacket
* Arguments    : IN  pcBuffer - Pointer to the buffer
*                IN  stPacketLength - the size of the data to check out
* Return Value : none
******************************************************************************/

extern  void cbCheckOut(PCBUFF pcBuffer, size_t stPacketLength);

/******************************************************************************
* Function Name: cbPutPacket
* Description  : Function to put a packet of data into the buffer
* Arguments    : IN  pcBuffer - Pointer to the buffer
*                IN  stPacketLength - The length of the packet to put
*                IN  pSrc - Pointer to the data to put
* Return Value : none
******************************************************************************/

extern  void cbPutPacket(PCBUFF pcBuffer, size_t stPacketLength, void *pSrc);

/******************************************************************************
* Function Name: cbCheckIn
* Description  : Function to check a packet into the buffer
* Arguments    : IN  pcBuffer - Pointer to the buffer
*                IN  stPacketLength - The length of data to check in
* Return Value : none
******************************************************************************/

extern  void cbCheckIn(PCBUFF pcBuffer, size_t stPacketLength);

/******************************************************************************
* Function Name: cbLinOut
* Description  : Function to calculate how much can be delivered in one hit
* Arguments    : IN  pcBuffer - Pointer to the buffer
* Return Value : The number of bytes until the end of the data or the buffer
******************************************************************************/

extern  size_t cbLinOut(PCBUFF pcBuffer);

/******************************************************************************
* Function Name: cbLinIn
* Description  : Function to return how much data can be placed in the buffer
* Arguments    : IN  pcBuffer - Pointer to the buffer
* Return Value : The length of data until the end of the data or the buffer
******************************************************************************/

extern  size_t cbLinIn(PCBUFF pcBuffer);

/******************************************************************************
* Function Name: cbInPointer
* Description  : Function to return a pointer to the input of the buffer
* Arguments    : IN  pcBuffer - Pointer to the buffer
* Return Value : Pointer to the buffer input
******************************************************************************/

extern  void *cbInPointer(PCBUFF pcBuffer);

/******************************************************************************
* Function Name: cbOutPointer
* Description  : Function to return a pointer to the output of the buffer
* Arguments    : IN  pcBuffer - Pointer to the buffer
* Return Value : Pointer to the buffer input
******************************************************************************/

extern  void *cbOutPointer(PCBUFF pcBuffer);

#ifdef __cplusplus
}
#endif

#endif /* CBUFFER_H_INCLUDED */

/******************************************************************************
End  Of File CBUFFER_H
******************************************************************************/
