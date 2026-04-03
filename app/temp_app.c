#include "temp_app.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "demo_temperature.h"
#include "mini_packet.h"

#ifndef TEMP_APP_USE_HALOW_UDP
#define TEMP_APP_USE_HALOW_UDP 0
#endif

#if TEMP_APP_USE_HALOW_UDP
#include "mm_app_common.h"
#include "lwip/fcntl.h"
#include "lwip/inet.h"
#include "lwip/sockets.h"

#ifndef TEMP_APP_HALOW_LOCAL_PORT
#define TEMP_APP_HALOW_LOCAL_PORT 5000
#endif
#endif

extern UART_HandleTypeDef hlpuart1;

__weak int temp_app_halow_poll_line(char *out_line, size_t out_size, size_t *out_len)
{
#if TEMP_APP_USE_HALOW_UDP
    static bool net_ready = false;
    static int rx_sock = -1;
    int received = 0;

    if ((out_line == NULL) || (out_len == NULL) || (out_size < 2U))
    {
        return -2;
    }

    if (!net_ready)
    {
        struct sockaddr_in local_addr;
        int flags;

        app_wlan_init();
        app_wlan_start();

        rx_sock = lwip_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (rx_sock < 0)
        {
            return -3;
        }

        memset(&local_addr, 0, sizeof(local_addr));
        local_addr.sin_family = AF_INET;
        local_addr.sin_port = PP_HTONS(TEMP_APP_HALOW_LOCAL_PORT);
        local_addr.sin_addr.s_addr = PP_HTONL(INADDR_ANY);

        if (lwip_bind(rx_sock, (const struct sockaddr *)&local_addr, (socklen_t)sizeof(local_addr)) < 0)
        {
            lwip_close(rx_sock);
            rx_sock = -1;
            return -4;
        }

        flags = lwip_fcntl(rx_sock, F_GETFL, 0);
        if (flags >= 0)
        {
            (void)lwip_fcntl(rx_sock, F_SETFL, flags | O_NONBLOCK);
        }

        net_ready = true;
    }

    received = lwip_recvfrom(rx_sock, out_line, out_size - 1U, 0, NULL, NULL);
    if (received <= 0)
    {
        return -1;
    }

    out_line[received] = '\0';
    *out_len = (size_t)received;
    return 0;
#else
    static char rx_accum[96];
    static size_t rx_used = 0U;
    uint8_t ch = 0U;

    if ((out_line == NULL) || (out_len == NULL) || (out_size < 2U))
    {
        return -2;
    }

    while (HAL_UART_Receive(&hlpuart1, &ch, 1U, 0U) == HAL_OK)
    {
        if ((ch == '\n') || (ch == '\r'))
        {
            if (rx_used == 0U)
            {
                continue;
            }

            if (rx_used >= out_size)
            {
                rx_used = out_size - 1U;
            }

            memcpy(out_line, rx_accum, rx_used);
            out_line[rx_used] = '\0';
            *out_len = rx_used;
            rx_used = 0U;
            return 0;
        }

        if (rx_used < (sizeof(rx_accum) - 1U))
        {
            rx_accum[rx_used++] = (char) ch;
        }
        else
        {
            /* Drop overlength frame and wait for next newline. */
            rx_used = 0U;
        }
    }

    return -1;
#endif
}

void temp_app_on_halow_line_received(const char *line, size_t len)
{
    mini_packet_t decoded;
    char frame[96];
    size_t copy_len = len;

    if ((line == NULL) || (len == 0U))
    {
        return;
    }

    if (copy_len >= sizeof(frame))
    {
        copy_len = sizeof(frame) - 1U;
    }

    memcpy(frame, line, copy_len);
    frame[copy_len] = '\0';

    if (strncmp(frame, "MMHALOW,", 8) != 0)
    {
        return;
    }

    if (mini_packet_decode(frame, &decoded) == 0)
    {
        printf("GATEWAY_RX seq=%lu temp_c=%.3f hum_rh=%.3f\r\n",
               (unsigned long) decoded.seq,
               decoded.temperature_milli_degC / 1000.0f,
               decoded.humidity_milli_RH / 1000.0f);

        printf("DASHBOARD {\"node\":\"sensor\",\"seq\":%lu,\"temp_c\":%.3f,\"hum_rh\":%.3f}\r\n",
               (unsigned long) decoded.seq,
               decoded.temperature_milli_degC / 1000.0f,
               decoded.humidity_milli_RH / 1000.0f);
    }
    else
    {
        printf("GATEWAY_RX parse_error payload=%s\r\n", frame);
    }
}

void temp_app_run_forever(void)
{
    uint32_t heartbeat = 0;
    char rx_line[96];
    size_t rx_len = 0U;

    temperature_init();

    printf("GATEWAY NODE: boot complete\r\n");
    printf("GATEWAY NODE: waiting for sensor packets over HaLow\r\n");
    if (TEMP_APP_USE_HALOW_UDP)
    {
        printf("GATEWAY NODE: transport=HaLow UDP listen_port=%u\r\n",
               (unsigned)TEMP_APP_HALOW_LOCAL_PORT);
    }
    else
    {
        printf("GATEWAY NODE: transport=UART fallback on LPUART1\r\n");
    }

    while (1)
    {
        th_value_t th;

        temperature_process();
        th = get_th_values();

        if (temp_app_halow_poll_line(rx_line, sizeof(rx_line), &rx_len) == 0)
        {
            temp_app_on_halow_line_received(rx_line, rx_len);
        }

        printf("GATEWAY_HEARTBEAT n=%lu local_temp_c=%.3f local_hum_rh=%.3f\r\n",
               (unsigned long) heartbeat,
               th.temperature_milli_degC / 1000.0f,
               th.humidity_milli_RH / 1000.0f);

         heartbeat++;
         HAL_Delay(1000);
    }
}
