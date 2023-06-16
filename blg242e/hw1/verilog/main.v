module or_gate(
input A,
input B,
output C);
assign C=A|B;
endmodule 

module not_gate(
  input  A,
  output  B);
  assign B = ~A;
 endmodule
  
module and_gate(
    input  A,
    input  B,
    output  C
    );
    assign C = A&B;
endmodule

module nand_gate(
input A,
input B,
output C);
wire CNAND;
and_gate ANDFORNAND(.A(A),.B(B),.C(CNAND));
not_gate NOTFORNAND(.A(CNAND),.B(C));
endmodule

module xor_gate(
input A,
input B,
output C);
wire CXOR1;
wire Anot;
wire Bnot;
wire CXOR2;
not_gate N1(.A(A),.B(Anot));
not_gate N2(.A(B),.B(Bnot));
or_gate ORFORXOR1(.A(A),.B(B),.C(CXOR1));
or_gate ORFORXOR2(.A(Anot),.B(Bnot),.C(CXOR2));
and_gate ANDFORXOR(.A(CXOR1),.B(CXOR2),.C(C));
endmodule


//  8:1 multiplexerrr

module nand_gate3(i0, i1, i2, o);
    input wire i0;
    input wire i1;
    input wire i2;
    output wire o;
    
    wire AND_WIRE;
    and_gate4 A(i0, i1, i2, 1, AND_WIRE);
    
    not_gate N(AND_WIRE, o);
endmodule

module or_gate4(i0,i1,i2,i3,o);
    input wire i0;
    input wire i1;
    input wire i2;
    input wire i3;
    output wire o;
    assign o = i0 | i1 | i2 | i3;
endmodule

module and_gate4(i0,i1,i2,i3,o);
    input wire i0;
    input wire i1;
    input wire i2;
    input wire i3;
    output wire o;
    assign o = i0 & i1 & i2 & i3;
endmodule

module or_gate8(i0,i1,i2,i3,i4,i5,i6,i7,o);
    input wire i0;
    input wire i1;
    input wire i2;
    input wire i3;
    input wire i4;
    input wire i5;
    input wire i6;
    input wire i7;
    output wire o;
    assign o = i0 | i1 | i2 | i3 | i4 | i5 | i6 | i7;
endmodule

module not_gate(i0,o);
    input wire i0;
    output wire o;
    assign o = ~i0;
endmodule

module multiplexer8x1(i0,i1,i2,i3,i4,i5,i6,i7,s0,s1,s2,o);
    input wire i0;
    input wire i1;
    input wire i2;
    input wire i3;
    input wire i4;
    input wire i5;
    input wire i6;
    input wire i7;
    input wire s0;
    input wire s1;
    input wire s2;
    output wire o;
    
    wire s0not;
    wire s1not;
    wire s2not;
    
    not_gate G9(.i0(s0), .o(s0not));
    not_gate G10(.i0(s1), .o(s1not));
    not_gate G11(.i0(s2), .o(s2not));
    
    wire D0;
    wire D1;
    wire D2;
    wire D3;
    wire D4;
    wire D5;
    wire D6;
    wire D7;
    
    and_gate4 G1(.i0(s0not), .i1(s1not), .i2(s2not), .i3(i0), .o(D0));
    and_gate4 G2(.i0(s0), .i1(s1not), .i2(s2not), .i3(i1), .o(D1));
    and_gate4 G3(.i0(s0not), .i1(s1), .i2(s2not), .i3(i2), .o(D2));
    and_gate4 G4(.i0(s0), .i1(s1), .i2(s2not), .i3(i3), .o(D3));
    and_gate4 G5(.i0(s0not), .i1(s1not), .i2(s2), .i3(i4), .o(D4));
    and_gate4 G6(.i0(s0), .i1(s1not), .i2(s2), .i3(i5), .o(D5));
    and_gate4 G7(.i0(s0not), .i1(s1), .i2(s2), .i3(i6), .o(D6));
    and_gate4 G8(.i0(s0), .i1(s1), .i2(s2), .i3(i7), .o(D7));
    
    or_gate8 F(.i0(D0), .i1(D1), .i2(D2), .i3(D3), .i4(D4), .i5(D5), .i6(D6), .i7(D7), .o(o));
endmodule


// DECOODEEERRRR

module not_gate(
  input  A,
  output  B);
  assign B = ~A;
 endmodule
  
module and_gate(
    input  A,
    input  B,
    output  C
    );
    assign C = A&B;
endmodule

module or_gate(
input A,
input B,
output C);
assign C=A|B;
endmodule 

