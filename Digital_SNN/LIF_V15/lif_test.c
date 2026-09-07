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
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xparameters.h"
#include "sleep.h"


void pulsate(int , int);
void waitUntilClockHigh();
void waitUntilClockLow();
void readMembrane();

int main()
{
    init_platform();

    XGpio	clk;
    XGpio	imp;
    XGpio	membrane;

    XGpio_Initialize(&clk, XPAR_AXI_GPIO_CLK_DEVICE_ID);
    XGpio_Initialize(&imp, XPAR_AXI_GPIO_IMP_DEVICE_ID);
    XGpio_Initialize(&membrane, XPAR_AXI_GPIO_MEMBRANE_DEVICE_ID);

    XGpio_SetDataDirection(&clk, 1, 1);
    XGpio_SetDataDirection(&imp, 1, 0);
    XGpio_SetDataDirection(&imp, 2, 0);
    XGpio_SetDataDirection(&membrane, 1, 1);


    int choice;
//    int temp;


    while(1)
    {
    	printf("1. Pulse at synapse  1 \n");
    	printf("2. Pulse at synapse  2 \n");
    	printf("3. Pulse at synapse 1,2 \n");
    	printf("4. Read Membrane \n");
    	scanf("%d" , &choice);
    	printf("\n\n");


    	if(choice == 1)
    	{
    		pulsate(0,1);
    		readMembrane();
    	}

    	else if(choice == 2)
    	{
    		pulsate(1,0);
    		readMembrane();
    	}

    	else if(choice == 3)
    	{
    		pulsate(1,1);
    		readMembrane();
    	}

    	else if(choice == 4)
    	{
//    		temp = XGpio_DiscreteRead(&membrane, 1);
//    		printf("Membrane : %d \n" , temp);
    		readMembrane();
    	}
    }

    cleanup_platform();
    return 0;
}


void waitUntilClockHigh()
{
	XGpio	clk;
	XGpio_Initialize(&clk, XPAR_AXI_GPIO_CLK_DEVICE_ID);
	XGpio_SetDataDirection(&clk, 1, 1);

	int temp;

	temp = XGpio_DiscreteRead(&clk, 1);

	if(temp == 0)
	{
		while(temp != 1)
		{
			temp = XGpio_DiscreteRead(&clk, 1);
		}
	}
}


void waitUntilClockLow()
{
	XGpio	clk;
	XGpio_Initialize(&clk, XPAR_AXI_GPIO_CLK_DEVICE_ID);
	XGpio_SetDataDirection(&clk, 1, 1);

	int temp;

	temp = XGpio_DiscreteRead(&clk, 1);

	if(temp == 1)
	{
		while(temp != 0)
		{
			temp = XGpio_DiscreteRead(&clk, 1);
		}
	}
}



void pulsate(int syn2 , int syn1)
{
	XGpio	clk;
	XGpio	imp;

	XGpio_Initialize(&clk, XPAR_AXI_GPIO_CLK_DEVICE_ID);
	XGpio_Initialize(&imp, XPAR_AXI_GPIO_IMP_DEVICE_ID);

	XGpio_SetDataDirection(&clk, 1, 1);
	XGpio_SetDataDirection(&imp, 1, 0);
	XGpio_SetDataDirection(&imp, 2, 0);

	waitUntilClockLow();
	XGpio_DiscreteWrite(&imp, 2, syn2);
	XGpio_DiscreteWrite(&imp, 1, syn1);
	waitUntilClockHigh();
	XGpio_DiscreteWrite(&imp, 2, 0);
	XGpio_DiscreteWrite(&imp, 1, 0);
}


void readMembrane()
{
	XGpio mem;
	XGpio_Initialize(&mem, XPAR_AXI_GPIO_MEMBRANE_DEVICE_ID);
	XGpio_SetDataDirection(&mem, 1, 1);

	int temp = XGpio_DiscreteRead(&mem, 1);

	printf("Membrane : %d \n" , temp);
}
