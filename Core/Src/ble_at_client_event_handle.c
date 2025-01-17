/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ble_at_client_event_handle.h"
#include "stm32wb_at.h"
#include "stm32wb_at_ble.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ASSIGN_AT_BLE_EVENT_HANDLE(CMD) stm32wb_at_##CMD##_event_handle,
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern volatile uint8_t global_ble_test;
extern stm32wb_at_BLE_VER_t global_ble_ver;
extern stm32wb_at_BLE_DEVSTAT_t globla_ble_devstat;
extern stm32wb_at_BLE_PROFILE_t global_ble_profile;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t stm32wb_at_BLE_TEST_event_handle(void)
{
    if (global_ble_test == BLE_RET_TEST_ERROR)
        ble_debug("Error\n");
    global_ble_test = 0;

    return 0;
}

uint8_t stm32wb_at_BLE_VER_event_handle(void)
{
    ble_debug("Module Type: %s\n", global_ble_ver.module_type);
    ble_debug("Firmware Version: %s\n", global_ble_ver.fw_ver);
    ble_debug("Production Date: %s\n", global_ble_ver.production_date);

    return 0;
}

uint8_t stm32wb_at_BLE_BTEN_event_handle(void)
{
    return 0;
}

uint8_t stm32wb_at_BLE_DEVSTAT_event_handle(void)
{
    ble_debug("Power On: %d\n", globla_ble_devstat.bits.power_on);
    ble_debug("BR/EDR Discoverable: %d\n",
              globla_ble_devstat.bits.br_edr_discoverable);
    ble_debug("BLE Advertising: %d\n", globla_ble_devstat.bits.ble_advertising);
    ble_debug("BR/EDR Scanning: %d\n", globla_ble_devstat.bits.br_edr_scanning);
    ble_debug("BLE Scanning: %d\n", globla_ble_devstat.bits.ble_scanning);

    return 0;
}

uint8_t stm32wb_at_BLE_PROFILE_event_handle(void)
{
    ble_debug("SPP: %d\n", global_ble_profile.bits.spp);
    ble_debug("GATT Server: %d\n", global_ble_profile.bits.gatt_server);
    ble_debug("GATT Client: %d\n", global_ble_profile.bits.gatt_client);
    ble_debug("HFP-HF: %d\n", global_ble_profile.bits.hfp_hf);
    ble_debug("HFP-AG: %d\n", global_ble_profile.bits.hfp_ag);
    ble_debug("A2DP Sink: %d\n", global_ble_profile.bits.a2dp_sink);
    ble_debug("A2DP Source: %d\n", global_ble_profile.bits.a2dp_source);
    ble_debug("AVRCP Controller: %d\n",
              global_ble_profile.bits.avrcp_controller);
    ble_debug("AVRCP Target: %d\n", global_ble_profile.bits.avrcp_target);
    ble_debug("HID Keyboard: %d\n", global_ble_profile.bits.hid_keyboard);
    ble_debug("PBAP Server: %d\n", global_ble_profile.bits.pbap_server);
    ble_debug("iAP2: %d\n", global_ble_profile.bits.iap2);

    return 0;
}

uint8_t stm32wb_at_BLE_NONE_event_handle(void)
{
    return 0;
}
/* Declare an array of BLE AT event handle function pointers */
ble_at_event_handle event_handles[] = {
    FOREACH_AT_BLE_CMD(ASSIGN_AT_BLE_EVENT_HANDLE)};
/* USER CODE END 0 */

/******************************************************************************/
