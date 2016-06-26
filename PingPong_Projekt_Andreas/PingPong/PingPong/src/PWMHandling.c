/*
 * PWMHandling.c
 *
 * Created: 2015-05-13 15:17:02
 *  Author: Andreas
 */
#include <asf.h>
#include <stdio.h>
#include "PWMHandling.h"

/*
* This function initiate the Pin 6 so it can produce PWM signals
*/ 
void PWM_setup()
{
	//Main PWM settings
	pmc_enable_periph_clk(ID_PWM);
	pwm_clock_t clock_setting;
	clock_setting.ul_clka = 1000 * 100; // Clock A
	clock_setting.ul_clkb = 0; // Clock B
	clock_setting.ul_mck = 84000000; // Master clock
	pwm_init(PWM, &clock_setting);
	
	//PWM_6 settings (Pin 6 on Arduino due)
	pwm_channel_disable(PWM, PWM_CHANNEL_7);
	PWM_Pin_6.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWM_Pin_6.ul_period = 100;
	PWM_Pin_6.ul_duty = 100;
	PWM_Pin_6.channel = PWM_CHANNEL_7;
	pwm_channel_init(PWM, &PWM_Pin_6);
	pio_set_peripheral(PIOC, PIO_PERIPH_B,PIO_PC24B_PWML7 ); // PWML7 goes to Pin 6
	pwm_channel_enable(PWM, PWM_CHANNEL_7);
}

/*
* Gives the fan a certain power
* Fan_power = the amount of power the fan should receive in %
*/
void setFan(int Fan_power)
{
	pwm_channel_update_duty(PWM, &PWM_Pin_6 , Fan_power);
}
