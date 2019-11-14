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
 *******************************************************************************
 * File Name    : cbuffer.c
 * Version      : 1.02
 * Device(s)    : Renesas
 * Tool-Chain   : GNUARM-NONE-EABI v14.02
 * OS           : None
 * H/W Platform : EBK
 * Description  : Circular Buffering Routines
 *******************************************************************************
 * History      : DD.MM.YYYY Version Description
 *              : 04.02.2010 1.00    First Release
 *              : 10.06.2010 1.01    Updated type definitions
 *              : 07.03.2011 1.02    Added Memeory Type Parameter
 ******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "r_cbuffer.h"
#include "r_typedefs.h"

/* OS abstraction specific API header */
#include "r_os_abstraction_api.h"

/******************************************************************************
 Typedef definitions
 ******************************************************************************/

/* Define the structure of a buffer */
typedef struct _CBUFF
{
    /* a pointer to the base of the memory */
    uint8_t *pBase;

    /* The in index */
    size_t  stInIdx;

    /* The out index */
    size_t  stOutIdx;

    /* The length of the circular buffer */
    size_t  stLength;
} CBUFF;

/* Define the structure of a buffer including alignment */
typedef struct _CBOBJECT
{
    CBUFF    cBuffer;
    uint32_t ulAlign;
} CBOBJECT, *PCBOBJECT;

/******************************************************************************
 Function Prototypes
 ******************************************************************************/

static void cbAdjustOutIndex (PCBUFF pcBuffer, size_t stLength);
static void cbAdjustInIndex (PCBUFF pcBuffer, size_t stLength);

/******************************************************************************
 Exported global variables and functions (to be accessed by other files)
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbCreate
 * Description  : Function to create a circular buffer
 * Arguments    : IN  memType - The type of memory to use
 *              : IN  stBufferSize - The size of the circular buffer required
 * Return Value : Pointer to the circular buffer or NULL on failure
 ******************************************************************************/
PCBUFF cbCreate (size_t stBufferSize)
{
    PCBUFF pcBuffer;

    /* Allocate the buffer with enough memory for alignment and extra byte for signalling */
    pcBuffer = (PCBUFF) R_OS_Malloc(stBufferSize + sizeof(CBOBJECT) + sizeof(uint8_t), R_MEMORY_REGION_DEFAULT);

    if (pcBuffer)
    {
        /* Initialise the buffer variables */
        pcBuffer->pBase = (uint8_t *) &((PCBOBJECT) pcBuffer)->ulAlign;
        pcBuffer->stLength = (size_t) (stBufferSize + sizeof(uint8_t));
        pcBuffer->stInIdx = 0;
        pcBuffer->stOutIdx = 0;
    }

    return pcBuffer;
}
/******************************************************************************
 End of function cbCreate
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbDestroy
 * Description  : Function to destroy a circular buffer
 * Arguments    : IN  memType - The type of memory to use
 *                IN  pcBuffer - Pointer to the buffer to destroy
 * Return Value : N/A
 ******************************************************************************/
void cbDestroy (PCBUFF pcBuffer)
{
    R_OS_Free((void *)&pcBuffer);
}
/******************************************************************************
 End of function cbDestroy
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbPut
 * Description  : Put a uint8_t in the Buffer
 * Arguments    : IN  pcBuffer - pointer to the circular buffer
 *                IN  byData - The byte to put into the buffer
 * Return Value : true if the byte was entered into the buffer
 ******************************************************************************/
_Bool cbPut (PCBUFF pcBuffer, uint8_t byData)
{
    size_t l_stInIdx = (pcBuffer->stInIdx + sizeof(uint8_t));

    /* Check for top of Buffer */
    if (l_stInIdx >= pcBuffer->stLength)
    {
        l_stInIdx = 0;
    }

    /* If there is room */
    if (l_stInIdx != pcBuffer->stOutIdx)
    {
        /* Put the byte in the buffer */
        *(pcBuffer->pBase + pcBuffer->stInIdx) = byData;

        /* Update the index */
        pcBuffer->stInIdx = l_stInIdx;
        return true;
    }

    return false;
}
/******************************************************************************
 End of function cbPut
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbGet
 * Description  : Get a uint8_t from the Buffer
 * Arguments    : IN  pcBuffer - pointer to the circular buffer
 *                OUT pbyData - pointer to the destination byte of data
 * Return Value : true if a byte was retrieved
 ******************************************************************************/
