#ifndef _LED
#define _LED

/* functions */
void e_set_led(unsigned int led_number, unsigned int value); // set led_number (0-7) to value (0-1)
void e_led_clear(void);
void e_blink_led(void);
void e_blink_led0(void);
void e_blink_led1(void);
void e_blink_led2(void);
void e_blink_led3(void);
void e_blink_led4(void);
void e_blink_led5(void);
void e_blink_led6(void);
void e_blink_led7(void);

void e_set_body_led(unsigned int value); // value (0=off 1=on higher=inverse) 
void e_set_front_led(unsigned int value); //value (0=off 1=on higher=inverse) 

void e_start_led_blinking(int cycle);
void e_stop_led_blinking(void);

#endif
