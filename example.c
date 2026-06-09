/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
  *                   Called by the main after system initialization
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "example.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables */
lsm6dsv16x_object_t *pLsm6dsv16x0; /* pointer referencing the LSM6DSV16X object instance */
lsm6dsv16x_axes_t gAccData; /* This variable store the acceleratometer measurement (unit: deg mg) */
lsm6dsv16x_axes_t gGyroData; /* This variable store the gyroscope measurement (unit mpds) */
/** ########## Step 1 ##########
  * The init of LSM6DSV16X is triggered by the applicative code

  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* Retrieve and store the LSM6DSV16X object pointer */
  pLsm6dsv16x0 = mx_lsm6dsv16x_0_getobject();
  /* Initialize the LSM6DSV16X device 0 */
  if (lsm6dsv16x_drv_init(pLsm6dsv16x0, MX_LSM6DSV16X) != 0)
  {
    PRINTF("[ERROR] Step 1: LSM6DSV16X sensor init error\r\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] Step 1: LSM6DSV16X sensor init completed\r\n");
  /* LSM6DSV16X device 0: enable the accelerometer feature */
  if (lsm6dsv16x_drv_acc_enable(pLsm6dsv16x0) != 0)
  {
    PRINTF("[ERROR] Enabling the ACC feature failed\r\n");
    goto _app_init_exit;
  }
    PRINTF("[INFO] Enabling ACC feature SUCCESS\r\n");
  /* LSM6DSV16X device 0: enable the gyroscope feature */
  if (lsm6dsv16x_drv_gyro_enable(pLsm6dsv16x0) != 0)
  {
    PRINTF("[ERROR] Enabling the GYRO feature failed\r\n");
    goto _app_init_exit;
  }
   PRINTF("[INFO] Enabling GYRO feature SUCCESS\r\n");
   return_status = EXEC_STATUS_OK;
_app_init_exit:
  return return_status;
}

/**
  * ########## Step 2 ##########
  * Gets the values from LSM6DSV16X.
  * The values are displayed on the terminal.
  * output: EXEC_STATUS_OK if OK, EXEC_STATUS_ERROR in case of error
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* LSM6DSV16X device 0: get the acceleration value and print it */
  if (lsm6dsv16x_drv_acc_get_axes(pLsm6dsv16x0, &gAccData) != 0)
  {
    PRINTF("[ERROR] Step 2: Reading acceleration error\n");
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: ACC X=%" PRIi32 " Y=%" PRIi32 " Z=%" PRIi32 "\n", (int32_t)gAccData.x_axis,
         (int32_t)gAccData.y_axis, (int32_t)gAccData.z_axis);
  /* LSM6DSV16X device 0: get the gyroscope value and print it */
  if (lsm6dsv16x_drv_gyro_get_axes(pLsm6dsv16x0, &gGyroData) != 0)
  {
    PRINTF("[ERROR] Step 2: Reading gyroscope error\n");
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: GYR X=%" PRIi32 " Y=%" PRIi32 " Z=%" PRIi32 "\n", (int32_t)gGyroData.x_axis,
         (int32_t)gGyroData.y_axis, (int32_t)gGyroData.z_axis);
  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
}

/** ########## Step 3 ##########
  * In this example, app_deinit is never called and is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  lsm6dsv16x_drv_deinit(pLsm6dsv16x0);

  return EXEC_STATUS_OK;
}
