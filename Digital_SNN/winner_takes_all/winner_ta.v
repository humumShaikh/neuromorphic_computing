`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CWIR3
// Engineer: copperwire
// 
// Create Date: 09/10/2026 10:36:34 AM
// Design Name: 
// Module Name: winner_ta
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


module winner_ta
#
(
    parameter   inputs  =   4,
    parameter   samples =   100
)
(
    input   wire                    clk,
    input   wire    [0 : inputs-1]  din,
    output  reg     [0 : inputs-1]  dout
);


    reg [($clog2(samples)-1) : 0]   fireCount   [0 : (inputs-1)];
    reg [($clog2(samples)-1) : 0]   counter;
    reg [($clog2(samples)-1) : 0]   temp;  

    
    localparam [3:0]    IDLE        =   0,
                        SAMPLE      =   1,
                        COMPARE     =   2,
                        DECIDE      =   3;
                        
    reg [3:0] STATE = IDLE;
    
    integer i;
    integer j;
    
    initial
    begin
        dout <= 0;
        
        counter <= 0;
        
        temp <= 0;
        
        for(i = 0; i < inputs; i = i + 1)
        begin
            fireCount[i] <= 0;
        end
    end
    
    
    
    always @(posedge clk)
    begin
    
        case (STATE)
        
            IDLE            :           begin
                                            for(i = 0; i < inputs; i = i + 1)
                                            begin
                                                fireCount[i] <= 0;
                                                temp <= 0;
                                                counter <= 0;
                                            end
                                            
                                            STATE <= SAMPLE;
                                        end
        
            SAMPLE          :           begin
                                            if(counter != (samples-1))
                                            begin
                                                for(i = 0; i < inputs; i = i + 1)
                                                begin
                                                    if(din[i] == 1) fireCount[i] <= fireCount[i] + 1;
                                                    else            fireCount[i] <= fireCount[i];
                                                end
                                                
                                                counter <= counter + 1;
                                                STATE <= SAMPLE;
                                            end
                                            
                                            else
                                            begin
                                                counter <= 0;
                                                STATE <= COMPARE;
                                            end
                                        end
                                        
            COMPARE         :           begin
                                            if(counter != inputs)
                                            begin
                                                
                                                if(fireCount[counter] > temp)   temp <= fireCount[counter];
                                                else                            temp <= temp;
                                            
                                                counter <= counter + 1;
                                                STATE <= COMPARE;
                                            end
                                            
                                            else
                                            begin
                                                counter <= 0;
                                                STATE <= DECIDE;
                                            end
                                        end                  
                                        
            DECIDE          :           begin
                                            for(i = 0; i < inputs; i = i + 1)
                                            begin
                                                if(fireCount[i] == temp)    dout[i] <= 1;
                                                else                        dout[i] <= 0;  
                                            end
                                            
                                            STATE <= IDLE;
                                        end                                                
            
        endcase
    
    end
    
    

endmodule
