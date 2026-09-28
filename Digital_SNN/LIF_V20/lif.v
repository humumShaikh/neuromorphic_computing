`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/24/2026 03:08:13 PM
// Design Name: 
// Module Name: lif
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////



module lif 
#
(
    parameter   synapse =   4
)
(
    input   wire                                    clk,
    input   wire            [00:synapse-1]          syn_in,
    input   wire    signed  [00:((synapse*8)-1)]    weight,
    input   wire    signed  [07:00]                 bias,
    input   wire    signed  [03:00]                 leak,
    input   wire    signed  [06:00]                 threshold,
    output  wire                                    neuron_out,
    output  wire    signed  [07:00]                 membrane                    //debug port
);


    
        reg                 fire;
        reg signed  [07:00] vmem;
        reg signed  [07:00] temp;
        reg signed  [07:00] val     [00:synapse-1];
        
        integer i;

        genvar  k;
        
        
        
        initial
        begin
            fire    <=  0;
            vmem    <=  0;
            
            for(i = 0;  i < synapse;  i = i + 1)
            begin
                val[i]  <=  0;
            end
        end
        
        
        
        generate
            for(k = 0;  k < synapse;    k = k + 1)
            begin
                always @(posedge clk)
                begin
                    if(syn_in[k] == 1)      val[k]  =  $signed(weight[(k*8)+:8]);
                    else if(syn_in[k] == 0) val[k]  =  $signed(0);
                end
            end
        endgenerate
        
        
        
        always @(*)
        begin
            temp    =   0;
            
            for(i = 0;  i < synapse;    i = i + 1)
            begin
                if(i == (synapse-1))
                begin
                    temp    =   temp    +   val[i] + $signed(bias);
                end
                
                else
                begin
                    temp    =   temp    +   val[i];
                end
            end
        end
        
        
        
        always @(posedge clk)
        begin
            if(vmem >= threshold)
            begin
                fire    <=  1;
                vmem    <=  0;
            end
            
            else
            begin
                fire    <=  0;
                
                if((vmem + temp - leak) < 0)   vmem <=  0;
                
                else    vmem    <=  vmem + temp - leak;
            end
        end
        
        
        
        assign  neuron_out  =   fire;
        assign  membrane    =   vmem;
        
        
        
endmodule