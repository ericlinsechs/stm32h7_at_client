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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t stm32wb_at_BLE_TEST_event_handle(void)
{
    if (global_ble_test == BLE_RET_TEST_ERROR) {
        global_ble_test = 0;
        ble_debug("Error\n");
    }

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
    ble_debug("Status Byte: 0x%02X\n", globla_ble_devstat.status);

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
