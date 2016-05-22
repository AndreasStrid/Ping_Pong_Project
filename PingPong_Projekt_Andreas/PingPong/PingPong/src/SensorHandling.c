/*
 * SensorHandling.c
 *
 * Created: 2015-04-22 14:14:23
 *  Author: Andreas
 */ 

#include <asf.h>
#include <stdio.h>
#include "SensorHandling.h"

#define AD_0 PIO_PA16_IDX // AD7(Chanel_7) - PA16

uint16_t PR; // Ping Reader
uint16_t PR_Filter[10];
int PR_Sum = 0;
uint8_t count = 0;

//Our measurements
int Measure[] = {0, 125, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 250, 251, 251, 254, 254, 260, 261, 266, 276, 274, 
 284, 286, 296, 297, 304, 315, 316, 320, 324, 330, 342, 344, 349, 364, 370, 384, 398, 416, 445, 452, 472, 495, 544, 584, 683, 728, 728, 728, 728, 729
	, 729, 729, 729 };

/*
* This function setup the AD converter so it will work
*/
void adc_setup()
{
	pmc_enable_periph_clk(ID_ADC); // Give ID_ADC its own periphclock
	adc_init(ADC, sysclk_get_main_hz(), 1000000, 8);
	adc_configure_timing(ADC, 0, 0, 0);
	adc_set_resolution(ADC, ADC_MR_LOWRES_BITS_10); // 10bits = 3.3v/1024
	adc_enable_channel(ADC, ADC_CHANNEL_7); // AD_0
	adc_configure_trigger(ADC, ADC_TRIG_SW, 0);	//Trigg
}
/*
* This task will read the values from the sensor and put them in the respective variable for the sensor
*/
void sensorCheck(void *p)
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	const xTimeIncrement = 2.5;
	
	while (1)
	{
		// Gets the value from A0 port
		vTaskDelayUntil( &xLastWakeTime, xTimeIncrement);
 		adc_start(ADC);	
 		//PR_Filter[count] =  bitToCm(adc_get_channel_value(ADC, ADC_CHANNEL_7));
		 PR_Filter[count] = adc_get_channel_value(ADC, ADC_CHANNEL_7);		
		count++;
		//When 10 values have been stored the averege value will be calculated
		if(count >= 10)
		{
			for(int i = 0; i < 10; i++ )
			{
				PR_Sum += (int) PR_Filter[i];
			}
		
			PR = (uint16_t) (PR_Sum/10);
			//Clear the sum to zero again
		    PR_Sum = 0;
			count = 0;
		}
	}
}
/*
* This function transforms bits to cm
* return: returns the converted value
*/
int bitToCm(int v)
{
	for(int i = 0; i < 60; i++)
	{
		if(v >= Measure[i] && v <= Measure[i+1])
		{
			return i;
		}
	}
	return 1;
}
/*
* This function transforms cm to bits
* return: returns the converted value
*/
int cmToBit(int v)
{
	return Measure[v];
}
/*
* Gives a certain fan a certain power
* number = which sensor you want to recieve the value from
* return = return the value from a sensor
*/
int getSensorValues()
{
		return PR;
}