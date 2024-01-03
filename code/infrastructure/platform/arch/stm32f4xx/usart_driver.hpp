/**
*********************************************************************************************************
* Copyright (C) 2023-2026 by liyoyan - All Rights Reserved.                                              *
*                                                                                                       *
* This file is part of the project.                                                                     *
*                                                                                                       *
* This file can not be copied and/or distributed without the express permission of the project owner.   *
*********************************************************************************************************/

/**
*********************************************************************************************************
* @file   : usart_driver.hpp
* @author : liyoyan
* @date   : 2 Jan 2024
* @brief  :
*
*********************************************************************************************************
*/

#include "infrastructure/platform/hal/usart.hpp"
#include "stm32f4xx.h"

class UsartDriver : public Usart {
private:
    uint32_t Usart_tx_mailbox;

    bool is_error = false;

private:
    USART_HandleTypeDef *_husart;

public:
    UsartDriver(USART_HandleTypeDef *husart)
        : _husart(husart)
        {

        }

void Usart_Send(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
        const uint32_t *tmp;

  /* Check that a Tx process is not already ongoing */
  if (huart->gState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);

    huart->pTxBuffPtr = pData;
    huart->TxXferSize = Size;
    huart->TxXferCount = Size;

    huart->ErrorCode = HAL_UART_ERROR_NONE;
    huart->gState = HAL_UART_STATE_BUSY_TX;

    /* Set the UART DMA transfer complete callback */
    huart->hdmatx->XferCpltCallback = UART_DMATransmitCplt;

    /* Set the UART DMA Half transfer complete callback */
    huart->hdmatx->XferHalfCpltCallback = UART_DMATxHalfCplt;

    /* Set the DMA error callback */
    huart->hdmatx->XferErrorCallback = UART_DMAError;

    /* Set the DMA abort callback */
    huart->hdmatx->XferAbortCallback = NULL;

    /* Enable the UART transmit DMA stream */
    tmp = (const uint32_t *)&pData;
    HAL_DMA_Start_IT(huart->hdmatx, *(const uint32_t *)tmp, (uint32_t)&huart->Instance->DR, Size);

    /* Clear the TC flag in the SR register by writing 0 to it */
    __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_TC);

    /* Process Unlocked */
    __HAL_UNLOCK(huart);

    /* Enable the DMA transfer for transmit request by setting the DMAT bit
       in the UART CR3 register */
    ATOMIC_SET_BIT(huart->Instance->CR3, USART_CR3_DMAT);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

void Usart_Receive(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size)
{
  /* Check that a Rx process is not already ongoing */
  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(huart);

    /* Set Reception type to Standard reception */
    huart->ReceptionType = HAL_UART_RECEPTION_STANDARD;

    return (UART_Start_Receive_DMA(huart, pData, Size));
  }
  else
  {
    return HAL_BUSY;
  }
}
