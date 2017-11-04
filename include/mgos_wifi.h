/*
 * Copyright (c) 2014-2016 Cesanta Software Limited
 * All rights reserved
 */

#ifndef CS_MOS_LIBS_WIFI_SRC_MGOS_WIFI_H_
#define CS_MOS_LIBS_WIFI_SRC_MGOS_WIFI_H_

#include <stdbool.h>
#include "mgos_sys_config.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

bool mgos_wifi_setup_sta(const struct mgos_config_wifi_sta *cfg);

bool mgos_wifi_setup_ap(const struct mgos_config_wifi_ap *cfg);

bool mgos_wifi_connect(void); /* To the previously _setup network. */

bool mgos_wifi_disconnect(void);

#define MGOS_NET_IF_WIFI_STA 0
#define MGOS_NET_IF_WIFI_AP 1

/*
 * DEPRECATED: API below is deprecated in favor of mgos_net_* API.
 * Check for events with if_type == MGOS_NET_IF_TYPE_WIFI
 * and if_instance == MGOS_NET_IF_WIFI_STA or MGOS_NET_IF_WIFI_AP
 */
enum mgos_wifi_status {
  MGOS_WIFI_DISCONNECTED = 0,
  MGOS_WIFI_CONNECTING = 1,
  MGOS_WIFI_CONNECTED = 2,
  MGOS_WIFI_IP_ACQUIRED = 3,
};

typedef void (*mgos_wifi_changed_t)(enum mgos_wifi_status event, void *arg);
/* Add a callback to be invoked when WiFi state changes. */
void mgos_wifi_add_on_change_cb(mgos_wifi_changed_t fn, void *arg);
/* Remove a previously added callback, fn and arg have to match exactly. */
void mgos_wifi_remove_on_change_cb(mgos_wifi_changed_t fn, void *arg);

bool mgos_wifi_validate_ap_cfg(const struct mgos_config_wifi_ap *cfg,
                               char **msg);
bool mgos_wifi_validate_sta_cfg(const struct mgos_config_wifi_sta *cfg,
                                char **msg);

enum mgos_wifi_status mgos_wifi_get_status(void);
/* These return allocated strings which will be free'd. */
char *mgos_wifi_get_status_str(void);
char *mgos_wifi_get_connected_ssid(void);
char *mgos_wifi_get_sta_default_dns(void);

/*
 * Callback must be invoked, with list of SSIDs or NULL on error.
 * Caller owns SSIDS, they are not freed by the callee.
 * Invoking inline is ok.
 */

enum mgos_wifi_auth_mode {
  MGOS_WIFI_AUTH_MODE_OPEN = 0,
  MGOS_WIFI_AUTH_MODE_WEP = 1,
  MGOS_WIFI_AUTH_MODE_WPA_PSK = 2,
  MGOS_WIFI_AUTH_MODE_WPA2_PSK = 3,
  MGOS_WIFI_AUTH_MODE_WPA_WPA2_PSK = 4,
  MGOS_WIFI_AUTH_MODE_WPA2_ENTERPRISE = 5,
};

struct mgos_wifi_scan_result {
  char ssid[33];
  uint8_t bssid[6];
  enum mgos_wifi_auth_mode auth_mode;
  int channel;
  int rssi;
};

typedef void (*mgos_wifi_scan_cb_t)(int num_res,
                                    struct mgos_wifi_scan_result *res,
                                    void *arg);
void mgos_wifi_scan(mgos_wifi_scan_cb_t cb, void *arg);

bool mgos_wifi_init(void);

#ifdef MGOS_HAVE_MJS
struct mjs;
void mgos_wifi_scan_js(struct mjs *mjs);
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CS_MOS_LIBS_WIFI_SRC_MGOS_WIFI_H_ */