_Bool cbGet (PCBUFF pcBuffer, uint8_t *pbyData)
{
    /* Check that the buffer is not empty */
    if (pcBuffer->stInIdx != pcBuffer->stOutIdx)
    {
        size_t l_stOutIdx;

        /* Get Data from Buffer, bump in index */
        l_stOutIdx = pcBuffer->stOutIdx;
        *pbyData = *(pcBuffer->pBase + l_stOutIdx++);

        /* Check for top of Buffer */
        if (l_stOutIdx >= pcBuffer->stLength)
        {
            l_stOutIdx = 0;
        }

        /* Update the index */
        pcBuffer->stOutIdx = l_stOutIdx;
        return true;
    }

    return false;
}
/******************************************************************************
 End of function cbGet
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbUsed
 * Description  : Function to return the number of bytes in the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 * Return Value : The number of bytes in the buffer
 ******************************************************************************/
size_t cbUsed (PCBUFF pcBuffer)
{
    size_t l_stInIdx, l_stOutIdx;
    size_t stUsed;
    l_stInIdx = pcBuffer->stInIdx;
    l_stOutIdx = pcBuffer->stOutIdx;
    if (l_stInIdx < l_stOutIdx)
    {
        stUsed = (pcBuffer->stLength - (l_stOutIdx - l_stInIdx));
    }
    else
    {
        stUsed = (l_stInIdx - l_stOutIdx);
    }
    return stUsed;
}
/******************************************************************************
 End of function  cbUsed
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbFree
 * Description  : Function to return the number of free space in the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 * Return Value : The number of bytes that can be put in the buffer
 ******************************************************************************/
size_t cbFree (PCBUFF pcBuffer)
{
    return (pcBuffer->stLength - (cbUsed(pcBuffer) + sizeof(uint8_t)));
}
/******************************************************************************
 End of function cbFree
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbFull
 * Description  : Function to return true when the buffer is full
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
_Bool cbFull (PCBUFF pcBuffer)
{
    size_t l_stInIdx = (pcBuffer->stInIdx + sizeof(uint8_t));

    /* Check for top of Buffer */
    if (l_stInIdx >= pcBuffer->stLength)
    {
        l_stInIdx = 0;
    }

    /* Now test for full */
    if (l_stInIdx == pcBuffer->stOutIdx)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/******************************************************************************
 End of function cbFull
 ******************************************************************************/

/*****************************************************************************
 * Function Name: cbClear
 * Description  : Function to clear the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer to clear
 * Return Value :
 ******************************************************************************/
void cbClear (PCBUFF pcBuffer)
{
    pcBuffer->stInIdx = pcBuffer->stOutIdx = 0;
}
/*****************************************************************************
 End of function  cbClear
 ******************************************************************************/

volatile uint8_t mcstatus = 0;

/******************************************************************************
 * Function Name: cbGetPacket
 * Description  : Function to get data from the buffer but not check it out
 *                cbUsed should be called before calls to this function to
 *                ensure that there is sufficient data in the buffer
 * Arguments    : IN  pcBuffer - pointer to the buffer to get the data from
 *                IN  stPacketLength - the length of data to read from the
 *                                     buffer
 *                IN  pDest - the destination address
 * Return Value : none
 ******************************************************************************/
