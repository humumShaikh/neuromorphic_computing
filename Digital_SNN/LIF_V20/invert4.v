`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09/24/2026 03:30:27 PM
// Design Name: 
// Module Name: invert4
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


module invert4
(
    input   wire    [3:0]   sig_in,
    output  wire    [0:3]   sig_out
);

    assign  sig_out[0]  =   sig_in[3];
    assign  sig_out[1]  =   sig_in[2];
    assign  sig_out[2]  =   sig_in[1];
    assign  sig_out[3]  =   sig_in[0];

endmodule
