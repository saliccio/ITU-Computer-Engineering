`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Istanbul Technical University
// Engineer: Eyupcan Cakir & Furkan Salik
// 
// Create Date: 30.04.2022 23:15:11
// Design Name: 
// Module Name: Design
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

module Memory(
    input wire[7:0] address,
    input wire[7:0] data,
    input wire wr, //Read = 0, Write = 1
    input wire cs, //Chip is enable when cs = 0
    input wire clock,
    output reg[7:0] o // Output
);
    //Declaration oýf the RAM Area
    reg[7:0] RAM_DATA[0:255];
    //Read Ram data from the file
    initial $readmemh("RAM.mem", RAM_DATA);
    //Read the selected data from RAM
    always @(*) begin
        o = ~wr && ~cs ? RAM_DATA[address] : 8'hZ;
    end
    
    //Write the data to RAM
    always @(posedge clock) begin
        if (wr && ~cs) begin
            RAM_DATA[address] <= data; 
        end
    end
endmodule

module register_8_bit(
    input [7:0] I,
    input [1:0] FunSel,
    input clk, E,
    output reg [7:0] Q
    );
    initial Q <= 8'd0;
    always @ (posedge clk)
        if (E)
            case (FunSel)
                2'b00   : Q <= Q - 1;
                2'b01   : Q <= Q + 1;
                2'b10   : Q <= I;
                2'b11   : Q <= 8'd0;
            endcase
endmodule
    
module register_16_bit(
    input [15:0] I,
    input [1:0] FunSel,
    input clk, E,
    output reg [15:0] Q
    );
    always @ (posedge clk)
        if (E)
            case (FunSel)
                2'b00   : Q <= Q - 1;
                2'b01   : Q <= Q + 1;
                2'b10   : Q <= I;
                2'b11   : Q <= 16'd0;
            endcase
endmodule

module RegisterFile(
    input [7:0] I,
    input [1:0] OutASel, OutBSel, FunSel,
    input [0:3] RegSel,
    input clk,
    output [7:0] OutA, OutB
    );
    wire [7:0] R [0:3];
    generate
        genvar i;
        // generate 4 8-bit General Purpose Registers
        for (i = 0; i < 4; i = i + 1) begin
            register_8_bit R (I, FunSel, clk, ~RegSel[i], R[i]);
        end
    endgenerate
    
    //Conitnuous assignment of outputs
    assign OutA = R[OutASel];
    assign OutB = R[OutBSel];
    
    /* alwyas assign selected register values to outputs
    always @ (R[0], R[1], R[2], R[3]) begin
        OutA <= R[OutASel];
        OutB <= R[OutBSel];
    end*/
endmodule

module AddressRegisterFile(
        input [7:0] I,
        input [1:0] OutCSel,
        input [1:0] OutDSel,
        input [1:0] FunSel,
        input [0:2] RegSel,
        input CLK,
        output [7:0] OutC,
        output [7:0] OutD
    );
    wire [7:0] RegisterOutputs [0:2];
    
    register_8_bit PC(I, FunSel, CLK, ~RegSel[0], RegisterOutputs[0]);
    register_8_bit AR(I, FunSel, CLK, ~RegSel[1], RegisterOutputs[1]);
    register_8_bit SP(I, FunSel, CLK, ~RegSel[2], RegisterOutputs[2]);
    
    //Conitnuous assignment of outputs
    assign OutC = RegisterOutputs[OutCSel ? OutCSel - 1 : 0];
    assign OutD = RegisterOutputs[OutDSel ? OutDSel - 1 : 0];
    
    /* alwyas assign selected register values to outputs
    always @ (RegisterOutputs[0], RegisterOutputs[1], RegisterOutputs[2]) begin
        // if OutSel 0 or 1, assign Out to PC and if OutSel 1 and 2, assign Out to AR and SP respectively
        OutC <= RegisterOutputs[OutCSel ? OutCSel - 1 : 0];
        OutD <= RegisterOutputs[OutDSel ? OutDSel - 1 : 0];
    end*/
endmodule

module InstructionRegister(
    input [7:0] I,
    input [1:0] FunSel,
    input enable, lh, clk,
    output [15:0] IROut
    );
    // if lh flag is high, load I to (7-0) bits otherwise load I to (15-8) bits
    register_16_bit R (lh ? {IROut[15:8], I} : {I, IROut[7:0]}, FunSel, clk, enable, IROut);
endmodule

module ArithmeticLogicUnit(
    input [7:0] A, B,
    input [3:0] FunSel,
    input clk,
    output reg [3:0] OutFlag,
    output reg [7:0] OutALU
    );
    reg [8:0] carry;
    reg [3:0] R;
    always @ (posedge clk) begin
        #0.5;
        OutFlag <= R;
    end
    //initial OutFlag[2] <= 0;
    //initial OutFlag <= 4'd0;
    always @* begin
        case (FunSel)
            4'd0    : OutALU = A;
            4'd1    : OutALU = B;
            4'd2    : OutALU = ~A;
            4'd3    : OutALU = ~B;
            4'd4    : begin OutALU = A + B; carry = A + B; R[2] = carry[8]; R[0] = ~A[7] & ~B[7] & OutALU[7] | A[7] & B[7] & ~OutALU[7]; end
            4'd5    : begin OutALU = A + B + OutFlag[2]; carry = A + B + OutFlag[2]; R[2] = carry[8];  R[0] <= ~A[7] & ~B[7] & OutALU[7] | A[7] & B[7] & ~OutALU[7]; end
            4'd6    : begin OutALU = A - B; carry = A - B; R[2] = carry[8]; R[0] = A[7] & ~B[7] & ~OutALU[7] | ~A[7] & B[7] & OutALU[7]; end
            4'd7    : OutALU = A & B;
            4'd8    : OutALU = A | B;
            4'd9    : OutALU = A ^ B;
            4'd10   : begin OutALU = {A[6:0], 1'b0}; R[2] = A[6]; end
            4'd11   : begin OutALU = {1'b0, A[7:1]}; R[2] = OutALU[1]; end
            4'd12   : begin R[0] = A[7] ^ A[6]; OutALU = {A[6:0], 1'b0}; end
            4'd13   : OutALU = {A[7], A[7:1]};
            4'd14   : begin R[0] = A[7] ^ A[6]; R[2] = A[7]; OutALU = {A[6:0], R[2]}; end
            4'd15   : begin R[0] = A[7] ^ A[0]; R[2] = A[0]; OutALU = {R[2], A[7:1]}; end
        endcase
        R[3] = (OutALU === 8'd0 ? 1 : (OutALU === 8'dx ? 1'bx : 0));
        //OutFlag[3] = (OutALU === 8'd0);
        R[1] = (OutALU[7] === 1 ? 1 : (OutALU === 8'dx ? 1'bx : 0));
        //OutFlag[1] = (OutALU[7] === 1);
    end
endmodule

/*Flag Register not synchronized with clock
module ArithmeticLogicUnit(
    input [7:0] A, B,
    input [3:0] FunSel,
    output reg [3:0] OutFlag,
    output reg [7:0] OutALU
    );
    integer carry;
    //initial OutFlag[2] <= 0;
    //initial OutFlag <= 4'd0;
    always @* begin
        case (FunSel)
            4'd0    : OutALU = A;
            4'd1    : OutALU = B;
            4'd2    : OutALU = ~A;
            4'd3    : OutALU = ~B;
            4'd4    : begin OutALU = A + B; carry = A + B; OutFlag[2] = (carry > 255); OutFlag[0] = ~A[7] & ~B[7] & OutALU[7] | A[7] & B[7] & ~OutALU[7]; end
            4'd5    : begin OutALU = A + B + OutFlag[2]; carry = A + B + OutFlag[2]; OutFlag[2] = (carry > 255);  OutFlag[0] <= ~A[7] & ~B[7] & OutALU[7] | A[7] & B[7] & ~OutALU[7]; end
            4'd6    : begin OutALU = A - B; carry = A - B; OutFlag[2] = (carry >= 0); OutFlag[0] = A[7] & ~B[7] & ~OutALU[7] | ~A[7] & B[7] & OutALU[7]; end
            4'd7    : OutALU = A & B;
            4'd8    : OutALU = A | B;
            4'd9    : OutALU = A ^ B;
            4'd10   : begin OutALU = {A[6:0], 1'b0}; OutFlag[2] = A[6]; end
            4'd11   : begin OutALU = {1'b0, A[7:1]}; OutFlag[2] = OutALU[1]; end
            4'd12   : begin OutFlag[0] = A[7] ^ A[6]; OutALU = {A[6:0], 1'b0}; end
            4'd13   : OutALU = {A[7], A[7:1]};
            4'd14   : begin OutFlag[0] = A[7] ^ A[6]; OutFlag[2] = A[7]; OutALU = {A[6:0], OutFlag[2]}; end
            4'd15   : begin OutFlag[0] = A[7] ^ A[0]; OutFlag[2] = A[0]; OutALU = {OutFlag[2], A[7:1]}; end
        endcase
        OutFlag[3] = (OutALU === 8'd0 ? 1 : (OutALU === 8'dx ? 1'bx : 0));
        //OutFlag[3] = (OutALU === 8'd0);
        OutFlag[1] = (OutALU[7] === 1 ? 1 : (OutALU === 8'dx ? 1'bx : 0));
        //OutFlag[1] = (OutALU[7] === 1);
    end
endmodule*/

module ALUSystem(
    input [1:0] RF_OutASel, RF_OutBSel, RF_FunSel,
    input [3:0] RF_RegSel, ALU_FunSel,
    input [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel,
    input [2:0] ARF_RegSel,
    input IR_LH, IR_Enable,
    input [1:0] IR_Funsel,
    input Mem_WR, Mem_CS,
    input [1:0] MuxASel, MuxBSel,
    input MuxCSel, Clock,
    output reg [7:0] MuxAOut, MuxBOut, MuxCOut,
    output [7:0] AOut, BOut, ARF_COut, Address, MemoryOut, ALUOut,
    output [3:0] ALUOutFlag,
    output [15:0] IROut
    );
    RegisterFile RF (MuxAOut, RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, Clock, AOut, BOut);
    //ArithmeticLogicUnit ALU (MuxCOut, BOut, ALU_FunSel, ALUOutFlag, ALUOut);
    ArithmeticLogicUnit ALU (MuxCOut, BOut, ALU_FunSel, Clock, ALUOutFlag, ALUOut);
    AddressRegisterFile ARF (MuxBOut, ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, Clock, ARF_COut, Address);
    InstructionRegister IR (MemoryOut, IR_Funsel, IR_Enable, IR_LH, Clock, IROut);
    Memory MEM (Address, ALUOut, Mem_WR, Mem_CS, Clock, MemoryOut);
    always @ (IROut[7:0] or MemoryOut or ARF_COut or ALUOut or MuxASel)
        case (MuxASel)
            2'b00: MuxAOut <= IROut[7:0];
            2'b01: MuxAOut <= MemoryOut;
            2'b10: MuxAOut <= ARF_COut;
            2'b11: MuxAOut <= ALUOut;
        endcase
    always @ (IROut[7:0] or MemoryOut or ALUOut or MuxBSel)
        case (MuxBSel)
            2'b01: MuxBOut <= IROut[7:0];
            2'b10: MuxBOut <= MemoryOut;
            2'b11: MuxBOut <= ALUOut;   
        endcase
    always @ (AOut or ARF_COut or MuxCSel)
        MuxCOut <= MuxCSel ? AOut : ARF_COut;
endmodule

module ControlUnit(
    input Clock,
    input [3:0] ALUOutFlag,
    input [15:0] IROut,
    output [1:0] RF_OutASel, RF_OutBSel, RF_FunSel,
    output [3:0] RF_RegSel,
    output reg [3:0] ALU_FunSel,
    output [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel,
    output [2:0] ARF_RegSel,
    output IR_LH, IR_Enable,
    output [1:0] IR_Funsel,
    output Mem_WR, Mem_CS,
    output [1:0] MuxASel, MuxBSel,
    output MuxCSel
    );
    reg [3:0] SC;
    reg [15:0] D, T;
    reg I, TYP_SRC1, TYP_SRC2;
    reg [0:3] DEC_DEST;
    wire [2:0] RF_SRCSEL;
    wire [1:0] ARF_SRCSEL;
    wire SC_Reset;
    always @ (posedge Clock) begin
        if (SC_Reset | SC === 4'bx)
            SC <= 4'd0;
        else
            SC <= SC + 1;
    end
    always @ (SC) begin
        T = 16'd0;
        T[SC] = 1;
    end
    always @ (posedge T[2]) begin
        #0.1;
        D = 16'd0;
        D[IROut[15:12]] = 1;
        DEC_DEST = 4'd15;
        DEC_DEST[IROut[9:8]] = 0;
        I = IROut[10];
        TYP_SRC1 = IROut[6];
        TYP_SRC2 = IROut[2];
    end
    assign RF_OutASel = (T[5] & (D[13] | D[14]) & I) ? IROut[9:8] : ((T[3] & TYP_SRC1 & TYP_SRC2 & (D[4] | D[5] | D[7] | D[8]) | (T[3] & TYP_SRC1 & (D[3] | D[13] | D[14] | D[6] | D[10] | D[9]))) ? IROut[5:4] : RF_OutASel);
    assign RF_OutBSel = RF_SRCSEL[0] ? IROut[9:8] : (RF_SRCSEL[1] ? IROut[5:4] : IROut[1:0]);
    assign RF_SRCSEL[0] = T[3] & ((D[2] & ~I) | D[12]);
    assign RF_SRCSEL[1] = T[3] & (D[4] | D[5] | D[7] | D[8]) & (TYP_SRC1 & ~TYP_SRC2);
    assign RF_SRCSEL[2] = T[3] & (D[4] | D[5] | D[7] | D[8]) & (TYP_SRC2 & I);
    assign RF_FunSel = (T[4] & D[14] & I) ? 2'd0 : ((T[4] & D[13] & I) ? 2'd1 : 2'd2);
    assign RF_RegSel = (T[3] & D[1] | T[4] & D[11] | T[3] & (D[3] | D[13] | D[14] | D[6] | D[10] | D[9]) & I | T[4] & (D[13] | D[14]) & I | T[3] & (D[4] | D[5] | D[7] | D[8]) & I & (TYP_SRC1 | TYP_SRC2)) ? DEC_DEST : 4'd15;
    always @ (posedge T[3], posedge T[5]) begin
        if ((D[2] & ~I) | D[12])
            ALU_FunSel = 4'd1;
        if (D[3] | D[13] | D[14])
            ALU_FunSel = 4'd0;
        if (D[6])
            ALU_FunSel = 4'd2;
        if (D[10])
            ALU_FunSel = 4'd10;
        if (D[9])
            ALU_FunSel = 4'd11;
        if (D[4])
            ALU_FunSel = 4'd7;
        if (D[5])
            ALU_FunSel = 4'd8;
        if (D[7])
            ALU_FunSel = 4'd4;
        if (D[8])
            ALU_FunSel = 4'd6;
    end
    assign ARF_SRCSEL[0] = (T[3] & (D[3] | D[6] | D[9] | D[10] | D[13] | D[14]) & ~TYP_SRC1) | (T[3] & (D[4] | D[5] | D[7] | D[8]) & ~TYP_SRC1 & TYP_SRC2);
    assign ARF_SRCSEL[1] = (T[3] & (D[4] | D[5] | D[7] | D[8]) & TYP_SRC1 & ~TYP_SRC2);
    assign ARF_OutCSel = (T[5] & (D[13] | D[14]) & I) ? IROut[9:8] : (ARF_SRCSEL[0] ? IROut[5:4] : IROut[1:0]);
    assign ARF_OutDSel = (T[0] | T[1]) ? 2'b00 : ((T[3] & ~I & (D[1] | D[2]) ? 2'b10 : 2'b11));
    assign ARF_FunSel = (T[0] | T[1] | T[3] & D[11] | T[4] & D[13] & ~I) ? 2'b01 : ((T[4] & D[14] & ~I | T[3] & D[12]) ? 2'b00 : 2'b10);
    assign ARF_RegSel = (T[0] | T[1] | (T[3] & ((D[0] & I) | (D[15] & I & ~ALUOutFlag[3])))) ? (3'b011) : (((T[3] & (D[11] | D[12])) ? 3'b110 : ((~I & (((T[3] & (((D[4] | D[5] | D[7] | D[8]) & (TYP_SRC1 | TYP_SRC2)) | D[3] | D[13] | D[14] | D[6] | D[10] | D[9])) | (T[4] & (D[13] | D[14]))))) ? ((IROut[9:8] === 2'd0) ? 3'b011 : DEC_DEST[1:3]) : 3'd7)));
    assign IR_Enable = T[0] | T[1];
    assign IR_Funsel = 2'd2;
    assign IR_LH = T[0];
    assign Mem_WR = T[3] & ((D[2] & ~I) | D[12]);
    assign Mem_CS = ~(T[0] | T[1] | (T[3] & (~I & (D[2] | D[1])) | D[12]) | T[4] & D[11]);
    assign MuxASel = (T[3] & D[1] & I) ? 2'd0 : (((T[3] & D[1] & ~I) | (T[4] & D[11])) ? 2'd1 : 2'd3);
    assign MuxBSel = (T[3] & ((D[0] & I) | (D[15] & I & ~ALUOutFlag[3]))) ? 2'd1 : 2'd3;
    assign MuxCSel = T[3] & TYP_SRC1 & ((D[3] | D[13] | D[14] | D[6] | D[10] | D[9]) | (TYP_SRC2 & (D[4] | D[5] | D[7] | D[8]))) | (T[5] & D[13]) | (T[5] & D[14]) ? 1 : ((T[3] & ~TYP_SRC1 & (D[3] | D[13] | D[14] | D[6] | D[10] | D[9]) | ((T[3] & ((TYP_SRC1 & ~TYP_SRC2) | (~TYP_SRC1 & TYP_SRC2)) & (D[4] | D[5] | D[7] | D[8])))) ? 0 : MuxCSel);
    assign SC_Reset = (T[5] & (D[13] | D[14])) | (T[4] & (D[11])) | (T[3] & (D[0] | D[1] | D[2] | D[3] | D[4] | D[5] | D[6] | D[7] | D[8] | D[9] | D[10] | D[12] | D[15]));
endmodule

module CPU(
    input Clock
    );
    wire [1:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    wire [3:0] RF_RegSel, ALU_FunSel;
    wire [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel;
    wire [2:0] ARF_RegSel;
    wire IR_LH, IR_Enable;
    wire [1:0] IR_Funsel;
    wire Mem_WR, Mem_CS;
    wire [1:0] MuxASel, MuxBSel;
    wire MuxCSel;
    wire [3:0] ALUOutFlag;
    wire [15:0] IROut;
    ALUSystem _ALUSystem(
        .RF_OutASel(RF_OutASel), 
        .RF_OutBSel(RF_OutBSel), 
        .RF_FunSel(RF_FunSel),
        .RF_RegSel(RF_RegSel),
        .ALU_FunSel(ALU_FunSel),
        .ARF_OutCSel(ARF_OutCSel), 
        .ARF_OutDSel(ARF_OutDSel), 
        .ARF_FunSel(ARF_FunSel),
        .ARF_RegSel(ARF_RegSel),
        .IR_LH(IR_LH),
        .IR_Enable(IR_Enable),
        .IR_Funsel(IR_Funsel),
        .Mem_WR(Mem_WR),
        .Mem_CS(Mem_CS),
        .MuxASel(MuxASel),
        .MuxBSel(MuxBSel),
        .MuxCSel(MuxCSel),
        .Clock(Clock),
        .IROut(IROut),
        .ALUOutFlag(ALUOutFlag)
        );
    ControlUnit CU (Clock, ALUOutFlag, IROut, RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, ALU_FunSel,
        ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel);
endmodule

/* with reset input
module ControlUnit(
    input Clock, Reset,
    input [3:0] ALUOutFlag,
    input [15:0] IROut,
    output [1:0] RF_OutASel, RF_OutBSel, RF_FunSel,
    output [3:0] RF_RegSel,
    output reg [3:0] ALU_FunSel,
    output [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel,
    output [2:0] ARF_RegSel,
    output IR_LH, IR_Enable,
    output [1:0] IR_Funsel,
    output Mem_WR, Mem_CS,
    output [1:0] MuxASel, MuxBSel,
    output MuxCSel
    );
    reg [3:0] SC;
    reg [15:0] D, T;
    reg I, TYP_SRC1, TYP_SRC2;
    reg [0:3] DEC_DEST;
    wire [2:0] RF_SRCSEL;
    wire [1:0] ARF_SRCSEL;
    wire SC_Reset;
    always @ (posedge Clock) begin
        if (~Reset) begin
            if (SC_Reset | SC === 4'bx)
                SC <= 4'd0;
            else
                SC <= SC + 1;
        end
    end
    always @ (SC) begin
        T = 16'd0;
        T[SC] = 1;
    end
    always @ (posedge T[2]) begin
        #0.1;
        D = 16'd0;
        D[IROut[15:12]] = 1;
        DEC_DEST = 4'd15;
        DEC_DEST[IROut[9:8]] = 0;
        I = IROut[10];
        TYP_SRC1 = IROut[6];
        TYP_SRC2 = IROut[2];
    end
    assign RF_OutASel = IROut[5:4];
    assign RF_OutBSel = RF_SRCSEL[0] ? IROut[9:8] : (RF_SRCSEL[1] ? IROut[5:4] : IROut[1:0]);
    assign RF_SRCSEL[0] = T[3] & ((D[2] & ~I) | D[12]);
    assign RF_SRCSEL[1] = T[3] & (D[4] | D[5] | D[7] | D[8]) & (TYP_SRC1 & ~TYP_SRC2);
    assign RF_SRCSEL[2] = T[3] & (D[4] | D[5] | D[7] | D[8]) & (TYP_SRC2 & I);
    assign RF_FunSel = Reset ? 2'd3 : (T[4] & D[14] & I) ? 2'd0 : ((T[4] & D[13] & I) ? 2'd1 : 2'd2);
    assign RF_RegSel = Reset ? 4'd0 : (T[3] & D[1] | T[4] & D[11] | T[3] & (D[3] | D[13] | D[14] | D[6] | D[10] | D[9]) & I | T[4] & (D[13] | D[14]) & I | T[3] & (D[4] | D[5] | D[7] | D[8]) & I & (TYP_SRC1 | TYP_SRC2)) ? DEC_DEST : 4'd15;
    always @ (posedge T[3], posedge T[5]) begin
        if ((D[2] & ~I) | D[12])
            ALU_FunSel = 4'd1;
        if (D[3] | D[13] | D[14])
            ALU_FunSel = 4'd0;
        if (D[6])
            ALU_FunSel = 4'd2;
        if (D[10])
            ALU_FunSel = 4'd10;
        if (D[9])
            ALU_FunSel = 4'd11;
        if (D[4])
            ALU_FunSel = 4'd7;
        if (D[5])
            ALU_FunSel = 4'd8;
        if (D[7])
            ALU_FunSel = 4'd4;
        if (D[8])
            ALU_FunSel = 4'd6;
    end
    assign ARF_SRCSEL[0] = (T[3] & (D[3] | D[6] | D[9] | D[10] | D[13] | D[14]) & ~TYP_SRC1) | (T[3] & (D[4] | D[5] | D[7] | D[8]) & ~TYP_SRC1 & TYP_SRC2);
    assign ARF_SRCSEL[1] = (T[3] & (D[4] | D[5] | D[7] | D[8]) & TYP_SRC1 & ~TYP_SRC2);
    assign ARF_OutCSel = ARF_SRCSEL[0] ? IROut[5:4] : IROut[1:0];
    assign ARF_OutDSel = (T[0] | T[1]) ? 2'b00 : ((T[3] & ~I & (D[1] | D[2]) ? 2'b10 : 2'b11));
    assign ARF_FunSel = Reset ? 2'd3 : (T[0] | T[1] | T[3] & D[11] | T[4] & D[13] & ~I) ? 2'b01 : ((T[4] & D[14] & ~I | T[3] & D[12]) ? 2'b00 : 2'b10);
    assign ARF_RegSel = Reset ? 3'd0 : (T[0] | T[1] | (T[3] & ((D[0] & I) | (D[15] & I & ~ALUOutFlag[3])))) ? (3'b011) : (((T[3] & (D[11] | D[12])) ? 3'b110 : ((~I & (((T[3] & (((D[4] | D[5] | D[7] | D[8]) & (TYP_SRC1 | TYP_SRC2)) | D[3] | D[13] | D[14] | D[6] | D[10] | D[9])) | (T[4] & (D[13] | D[14]))))) ? ((IROut[9:8] === 2'd0) ? 3'b011 : DEC_DEST[1:3]) : 3'd7)));
    assign IR_Enable = T[0] | T[1];
    assign IR_Funsel = 2'd2;
    assign IR_LH = T[0];
    assign Mem_WR = T[3] & ((D[2] & ~I) | D[12]);
    assign Mem_CS = ~(T[0] | T[1] | (T[3] & (~I & (D[2] | D[1])) | D[12]) | T[4] & D[11]);
    assign MuxASel = (T[3] & D[1] & I) ? 2'd0 : (((T[3] & D[1] & ~I) | (T[4] & D[11])) ? 2'd1 : 2'd3);
    assign MuxBSel = (T[3] & ((D[0] & I) | (D[15] & I & ~ALUOutFlag[3]))) ? 2'd1 : 2'd3;
    assign MuxCSel = T[3] & TYP_SRC1 & ((D[3] | D[13] | D[14] | D[6] | D[10] | D[9]) | (TYP_SRC2 & (D[4] | D[5] | D[7] | D[8]))) | (T[5] & D[13]) | (T[5] & D[14]) ? 1 : ((T[3] & ~TYP_SRC1 & (D[3] | D[13] | D[14] | D[6] | D[10] | D[9]) | ((T[3] & ((TYP_SRC1 & ~TYP_SRC2) | (~TYP_SRC1 & TYP_SRC2)) & (D[4] | D[5] | D[7] | D[8]);
    assign SC_Reset = (T[4] & (D[11] | D[13] | D[14])) | (T[3] & (D[0] | D[1] | D[2] | D[3] | D[4] | D[5] | D[6] | D[7] | D[8] | D[9] | D[10] | D[12] | D[15]));
endmodule

module CPU(
    input Clock, Reset
    );
    wire [1:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    wire [3:0] RF_RegSel, ALU_FunSel;
    wire [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel;
    wire [2:0] ARF_RegSel;
    wire IR_LH, IR_Enable;
    wire [1:0] IR_Funsel;
    wire Mem_WR, Mem_CS;
    wire [1:0] MuxASel, MuxBSel;
    wire MuxCSel;
    wire [3:0] ALUOutFlag;
    wire [15:0] IROut;
    ALUSystem _ALUSystem(
        .RF_OutASel(RF_OutASel), 
        .RF_OutBSel(RF_OutBSel), 
        .RF_FunSel(RF_FunSel),
        .RF_RegSel(RF_RegSel),
        .ALU_FunSel(ALU_FunSel),
        .ARF_OutCSel(ARF_OutCSel), 
        .ARF_OutDSel(ARF_OutDSel), 
        .ARF_FunSel(ARF_FunSel),
        .ARF_RegSel(ARF_RegSel),
        .IR_LH(IR_LH),
        .IR_Enable(IR_Enable),
        .IR_Funsel(IR_Funsel),
        .Mem_WR(Mem_WR),
        .Mem_CS(Mem_CS),
        .MuxASel(MuxASel),
        .MuxBSel(MuxBSel),
        .MuxCSel(MuxCSel),
        .Clock(Clock),
        .IROut(IROut),
        .ALUOutFlag(ALUOutFlag)
        );
    ControlUnit CU (Clock, Reset, ALUOutFlag, IROut, RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, ALU_FunSel,
        ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel);
endmodule
*/