void cbGetPacket (PCBUFF pcBuffer, size_t stPacketLength, void *pDest)
{
    uint8_t *pData, *pTemp;
    size_t stBlock;

    /* Get the pointer to the data */
    pData = (pcBuffer->pBase + pcBuffer->stOutIdx);

    /* Get the length of the linear chunk */
    stBlock = cbLinOut(pcBuffer);

    /* Check to see if this can be done in one hit */
    if (stBlock >= stPacketLength)
    {
        /* All in one block */
        mcstatus = 1;
        memcpy(pDest, pData, stPacketLength);
        mcstatus = 1;
    }
    else
    {
        /* Splits into two blocks */
        mcstatus = 2;
        memcpy(pDest, pData, stBlock);
        mcstatus = 0;
        pData = pcBuffer->pBase;

        /* re-calculate the address */
        pTemp = ((uint8_t *) pDest) + stBlock;

        /* calculate size of second block */
        stBlock = (stPacketLength - stBlock);
        mcstatus = 3;
        memcpy(pTemp, pData, stBlock);
        mcstatus = 0;
    }
}
/******************************************************************************
 End of function cbGetPacket
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbCheckOut
 * Description  : Function to check the data out of the data following a call to
 *                cbGetPacket
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 *                IN  stPacketLength - the size of the data to check out
 * Return Value : none
 ******************************************************************************/
void cbCheckOut (PCBUFF pcBuffer, size_t stPacketLength)
{
    size_t stBlock;

    /* Get the length of the linear chunk */
    stBlock = cbLinOut(pcBuffer);

    /* Check to see if this can be done in one hit */
    if (stBlock >= stPacketLength)
    {
        /* All in one block */
        cbAdjustOutIndex(pcBuffer, stPacketLength);
    }
    else
    {
        /* Two blocks */
        cbAdjustOutIndex(pcBuffer, stBlock);

        /* Calculate size of second block */
        stBlock = (stPacketLength - stBlock);
        cbAdjustOutIndex(pcBuffer, stBlock);
    }
}
/******************************************************************************
 End of function cbCheckOut
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbPutPacket
 * Description  : Function to put a packet of data into the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 *                IN  stPacketLength - The length of the packet to put
 *                IN  pSrc - Pointer to the data to put
 * Return Value : none
 ******************************************************************************/
void cbPutPacket (PCBUFF pcBuffer, size_t stPacketLength, void *pSrc)
{
    uint8_t *pData, *pTemp;
    size_t stBlock;

    /* How much linear space is there */
    stBlock = cbLinIn(pcBuffer);
    pData = (pcBuffer->pBase + pcBuffer->stInIdx);

    /* Check for one or two blocks */
    if (stBlock >= stPacketLength)
    {
        /* All in one block */
        mcstatus = 4;
        memcpy(pData, pSrc, stPacketLength);
        mcstatus = 0;
    }
    else
    {
        /* Splits into two blocks */
        mcstatus = 5;
        memcpy(pData, pSrc, stBlock);
        mcstatus = 0;
        pData = pcBuffer->pBase;

        /* Re-calculate the address */
        pTemp = ((uint8_t *) pSrc) + stBlock;

        /* Calculate size of second block */
        stBlock = (stPacketLength - stBlock);
        mcstatus = 6;
        memcpy(pData, pTemp, stBlock);
        mcstatus = 0;
    }
}
/******************************************************************************
 End of function cbPutPacket
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbCheckIn
 * Description  : Function to check a packet into the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 *                IN  stPacketLength - The length of data to check in
 * Return Value : none
 ******************************************************************************/
void cbCheckIn (PCBUFF pcBuffer, size_t stPacketLength)
{
    size_t stBlock;

    /* Find out the free linear space there is in the buffer */
    stBlock = cbLinIn(pcBuffer);

    /* Test to see if it fits or if it splits */
    if (stBlock >= stPacketLength)
    {
        /* All in one block */
        cbAdjustInIndex(pcBuffer, stPacketLength);
    }
    else
    {
        /* Two blocks */
        cbAdjustInIndex(pcBuffer, stBlock);

        /* Calculate size of second block */
        stBlock = (stPacketLength - stBlock);
        cbAdjustInIndex(pcBuffer, stBlock);
    }
}
/******************************************************************************
 End of function cbCheckIn
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbLinOut
 * Description  : Function to calculate how much can be delivered in one hit
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 * Return Value : The number of bytes until the end of the data or the buffer
 ******************************************************************************/
