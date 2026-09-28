`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/24/2026 03:33:44 PM
// Design Name: 
// Module Name: concat32
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


module concat32
(
    input   wire    [07:00] sig_in0,
    input   wire    [07:00] sig_in1,
    input   wire    [07:00] sig_in2,
    input   wire    [07:00] sig_in3,
    output  wire    [00:31] sig_out
);

    assign  sig_out[00:07]   =   sig_in0;
    assign  sig_out[08:15]   =   sig_in1;
    assign  sig_out[16:23]   =   sig_in2;
    assign  sig_out[24:31]   =   sig_in3;

endmodule
