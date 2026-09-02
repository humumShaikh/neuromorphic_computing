`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CWIR3
// Engineer: copperwire
// 
// Create Date: 08/28/2026 04:55:35 PM
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
    parameter   Leak        =   2,
    parameter   synapse     =   2,
    parameter   signed [((synapse*8)-1):0] weight = {-8'sd3 , 8'sd4}
)
(
    input   wire            clk,
    input   wire    [synapse-1:0]   in,
    output  wire            neuron_out,
    output  wire    signed  [((($clog2(VThreshold))*2)-1):0] membrane                //debug port
);
    
    
    
    reg signed [((($clog2(VThreshold))*2)-1):0]    VMem;
    reg                             fire;
    reg signed [((($clog2(VThreshold))*2)-1):0] temp;
    
    reg signed  [15:0]  val [synapse-1 : 0];
    
        
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
                if(in[k] == 1) val[k] = $signed(weight[(k*8)+:8]);
                else if(in[k] == 0) val[k] = $signed(0);
            end
        end
        
    endgenerate
     
    
   
    always @(*)
    begin
        
        temp = 0;
    
        for(i = 0; i < synapse; i = i + 1)
        begin
            temp = temp + val[i];
        end
    end

    
    
//    always @(posedge clk)
//    begin

//        if(VMem >= VThreshold)
//        begin
//            fire <= 1;
//            VMem <= 0;
//        end
        
//        else
//        begin
            
//            fire <= 0;
            
//            if(1'b1)
//            begin
//                if((VMem + temp) < 0)   VMem <= 0;
                
//                else
//                begin
//                    VMem <= VMem + temp;
//                end
//            end
            
//            else
//            begin
//                if(VMem >= Leak)
//                begin
//                    VMem <= VMem - Leak;
//                end
                
//                else
//                begin
//                    VMem <= 0;
//                end
//            end
            
//        end
        
//    end


    
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
                    
                    if(temp == 0)   
                    begin
                        if(VMem >= Leak)    VMem <= VMem - Leak;
                       
                        else    VMem <= 0;
                    end
                    
                    else
                    begin
                        if((VMem + temp) < 0)   VMem <= 0;
                        
                        else    VMem <= VMem + temp;
                    end
                    
                    
                end
                
            end
        
    
    
    assign  neuron_out = fire;
    
    assign  membrane = VMem;
        
    
        
endmodule
