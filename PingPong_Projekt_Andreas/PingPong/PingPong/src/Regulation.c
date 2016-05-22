#include <asf.h>
#include <stdio.h>
#include "SensorHandling.h"
#include "PWMHandling.h"
#include "Regulation.h"


int error_value = 0;
double P = 0;
double I = 0;
double D = 0;
int Old_error = 0;

//PID konstants
double Kp = 0.7;
double TI = 0.35;
double TD= 0.125;
int bv = 400;
int dT = 1;

double PID = 0;
int u = 0;


/*
* This task will decide the amount of power the fan will recieve
*/
void FanRegulation(void *p)
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	
	while(1)
	{
		vTaskDelayUntil( &xLastWakeTime, 50);
		
		//The error value of the sensor
		error_value = ( bv - getSensorValues(1) );

		//The regulation value
		setFan(PID_calculation(error_value));
	}			
 }
/*
* This function calculate the regulation value
* Error_value = the sensors error value
* return = a precentage in power that the fan should recieve
*/
uint8_t PID_calculation(int Error_value)
{	
		//int Current_error = cmToBit(Error_value);
		int Current_error = Error_value;
	
	 	P = (double) Current_error;
		I += (double) Old_error * (0.05); // Transform 100 to 0.1 which is 100ms
	 	D = (double) ( Current_error - Old_error ) / (0.05) ; // dT
        
		Old_error = Error_value;

	 	PID = (double) ( ( P * Kp ) + ( I * TI ) + ( D * TD ) );
		// Stores the power signal that will go to matlab
	    
		//1023 is 100% fan power, so if PID is higher then 1023, it will be 1023
	 	if(PID >= 1023)
	 	{
			PID = 1023;
		}
		//0 is 0% fan power, so if PID is lower then 0, it will be 0
		else if(PID <= 0)
		{
			PID = 0;
		}
		//the outsignal to matlab
		u = (int) PID;
	 	// Return the percentage the fan should be on, 100% = 1023, 0% = 0.
	     return (uint8_t) ( ( PID/1023 ) * 100 );
}
/*
* This function sets regulation values
*/	
void SetPID()
{
 	 scanf("%d", Kp);
	 scanf("%d", TI);
	 scanf("%d", TD);
	 scanf("%d", bv);
	 scanf("%d", dT);
}
/*
* This returns the error_value
*/
int getErrorValue()
{
	return error_value;
}
/*
* This function return the outsignal
*/
int getPowerValue()
{
	return u;
}