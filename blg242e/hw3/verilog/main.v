`timescale 1ns / 1ps

// Furkan SALIK - 150200056

module CharDecoder(
    input [7:0] char,
    output [25:0] decodedChar
    );
    wire [7:0] charAlphabeticalIndex = char - 8'd65;
    reg [25:0] tempDecodedChar = 26'd0;
    always @* begin
        tempDecodedChar = 26'd0;  // First, reset current decoded state
        tempDecodedChar[charAlphabeticalIndex] = 1'b1;
    end
    
    assign decodedChar = tempDecodedChar;
endmodule

module CharEncoder(
    input [25:0] decodedChar,
    output [7:0] char
    );
    reg [7:0] decodedIndex;
    integer i;
    always @ (decodedChar) begin
        for(i = 0; i < 26; i = i + 1) begin
            if(decodedChar[i] == 1'b1) begin
                decodedIndex = i;
            end
        end
    end    
    assign char = 8'd65 + decodedIndex;
endmodule

module CircularRightShift(
    input [25:0] data,
    input [4:0] shiftAmount,
    output reg [25:0] out
    );
    reg lastDigit;  // Last digit in the last (shifted) data
        
    integer i;
    always @ (data, shiftAmount) begin
        out = data;
        lastDigit = out[0];
        for(i = 5'd0; i < shiftAmount; i = i + 5'd1) begin
            out = {lastDigit, out[25:1]};
            lastDigit = out[0];
        end
    end
endmodule

module CircularLeftShift(
    input [25:0] data,
    input [4:0] shiftAmount,
    output reg [25:0] out
    );
    reg lastDigit;  // Last digit in the last (shifted) data
        
    integer i;
    always @ (data, shiftAmount) begin
        out = data;
        lastDigit = out[25];
        for(i = 5'd0; i < shiftAmount; i = i + 5'd1) begin
            out = {out[24:0], lastDigit};
            lastDigit = out[25];
        end
    end
endmodule

module CaesarEncryption(
    input [7:0] plainChar,
    input [4:0] shiftCount,
    output reg [7:0] chipherChar
    );
        
    wire [25:0] decodedChar;
    CharDecoder CD1(plainChar, decodedChar);
    
    wire [25:0] shiftedData;
    CircularLeftShift CRS1(decodedChar, shiftCount, shiftedData);
    
    wire [7:0] tempOutput;
    CharEncoder CE1(shiftedData, tempOutput);
    always @ (tempOutput) begin
        chipherChar = tempOutput;
    end
endmodule

module CaesarDecryption(
    input [7:0] chipherChar,
    input [4:0] shiftCount,
    output reg [7:0] decryptedChar
    );
    
    wire [25:0] decodedChar;
    CharDecoder CD1(chipherChar, decodedChar);
    
    wire [25:0] shiftedData;
    CircularRightShift CLS1(decodedChar, shiftCount, shiftedData);
    
    wire [7:0] tempOutput;
    CharEncoder CE1(shiftedData, tempOutput);
    always @ (tempOutput) begin
        decryptedChar = tempOutput;
    end
endmodule

module CaesarEnvironment(
    input [7:0] plainChar,
    input [4:0] shiftCount,
    output [7:0] chipherChar,
    output reg [7:0] decryptedChar
    );
    CaesarEncryption CE1(plainChar, shiftCount, chipherChar);
    
    wire [7:0] tempDecryptedChar;
    CaesarDecryption CD1(chipherChar, shiftCount, tempDecryptedChar);
    
    always @ (tempDecryptedChar) begin
        decryptedChar = tempDecryptedChar;
    end
endmodule

module VigenereEncryption(
    input [7:0] plainChar,
    input [0:79] keyInput,
    input load,
    input clock,
    output [7:0] chipherChar
    );
    reg [0:79] keyRegister;
    always @ (posedge load) begin
        keyRegister = keyInput;
    end
    always @ (posedge clock) begin
        if(!load) begin
            keyRegister = {keyRegister[8:79], keyRegister[0:7]};
        end
    end
    
    wire [7:0] plainCharIndex;
    assign plainCharIndex = plainChar - 8'd65;
    
    wire [7:0] keyInputIndex;
    assign keyInputIndex = keyRegister[0:7] - 8'd65;
    
    assign chipherChar = 8'd65 + ((plainCharIndex + keyInputIndex) % 26);
endmodule

module VigenereDecryption(
    input [7:0] chipherChar,
    input [0:79] keyInput,
    input load,
    input clock,
    output reg [7:0] decryptedChar
    );
    reg [0:79] keyRegister;

    always @ (posedge load) begin
        keyRegister = keyInput;
    end
    always @ (posedge clock) begin
        if(!load) begin
            keyRegister = {keyRegister[8:79], keyRegister[0:7]};
        end
    end
    
    reg [7:0] difference;
    always@ (chipherChar, keyRegister) begin
        difference = (chipherChar)-(keyRegister[0:7]);
        if(difference[7] == 1'b1) begin // If the difference is negative
            decryptedChar = difference + 8'd26 + 8'd65;  // Add 26 to the difference, this is done because negative operands in modulo causes problems
        end else begin
            decryptedChar = (difference % 26) + 8'd65;
        end
    end
endmodule

module VigenereEnvironment(
    input [7:0] plainChar,
    input [0:79] keyInput,
    input load,
    input clock,
    output [7:0] chipherChar,
    output [7:0] decryptedChar
    );
    VigenereEncryption VE1(plainChar, keyInput, load, clock, chipherChar);
        
    VigenereDecryption VD1(chipherChar, keyInput, load, clock, decryptedChar);
endmodule

module PlugBoard(
    input [25:0] charInput,
    input [25:0] backwardInput,
    output [25:0] forwardOutput,
    output [25:0] backwardOutput
    );
    assign forwardOutput[0] = charInput[4];    assign backwardOutput[4] = backwardInput[0];
    assign forwardOutput[1] = charInput[10];    assign backwardOutput[10] = backwardInput[1];
    assign forwardOutput[2] = charInput[12];    assign backwardOutput[12] = backwardInput[2];
    assign forwardOutput[3] = charInput[5];    assign backwardOutput[5] = backwardInput[3];
    assign forwardOutput[4] = charInput[11];    assign backwardOutput[11] = backwardInput[4];
    assign forwardOutput[5] = charInput[6];    assign backwardOutput[6] = backwardInput[5];
    assign forwardOutput[6] = charInput[3];    assign backwardOutput[3] = backwardInput[6];
    assign forwardOutput[7] = charInput[16];    assign backwardOutput[16] = backwardInput[7];
    assign forwardOutput[8] = charInput[21];    assign backwardOutput[21] = backwardInput[8];
    assign forwardOutput[9] = charInput[25];    assign backwardOutput[25] = backwardInput[9];
    assign forwardOutput[10] = charInput[13];    assign backwardOutput[13] = backwardInput[10];
    assign forwardOutput[11] = charInput[19];    assign backwardOutput[19] = backwardInput[11];
    assign forwardOutput[12] = charInput[14];    assign backwardOutput[14] = backwardInput[12];
    assign forwardOutput[13] = charInput[22];    assign backwardOutput[22] = backwardInput[13];
    assign forwardOutput[14] = charInput[24];    assign backwardOutput[24] = backwardInput[14];
    assign forwardOutput[15] = charInput[7];    assign backwardOutput[7] = backwardInput[15];
    assign forwardOutput[16] = charInput[23];    assign backwardOutput[23] = backwardInput[16];
    assign forwardOutput[17] = charInput[20];    assign backwardOutput[20] = backwardInput[17];
    assign forwardOutput[18] = charInput[18];    assign backwardOutput[18] = backwardInput[18];
    assign forwardOutput[19] = charInput[15];    assign backwardOutput[15] = backwardInput[19];
    assign forwardOutput[20] = charInput[0];    assign backwardOutput[0] = backwardInput[20];
    assign forwardOutput[21] = charInput[8];    assign backwardOutput[8] = backwardInput[21];
    assign forwardOutput[22] = charInput[1];    assign backwardOutput[1] = backwardInput[22];
    assign forwardOutput[23] = charInput[17];    assign backwardOutput[17] = backwardInput[23];
    assign forwardOutput[24] = charInput[2];    assign backwardOutput[2] = backwardInput[24];
    assign forwardOutput[25] = charInput[9];    assign backwardOutput[9] = backwardInput[25];
endmodule

module Rotor1(
    input [25:0] forwardInput,
    input [25:0] backwardInput,
    input [4:0] startPosition,
    input load,
    input clockIn,
    output reg clockOut,
    output [25:0] forwardOutput,
    output [25:0] backwardOutput
    );
    reg [4:0] shiftAmount;
    initial begin
        if(load) begin
            shiftAmount = startPosition;
        end
        else begin
            shiftAmount = 5'd0;
        end
    end
    
    always @ (posedge load) begin
        shiftAmount = startPosition;
    end
    
    always @ (posedge clockIn) begin
        if(!load) begin
            if(shiftAmount < 5'd25) begin
                shiftAmount = shiftAmount + 1;
            end
            else begin
                shiftAmount = 5'd0;
                clockOut = 1; #0.1; clockOut = 0;
            end
        end
    end
    
    wire [25:0] shiftedCharInput;
    CircularRightShift CRS1(forwardInput, shiftAmount, shiftedCharInput);
    
    wire [25:0] shiftedBackwardInput;
    CircularRightShift CRS2(backwardInput, shiftAmount, shiftedBackwardInput);
    
    wire [25:0] intermediateForwardOutput;
    wire [25:0] intermediateBackwardOutput;
                
    assign intermediateForwardOutput[0] = shiftedCharInput[7];    assign intermediateBackwardOutput[7] =   shiftedBackwardInput[0];
    assign intermediateForwardOutput[1] = shiftedCharInput[12];    assign intermediateBackwardOutput[12] = shiftedBackwardInput[1];
    assign intermediateForwardOutput[2] = shiftedCharInput[21];    assign intermediateBackwardOutput[21] = shiftedBackwardInput[2];
    assign intermediateForwardOutput[3] = shiftedCharInput[17];    assign intermediateBackwardOutput[17] =   shiftedBackwardInput[3];
    assign intermediateForwardOutput[4] = shiftedCharInput[0];    assign intermediateBackwardOutput[0] = shiftedBackwardInput[4];
    assign intermediateForwardOutput[5] = shiftedCharInput[2];    assign intermediateBackwardOutput[2] =   shiftedBackwardInput[5];
    assign intermediateForwardOutput[6] = shiftedCharInput[22];    assign intermediateBackwardOutput[22] =   shiftedBackwardInput[6];
    assign intermediateForwardOutput[7] = shiftedCharInput[20];    assign intermediateBackwardOutput[20] = shiftedBackwardInput[7];
    assign intermediateForwardOutput[8] = shiftedCharInput[23];    assign intermediateBackwardOutput[23] = shiftedBackwardInput[8];
    assign intermediateForwardOutput[9] = shiftedCharInput[18];    assign intermediateBackwardOutput[18] = shiftedBackwardInput[9];
    assign intermediateForwardOutput[10] =shiftedCharInput[9];    assign intermediateBackwardOutput[9] = shiftedBackwardInput[10];
    assign intermediateForwardOutput[11] =shiftedCharInput[25];    assign intermediateBackwardOutput[25] = shiftedBackwardInput[11];
    assign intermediateForwardOutput[12] =shiftedCharInput[15];    assign intermediateBackwardOutput[15] = shiftedBackwardInput[12];
    assign intermediateForwardOutput[13] =shiftedCharInput[3];    assign intermediateBackwardOutput[3] = shiftedBackwardInput[13];
    assign intermediateForwardOutput[14] =shiftedCharInput[14];    assign intermediateBackwardOutput[14] = shiftedBackwardInput[14];
    assign intermediateForwardOutput[15] =shiftedCharInput[13];    assign intermediateBackwardOutput[13] =   shiftedBackwardInput[15];
    assign intermediateForwardOutput[16] =shiftedCharInput[11];    assign intermediateBackwardOutput[11] = shiftedBackwardInput[16];
    assign intermediateForwardOutput[17] =shiftedCharInput[8];    assign intermediateBackwardOutput[8] = shiftedBackwardInput[17];
    assign intermediateForwardOutput[18] =shiftedCharInput[4];    assign intermediateBackwardOutput[4] = shiftedBackwardInput[18];
    assign intermediateForwardOutput[19] =shiftedCharInput[10];    assign intermediateBackwardOutput[10] = shiftedBackwardInput[19];
    assign intermediateForwardOutput[20] =shiftedCharInput[6];    assign intermediateBackwardOutput[6] =   shiftedBackwardInput[20];
    assign intermediateForwardOutput[21] =shiftedCharInput[5];    assign intermediateBackwardOutput[5] =   shiftedBackwardInput[21];
    assign intermediateForwardOutput[22] =shiftedCharInput[19];    assign intermediateBackwardOutput[19] =   shiftedBackwardInput[22];
    assign intermediateForwardOutput[23] =shiftedCharInput[16];    assign intermediateBackwardOutput[16] = shiftedBackwardInput[23];
    assign intermediateForwardOutput[24] =shiftedCharInput[24];    assign intermediateBackwardOutput[24] =   shiftedBackwardInput[24];
    assign intermediateForwardOutput[25] =shiftedCharInput[1];    assign intermediateBackwardOutput[1] =   shiftedBackwardInput[25];
    
    wire [25:0] shiftedForwardOutput;
    CircularLeftShift CLS1(intermediateForwardOutput, shiftAmount, shiftedForwardOutput);
    
    wire [25:0] shiftedBackwardOutput;
    CircularLeftShift CLS2(intermediateBackwardOutput, shiftAmount, shiftedBackwardOutput);
    
    assign forwardOutput = shiftedForwardOutput;
    assign backwardOutput = shiftedBackwardOutput;
endmodule

module Rotor2(
    input [25:0] forwardInput,
    input [25:0] backwardInput,
    input [4:0] startPosition,
    input load,
    input clockIn,
    output reg clockOut,
    output [25:0] forwardOutput,
    output [25:0] backwardOutput
    );
    reg [4:0] shiftAmount;
    initial begin
        if(load) begin
            shiftAmount = startPosition;
        end
        else begin
            shiftAmount = 5'd0;
        end
    end
    
    always @ (posedge load) begin
        shiftAmount = startPosition;
    end
    
    always @ (posedge clockIn) begin
        if(!load) begin
            if(shiftAmount < 5'd25) begin
                shiftAmount = shiftAmount + 1;
            end
            else begin
                shiftAmount = 5'd0;
                clockOut = 1; #1; clockOut = 0;
            end
        end
    end
    
    wire [25:0] shiftedCharInput;
    CircularRightShift CRS1(forwardInput, shiftAmount, shiftedCharInput);
    
    wire [25:0] shiftedBackwardInput;
    CircularRightShift CRS2(backwardInput, shiftAmount, shiftedBackwardInput);
    
    wire [25:0] intermediateForwardOutput;
    wire [25:0] intermediateBackwardOutput;
    
    assign intermediateForwardOutput[0] = shiftedCharInput[19];    assign intermediateBackwardOutput[19] =   shiftedBackwardInput[0];
    assign intermediateForwardOutput[1] = shiftedCharInput[4];    assign intermediateBackwardOutput[4] = shiftedBackwardInput[1];
    assign intermediateForwardOutput[2] = shiftedCharInput[7];    assign intermediateBackwardOutput[7] = shiftedBackwardInput[2];
    assign intermediateForwardOutput[3] = shiftedCharInput[6];    assign intermediateBackwardOutput[6] =   shiftedBackwardInput[3];
    assign intermediateForwardOutput[4] = shiftedCharInput[12];    assign intermediateBackwardOutput[12] = shiftedBackwardInput[4];
    assign intermediateForwardOutput[5] = shiftedCharInput[17];    assign intermediateBackwardOutput[17] =   shiftedBackwardInput[5];
    assign intermediateForwardOutput[6] = shiftedCharInput[8];    assign intermediateBackwardOutput[8] =   shiftedBackwardInput[6];
    assign intermediateForwardOutput[7] = shiftedCharInput[5];    assign intermediateBackwardOutput[5] = shiftedBackwardInput[7];
    assign intermediateForwardOutput[8] = shiftedCharInput[2];    assign intermediateBackwardOutput[2] = shiftedBackwardInput[8];
    assign intermediateForwardOutput[9] = shiftedCharInput[0];    assign intermediateBackwardOutput[0] = shiftedBackwardInput[9];
    assign intermediateForwardOutput[10] =shiftedCharInput[1];    assign intermediateBackwardOutput[1] = shiftedBackwardInput[10];
    assign intermediateForwardOutput[11] =shiftedCharInput[20];    assign intermediateBackwardOutput[20] = shiftedBackwardInput[11];
    assign intermediateForwardOutput[12] =shiftedCharInput[25];    assign intermediateBackwardOutput[25] = shiftedBackwardInput[12];
    assign intermediateForwardOutput[13] =shiftedCharInput[9];    assign intermediateBackwardOutput[9] = shiftedBackwardInput[13];
    assign intermediateForwardOutput[14] =shiftedCharInput[14];    assign intermediateBackwardOutput[14] = shiftedBackwardInput[14];
    assign intermediateForwardOutput[15] =shiftedCharInput[22];    assign intermediateBackwardOutput[22] =   shiftedBackwardInput[15];
    assign intermediateForwardOutput[16] =shiftedCharInput[24];    assign intermediateBackwardOutput[24] = shiftedBackwardInput[16];
    assign intermediateForwardOutput[17] =shiftedCharInput[18];    assign intermediateBackwardOutput[18] = shiftedBackwardInput[17];
    assign intermediateForwardOutput[18] =shiftedCharInput[15];    assign intermediateBackwardOutput[15] = shiftedBackwardInput[18];
    assign intermediateForwardOutput[19] =shiftedCharInput[13];    assign intermediateBackwardOutput[13] = shiftedBackwardInput[19];
    assign intermediateForwardOutput[20] =shiftedCharInput[3];    assign intermediateBackwardOutput[3] =   shiftedBackwardInput[20];
    assign intermediateForwardOutput[21] =shiftedCharInput[10];    assign intermediateBackwardOutput[10] =   shiftedBackwardInput[21];
    assign intermediateForwardOutput[22] =shiftedCharInput[21];    assign intermediateBackwardOutput[21] =   shiftedBackwardInput[22];
    assign intermediateForwardOutput[23] =shiftedCharInput[16];    assign intermediateBackwardOutput[16] = shiftedBackwardInput[23];
    assign intermediateForwardOutput[24] =shiftedCharInput[11];    assign intermediateBackwardOutput[11] =   shiftedBackwardInput[24];
    assign intermediateForwardOutput[25] =shiftedCharInput[23];    assign intermediateBackwardOutput[23] =   shiftedBackwardInput[25];
    
    wire [25:0] shiftedForwardOutput;
    CircularLeftShift CLS1(intermediateForwardOutput, shiftAmount, shiftedForwardOutput);
    
    wire [25:0] shiftedBackwardOutput;
    CircularLeftShift CLS2(intermediateBackwardOutput, shiftAmount, shiftedBackwardOutput);
    
    assign forwardOutput = shiftedForwardOutput;
    assign backwardOutput = shiftedBackwardOutput;
endmodule

module Rotor3(
    input [25:0] forwardInput,
    input [25:0] backwardInput,
    input [4:0] startPosition,
    input load,
    input clockIn,
    output [25:0] forwardOutput,
    output [25:0] backwardOutput
    );
    reg [4:0] shiftAmount;
    initial begin
        if(load) begin
            shiftAmount = startPosition;
        end
        else begin
            shiftAmount = 5'd0;
        end
    end
    
    always @ (posedge load) begin
        shiftAmount = startPosition;
    end
    
    always @ (posedge clockIn) begin
        if(!load) begin
            if(shiftAmount < 5'd25) begin
                shiftAmount = shiftAmount + 1;
            end
            else begin
                shiftAmount = 5'd0;
            end
        end
    end
    
    wire [25:0] shiftedCharInput;
    CircularRightShift CRS1(forwardInput, shiftAmount, shiftedCharInput);
    
    wire [25:0] shiftedBackwardInput;
    CircularRightShift CRS2(backwardInput, shiftAmount, shiftedBackwardInput);
    
    wire [25:0] intermediateForwardOutput;
    wire [25:0] intermediateBackwardOutput;
    
    assign intermediateForwardOutput[0] = shiftedCharInput[19];    assign intermediateBackwardOutput[19] =   shiftedBackwardInput[0];
    assign intermediateForwardOutput[1] = shiftedCharInput[0];    assign intermediateBackwardOutput[0] = shiftedBackwardInput[1];
    assign intermediateForwardOutput[2] = shiftedCharInput[6];    assign intermediateBackwardOutput[6] = shiftedBackwardInput[2];
    assign intermediateForwardOutput[3] = shiftedCharInput[1];    assign intermediateBackwardOutput[1] =   shiftedBackwardInput[3];
    assign intermediateForwardOutput[4] = shiftedCharInput[15];    assign intermediateBackwardOutput[15] = shiftedBackwardInput[4];
    assign intermediateForwardOutput[5] = shiftedCharInput[2];    assign intermediateBackwardOutput[2] =   shiftedBackwardInput[5];
    assign intermediateForwardOutput[6] = shiftedCharInput[18];    assign intermediateBackwardOutput[18] =   shiftedBackwardInput[6];
    assign intermediateForwardOutput[7] = shiftedCharInput[3];    assign intermediateBackwardOutput[3] = shiftedBackwardInput[7];
    assign intermediateForwardOutput[8] = shiftedCharInput[16];    assign intermediateBackwardOutput[16] = shiftedBackwardInput[8];
    assign intermediateForwardOutput[9] = shiftedCharInput[4];    assign intermediateBackwardOutput[4] = shiftedBackwardInput[9];
    assign intermediateForwardOutput[10] =shiftedCharInput[20];    assign intermediateBackwardOutput[20] = shiftedBackwardInput[10];
    assign intermediateForwardOutput[11] =shiftedCharInput[5];    assign intermediateBackwardOutput[5] = shiftedBackwardInput[11];
    assign intermediateForwardOutput[12] =shiftedCharInput[21];    assign intermediateBackwardOutput[21] = shiftedBackwardInput[12];
    assign intermediateForwardOutput[13] =shiftedCharInput[13];    assign intermediateBackwardOutput[13] = shiftedBackwardInput[13];
    assign intermediateForwardOutput[14] =shiftedCharInput[25];    assign intermediateBackwardOutput[25] = shiftedBackwardInput[14];
    assign intermediateForwardOutput[15] =shiftedCharInput[7];    assign intermediateBackwardOutput[7] =   shiftedBackwardInput[15];
    assign intermediateForwardOutput[16] =shiftedCharInput[24];    assign intermediateBackwardOutput[24] = shiftedBackwardInput[16];
    assign intermediateForwardOutput[17] =shiftedCharInput[8];    assign intermediateBackwardOutput[8] = shiftedBackwardInput[17];
    assign intermediateForwardOutput[18] =shiftedCharInput[23];    assign intermediateBackwardOutput[23] = shiftedBackwardInput[18];
    assign intermediateForwardOutput[19] =shiftedCharInput[9];    assign intermediateBackwardOutput[9] = shiftedBackwardInput[19];
    assign intermediateForwardOutput[20] =shiftedCharInput[22];    assign intermediateBackwardOutput[22] =   shiftedBackwardInput[20];
    assign intermediateForwardOutput[21] =shiftedCharInput[11];    assign intermediateBackwardOutput[11] =   shiftedBackwardInput[21];
    assign intermediateForwardOutput[22] =shiftedCharInput[17];    assign intermediateBackwardOutput[17] =   shiftedBackwardInput[22];
    assign intermediateForwardOutput[23] =shiftedCharInput[10];    assign intermediateBackwardOutput[10] = shiftedBackwardInput[23];
    assign intermediateForwardOutput[24] =shiftedCharInput[14];    assign intermediateBackwardOutput[14] =   shiftedBackwardInput[24];
    assign intermediateForwardOutput[25] =shiftedCharInput[12];    assign intermediateBackwardOutput[12] =   shiftedBackwardInput[25];
    
    wire [25:0] shiftedForwardOutput;
    CircularLeftShift CLS1(intermediateForwardOutput, shiftAmount, shiftedForwardOutput);
    
    wire [25:0] shiftedBackwardOutput;
    CircularLeftShift CLS2(intermediateBackwardOutput, shiftAmount, shiftedBackwardOutput);
    
    assign forwardOutput = shiftedForwardOutput;
    assign backwardOutput = shiftedBackwardOutput;
endmodule

module Reflector(
    input [25:0] inputConnection,
    output [25:0] outputConnection
    );                    
    assign outputConnection[0] = inputConnection[24];
    assign outputConnection[1] = inputConnection[17];
    assign outputConnection[2] = inputConnection[20];
    assign outputConnection[3] = inputConnection[7];
    assign outputConnection[4] = inputConnection[16];
    assign outputConnection[5] = inputConnection[18];
    assign outputConnection[6] = inputConnection[11];
    assign outputConnection[7] = inputConnection[3];
    assign outputConnection[8] = inputConnection[15];
    assign outputConnection[9] = inputConnection[23];
    assign outputConnection[10] =inputConnection[13];
    assign outputConnection[11] =inputConnection[6];
    assign outputConnection[12] =inputConnection[14];
    assign outputConnection[13] =inputConnection[10];
    assign outputConnection[14] =inputConnection[12];
    assign outputConnection[15] =inputConnection[8];
    assign outputConnection[16] =inputConnection[4];
    assign outputConnection[17] =inputConnection[1];
    assign outputConnection[18] =inputConnection[5];
    assign outputConnection[19] =inputConnection[25];
    assign outputConnection[20] =inputConnection[2];
    assign outputConnection[21] =inputConnection[22];
    assign outputConnection[22] =inputConnection[21];
    assign outputConnection[23] =inputConnection[9];
    assign outputConnection[24] =inputConnection[0];
    assign outputConnection[25] =inputConnection[19];
endmodule

module EnigmaMachine(
    input [7:0] char,
    input [4:0] startPosition1,
    input [4:0] startPosition2,
    input [4:0] startPosition3,
    input load,
    input clock,
    output [7:0] outChar
    );
    wire [25:0] decodedChar;
    
    wire [25:0] plugBoardForwardOutput;
    wire [25:0] plugBoardBackwardOutputDecoded;
    
    wire rotor1ClockOut;
    wire [25:0] rotor1ForwardOutput;
    wire [25:0] rotor1BackwardOutput;
    
    wire rotor2ClockOut;
    wire [25:0] rotor2ForwardOutput;
    wire [25:0] rotor2BackwardOutput;
    
    wire [25:0] rotor3ForwardOutput;
    wire [25:0] rotor3BackwardOutput;
    
    wire [25:0] reflectorOutput;
    
    CharDecoder CD1(char, decodedChar);
    PlugBoard PB(decodedChar, rotor1BackwardOutput, plugBoardForwardOutput, plugBoardBackwardOutputDecoded);
    Rotor1 R1(plugBoardForwardOutput, rotor2BackwardOutput, startPosition1, load, clock, rotor1ClockOut, rotor1ForwardOutput, rotor1BackwardOutput);
    Rotor2 R2(rotor1ForwardOutput, rotor3BackwardOutput, startPosition2, load, rotor1ClockOut, rotor2ClockOut, rotor2ForwardOutput, rotor2BackwardOutput);
    Rotor3 R3(rotor2ForwardOutput, reflectorOutput, startPosition3, load, rotor2ClockOut, rotor3ForwardOutput, rotor3BackwardOutput);
    Reflector RFL(rotor3ForwardOutput, reflectorOutput);
    
    CharEncoder CE(plugBoardBackwardOutputDecoded, outChar);
    
    always@* begin
        $display("char:%d", char);
        $display("decodedChar:%b", decodedChar);
        $display("plugBoardForwardOutput:%b", plugBoardForwardOutput);
        $display("rotor1ForwardOutput:%b", rotor1ForwardOutput);
        $display("rotor2ForwardOutput:%b", rotor2ForwardOutput);
        $display("rotor3ForwardOutput:%b", rotor3ForwardOutput);
        $display("reflectorOutput:%b", reflectorOutput);
        $display("rotor3BackwardOutput:%b", rotor3BackwardOutput);
        $display("rotor2BackwardOutput:%b", rotor2BackwardOutput);
        $display("rotor1BackwardOutput:%b", rotor1BackwardOutput);
        $display("plugBoardBackwardOutputDecoded:%b", plugBoardBackwardOutputDecoded);
        $display("outChar:%d", outChar);
    end
endmodule

module EnigmaCommunication(
    input [7:0] plainChar,
    input [4:0] startPosition1,
    input [4:0] startPosition2,
    input [4:0] startPosition3,
    input load,
    input clock,
    output [7:0] chipherChar,
    output [7:0] decryptedChar
    );
    EnigmaMachine EM1(plainChar, startPosition1, startPosition2, startPosition3, load, clock, chipherChar);
    EnigmaMachine EM2(chipherChar, startPosition1, startPosition2, startPosition3, load, clock, decryptedChar);
endmodule