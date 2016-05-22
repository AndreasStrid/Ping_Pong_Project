/*
 * PWMHandling.h
 *
 * Created: 2015-05-13 15:17:36
 *  Author: Andreas Hamoud
 */ 

// Side Fans PWM Pins 6-9
pwm_channel_t PWM_Pin_6; // Front Right fan

void PWM_setup(void);
void setFan(int Fan_power);