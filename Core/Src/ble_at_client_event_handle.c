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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern volatile uint8_t global_ble_test;
extern stm32wb_at_BLE_VER_t global_ble_ver;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t stm32wb_at_BLE_TEST_event_handle(void)
{
    if (global_ble_test == BLE_RET_TEST_OK) {
        global_ble_test = 0;
        ble_debug("BLE_TEST OK\n");
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

/* Declare an array of BLE AT event handle function pointers */
ble_at_event_handle event_handles[] = {stm32wb_at_BLE_TEST_event_handle,
                                       stm32wb_at_BLE_VER_event_handle};
/* USER CODE END 0 */

/******************************************************************************/
