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
#include "xparameters.h"
#include "xgpio.h"


void givePulse(XGpio* , XGpio* , int);


int main()
{
    init_platform();

    XGpio	clk;
    XGpio	W0;
    XGpio	W1;
    XGpio	W2;
    XGpio	W3;
    XGpio	synapse;
    XGpio	bias;
    XGpio	leak;
    XGpio	threshold;
    XGpio	membrane;

    XGpio_Initialize(&clk, XPAR_AXI_GPIO_CLK_DEVICE_ID);

    XGpio_Initialize(&W0, XPAR_AXI_GPIO_W0_DEVICE_ID);
    XGpio_Initialize(&W1, XPAR_AXI_GPIO_W1_DEVICE_ID);
    XGpio_Initialize(&W2, XPAR_AXI_GPIO_W2_DEVICE_ID);
    XGpio_Initialize(&W3, XPAR_AXI_GPIO_W3_DEVICE_ID);

    XGpio_Initialize(&synapse, XPAR_AXI_GPIO_SYNAPSE_DEVICE_ID);

    XGpio_Initialize(&bias, XPAR_AXI_GPIO_BIAS_DEVICE_ID);

    XGpio_Initialize(&leak, XPAR_AXI_GPIO_LEAK_DEVICE_ID);

    XGpio_Initialize(&threshold, XPAR_AXI_GPIO_THRESHOLD_DEVICE_ID);

    XGpio_Initialize(&membrane, XPAR_AXI_GPIO_MEMBRANE_DEVICE_ID);

    XGpio_SetDataDirection(&clk, 1, 1);

    XGpio_SetDataDirection(&W0, 1, 0);
    XGpio_SetDataDirection(&W1, 1, 0);
    XGpio_SetDataDirection(&W2, 1, 0);
    XGpio_SetDataDirection(&W3, 1, 0);

    XGpio_SetDataDirection(&synapse, 1, 0);

    XGpio_SetDataDirection(&bias, 1, 0);

    XGpio_SetDataDirection(&leak, 1, 0);

    XGpio_SetDataDirection(&threshold, 1, 0);

    XGpio_SetDataDirection(&membrane, 1, 1);

    XGpio_DiscreteWrite(&synapse, 1, 0);
    XGpio_DiscreteWrite(&threshold, 1, 10);
    XGpio_DiscreteWrite(&bias, 1, 0);
    XGpio_DiscreteWrite(&leak, 1, 1);
    XGpio_DiscreteWrite(&W0, 1, 0);
    XGpio_DiscreteWrite(&W1, 1, 0);
    XGpio_DiscreteWrite(&W2, 1, 0);
    XGpio_DiscreteWrite(&W3, 1, 0);

    int	choice;
    int w0,w1,w2,w3;
    int	b;
    int	l;
    int	t;
    int	m;
    int	s;

    while(1)
    {
    	printf("LIF Neuron Test \n\n");

    	printf("0. Set Weight [0] \n");
    	printf("1. Set Weight [1] \n");
    	printf("2. Set Weight [2] \n");
    	printf("3. Set Weight [3] \n");
    	printf("4. Set Bias \n");
		printf("5. Set Leak \n");
		printf("6. Set Threshold \n");
		printf("7. Give Pulse \n");
		printf("8. Read Membrane \n\n");

		scanf("%d" , &choice);
		printf("\n\n");

		if(choice == 0)
		{
			printf("Enter the weight for synapse 0 : ");
			scanf("%d" , &w0);
			XGpio_DiscreteWrite(&W0, 1, w0);
			printf("\n");
			printf("W[0] = %d \n\n" , w0);
		}

		else if(choice == 1)
		{
			printf("Enter the weight for synapse 1 : ");
			scanf("%d" , &w1);
			XGpio_DiscreteWrite(&W1, 1, w1);
			printf("\n");
			printf("W[1] = %d \n\n" , w1);
		}

		else if(choice == 2)
		{
			printf("Enter the weight for synapse 2 : ");
			scanf("%d" , &w2);
			XGpio_DiscreteWrite(&W2, 1, w2);
			printf("\n");
			printf("W[2] = %d \n\n" , w2);
		}

		else if(choice == 3)
		{
			printf("Enter the weight for synapse 3 : ");
			scanf("%d" , &w3);
			XGpio_DiscreteWrite(&W3, 1, w3);
			printf("\n");
			printf("W[3] = %d \n\n" , w3);
		}

		else if(choice == 4)
		{
			printf("Enter the bias : ");
			scanf("%d" , &b);
			XGpio_DiscreteWrite(&bias, 1, b);
			printf("\n");
			printf("Bias = %d \n\n" , b);
		}

		else if(choice == 5)
		{
			printf("Enter the leak : ");
			scanf("%d" , &l);
			XGpio_DiscreteWrite(&leak, 1, l);
			printf("\n");
			printf("Leak = %d \n\n" , l);
		}

		else if(choice == 6)
		{
			printf("Enter the threshold : ");
			scanf("%d" , &t);
			XGpio_DiscreteWrite(&threshold, 1, t);
			printf("\n");
			printf("Threshold = %d \n\n" , t);
		}

		else if(choice == 7)
		{
			printf("Set the synaptic input : \n");
			scanf("%d" , &s);
			XGpio_DiscreteWrite(&synapse, 1, s);
			printf("\n\n");
		}

		else if(choice == 8)
		{
			m = XGpio_DiscreteRead(&membrane, 1);
			printf("Membrane = %d \n\n" , m);
		}
    }


    cleanup_platform();
    return 0;
}


void givePulse(XGpio *clk , XGpio *synapse , int s)
{
	int temp = XGpio_DiscreteRead(clk, 1);

	if(temp == 0)
	{
		if(s == 1)		XGpio_DiscreteWrite(synapse, 1, 0x8);
		else if(s == 2)	XGpio_DiscreteWrite(synapse, 1, 0x4);
		else if(s == 3)	XGpio_DiscreteWrite(synapse, 1, 0x2);
		else if(s == 4)	XGpio_DiscreteWrite(synapse, 1, 0x1);

		while(temp != 1)
		{
			temp = XGpio_DiscreteRead(clk, 1);
		}

		XGpio_DiscreteWrite(synapse, 1, 0);
	}
	else if(temp == 1)
	{
		while(temp != 0)
		{
			temp = XGpio_DiscreteRead(clk, 1);
		}

		if(s == 1)		XGpio_DiscreteWrite(synapse, 1, 0x8);
		else if(s == 2)	XGpio_DiscreteWrite(synapse, 1, 0x4);
		else if(s == 3)	XGpio_DiscreteWrite(synapse, 1, 0x2);
		else if(s == 4)	XGpio_DiscreteWrite(synapse, 1, 0x1);

		while(temp != 1)
		{
			temp = XGpio_DiscreteRead(clk, 1);
		}

		XGpio_DiscreteWrite(synapse, 1, 0);
	}

	XGpio_DiscreteWrite(synapse, 1, temp);
}
