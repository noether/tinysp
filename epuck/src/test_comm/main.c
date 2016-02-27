#include <p30f6014a.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <e_uart_char.h>
#include <e_init_port.h>
#include <e_agenda.h>
#include <e_led.h>
#include <e_comm.h>

int long delay;
void ping_pong_pkt(void);

int main() {

    e_init_port();
    e_init_uart1();
    e_led_clear();

    e_activate_agenda(e_blink_led0, 2500);
    e_activate_agenda(radio, 100);
    e_start_agendas_processing();

    while(1){
        for ( delay = 0 ; delay < 15000; delay++){
            __asm__("nop");
        }
    }

    return 0;
}

void ping_pong_pkt(void)
{
    unsigned char pkg_send[256];
    int n = readPkt(pkg_send);
    if(n)
    {
        sendPkt(pkg_send, n);
        e_blink_led1();
    }
}

