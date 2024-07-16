/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLE_AT_CLIENT_EVENT_HANDLE_H
#define BLE_AT_CLIENT_EVENT_HANDLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef uint8_t (*ble_at_event_handle)(void);

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* BLE_AT_CLIENT_EVENT_HANDLE_H */