module decoder (A,B,C,D0,D1,D2,D3,D4,D5,D6,D7);
    input wire A;
    input wire B;
    input wire C;
    output wire D0;
    output wire D1;
    output wire D2;
    output wire D3;
    output wire D4;
    output wire D5;
    output wire D6;
    output wire D7;
    
    wire AC; // ~~A
    wire BC; // ~~B
    wire CC; // ~~C
    wire CCBC1;
    wire CCBC2;
    wire CCB1;
    wire CCB2;
    wire CBC1;
    wire CBC2;
    wire CB1;
    wire CB2;
    
    
    not_gate NOT1(.A(A),.B(AC));
    not_gate NOT2(.A(B),.B(BC));
    not_gate NOT3(.A(C),.B(CC));
    
    and_gate AND1(.A(CC),.B(BC),.C(CCBC1));
    and_gate AND2(.A(CCBC1),.B(AC),.C(D0));
    
    and_gate AND3A(.A(CC),.B(BC),.C(CCBC2));
    and_gate AND3(.A(CCBC2),.B(A),.C(D1));
    
    and_gate AND4(.A(CC),.B(B),.C(CCB1));
    and_gate AND5(.A(CCB1),.B(AC),.C(D2));
    
    and_gate AND6(.A(CC),.B(B),.C(CCB2));
    and_gate AND7(.A(CCB2),.B(A),.C(D3));
    
    and_gate AND8(.A(C),.B(BC),.C(CBC1));
    and_gate AND9(.A(CBC1),.B(AC),.C(D4));
    
    and_gate AND10(.A(C),.B(BC),.C(CBC2));
    and_gate AND11(.A(CBC2),.B(A),.C(D5));
    
    and_gate AND12(.A(C),.B(B),.C(CB1));
    and_gate AND13(.A(CB1),.B(AC),.C(D6));
    
    and_gate AND14(.A(C),.B(B),.C(CB2));
    and_gate AND15(.A(CB2),.B(A),.C(D7));
    
endmodule

module f1_1(A, B, C, D, F);
    input wire A;
    input wire B;
    input wire C;
    input wire D;
    output wire F;
    
    wire bNOT;
    not_gate N1(.A(B), .B(bNOT));
    
    wire dNOT;
    not_gate N2(.A(D), .B(bNOT));
    
    wire BD;
    and_gate A1(bNOT, dNOT, BD);
    
    wire ACD;
    and_gate4 A2(A, C, D, 1, ACD);
    
    wire aNOT;
    not_gate N3(A, aNOT);
    
    wire ABC;
    and_gate4 A3(aNOT, B, C, 1, ABC);
    
    or_gate4 O4(BD, ACD, ABC, 0, F);
endmodule

module f1_2(A, B, C, D, F);
    input wire A;
    input wire B;
    input wire C;
    input wire D;
    output wire F;
    
    wire bNOT;
    nand_gate N1(B, B, bNOT);
    
    wire dNOT;
    nand_gate N2(D, D, dNOT);
    
    wire nand1;
    nand_gate N3(bNOT, dNOT, nand1);
    
    wire ACD;
    nand_gate3 N4(A, C, D, ACD);
    
    wire aNOT;
    nand_gate N5(A, A, aNOT);
    
    wire ABC;
    nand_gate3 N6(aNOT, B, C, ABC);
    
    nand_gate3 N7(nand1, ACD, ABC, F);
endmodule

module f1_3(A, B, C, D, F);
    input wire A;
    input wire B;
    input wire C;
    input wire D;
    output wire F;
    
    wire dNOT;
    not_gate n1(D, dNOT);
    
    multiplexer8x1 mux(dNOT, dNOT, 0, 1, dNOT, 1, 0, D, C, B, A, F);
endmodule

module f2_1(A, B, C, F);
    input wire A;
    input wire B;
    input wire C;
    output wire F;
    
    wire dec3;
    wire dec5;
    
    decoder dec(A, B, C, 0, 0, 0, dec3, 0, dec5, 0, 0);
    
    or_gate O(dec3, dec5, F);
endmodule

module half_adder(A, B, SUM, COUT);
    input wire A;
    input wire B;
    
    output wire SUM;
    output wire COUT;
    
    xor_gate X(A, B, SUM);
    and_gate A1(A, B, COUT);
endmodule

module full_adder(A, B, CIN, SUM, COUT);
    input wire A;
    input wire B;
    input wire CIN;
    
    output wire SUM;
    output wire COUT;
    
    wire sum1;
    wire cout1;
    half_adder HA1(A, B, sum1, cout1);
    
    wire cout2;
    half_adder HA2(CIN, sum1, SUM, cout2);
    
    or_gate O(cout1, cout2, COUT);
endmodule

module full_adder4(A, B, CIN, SUM, COUT);
    input wire [3:0] A;
    input wire [3:0] B; 
    input wire CIN;
    output wire [3:0] SUM;
    output wire COUT;
    
    
endmodule