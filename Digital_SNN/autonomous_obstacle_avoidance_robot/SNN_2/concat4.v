`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: CWIR3
// Engineer: copperwire
// 
// Create Date: 09/16/2026 12:23:10 PM
// Design Name: 
// Module Name: concat4
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


module concat4
(
    input   wire    sig_0,
    input   wire    sig_1,
    input   wire    sig_2,
    input   wire    sig_3,
    output  wire    [0 : 3] sig
);

    assign  sig[0]  =   sig_0;
    assign  sig[1]  =   sig_1;
    assign  sig[2]  =   sig_2;
    assign  sig[3]  =   sig_3;
    
endmodule
