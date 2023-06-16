// Furkan Salýk - 150200056

`timescale 1ns / 1ps

module NOR2(A, B, OUT);
    input wire A;
    input wire B;
    
    output wire OUT;
    
    wire AorB;
    assign AorB = A | B;
    
    assign OUT = ~AorB;
endmodule

module NAND2(A, B, OUT);
    input wire A;
    input wire B;
    
    output wire OUT;
    
    wire AandB;
    assign AandB = A & B;
    
    assign OUT = ~AandB;
endmodule

module SRLatchWithoutEnable(S, R, Q, Qneg);
    input wire S;
    input wire R;
    
    output wire Q;
    output wire Qneg;
    
    NOR2 N1(R, Qneg, Q);
    NOR2 N2(Q, S, Qneg);
endmodule

module SRLatchWithEnable(S, R, E, Q, Qneg);
    input wire S;
    input wire R;
    input wire E;
    
    output wire Q;
    output wire Qneg;
    
    wire SnandE;
    NAND2 N1(S, E, SnandE);
    
    wire RnandE;
    NAND2 N2(R, E, RnandE);
    
    NAND2 N3(SnandE, Qneg, Q);
    NAND2 N4(RnandE, Q, Qneg);
endmodule

module DLatch(D, E, Q, Qneg);
    input wire D;
    input wire E;
    
    output wire Q;
    output wire Qneg;
    
    wire DnandE;
    NAND2 N1(D, E, DnandE);
    
    wire notD;
    NAND2 N2(D, D, notD);
    
    wire notDnandE;
    NAND2 N3(notD, E, notDnandE);
    
    NAND2 N4(DnandE, Qneg, Q);
    NAND2 N5(notDnandE, Q, Qneg);
endmodule

module DFlipFlopPosEdge(D, CLK, Q, Qneg);
    input wire D;
    input wire CLK;
    
    output wire Q;
    output wire Qneg;
    
    wire QIntermediate;
    wire QNegIntermediate;
    
    wire notCLK;
    NAND2 N1(CLK, CLK, notCLK);
    
    DLatch D1(.D(D), .E(notCLK), .Q(QIntermediate), .Qneg(QNegIntermediate));
    DLatch D2(.D(QIntermediate), .E(CLK), .Q(Q), .Qneg(Qneg));
endmodule

module JKFlipFlopPosEdge(J, K, CLK, Q, Qneg);
    input wire J;
    input wire K;
    input wire CLK;
                 
    output wire Q;
    output wire Qneg;
    
    wire notK;
    NAND2 N1(K, K, notK);
    
    wire JNandNotK;
    NAND2 N2(J, notK, JNandNotK);
    
    wire notJ;
    NAND2 N3(J, J, notJ);
    
    wire notJNandK;
    NAND2 N4(notJ, K, notJNandK);
    
    wire JNandK;
    NAND2 N5(J, K, JNandK);
    
    wire JAndK;
    NAND2 N6(JNandK, JNandK, JAndK);
    
    wire notQ;
    NAND2 N7(Q, Q, notQ);
    
    wire JAndKNandNotQ;
    NAND2 N8(JAndK, notQ, JAndKNandNotQ);
    
    wire JAndKNandQ;
    NAND2 N9(JAndK, Q, JAndKNandQ);
    
    wire S;
    NAND2 N10(JNandNotK, JAndKNandNotQ, S);
    
    wire R;
    NAND2 N11(notJNandK, JAndKNandQ, R);
    
    wire notCLK;
    NAND2 N12(CLK, CLK, notCLK);
    
    wire QIntermediate;
    wire QnegIntermediate;
    
    SRLatchWithEnable SR1(.S(S), .R(R), .E(notCLK), .Q(QIntermediate), .Qneg(QnegIntermediate));
    SRLatchWithEnable SR2(.S(QIntermediate), .R(QnegIntermediate), .E(CLK), .Q(Q), .Qneg(Qneg));
endmodule

module AsyncUpCounterPosEdge4(CLK, Q0, Q1, Q2, Q3);
    input wire CLK;
    
    output wire Q0;
    output wire Q1;
    output wire Q2;
    output wire Q3;
    
    /*wire notQ0;
    NAND2 N1(Q0, Q0, notQ0);
    wire notQ0_nand_Q1;
    NAND2 N2(notQ0, Q1, notQ0_nand_Q1);
    wire Q2nandQ3;
    NAND2 N3(Q2, Q3, Q2nandQ3);
    wire notQ0_and_Q1;
    NAND2 N4(notQ0_nand_Q1, notQ0_nand_Q1, notQ0_and_Q1);
    wire Q2andQ3;
    NAND2 N5(Q2nandQ3, Q2nandQ3, Q2andQ3);
    wire Qisnot14;
    NAND2 N6(notQ0_and_Q1, Q2andQ3, Qisnot14);*/
        
    wire Qneg0;
    wire Qneg1;
    wire Qneg2;
    wire Qneg3;
    JKFlipFlopPosEdge JKFF1(.J(1), .K(1), .CLK(CLK), .Q(Q0), .Qneg(Qneg0));
    JKFlipFlopPosEdge JKFF2(.J(1), .K(1), .CLK(Qneg0), .Q(Q1), .Qneg(Qneg1));
    JKFlipFlopPosEdge JKFF3(.J(1), .K(1), .CLK(Qneg1), .Q(Q2), .Qneg(Qneg2));
    JKFlipFlopPosEdge JKFF4(.J(1), .K(1), .CLK(Qneg2), .Q(Q3), .Qneg(Qneg3));
endmodule

module SyncUpCounterPosEdge4(CLK, Q0, Q1, Q2, Q3);
    input wire CLK;
    
    output wire Q0;
    output wire Q1;
    output wire Q2;
    output wire Q3;

    wire Q0neg;
    wire Q1neg;
    wire Q2neg;
    wire Q3neg;
    
    wire notQ0;
    NAND2 N1(Q0, Q0, notQ0);
    wire notQ0_nand_Q1;
    NAND2 N2(notQ0, Q1, notQ0_nand_Q1);
    wire Q2nandQ3;
    NAND2 N3(Q2, Q3, Q2nandQ3);
    wire notQ0_and_Q1;
    NAND2 N4(notQ0_nand_Q1, notQ0_nand_Q1, notQ0_and_Q1);
    wire Q2andQ3;
    NAND2 N5(Q2nandQ3, Q2nandQ3, Q2andQ3);
    wire Qisnot14;
    NAND2 N6(notQ0_and_Q1, Q2andQ3, Qisnot14);
    
    JKFlipFlopPosEdge JKFF1(.J(Qisnot14), .K(1), .CLK(CLK), .Q(Q0), .Qneg(Q0neg));
    
    wire Q0nandQisnot14;
    NAND2 N7(Q0, Qisnot14, Q0nandQisnot14);
    wire Q0andQisnot14;
    NAND2 N8(Q0nandQisnot14, Q0nandQisnot14, Q0andQisnot14);
    
    wire Q0orQis14;
    NAND2 N9(Q0neg, Qisnot14, Q0orQis14); 
    
    JKFlipFlopPosEdge JKFF2(.J(Q0andQisnot14), .K(Q0orQis14), .CLK(CLK), .Q(Q1), .Qneg(Q1neg));
    
    wire Q0nandQ1;
    NAND2 N10(Q0, Q1, Q0nandQ1);
    wire Q0andQ1;
    NAND2 N11(Q0nandQ1, Q0nandQ1, Q0andQ1);
    
    wire Q0andQ1_nand_Q2;
    NAND2 N12(Q0andQ1, Q2, Q0andQ1_nand_Q2);
    wire Q0andQ1andQ2;
    NAND2 N13(Q0andQ1_nand_Q2, Q0andQ1_nand_Q2, Q0andQ1andQ2);
    
    wire not_Q0andQ1andQisnot14;
    NAND2 N14(Q0andQ1, Qisnot14, not_Q0andQ1andQisnot14);
    wire Q0andQ1andQisnot14;
    NAND2 N15(not_Q0andQ1andQisnot14, not_Q0andQ1andQisnot14, Q0andQ1andQisnot14);
    
    wire Q0andQ1_or_Qis14;
    NAND2 N16(Q0nandQ1, Qisnot14, Q0andQ1_or_Qis14);
    
    JKFlipFlopPosEdge JKFF3(.J(Q0andQ1andQisnot14), .K(Q0andQ1_or_Qis14), .CLK(CLK), .Q(Q2), .Qneg(Q2neg));
    
    wire not_Q0andQ1andQ2andQisnot14;
    NAND2 N17(Q0andQ1andQ2, Qisnot14, not_Q0andQ1andQ2andQisnot14);
    wire Q0andQ1andQ2andQisnot14;
    NAND2 N18(not_Q0andQ1andQ2andQisnot14, not_Q0andQ1andQ2andQisnot14, Q0andQ1andQ2andQisnot14);
    
    wire not_Q0andQ1andQ2;
    NAND2 N19(Q0andQ1andQ2, Q0andQ1andQ2, not_Q0andQ1andQ2);
    wire Q0andQ1andQ2_or_Qis14;
    NAND2 N20(not_Q0andQ1andQ2, Qisnot14, Q0andQ1andQ2_or_Qis14);
    
    JKFlipFlopPosEdge JKFF4(.J(Q0andQ1andQ2andQisnot14), .K(Q0andQ1andQ2_or_Qis14), .CLK(CLK), .Q(Q3), .Qneg(Q3neg));
endmodule

module PulseGeneratorPosEdge8(INP, CLK, LOAD, OUT);
    input wire[7:0] INP;
    input wire CLK;
    input wire LOAD;
    
    output wire OUT;
    
    wire[7:0] Q;
    wire[7:0] Qneg;
    
    wire SHIFT;
    assign SHIFT = ~LOAD;
    
    wire[7:0] loadAndInp;
    assign loadAndInp = LOAD & INP;
    
    wire shiftAndInp1;
    assign shiftAndInp1 = SHIFT & Q[7];
    wire inp1;
    assign inp1 = loadAndInp[0] | shiftAndInp1;
    
    wire shiftAndInp2;
    assign shiftAndInp2 = SHIFT & Q[0];
    wire inp2;
    assign inp2 = loadAndInp[1] | shiftAndInp2;
        
    wire shiftAndInp3;
    assign shiftAndInp3 = SHIFT & Q[1];
    wire inp3;
    assign inp3 = loadAndInp[2] | shiftAndInp3;
    
    wire shiftAndInp4;
    assign shiftAndInp4 = SHIFT & Q[2];
    wire inp4;
    assign inp4 = loadAndInp[3] | shiftAndInp4;
    
    wire shiftAndInp5;
    assign shiftAndInp5 = SHIFT & Q[3];
    wire inp5;
    assign inp5 = loadAndInp[4] | shiftAndInp5;
    
    wire shiftAndInp6;
    assign shiftAndInp6 = SHIFT & Q[4];
    wire inp6;
    assign inp6 = loadAndInp[5] | shiftAndInp6;
    
    wire shiftAndInp7;
    assign shiftAndInp7 = SHIFT & Q[5];
    wire inp7;
    assign inp7 = loadAndInp[6] | shiftAndInp7;
    
    wire shiftAndInp8;
    assign shiftAndInp8 = SHIFT & Q[6];
    wire inp8;
    assign inp8 = loadAndInp[7] | shiftAndInp8;
    
    DFlipFlopPosEdge DFF1(inp1, CLK, Q[0], Qneg[0]);
    DFlipFlopPosEdge DFF2(inp2, CLK, Q[1], Qneg[1]);
    DFlipFlopPosEdge DFF3(inp3, CLK, Q[2], Qneg[2]);
    DFlipFlopPosEdge DFF4(inp4, CLK, Q[3], Qneg[3]);
    DFlipFlopPosEdge DFF5(inp5, CLK, Q[4], Qneg[4]);
    DFlipFlopPosEdge DFF6(inp6, CLK, Q[5], Qneg[5]);
    DFlipFlopPosEdge DFF7(inp7, CLK, Q[6], Qneg[6]);
    DFlipFlopPosEdge DFF8(inp8, CLK, Q[7], Qneg[7]);
    
    assign OUT = Q[7];
endmodule