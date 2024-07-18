/**
  ******************************************************************************
  * @file    stm32wb_at_ble.h
  * @author  MCD Application Team
  * @brief   Header file of AT BLE commands.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WB_AT_BLE_H
#define STM32WB_AT_BLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wb_at.h"

/* Private includes ----------------------------------------------------------*/
#define FOREACH_AT_BLE_CMD(AT_BLE_CMD)\
        AT_BLE_CMD(BLE_TEST)\
        AT_BLE_CMD(BLE_VER)\
        AT_BLE_CMD(BLE_BTEN)\
        AT_BLE_CMD(BLE_DEVSTAT)\
        AT_BLE_CMD(BLE_PROFILE)\
        AT_BLE_CMD(BLE_NONE)\

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,
#define GENERATE_AT_BLE_CB_PROTO(CMD) uint8_t stm32wb_at_##CMD##_cb(stm32wb_at_##CMD##_t *param);
#define GENERATE_AT_BLE_EVENT_HANDLE_PROTO(CMD) uint8_t stm32wb_at_##CMD##_event_handle(void);
#define GENERATE_AT_BLE_CB_FUNC(CMD) __weak uint8_t stm32wb_at_##CMD##_cb(stm32wb_at_##CMD##_t *param){UNUSED(param);return 1;}
/* Exported types ------------------------------------------------------------*/

/* BLE_TEST */
typedef struct
{
  uint8_t status;
} stm32wb_at_BLE_TEST_t;

/* BLE_VER */
typedef struct
{
  char module_type[7];
  char fw_ver[7];
  char production_date[9];
} stm32wb_at_BLE_VER_t;

/* BLE_BTEN */
typedef struct
{
  uint8_t power;
} stm32wb_at_BLE_BTEN_t;

/* BLE_DEVSTAT */
typedef union {
    uint8_t status;                     // The whole status byte
    struct {
      uint8_t power_on : 1;             // BIT[0] - Power status
      uint8_t br_edr_discoverable : 1;  // BIT[1] - BR/EDR discoverability
      uint8_t ble_advertising : 1;      // BIT[2] - BLE advertising status
      uint8_t br_edr_scanning : 1;      // BIT[3] - BR/EDR scanning status
      uint8_t ble_scanning : 1;         // BIT[4] - BLE scanning status
      uint8_t reserved : 3;             // Remaining bits (BIT[5] to BIT[7]) reserved for future use
    } bits;
} stm32wb_at_BLE_DEVSTAT_t;

/* BLE_PROFILE */
typedef union {
    uint16_t profile;
    struct {
        uint16_t spp : 1;               // BIT[0] - SPP (Serial Port Profile)
        uint16_t gatt_server : 1;       // BIT[1] - GATT Server
        uint16_t gatt_client : 1;       // BIT[2] - GATT Client
        uint16_t hfp_hf : 1;            // BIT[3] - HFP-HF (Hands-Free Profile Handsfree)
        uint16_t hfp_ag : 1;            // BIT[4] - HFP-AG (Hands-Free Profile Audio Gateway)
        uint16_t a2dp_sink : 1;         // BIT[5] - A2DP Sink (Advanced Audio Distribution Profile)
        uint16_t a2dp_source : 1;       // BIT[6] - A2DP Source (Advanced Audio Distribution Profile)
        uint16_t avrcp_controller : 1;  // BIT[7] - AVRCP Controller (Audio/Video Remote Controller Profile)
        uint16_t avrcp_target : 1;      // BIT[8] - AVRCP Target (Audio/Video Remote Controller Profile)
        uint16_t hid_keyboard : 1;      // BIT[9] - HID Keyboard (Human Interface Profile)
        uint16_t pbap_server : 1;       // BIT[10] - PBAP Server (Phonebook Access Profile)
        uint16_t reserved : 4;          // BIT[11] to BIT[14] - Reserved for future use
        uint16_t iap2 : 1;              // BIT[15] - iAP2 (For iOS devices)
    } bits;
} stm32wb_at_BLE_PROFILE_t;

/* BLE_NONE */
typedef struct
{
  uint8_t dummy;
} stm32wb_at_BLE_NONE_t;

/* Exported constants --------------------------------------------------------*/
typedef enum {
  FOREACH_AT_BLE_CMD(GENERATE_ENUM)
}stm32wb_at_BLE_CMD_t;

extern const char *AT_BLE_CMD_STRING[BLE_NONE+1];

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
FOREACH_AT_BLE_CMD(GENERATE_AT_BLE_CB_PROTO)
FOREACH_AT_BLE_CMD(GENERATE_AT_BLE_EVENT_HANDLE_PROTO)

#ifdef __cplusplus
}
#endif

#endif /* STM32WB_AT_BLE_H */
