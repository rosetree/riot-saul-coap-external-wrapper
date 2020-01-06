#include <stdio.h>
#include "msg.h"
#include "shell.h"
#include "saul_cord_ep.h"
#include "saul_coap.h"
#include "winch.h"
#include "servo.h"
#include "winch_coap.h"

#define MAIN_QUEUE_SIZE (4)
#define CORD_EP_ADDRESS "[fdaa:bb:cc:dd::1]:5683"

#define WINCH_GPIO_PIN GPIO_PIN(0, 23)
#define WINCH_DIAMETER_MM (15)

#define DEV         PWM_DEV(0)
#define CHANNEL     2
#define SERVO_MIN	(500U)
#define SERVO_MAX 	(5500U)

static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

/* we will use custom event handler for dumping cord_ep events */
static void _on_ep_event(saul_cord_ep_event_t event)
{
    switch (event) {
        case SAUL_CORD_EP_REGISTERED:
            puts("DEBUG: Registered successfully with RD");
            break;
        case SAUL_CORD_EP_DEREGISTERED:
            puts("DEBUG: Deregistered from RD");
            break;
        case SAUL_CORD_EP_UPDATED:
            puts("DEBUG: Updated successfully the client registration");
            break;
    }
}

int main(void)
{
    puts("Welcome to RIOT @ HAW!\n");

    servo_t servo;
    int err = servo_init(&servo, DEV, CHANNEL, SERVO_MIN, SERVO_MAX);
    if (err < 0) {
        puts("Errors while initializing servo");
        return -1;
    }

    winch_t winch;
    winch_init(&winch, &servo, WINCH_DIAMETER_MM, WINCH_GPIO_PIN);

    winch_coap_init(&winch);

    saul_coap_init();

    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    saul_cord_ep_register_cb(_on_ep_event);
    saul_cord_ep_create(CORD_EP_ADDRESS);
    saul_cord_ep_run();

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
