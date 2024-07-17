/**
  ******************************************************************************
  * @file    stm32wb_at_client.c
  * @author  MCD Application Team
  * @brief   AT client.
  *
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
#include "stm32wb_at_client.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SRV_CUSTOM_APP_SVC_OFFSET     (3U)
#define SRV_CUSTOM_APP_SVC_COUNT      (5U)
#define PREFIX "BLE_"

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static char client_buff_tx[64];
static volatile stm32wb_at_BLE_CMD_t client_current_cmd;

/* Private function prototypes -----------------------------------------------*/
static uint8_t stm32wb_at_client_Wait_ready(void);

/**
 * @brief Remove the "BLE_" prefix from a given string if it exists.
 * @param str The input string which may start with the "BLE_" prefix.
 * @retval A pointer to the part of the string after the "BLE_" prefix if it exists,
 *         otherwise a pointer to the original string.
 */
static inline const char* remove_prefix(const char *str) {
    if (strncmp(str, PREFIX, strlen(PREFIX)) == 0) {
        return str + strlen(PREFIX);
    }
    return str;
}
/* Exported functions --------------------------------------------------------*/

/**
 * @brief Init the at client
 * @param None
 * @retval 0 in case of success, an error code otherwise
 */
uint8_t stm32wb_at_client_Init(void)
{
  (void)memset(&client_buff_tx[0], 0, sizeof(client_buff_tx));
  client_current_cmd =  BLE_NONE;

  return 0;
}

/**
 * @brief Query the server on a specified command
 * @param cmd code to query
 * @retval 0 in case of success, an error code otherwise
 */
uint8_t stm32wb_at_client_Query(stm32wb_at_BLE_CMD_t cmd)
{
  uint8_t status;

  (void)stm32wb_at_client_Wait_ready();

  if(cmd == BLE_TEST)
  {
    (void)strcpy(client_buff_tx, AT_CMD_TEST);
    (void)strcat(client_buff_tx, AT_EOL);

    client_current_cmd = cmd;
    status = stm32wb_at_ll_Transmit((uint8_t *)&client_buff_tx[0], (uint16_t)strlen(client_buff_tx));
    (void)memset(&client_buff_tx[0], 0, sizeof(client_buff_tx));
  }
  else if(cmd < BLE_NONE)
  {
    (void)strcpy(client_buff_tx, AT_PRE_CMD);
    (void)strcat(client_buff_tx, remove_prefix(AT_BLE_CMD_STRING[cmd]));
    (void)strcat(client_buff_tx, AT_EOL);

    client_current_cmd = cmd;
    status = stm32wb_at_ll_Transmit((uint8_t *)&client_buff_tx[0], (uint16_t)strlen(client_buff_tx));
    (void)memset(&client_buff_tx[0], 0, sizeof(client_buff_tx));
  }
  else
  {
    status = 1;
  }

  return status;
}

/**
 * @brief Process an At string and perform required actions
 * @param str pointer to the string to process
 * @retval 0 in case of success, an error code otherwise
 */
