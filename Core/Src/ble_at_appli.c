/**
 ******************************************************************************
 * @file    ble_at_appli.c
 * @brief   Application of the BLE AT Client project
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ble_at_appli.h"
#include "main.h"
#include "stm32wb_at.h"
#include "stm32wb_at_ble.h"
#include "stm32wb_at_client.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t received_byte;
uint8_t at_buffer[64];
uint8_t global_svc_index = 0;

extern UART_HandleTypeDef huart1;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Triggers the reception of a byte
 * @param  pBuff pointer to the first byte to transmit
 * @param  Size byte count to transfer
 * @retval 0 in case of success, an error code otherwise
 */
uint8_t stm32wb_at_ll_Transmit(uint8_t *pBuff, uint16_t Size)
{
    uint8_t status;

    status = HAL_UART_Transmit(&huart1, pBuff, Size, 0xFFFF);
    //    printf("  TX: %s\r\n",pBuff);

    return status;
}

/**
 * @brief  Triggers the reception of a byte
 * @param  new_frame contains the length of a new frame received in rx buffer,
 * else 0
 * @retval None
 */
uint8_t stm32wb_at_ll_Async_receive(uint8_t new_frame)
{
    uint8_t status;

    if (new_frame != 0) {
        ble_debug("  RX: %s\r\n", at_buffer);
    }
    status = HAL_UART_Receive_IT(&huart1, &received_byte, 1);

    return status;
}

/**
 * @brief  Rx Transfer completed callback
 * @param  UartHandle: UART handle
 * @note   This example shows a simple way to report end of DMA Rx transfer, and
 *         you can add your own implementation.
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    if ((uint32_t) UartHandle->Instance == (uint32_t) USART1) {
        stm32wb_at_Received(received_byte);
    }

    return;
}
