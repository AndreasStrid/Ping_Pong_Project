/*
 * SensorHandling.h
 *
 * Created: 2015-04-22 14:14:43
 *  Author: Andreas
 */

#ifndef ADCDAC_H_
#define ADCDAC_H_


void sensorCheck(void *pvParameters);
int getSensorValues();
int bitToCm(int value);
int cmToBit(int value);
void adc_setup(void);

#endif /* ADCDAC_H_ */
