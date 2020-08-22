#include <stdio.h>

#include <vcrtos/instance.h>
#include <vcrtos/thread.h>
#include <vcrtos/cli.h>

#include <vcdrivers/stdiobase.h>

#include "native_internal.h"
#include "tty_uart.h"

void cli_cmd_exit(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    tty_uart_close(VCDRIVERS_CONFIG_STDIOBASE_UART_DEV);

    real_exit(EXIT_SUCCESS);
}

const cli_command_t user_command_list[] = {
    { "exit", cli_cmd_exit },
};

int main(void)
{
    vccli_uart_init(_native_instance);
    vccli_set_user_commands(user_command_list, 1);

    while (1)
    {
        thread_sleep(_native_instance);
    }

    return 0;
}
