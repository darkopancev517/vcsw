/*
 * Copyright (c) 2020, Vertexcom Technologies, Inc.
 * All rights reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Vertexcom Technologies, Inc. and its suppliers,
 * if any. The intellectual and technical concepts contained
 * herein are proprietary to Vertexcom Technologies, Inc.
 * and may be covered by U.S. and Foreign Patents, patents in process,
 * and protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Vertexcom Technologies, Inc.
 *
 * Authors: Darko Pancev <darko.pancev@vertexcom.com>
 */

#ifndef VCRTOS_PROJECT_CONFIG_H
#define VCRTOS_PROJECT_CONFIG_H

#define VCRTOS_CONFIG_MULTIPLE_INSTANCE_ENABLE 0

#define VCRTOS_CONFIG_THREAD_FLAGS_ENABLE 1
#define VCRTOS_CONFIG_THREAD_EVENT_ENABLE 1

#define VCRTOS_CONFIG_ZTIMER_ENABLE 0
#define VCRTOS_CONFIG_ZTIMER_NOW64 0
#define VCRTOS_CONFIG_ZTIMER_USEC_BASE_FREQ (1000000LU)
#define VCRTOS_CONFIG_ZTIMER_USEC_DEV 0
#define VCRTOS_CONFIG_ZTIMER_USEC_MIN (10)
#define VCRTOS_CONFIG_ZTIMER_USEC_WIDTH (16)
#define VCRTOS_CONFIG_ZTIMER_EXTEND 1
#define VCRTOS_CONFIG_ZTIMER_CLOCK_SECOND (1200000LU)

// vcrtos kernel related stack size

#define VCRTOS_CONFIG_CPU_ISR_STACK_SIZE 2048
#define VCRTOS_CONFIG_MAIN_THREAD_STACK_SIZE 1024
#define VCRTOS_CONFIG_IDLE_THREAD_STACK_SIZE 256
#define VCRTOS_CONFIG_POLLHANDLER_THREAD_STACK_SIZE 1024

// contiki process stack size

#define VCRTOS_CONFIG_ETIMER_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_CTIMER_PROCESS_STACK_SIZE 2048
#define VCRTOS_CONFIG_WISUN_MAC_PROCESS_STACK_SIZE 2048
#define VCRTOS_CONFIG_CENTAURI_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_LOG_OUTPUT_DRV_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_UART_TX_DMA_DRV_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_UART_ATCMD_DRV_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_TCPIP_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_TELNET_SERVER_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_COAP_ENGINE_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_FAKE_COAP_CLIENT_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_REST_ENGINE_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_SYSRES_EV_HANDLER_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_DHCPV6_RELAY_AGENT_PROCESS_STACK_SIZE 1024
#define VCRTOS_CONFIG_DHCPV6_CLIENT_PROCESS_STACK_SIZE 1024
#define VCRTOS_CONFIG_RPL_RECALC_RANK_PROCESS_STACK_SIZE 512
#define VCRTOS_CONFIG_RPL_REMOVE_PARENT_PROCESS_STACK_SIZE 512
#define VCRTOS_CONFIG_WISUN_NTP_PROCESS_STACK_SIZE 512
#define VCRTOS_CONFIG_WISUN_RPL_LEAVE_PROCESS_STACK_SIZE 512
#define VCRTOS_CONFIG_TCP_SOCKET_PROCESS_STACK_SIZE 512
#define VCRTOS_CONFIG_UDP_SOCKET_PROCESS_STACK_SIZE 512

#define VCRTOS_CONFIG_VCAPPS_PROCESS_STACK_SIZE 256

#define VCRTOS_CONFIG_VCSHELL_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_SERIAL_SHELL_PROCESS_STACK_SIZE 1024
#define VCRTOS_CONFIG_SHELL_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_SHELL_SERVER_PROCESS_STACK_SIZE 256
#define VCRTOS_CONFIG_SHELL_CMD_DEFAULT_STACK_SIZE 512
#define VCRTOS_CONFIG_SHELL_PING6_PROCESS_STACK_SIZE 1024

#endif /* VCRTOS_PROJECT_CONFIG_H */
