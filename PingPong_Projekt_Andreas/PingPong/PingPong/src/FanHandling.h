/*
 * PWMHandling.h
 *
 * Created: 2015-05-13 15:17:36
 *  Author: Andreas
 */ 

// Side Fans PWM Pins 6-9
pwm_channel_t PWM_Pin_6; // Front Right fan
pwm_channel_t PWM_Pin_7; // Front Left fan
pwm_channel_t PWM_Pin_8; // Back Right fan
pwm_channel_t PWM_Pin_9; // Back Left fan
//Back Middle Fans PWM Pins 34 & 36
pwm_channel_t PWM_Pin_34; // Middle Right 
pwm_channel_t PWM_Pin_36; // Middle LEft
// The Lift fan PWM 10
pwm_channel_t PWM_Pin_40; // Lift fan

void PWM_setup(void);
void setFan(uint8_t Fan_power, uint8_t number);