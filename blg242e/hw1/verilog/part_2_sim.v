`timescale 1ns/1ps

module PART2_SIM();
reg A;
reg B;
wire Sum;
wire Carry; 
halfadder sim (.A(A),.B(B),.Sum(Sum),.Carry(Carry));
initial begin 
A=0; B=0;  #250;
A=0; B=1;  #500;
A=1; B=0;  #750;
A=1; B=1;  #1000;
end
endmodule