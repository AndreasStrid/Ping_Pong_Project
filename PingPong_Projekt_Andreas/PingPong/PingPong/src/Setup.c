/*
 * Setup.c
 *
 * Created: 2015-04-24 10:29:04
 *  Author: Andreas Strid
 */ 
/*
XXXXXXXXXXXXXX Functions XXXXXXXXXXXXXXX
pmc_enale_periph_clk(a ID/Variale) = Gives the  ID/variable its own periphclock;
adc_init(Pointer that points to the ADC register, Main clock ,A clock that ADC should follow, Start up time );
sysclk_get_main_hz() = Gets a 4MHz RC oscillator clock.
adc_configure_timig(Pointer that points to the ADC register, ADC Tracking, Analog settling time, Data transfer time);
adc_enable_channel(Pointer that points to the ADC register, Which channel that should be enabled) 
*/

#include <asf.h>
#include <stdio.h>
#include "Setup.h"

/*
* This function enables the ADC and enables analog pin 0-3 to read analoginput values.
*/
void arduino_setup()
{
	sysclk_init();
	board_init();
	ioport_init();
	adc_setup();
	PWM_setup();	
}
void adc_setup()
{		
	pmc_enable_periph_clk(ID_ADC); // Give ID_ADC its own periphclock
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_10); // 10bits = 3.3v/1024
	adc_enable_channel(ADC, ADC_CHANNEL_7); // AD_0
	adc_enable_channel(ADC, ADC_CHANNEL_6); // AD_1
	adc_enable_channel(ADC, ADC_CHANNEL_5); // AD_2	
	adc_enable_channel(ADC, ADC_CHANNEL_4); // AD_3			
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);	//Trigg
	
}
void PWM_setup()
{
	//Main PWM
	pmc_enable_periph_clk(ID_PWM);
	//pwm_channel_disable(PWM, PWM_CHANNEL_0);
	pwm_clock_t clock_setting;
	clock_setting.ul_clka = 1000 * 100; // Clock A
	clock_setting.ul_clkb = 0; // Clock B
	clock_setting.ul_mck = 84000000; // Master clock
	pwm_init(PWM, &clock_setting);
	
	//PWM_6 settings (Port 6 on Arduino due)
	pwm_channel_disable(PWM, PWM_CHANNEL_7);
	PWM_Pin_6.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWM_Pin_6.ul_period = 100;
	PWM_Pin_6.ul_duty = 50;
	PWM_Pin_6.channel = PWM_CHANNEL_7;

	pwm_channel_init(PWM, &PWM_Pin_6);
	pio_set_peripheral(PIOC, PIO_PERIPH_B,PIO_PC24B_PWML7 ); // PWML7 goes to Pin 6
	pwm_channel_enable(PWM, PWM_CHANNEL_7);
	
	//PWM_7 settings (Port 7 on Arduino due)
	pwm_channel_disable(PWM, PWM_CHANNEL_6);
	PWM_Pin_7.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWM_Pin_7.ul_period = 100;
	PWM_Pin_7.ul_duty = 10;
	PWM_Pin_7.channel = PWM_CHANNEL_6;

	pwm_channel_init(PWM, &PWM_Pin_7);
	pio_set_peripheral(PIOC, PIO_PERIPH_B,PIO_PC23B_PWML6 ); // PWML6 goes to Pin 7
	pwm_channel_enable(PWM, PWM_CHANNEL_6);
	
	//PWM_8 settings (Port 8 on Arduino due)
	pwm_channel_disable(PWM, PWM_CHANNEL_5);
	PWM_Pin_8.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWM_Pin_8.ul_period = 100;
	PWM_Pin_8.ul_duty = 100;
	PWM_Pin_8.channel = PWM_CHANNEL_5;

	pwm_channel_init(PWM, &PWM_Pin_8);
	pio_set_peripheral(PIOC, PIO_PERIPH_B,PIO_PC22B_PWML5 ); // PWML5 goes to Pin 8
	pwm_channel_enable(PWM, PWM_CHANNEL_5);
	//PWM_9 settings (Port 9 on Arduino due)
	pwm_channel_disable(PWM, PWM_CHANNEL_4);
	PWM_Pin_9.ul_prescaler = PWM_CMR_CPRE_CLKA;
	PWM_Pin_9.ul_period = 100;
	PWM_Pin_9.ul_duty = 50;
	PWM_Pin_9.channel = PWM_CHANNEL_4;

	pwm_channel_init(PWM, &PWM_Pin_6);
	pio_set_peripheral(PIOC, PIO_PERIPH_B,PIO_PC21B_PWML4 ); // PWML7 goes to Pin 6
	pwm_channel_enable(PWM, PWM_CHANNEL_4);
	
	
	//PWM_1 settings
// 	pwm_channel_t PWM_3;
// 	PWM_3.ul_prescaler = PWM_CMR_CPRE_CLKA;
// 	PWM_2.ul_period = 100;
// 	PWM_2.ul_duty = 50;
// 	PWM_2.channel = PWM_CHANNEL;
// 	pwm_channel_disable(PWM, PWM_CHANNEL_3);
// 	pwm_channel_init(PWM, &PWM_3);
// 	pio_set_peripheral(PIOC, PIO_PERIPH_B,PIO_PC23B_PWML6 )
	
	//ANVÄNDBARA FUNKTIONR?
	//pwm_channel_update_period();
}

