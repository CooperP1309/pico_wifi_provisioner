#pragma once

typedef enum {

    PICO_PROV_OK            = 0,

    PICO_PROV_ERR               = -1,
    PICO_PROV_ERR_INIT          = -2,
    PICO_PROV_ERR_FS_MOUNT      = -3,
    PICO_PROV_ERR_FS_READ       = -4,
    PICO_PROV_ERR_AP_INIT       = -5,
    PIVO_PROV_ERR_DHCP_INIT     = -6,
    PICO_PROV_ERR_DHCP_DEINIT   = -7,
    PICO_PROV_ERR_AP_DEINIT     = -8,
    PICO_PROV_ERR_FS_UMOUNT     = -9

} pico_prov_err_t;