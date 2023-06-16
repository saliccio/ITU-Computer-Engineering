`timescale 1ns / 1ps

// Furkan SALIK - 150200056

module CharDecoder_test();
    reg [7:0] char;
    wire [25:0] decodedChar;
    CharDecoder uut(char, decodedChar);
    
    initial begin
        char <= 8'd65; #5;
        char <= 8'd84; #5;
        char <= 8'd90;
    end
endmodule

module CharEncoder_test();
    reg [25:0] decodedChar;
    wire [7:0] char;
    CharEncoder uut(decodedChar, char);
    
    initial begin
        decodedChar <= 26'h0000001; #5;
        decodedChar <= 26'h0080000; #5;
        decodedChar <= 26'h2000000;
    end
endmodule

module CircularRightShift_test();
    reg [25:0] data;
    reg [4:0] shiftAmount;
    wire [25:0] out;
    CircularRightShift uut(data, shiftAmount, out);
    
    initial begin
        data <= 26'd1; shiftAmount <= 5'd1; #5;
        data <= 26'd1; shiftAmount <= 5'd10; #5;
        data <= 26'd1; shiftAmount <= 5'd31; #5;
        
        data <= 26'd10; shiftAmount <= 5'd1; #5;
        data <= 26'd10; shiftAmount <= 5'd10; #5;
        data <= 26'd10; shiftAmount <= 5'd31;
    end
endmodule

module CircularLeftShift_test();
    reg [25:0] data;
    reg [4:0] shiftAmount;
    wire [25:0] out;
    CircularLeftShift uut(data, shiftAmount, out);
    
    initial begin
        data <= 26'd1; shiftAmount <= 5'd1; #5;
        data <= 26'd1; shiftAmount <= 5'd10; #5;
        data <= 26'd1; shiftAmount <= 5'd31; #5;
        
        data <= 26'd10; shiftAmount <= 5'd1; #5;
        data <= 26'd10; shiftAmount <= 5'd10; #5;
        data <= 26'd10; shiftAmount <= 5'd31;
    end
endmodule

module CaesarEncryption_test();
    reg [7:0] plainChar;
    reg [4:0] shiftCount;
    wire [7:0] chipherChar;
    CaesarEncryption uut(plainChar, shiftCount, chipherChar);
    
    initial begin
        plainChar <= 8'd65; shiftCount <= 5'd3; #5;
    end
endmodule

module CaesarDecryption_test();
    reg [7:0] chipherChar;
    reg [4:0] shiftCount;
    wire [7:0] decryptedChar;
    CaesarDecryption uut(chipherChar, shiftCount, decryptedChar);
    
    initial begin
        chipherChar <= "A"; shiftCount <= 5'd3; #5;
    end
endmodule

module CaesarEnvironment_test();
    reg [7:0] plainChar;
    reg [4:0] shiftCount;
    wire [7:0] chipherChar;
    wire [7:0] decryptedChar;
    CaesarEnvironment uut(plainChar, shiftCount, chipherChar, decryptedChar);
    
    initial begin
        plainChar <= 8'd65; shiftCount <= 5'd3; #5;
    end
endmodule

module VigenereEncryption_test();
    reg [7:0] plainChar;
    reg [79:0] keyInput;
    reg load;
    reg clock;
    wire [7:0] chipherChar;
    VigenereEncryption uut(plainChar, keyInput, load, clock, chipherChar);
    
    initial begin
        keyInput <= "KADIROZLEM"; #5; load <= 1; #1; load <= 0; #5;
        plainChar <= "I"; #5;
        plainChar <= "S"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "T"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "A"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "N"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "B"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "U"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "L"; clock <= 1; #1; clock <= 0; #5;
    end
endmodule

module VigenereDecryption_test();
    reg [7:0] chipherChar;
    reg [79:0] keyInput;
    reg load;
    reg clock;
    wire [7:0] decryptedChar;
    VigenereDecryption uut(chipherChar, keyInput, load, clock, decryptedChar);
    
    initial begin
        keyInput = "KADIROZLEM"; #1;   load = 1; #1; load = 0; #5;
        chipherChar = "S"; #5;
        chipherChar = "S"; clock = 1; #1; clock = 0; #5;
        chipherChar = "W"; clock = 1; #1; clock = 0; #5;
        chipherChar = "I"; clock = 1; #1; clock = 0; #5;
        chipherChar = "E"; clock = 1; #1; clock = 0; #5;
        chipherChar = "P"; clock = 1; #1; clock = 0; #5;
        chipherChar = "T"; clock = 1; #1; clock = 0; #5;
        chipherChar = "W"; clock = 1; #1; clock = 0; #5;
    end
endmodule

module VigenereEnvironment_test();
    reg [7:0] plainChar;
    reg [79:0] keyInput;
    reg load;
    reg clock;
    wire [7:0] chipherChar;
    wire [7:0] decryptedChar;
    VigenereEnvironment uut(plainChar, keyInput, load, clock, chipherChar, decryptedChar);
    
    initial begin
        plainChar <= "I"; #1; keyInput <= "KADIROZLEM"; #5;
        load <= 1; #1; load <= 0; #5; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "S"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "T"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "A"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "N"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "B"; clock <= 1; #1; clock <= 0; #5;
        plainChar <= "U"; clock <= 1; #1; clock <= 0; #5;
    end
endmodule

module PlugBoard_test();
    reg [25:0] charInput;
    reg [25:0] backwardInput;
    wire [25:0] forwardOutput;
    wire [25:0] backwardOutput;
    PlugBoard uut(charInput, backwardInput, forwardOutput, backwardOutput);
    
    initial begin
        charInput <= 26'd1; backwardInput <= 26'd2;
    end
endmodule

module Rotor1_test();
    reg [25:0] forwardInput;
    reg [25:0] backwardInput;
    reg [4:0] startPosition;
    reg load;
    reg clockIn;
    wire clockOut;
    wire [25:0] forwardOutput;
    wire [25:0] backwardOutput;
    Rotor1 uut(forwardInput, backwardInput, startPosition, load, clockIn, clockOut, forwardOutput, backwardOutput);
    
    initial begin
        forwardInput <= 26'b00000000000000000000000001; backwardInput <= 26'h8; startPosition <= 5'b01100; load <= 1; clockIn <= 1; #5;
        load <= 0; clockIn <= 0;
    end
endmodule

module Rotor2_test();
    reg [25:0] forwardInput;
    reg [25:0] backwardInput;
    reg [4:0] startPosition;
    reg load;
    reg clockIn;
    wire clockOut;
    wire [25:0] forwardOutput;
    wire [25:0] backwardOutput;
    Rotor2 uut(forwardInput, backwardInput, startPosition, load, clockIn, clockOut, forwardOutput, backwardOutput);
    
    initial begin
        forwardInput <= 26'b00000000000000000000000001; backwardInput <= 26'h8; startPosition <= 5'd0; load <= 1; clockIn <= 0; #5;
        load <= 0; clockIn <= 0;
    end
endmodule

module Rotor3_test();
    reg [25:0] forwardInput;
    reg [25:0] backwardInput;
    reg [4:0] startPosition;
    reg load;
    reg clockIn;
    wire [25:0] forwardOutput;
    wire [25:0] backwardOutput;
    Rotor3 uut(forwardInput, backwardInput, startPosition, load, clockIn, forwardOutput, backwardOutput);
    
    initial begin
        forwardInput <= 26'b00000000000000000000000001; backwardInput <= 26'h8; startPosition <= 5'd0; load <= 1; clockIn <= 0; #5;
        load <= 0; clockIn <= 0;
    end
endmodule

module Reflector_test();
    reg [25:0] inputConnection;
    wire [25:0] outputConnection;
    Reflector uut(inputConnection, outputConnection);
    
    initial begin
        inputConnection <= 26'd1; #5;
    end
endmodule

module EnigmaMachine_test();
    reg [7:0] char;
    reg [4:0] startPosition1;
    reg [4:0] startPosition2;
    reg [4:0] startPosition3;
    reg load;
    reg clock;
    wire [7:0] outChar;
    EnigmaMachine uut(char, startPosition1, startPosition2, startPosition3, load, clock, outChar);
    
    initial begin
        char <= "D"; startPosition1 <= 5'd0; startPosition2 <= 5'd0; startPosition3 <= 5'd0; #10;
        load <= 1; #5; load <= 0; #10;
        clock <= 1; #5; clock <= 0;
    end
endmodule

module EnigmaCommunication_test();
    reg [7:0] plainChar;
    reg [4:0] startPosition1;
    reg [4:0] startPosition2;
    reg [4:0] startPosition3;
    reg load;
    reg clock;
    wire [7:0] chipherChar;
    wire [7:0] decryptedChar;
    EnigmaCommunication uut(plainChar, startPosition1, startPosition2, startPosition3, load, clock, chipherChar, decryptedChar);
    
    initial begin
        plainChar <= "A"; startPosition1 <= 5'd0; startPosition2 <= 5'd0; startPosition3 <= 5'd0; load <= 1; #10;
        load <= 0;
        clock = 1; #5; clock = 0;
    end
endmodule