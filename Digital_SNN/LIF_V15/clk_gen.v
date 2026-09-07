////    **Frequency Divider**    ////
//Synthesizable Design made for taking an FPGA board's inbuilt clock and reduce it down to get the desired clock frequency//
//Just change the value of parameter 'inbuiltClk' to the default clock frequency provided by your FPGA development board//
//and change the value of parameter 'desiredFrequency' to the frequency you want at the output//
//The formula that I have come up with if you are curious//
//maxCount = inbuiltClk/(2*outFrequency) //this will get the value that the counter must count upto before it negates the output wire working as clock//
//$clog2(inbuiltClk/2)-1 gives the MSB of the reg that is required to hold the maxCount value//
//Won't work if the inbuilt clock frequency and the desired output frequency are both same//
//Note: this design should work for almost every board but it was tested for Spartan-7//


module clk_gen #(parameter inbuiltClk = 100_000_000 , parameter desiredFrequency = 100)(
    input wire bClk,
    output reg outFreq
    );
    
    reg [($clog2(inbuiltClk/2))-1:0]maxCount = inbuiltClk/(2*desiredFrequency);
    reg [($clog2(inbuiltClk/2))-1:0]count;
    
    initial begin
        outFreq <= 0;
        count <= 0;
    end
    
    always @(posedge bClk) begin
        if(count==maxCount)
            begin
                outFreq <= ~outFreq;
                count <= 0;
            end
        else
            begin
                count <= count+1;
            end
    end
    
endmodule