size_t cbLinOut (PCBUFF pcBuffer)
{
    if (pcBuffer->stInIdx == pcBuffer->stOutIdx)
    {
        /* When empty nothig to take out */
        return 0;
    }
    else
    {
        size_t l_stInIdx, l_stOutIdx;

        /* Snap shot of Buffer controls as  ISR may be updating in background */
        l_stInIdx = pcBuffer->stInIdx;
        l_stOutIdx = pcBuffer->stOutIdx;

        /* Test for buffer wrap */
        if (l_stOutIdx > l_stInIdx)
        {
            /* Until the end (wrapped) */
            return (pcBuffer->stLength - l_stOutIdx);
        }
        else
        {
            /* Until the in index */
            return (l_stInIdx - l_stOutIdx);
        }
    }
}
/******************************************************************************
 End of function cbLinOut
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbLinIn
 * Description  : Function to return how much data can be placed in the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 * Return Value : The length of data until the end of the data or the buffer
 ******************************************************************************/
size_t cbLinIn (PCBUFF pcBuffer)
{
    if (cbFull(pcBuffer) == false)
    {
        size_t l_stInIdx, l_stOutIdx;

        /* Snap shot of Buffer controls as */
        /* ISR may be updating in background */
        l_stInIdx = pcBuffer->stInIdx;
        l_stOutIdx = pcBuffer->stOutIdx;

        /* Test for buffer wrap */
        if (l_stInIdx < l_stOutIdx)
        {
            /* Lin in is between out and in */
            return ((l_stOutIdx - sizeof(uint8_t)) - l_stInIdx);
        }
        else if (l_stOutIdx)
        {
            /* Lin in until top but room at bot */
            return (pcBuffer->stLength - l_stInIdx);
        }
        else
        {
            /* lin in to the end - 1 */
            return ((pcBuffer->stLength - sizeof(uint8_t)) - l_stInIdx);
        }
    }
    return 0;
}
/******************************************************************************
 End of function cbLinIn
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbInPointer
 * Description  : Function to return a pointer to the input of the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 * Return Value : Pointer to the buffer input
 ******************************************************************************/
void *cbInPointer (PCBUFF pcBuffer)
{
    return (pcBuffer->pBase + pcBuffer->stInIdx);
}
/******************************************************************************
 End of function cbInPointer
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbOutPointer
 * Description  : Function to return a pointer to the output of the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 * Return Value : Pointer to the buffer input
 ******************************************************************************/
void *cbOutPointer (PCBUFF pcBuffer)
{
    return (pcBuffer->pBase + pcBuffer->stOutIdx);
}
/******************************************************************************
 End of function cbOutPointer
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbAdjustOutIndex
 * Description  : Function to adjust the out index of the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 *                IN  stLength - The length of data to adjust for
 * Return Value : none
 ******************************************************************************/
static void cbAdjustOutIndex (PCBUFF pcBuffer, size_t stLength)
{
    size_t l_stOutIdx = (pcBuffer->stOutIdx + stLength);

    /* Check for top of Buffer */
    if (l_stOutIdx >= pcBuffer->stLength)
    {
        l_stOutIdx = (l_stOutIdx - pcBuffer->stLength);
    }
    pcBuffer->stOutIdx = l_stOutIdx;
}
/******************************************************************************
 End of function cbAdjustOutIndex
 ******************************************************************************/

/******************************************************************************
 * Function Name: cbAdjustInIndex
 * Description  : Function to adjust the in index of the buffer
 * Arguments    : IN  pcBuffer - Pointer to the buffer
 *                IN  stLength - The length of data to adjust for
 * Return Value : none
 ******************************************************************************/
static void cbAdjustInIndex (PCBUFF pcBuffer, size_t stLength)
{
    size_t l_stInIdx = (pcBuffer->stInIdx + stLength);

    /* Check for top of Buffer */
    if (l_stInIdx >= pcBuffer->stLength)
    {
        l_stInIdx = (l_stInIdx - pcBuffer->stLength);
    }
    pcBuffer->stInIdx = l_stInIdx;
}
/******************************************************************************
 End of function cbAdjustInIndex
 ******************************************************************************/

/******************************************************************************
 End  Of File
 ******************************************************************************/
