/*
 * Setup.h
 *
 * Created: 2015-04-24 10:29:17
 *  Author: Andreas
 */ 
#ifndef ADCDAC_H_
#define ADCDAC_H_

// The 4 pins that will recieve signals from the sensors
#define AD_0 PIO_PA16_IDX // AD7(Chanel_7) - PA16
#define AD_1 PIO_PA24_IDX // AD6(Chanel_6) - PA24
#define AD_2 PIO_PA23_IDX // AD5(Chanel_5) - PA16
#define AD_3 PIO_PA22_IDX // AD4(Chanel_4) - PA16

// PWM Pins 6-9
pwm_channel_t PWM_Pin_6;
pwm_channel_t PWM_Pin_7;
pwm_channel_t PWM_Pin_8;
pwm_channel_t PWM_Pin_9;


//#define ADC_CLOCK 84000000 // the labb says 20000000 is this right or should it be 84MHz

void adc_setup(void);
void arduino_setup(void);
void PWM_setup(void);


#endif /* ADCDAC_H_ */