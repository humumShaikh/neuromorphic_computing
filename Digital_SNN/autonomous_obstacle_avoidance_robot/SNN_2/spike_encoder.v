`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/07/2026 08:07:50 PM
// Design Name: 
// Module Name: spike_encoder
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


module spike_encoder
#
(
    parameter   resolution  =   12
)
(
    input   wire    clk,
    input   wire    [ (resolution-1) : 0] data_in,
    output  reg     data_out
);

    
    localparam [3:0]    FETCH       = 0,
                        PULSATE     = 1;
    
    reg [3:0]   STATE   =   FETCH;
    
    
    
    reg [ (resolution-1):0]   numPulse;
    reg         doneFlag;
    
    
    initial
    begin
        data_out <= 0;
        doneFlag <= 0;
        numPulse <= 0;
    end
    
    
    always @(posedge clk)
    begin
        
        case(STATE)
        
            FETCH               :           begin
                                                if(data_in != 0)
                                                begin
                                                    numPulse <= (data_in * 100) >> resolution;
                                                    STATE <= PULSATE;
                                                end
                                            end
                                        
            PULSATE             :           begin
                                                if(numPulse != 0)
                                                begin
                                                    if(doneFlag == 1)
                                                    begin
                                                        data_out <= 0;
                                                        doneFlag <= 0;
                                                        numPulse <= numPulse - 1;
                                                    end
                                                    
                                                    else
                                                    begin
                                                        data_out <= 1;
                                                        doneFlag <= 1;
                                                    end
                                                    
                                                    STATE <= PULSATE;
                                                end
                                                
                                                else
                                                begin
                                                    STATE <= FETCH;
                                                end 
                                            end                      
        
        endcase
        
    end


endmodule
