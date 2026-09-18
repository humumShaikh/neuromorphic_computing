`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/18/2026 10:34:58 AM
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
    parameter   VThreshold  =   20,
    parameter   Leak        =   1,
    parameter   synapse     =   4,
    parameter   signed [0 : ((synapse*8)-1)] weight = {8'sd1 , 8'sd2 , 8'sd3 , 8'sd4},
    parameter   signed  [7:0]   bias    =   0
)
(
    input   wire            clk,
    input   wire    [0 : synapse-1]   syn_in,
    output  wire            neuron_out,
    output  wire    signed  [((($clog2(VThreshold))*2)-1):0] membrane                //debug port
);
    
    
    
    reg signed [((($clog2(VThreshold))*2)-1):0]    VMem;
    reg                             fire;
    reg signed [((($clog2(VThreshold))*2)-1):0] temp;
    
    reg signed  [15:0]  val [0 : synapse-1];
    
        
    integer i;
    
    
    
    initial
    begin
        VMem <= 0;
        fire <= 0;
        
        for(i = 0; i < synapse; i = i + 1)
        begin
            val[i] <= 0;
        end
    end
    
    
    
    genvar  k;
    
    generate
        
        for(k = 0; k < synapse; k = k + 1)
        begin
            always @(posedge clk)
            begin
                if(syn_in[k] == 1) val[k] = $signed(weight[(k*8)+:8]);
                else if(syn_in[k] == 0) val[k] = $signed(0);
            end
        end
        
    endgenerate
     
    
   
    always @(*)
    begin
        
        temp = 0;
    
        for(i = 0; i < synapse; i = i + 1)
        begin
            if(i == (synapse-1))
            begin
                temp = temp + val[i] + $signed(bias);
            end
            
            else
            begin
                temp = temp + val[i];
            end
        end
    end

    


    
    always @(posedge clk)
    begin

        if(VMem >= VThreshold)
        begin
            fire <= 1;
            VMem <= 0;
        end
        
        
        else
        begin
            
            fire <= 0;
            
            if((VMem + temp - Leak) < 0)   VMem <= 0;
                
            else    VMem <= VMem + temp - Leak;
            
        end
        
    end
        
    
    
    assign  neuron_out = fire;
    
    assign  membrane = VMem;
        
    
        
endmodule
