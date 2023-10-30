#pragma once

#include <AP_HAL/AP_HAL_Boards.h>
#include <AP_UAVCAN/AP_UAVCAN.h>

#ifndef HAL_MOUNT_ENABLED
#define HAL_MOUNT_ENABLED !HAL_MINIMIZE_FEATURES
#endif

#define AP_MOUNT_BACKEND_DEFAULT_ENABLED HAL_MOUNT_ENABLED

#ifndef HAL_MOUNT_ALEXMOS_ENABLED
#define HAL_MOUNT_ALEXMOS_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED
#endif

#ifndef HAL_MOUNT_GREMSY_ENABLED
#define HAL_MOUNT_GREMSY_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED && (!HAL_MINIMIZE_FEATURES && BOARD_FLASH_SIZE > 1024)
#endif

#ifndef HAL_MOUNT_SCRIPTING_ENABLED
#define HAL_MOUNT_SCRIPTING_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED && AP_SCRIPTING_ENABLED
#endif

#ifndef HAL_MOUNT_SERVO_ENABLED
#define HAL_MOUNT_SERVO_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED
#endif

#ifndef HAL_MOUNT_SIYI_ENABLED
#define HAL_MOUNT_SIYI_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED
#endif

// solo gimbal is enabled explicitly in hwdefs on some Cubes:
#ifndef HAL_SOLO_GIMBAL_ENABLED
#define HAL_SOLO_GIMBAL_ENABLED 0
#endif

#ifndef HAL_MOUNT_STORM32MAVLINK_ENABLED
#define HAL_MOUNT_STORM32MAVLINK_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED
#endif

#ifndef HAL_MOUNT_STORM32SERIAL_ENABLED
#define HAL_MOUNT_STORM32SERIAL_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED
#endif

#ifndef HAL_MOUNT_XACTI_ENABLED
#define HAL_MOUNT_XACTI_ENABLED AP_MOUNT_BACKEND_DEFAULT_ENABLED && AP_DRONECAN_XACTI_MOUNT_ENABLED
#endif
