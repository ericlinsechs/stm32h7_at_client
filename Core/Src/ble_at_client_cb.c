/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ble_at_client_cb.h"
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
extern osMessageQId bleRxHandle;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile uint8_t global_ble_test = 0;
stm32wb_at_BLE_VER_t global_ble_ver;
stm32wb_at_BLE_DEVSTAT_t globla_ble_devstat;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t stm32wb_at_BLE_TEST_cb(stm32wb_at_BLE_TEST_t *param)
{
    global_ble_test = param->status;
    if (osMessagePut(bleRxHandle, BLE_TEST, 100) != osOK)
        ble_debug("Fail to put message into queue.\r\n");
    return 0;
}

uint8_t stm32wb_at_BLE_VER_cb(stm32wb_at_BLE_VER_t *param)
{
    strncpy(global_ble_ver.module_type, param->module_type,
            sizeof(global_ble_ver.module_type));
    strncpy(global_ble_ver.fw_ver, param->fw_ver,
            sizeof(global_ble_ver.fw_ver));
    strncpy(global_ble_ver.production_date, param->production_date,
            sizeof(global_ble_ver.production_date));

    if (osMessagePut(bleRxHandle, BLE_VER, 100) != osOK)
        ble_debug("Fail to put message into queue.\r\n");

    return 0;
}

uint8_t stm32wb_at_BLE_DEVSTAT_cb(stm32wb_at_BLE_DEVSTAT_t *param)
{
    globla_ble_devstat.status = param->status;
    if (!osMessagePut(bleRxHandle, BLE_DEVSTAT, 100))
        ble_debug("Fail to put message into queue.\r\n");

    return 0;
}


/* USER CODE END 0 */

/******************************************************************************/
