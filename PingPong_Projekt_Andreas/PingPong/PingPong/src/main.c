/*
 * main.c
 *
 * Created: 2015-04-22 08:30:13
 *  Author: Andreas Strid 
 */ 

// Loads all necessary libraries 
#include <asf.h>
#include <stdio.h>
#include "SensorHandling.h"
#include "Regulation.h"
#include "PWMHandling.h"

#define Sensor_Stack (1024/sizeof(portSTACK_TYPE))
#define Reg_Stack (1024/sizeof(portSTACK_TYPE))
#define Blue_Stack (1024/sizeof(portSTACK_TYPE))

/*
*This function makes it able for the arduino to communicate to a terminal window or bluetooth
*/
static void configure_UART(void)
{
	// 11520 Baud, Parity
	const usart_serial_options_t uart_serial_options = { .baudrate =CONF_UART_BAUDRATE, .paritytype = CONF_UART_PARITY };
	//Enables a perpipheral clock
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	//Initate serial communication
	//stdio_serial_init(CONF_UART, &uart_serial_options);
	stdio_serial_init(CONF_UART, &uart_serial_options);
	/* Specify that stdout shall not buffer */
	#if defined(__GNUC__)
	setbuf(stdout, NULL);
	#endif
}
/*
*This function initiate the arduinos clock, AD convert and PWN setup so the arduino will work
*/
void arduino_setup()
{
	sysclk_init();
	board_init();
	ioport_init();
	adc_setup();
	PWM_setup();
}
/*
*This will send information to matlab by the bluetooth modulue 
*/
void Bluetooth(void *p)
{
	portTickType xLastWakeTime = xTaskGetTickCount();
	const  xTimeIncrement = 1000;
	int apa = 0;
	while(1)
	{
		printf("%d \n", getSensorValues(1));
		printf("%d \n", getPowerValue());
		printf("%d \n", getErrorValue());
	        vTaskDelayUntil( &xLastWakeTime, xTimeIncrement);
	}
}
int main(void)
{
	arduino_setup();
	configure_UART();

	xTaskCreate(sensorCheck, (const signed char * const) "sensorCheck", Sensor_Stack, NULL,tskIDLE_PRIORITY , NULL); 
	xTaskCreate(FanRegulation, (const signed char * const) "FanRegulation", Reg_Stack, NULL, tskIDLE_PRIORITY, NULL);
	xTaskCreate(Bluetooth, (const signed char * const) "Bluetooth", Blue_Stack, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
}
