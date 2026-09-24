/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 *	 written by : copperwire
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"
#include "sleep.h"


int main()
{
    init_platform();


    XGpio	front;
    XGpio	back;
    XGpio	left;
    XGpio	right;
    XGpio	movement;


    XGpio_Initialize(&front, XPAR_AXI_GPIO_FRONT_DEVICE_ID);
    XGpio_Initialize(&back, XPAR_AXI_GPIO_BACK_DEVICE_ID);
    XGpio_Initialize(&left, XPAR_AXI_GPIO_LEFT_DEVICE_ID);
    XGpio_Initialize(&right, XPAR_AXI_GPIO_RIGHT_DEVICE_ID);
    XGpio_Initialize(&movement, XPAR_AXI_GPIO_MOVEMENT_DEVICE_ID);


    XGpio_SetDataDirection(&front, 1, 0);
    XGpio_SetDataDirection(&back, 1, 0);
    XGpio_SetDataDirection(&left, 1, 0);
    XGpio_SetDataDirection(&right, 1, 0);
    XGpio_SetDataDirection(&movement, 1, 1);


    int	choice;
    int val;
    int valFront;
    int valBack;
    int valLeft;
    int valRight;

    XGpio_DiscreteWrite(&front, 1, 0);
    XGpio_DiscreteWrite(&back, 1, 0);
    XGpio_DiscreteWrite(&left, 1, 0);
    XGpio_DiscreteWrite(&right, 1, 0);


    sleep(2);


    while(1)
    {
    	printf("1. Front Sensor   %d \n" , valFront);
    	printf("2. Back  Sensor   %d \n" , valBack);
    	printf("3. Left  Sensor   %d \n" , valLeft);
    	printf("4. Right Sensor   %d \n" , valRight);
    	printf("5. Check Movement \n");
    	scanf("%d" , &choice);

    	if(choice == 1)
    	{
    		printf("Enter value : \n");
    		scanf("%d" , &valFront);
    		XGpio_DiscreteWrite(&front, 1, valFront);
    	}

    	else if(choice == 2)
		{
			printf("Enter value : \n");
			scanf("%d" , &valBack);
			XGpio_DiscreteWrite(&back, 1, valBack);
		}

    	else if(choice == 3)
		{
			printf("Enter value : \n");
			scanf("%d" , &valLeft);
			XGpio_DiscreteWrite(&left, 1, valLeft);
		}

    	else if(choice == 4)
		{
			printf("Enter value : \n");
			scanf("%d" , &valRight);
			XGpio_DiscreteWrite(&right, 1, valRight);
		}

    	else if(choice == 5)
    	{
    		val = XGpio_DiscreteRead(&movement, 1);
    		if(val == 1)		printf("RIGHT ! \n");
    		else if(val == 2)	printf("LEFT ! \n");
    		else if(val == 4)	printf("BACK ! \n");
    		else if(val == 8)	printf("FRONT ! \n");
    	}
    }


    cleanup_platform();
    return 0;
}