uint8_t stm32wb_at_client_Process_rx_frame(char * str)
{
  uint8_t status;
  char *str_local;

  status = 1;
  str_local = str;

  if( strcmp(str_local, AT_CMD_STATUS_OK) == 0)
  {
    stm32wb_at_BLE_TEST_t param;
    client_current_cmd = BLE_NONE;
    param.status = BLE_RET_TEST_OK;
    stm32wb_at_BLE_TEST_cb(&param);
    status = 0;
  }
  else if( strncmp(str_local, AT_CMD_STATUS_ERROR, 3) == 0)
  {
    stm32wb_at_BLE_TEST_t param;
    client_current_cmd = BLE_NONE;
    param.status = BLE_RET_TEST_ERROR;
    stm32wb_at_BLE_TEST_cb(&param);
    status = 0;
  }
  else if( strncmp(str_local, AT_REPLY, strlen(AT_REPLY)) == 0)
  {
    str_local++;
    /* check if it's a response of current command */
    if( strncmp(str_local, remove_prefix(AT_BLE_CMD_STRING[client_current_cmd]), strlen(remove_prefix(AT_BLE_CMD_STRING[client_current_cmd]))) == 0)
    {
      str_local += strlen(remove_prefix(AT_BLE_CMD_STRING[client_current_cmd]));

      if( strncmp(str_local, AT_GET, strlen(AT_GET)) == 0)
      {
        str_local++;
        /* extract params regarding current command */
        switch (client_current_cmd) {
          case BLE_VER:
          {
            stm32wb_at_BLE_VER_t param;
            char * token;
            status = 0;
            
            /* Module type */
            token = strtok(str_local, AT_SEPARATOR);
            if(token != NULL)
            {
              strncpy(param.module_type, token, sizeof(param.module_type) - 1);
              param.module_type[sizeof(param.module_type) - 1] = '\0';
            }
            else
            {
              status |= 1U;
            }
            /* Firmware version */
            token = strtok(NULL, AT_SEPARATOR);
            if(token != NULL)
            {
              strncpy(param.fw_ver, token, sizeof(param.fw_ver) - 1);
              param.fw_ver[sizeof(param.fw_ver) - 1] = '\0';
            }
            else
            {
              status |= 1U;
            }

            /* Production date */
            token = strtok(NULL, AT_SEPARATOR);
            if(token != NULL)
            {
              strncpy(param.production_date, token, sizeof(param.production_date) - 1);
              param.production_date[sizeof(param.production_date) - 1] = '\0';
            }
            else
            {
              status |= 1U;
            }

            if(status == 0U)
            {
              status = stm32wb_at_BLE_VER_cb(&param);
              client_current_cmd = BLE_NONE;
            }
            break;
          }
          case BLE_DEVSTAT:
          {
            stm32wb_at_BLE_DEVSTAT_t param;
            char * token;
            status = 0;
            
            token = strtok(str_local, AT_SEPARATOR);
            if(token != NULL)
              param.status = (uint8_t)strtol(token, NULL, 0);
            else
              status |= 1U;

            if(status == 0U) {
              status = stm32wb_at_BLE_DEVSTAT_cb(&param);
              client_current_cmd = BLE_NONE;
            }
            break;
          }
          default:
            break;
        }
      }
    }
  }

  return status;
}

/**
 * @brief Send an AT set with specified command and parameters
 * @param cmd command code
 * @param param pointer to parameters of command
 * @retval 0 in case of success, an error code otherwise
 */
uint8_t stm32wb_at_client_Set(stm32wb_at_BLE_CMD_t cmd, void *param)
{
  uint8_t status;

  (void)stm32wb_at_client_Wait_ready();

  if(cmd < BLE_NONE)
  {
    client_current_cmd = cmd;

    (void)strcpy(client_buff_tx, AT_PRE_CMD);
    (void)strcat(client_buff_tx, AT_BLE_CMD_STRING[cmd]);
    (void)strcat(client_buff_tx, AT_SET);

    switch (cmd) {
      case BLE_BTEN:
      {
        stm32wb_at_BLE_BTEN_t *p = (stm32wb_at_BLE_BTEN_t*)param;
        char str_tmp[8];
        
        (void)sprintf(str_tmp, "%d", p->power);
        (void)strcat(client_buff_tx, str_tmp);

        break;
      }
      default:
        break;
    }

    (void)strcat(client_buff_tx, AT_EOL);

    client_current_cmd = cmd;
    status = stm32wb_at_ll_Transmit((uint8_t *)&client_buff_tx[0], (uint16_t)strlen(client_buff_tx));
    (void)memset(&client_buff_tx[0], 0, sizeof(client_buff_tx));
  }
  else
  {
    status = 1;
  }

  return status;
}

/**
 * @brief Wait for the last AT command completed
 * @param None
 * @retval 0 in case of success, an error code otherwise
 */
static uint8_t stm32wb_at_client_Wait_ready(void)
{
  while (client_current_cmd !=  BLE_NONE)
  {
  }

  return 0;
}
