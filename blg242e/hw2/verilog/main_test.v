// Furkan Salýk - 150200056

`timescale 1ns / 1ps

module SRLatchWithoutEnable_test();
    reg S;
    reg R;
    
    wire Q;
    wire Qneg;
    
    SRLatchWithoutEnable uut(S, R, Q, Qneg);
    
    initial begin
        S = 0; R = 0; #25;
        S = 1; R = 0; #25;
        S = 0; R = 1; #25;
        S = 1; R = 1; #25;
    end
endmodule

module SRLatchWithEnable_test();
    reg S;
    reg R;
    reg Enable;
    
    wire Q;
    wire Qneg;
    
    SRLatchWithEnable uut(S, R, Enable, Q, Qneg);
    
    initial begin
        S = 0; R = 0; Enable = 0; #25;
        S = 0; R = 0; Enable = 1; #25;
        S = 1; R = 0; Enable = 0; #25;
        S = 1; R = 0; Enable = 1; #25;
        S = 0; R = 1; Enable = 0; #25;
        S = 0; R = 1; Enable = 1; #25;
        S = 1; R = 1; Enable = 0; #25;
        S = 1; R = 1; Enable = 1; #25;
    end
endmodule

module DFlipFlopPosEdge_test();
    reg D;
    reg CLK;
    
    wire Q;
    wire Qneg;
    
    DFlipFlopPosEdge uut(D, CLK, Q, Qneg);
    
    initial begin
        CLK = 0; #5;
        D = 0; #5;
        CLK = 1; #5;
        D = 1; #5;
        CLK = 0; # 5;
        CLK = 1; #5;
    end
endmodule

module JKFlipFlopPosEdge_test();
    reg J;
    reg K;
    reg CLK;
    
    wire Q;
    wire Qneg;
    
    JKFlipFlopPosEdge uut(J, K, CLK, Q, Qneg);
    
    initial begin
        CLK = 0; #1;
        J = 0; K = 0; #5;
        J = 1; K = 0; #5;
        J = 0; K = 1; #5;
        J = 1; K = 1; #5;
    end
    
    always begin
        CLK = ~CLK; #2;
    end
endmodule

module AsyncUpCounterPosEdge4_test();
    reg CLK;
            
    wire Q0;
    wire Q1;
    wire Q2;
    wire Q3;
    
    assign Q0 = 0;
    assign Q1 = 0;
    assign Q2 = 0;
    assign Q3 = 0;
    
    AsyncUpCounterPosEdge4 uut(.CLK(CLK), .Q0(Q0), .Q1(Q1), .Q2(Q2), .Q3(Q3));
    
    initial begin
        CLK = 0; #5;
    end
    
    always begin
        CLK = ~CLK; #15;
    end
endmodule

module SyncUpCounterPosEdge4_test();
    reg CLK;
            
    wire Q0;
    wire Q1;
    wire Q2;
    wire Q3;
    
    assign Q0 = 0;
    assign Q1 = 0;
    assign Q2 = 0;
    assign Q3 = 0;
    
    SyncUpCounterPosEdge4 uut(.CLK(CLK), .Q0(Q0), .Q1(Q1), .Q2(Q2), .Q3(Q3));
    
    initial begin
        CLK = 0; #5;
    end
    
    always begin
        CLK = ~CLK; #15;
    end
endmodule

module PulseGeneratorPosEdge8_test();
    reg[7:0] INP;
    reg CLK;
    reg LOAD;
    
    wire Q;
    
    PulseGeneratorPosEdge8 uut(INP, CLK, LOAD, Q);
    
    initial begin
        CLK = 0; #5;
        INP <= 8'b11110000; #5;
        LOAD = 1; #5;
        LOAD = 0; #20;
    end
    
    always begin
        CLK = ~CLK; #100;
    end
endmodule