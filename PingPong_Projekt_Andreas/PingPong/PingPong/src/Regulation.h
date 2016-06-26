/*
 * Regulation.h
 *
 * Created: 2015-05-14 15:46:35
 *  Author: Andreas
 */ 


void FanRegulation(void *pvParameters);
uint8_t PID_calculation(int Error_value);
int getErrorValue(void);
int getPowerValue(void);
void SetPID(void);
