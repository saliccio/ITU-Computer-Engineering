`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Istanbul Technical University
// Engineer: Eyupcan Cakir & Furkan Salik
// 
// Create Date: 30.04.2022 23:23:52
// Design Name: 
// Module Name: Simulation
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


module SimPart1a;
    reg [7:0] I;
    reg [1:0] FunSel;
    reg clk, E;
    wire [7:0] Q;
    register_8_bit R (I, FunSel, clk, E, Q);
    always # 50 clk = ~clk;
    always # 100 E = ~E;
    initial begin
            clk = 0; I = 8'd13; E = 0; FunSel = 2'b10; #200;
            FunSel = 2'b11; #200;
            FunSel = 2'b01; #200;
            FunSel = 2'b00; #200;
            I = 8'd17; FunSel = 2'b10; #200;
    end
endmodule

module SimPart1b;
    reg [15:0] I;
    reg [1:0] FunSel;
    reg clk, E;
    wire [15:0] Q;
    register_16_bit R (I, FunSel, clk, E, Q);
    always # 50 clk = ~clk;
    always # 100 E = ~E;
        initial begin
                clk = 0; I = 16'd43; E = 0; FunSel = 2'b10; #200;
                FunSel = 2'b11; #200;
                FunSel = 2'b01; #200;
                FunSel = 2'b00; #200;
                I = 16'd47; FunSel = 2'b10; #200;
        end
endmodule

module SimPart2a;
    reg [7:0] I;
    reg [1:0] OutASel, OutBSel, FunSel;
    reg [3:0] RegSel;
    reg clk;
    wire [7:0] OutA, OutB;
    RegisterFile RF (I, OutASel, OutBSel, FunSel, RegSel, clk, OutA, OutB);
    always # 3.90625 clk = ~clk;
    always # 62.5 RegSel = RegSel + 1;
    always begin # 31.25 OutASel = OutASel + 1; OutBSel = OutBSel - 1; end
    always # 7.8125 FunSel = FunSel - 1;
    initial begin
        clk <= 0;
        I <= 8'd17;
        OutASel <= 2'd0;
        OutBSel <= 2'd3;
        FunSel <= 2'd3;
        RegSel <= 4'd0;
    end
endmodule

module SimPart2b;
    reg [7:0] I;
    reg [1:0] OutCSel, OutDSel, FunSel;
    reg [2:0] RegSel;
    reg clk;
    wire [7:0] OutC, OutD;
    AddressRegisterFile ARF (I, OutCSel, OutDSel, FunSel, RegSel, clk, OutC, OutD);
    always # 7.8125 clk = ~clk;
    always # 125 RegSel = RegSel + 1;
    always begin # 62.5 OutCSel = OutCSel + 1; OutDSel = OutDSel - 1; end
    always # 15.625 FunSel = FunSel - 1;
    initial begin
        clk <= 0;
        I <= 8'd17;
        OutCSel <= 2'd0;
        OutDSel <= 2'd3;
        FunSel <= 2'd3;
        RegSel <= 4'd0;
    end
endmodule

module SimPart2c;
    reg [7:0] I;
    reg [1:0] FunSel;
    reg enable, lh, clk;
    wire [15:0] IROut;
    InstructionRegister IR (I, FunSel, enable, lh, clk, IROut);
    always # 50 clk = ~clk;
    always # 100 enable = ~enable;
    initial begin
                clk = 0; I = 8'd13; enable = 0;
                FunSel = 2'b11; #200;
                lh = 0; FunSel = 2'b10; #200;
                lh = 1; FunSel = 2'b10; #200;
                FunSel = 2'b01; #200;
                FunSel = 2'b00; #200;
    end
endmodule

module SimPart3;
    reg [7:0] A, B;
    reg [3:0] FunSel;
    reg clk;
    wire [3:0] OutFlag;
    wire [7:0] OutALU;
    ArithmeticLogicUnit ALU (A, B, FunSel, clk, OutFlag, OutALU);
    always # 31.25 clk = ~clk;
    initial begin
        clk <= 0;
        A = 8'd12; FunSel = 4'd0; #62.5;
        B = 8'd17; FunSel = 4'd1; #62.5;
        FunSel = 4'd2; #62.5;
        FunSel = 4'd3; #62.5;
        A = 8'd24; B = 8'd47; FunSel = 4'd4; #62.5;
        A = 8'd4; B = 8'd23; FunSel = 4'd5; #62.5;
        A = 8'd17; B = 8'd9; FunSel = 4'd6; #62.5;
        FunSel = 4'd7; #62.5;
        FunSel = 4'd8; #62.5;
        FunSel = 4'd9; #62.5;
        A = 8'd37; FunSel = 4'd10; #62.5;
        A = 8'd48; FunSel = 4'd11; #62.5;
        A = 8'd11; FunSel = 4'd12; #62.5;
        A = 8'd82; FunSel = 4'd13; #62.5;
        A = 8'd93; FunSel = 4'd14; #62.5;
        A = 8'd38; FunSel = 4'd15; #62.5;
    end
endmodule

module SimPart4;
    reg  [1:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    reg  [3:0] RF_RegSel, ALU_FunSel;
    reg  [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel;
    reg  [2:0] ARF_RegSel;
    reg  IR_LH, IR_Enable;
    reg  [1:0] IR_Funsel;
    reg  Mem_WR, Mem_CS;
    reg  [1:0] MuxASel, MuxBSel;
    reg  MuxCSel, Clock;
    wire [7:0] MuxAOut, MuxBOut, MuxCOut;
    wire [7:0] AOut, BOut, ARF_COut, Address, MemoryOut, ALUOut;
    wire [3:0] ALUOutFlag;
    wire [15:0] IROut;
    ALUSystem _ALUSystem(RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, ALU_FunSel, ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel, Clock, MuxAOut, MuxBOut, MuxCOut, AOut, BOut, ARF_COut, Address, MemoryOut, ALUOut, ALUOutFlag, IROut);
    reg [31:0] VectorNum, Errors, TotalLine; 
        reg [34:0] TestVectors[10000:0];
        reg Reset, Operation;
        
        //Clock Signal Generation
        always 
        begin
            Clock = 1; #5; Clock = 0; #5; // 10ns period
        end
        
        //Read Test Bench Values
        initial begin
            $readmemb("TestBench.mem", TestVectors); // Read vectors
            VectorNum = 0; Errors = 0; TotalLine=0; Reset=0;// Initialize
        end
        
        // Apply test vectors on rising edge of clock
        always @(posedge Clock)
        begin
            #1; 
            {Operation, RF_OutASel, RF_OutBSel, RF_FunSel, 
            RF_RegSel, ALU_FunSel, ARF_OutCSel, ARF_OutDSel, 
            ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, 
            Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel} = TestVectors[VectorNum];
        end
        
        // Check results on falling edge of clk
        always @(negedge Clock)
            if (~Reset) // skip during reset
            begin
                // increment array index and read next testvector
                VectorNum = VectorNum + 1;
                if (TestVectors[VectorNum] === 35'bx)
                begin
                    $display("%d tests completed.",
                    VectorNum);
                    $finish; // End simulation
                end
            end
endmodule

/*module Project1Test();
    //Input Registers of ALUSystem
    reg[1:0] RF_OutASel; 
    reg[1:0] RF_OutBSel; 
    reg[1:0] RF_FunSel;
    reg[3:0] RF_RegSel;
    reg[3:0] ALU_FunSel;
    reg[1:0] ARF_OutCSel; 
    reg[1:0] ARF_OutDSel; 
    reg[1:0] ARF_FunSel;
    reg[2:0] ARF_RegSel;
    reg      IR_LH;
    reg      IR_Enable;
    reg[1:0]      IR_Funsel;
    reg      Mem_WR;
    reg      Mem_CS;
    reg[1:0] MuxASel;
    reg[1:0] MuxBSel;
    reg MuxCSel;
    reg      Clock;
    
    //Test Bench Connection of ALU System
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
    .Clock(Clock)
    );
    
    //Test Vector Variables
    reg [31:0] VectorNum, Errors, TotalLine; 
    reg [34:0] TestVectors[10000:0];
    reg Reset, Operation;
    
    //Clock Signal Generation
    always 
    begin
        Clock = 1; #5; Clock = 0; #5; // 10ns period
    end
    
    //Read Test Bench Values
    initial begin
        $readmemb("TestBench.mem", TestVectors); // Read vectors
        VectorNum = 0; Errors = 0; TotalLine=0; Reset=0;// Initialize
    end
    
    // Apply test vectors on rising edge of clock
    always @(posedge Clock)
    begin
        #1; 
        {Operation, RF_OutASel, RF_OutBSel, RF_FunSel, 
        RF_RegSel, ALU_FunSel, ARF_OutCSel, ARF_OutDSel, 
        ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, 
        Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel} = TestVectors[VectorNum];
    end
    
    // Check results on falling edge of clk
    always @(negedge Clock)
        if (~Reset) // skip during reset
        begin
            $display("Input Values:");
            $display("Operation: %d", Operation);
            $display("Register File: OutASel: %d, OutBSel: %d, FunSel: %d, Regsel: %d", RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel);            
            $display("ALU FunSel: %d", ALU_FunSel);
            $display("Addres Register File: OutCSel: %d, OutDSel: %d, FunSel: %d, Regsel: %d", ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel);            
            $display("Instruction Register: LH: %d, Enable: %d, FunSel: %d", IR_LH, IR_Enable, IR_Funsel);            
            $display("Memory: WR: %d, CS: %d", Mem_WR, Mem_CS);
            $display("MuxASel: %d, MuxBSel: %d, MuxCSel: %d", MuxASel, MuxBSel, MuxCSel);
            
            $display("");
            $display("Ouput Values:");
            $display("Register File: AOut: %d, BOut: %d", _ALUSystem.AOut, _ALUSystem.BOut);            
            $display("ALUOut: %d, ALUOutFlag: %d, ALUOutFlags: Z:%d, C:%d, N:%d, O:%d,", _ALUSystem.ALUOut, _ALUSystem.ALUOutFlag, _ALUSystem.ALUOutFlag[3],_ALUSystem.ALUOutFlag[2],_ALUSystem.ALUOutFlag[1],_ALUSystem.ALUOutFlag[0]);
            $display("Address Register File: COut: %d, DOut (Address): %d", _ALUSystem.ARF_COut, _ALUSystem.Address);            
            $display("Memory Out: %d", _ALUSystem.MemoryOut);            
            $display("Instruction Register: IROut: %d", _ALUSystem.IROut);            
            $display("MuxAOut: %d, MuxBOut: %d, MuxCOut: %d", _ALUSystem.MuxAOut, _ALUSystem.MuxBOut, _ALUSystem.MuxCOut);
            
            // increment array index and read next testvector
            VectorNum = VectorNum + 1;
            if (TestVectors[VectorNum] === 35'bx)
            begin
                $display("%d tests completed.",
                VectorNum);
                $finish; // End simulation
            end
        end
endmodule*/

module Project1Test();
    //Input Registers of ALUSystem
    reg[1:0] RF_OutASel; 
    reg[1:0] RF_OutBSel; 
    reg[1:0] RF_FunSel;
    reg[3:0] RF_RegSel;
    reg[3:0] ALU_FunSel;
    reg[1:0] ARF_OutCSel; 
    reg[1:0] ARF_OutDSel; 
    reg[1:0] ARF_FunSel;
    reg[2:0] ARF_RegSel;
    reg      IR_LH;
    reg      IR_Enable;
    reg[1:0]      IR_Funsel;
    reg      Mem_WR;
    reg      Mem_CS;
    reg[1:0] MuxASel;
    reg[1:0] MuxBSel;
    reg MuxCSel;
    reg      Clock;
    
    //Output Check
    reg Check_AOut;	reg [7:0] AOut;	reg Check_BOut;	
    reg [7:0] BOut;	reg Check_ALUOut;	reg [7:0] ALUOut;	
    reg Check_ALUOutFlag;	reg [3:0] ALUOutFlag;	
    reg Check_Z;	reg Z;	reg Check_C;	reg C;	
    reg Check_N;	reg N;	reg Check_O;	reg O;	
    reg Check_ARF_COut;	reg [7:0] ARF_COut;	reg Check_Address;	
    reg [7:0] Address;	reg Check_MemoryOut;	reg [7:0] MemoryOut;	
    reg Check_IROut;	reg [15:0] IROut;	reg Check_MuxAOut;	
    reg [7:0] MuxAOut;	reg Check_MuxBOut;	reg [7:0] MuxBOut;	
    reg Check_MuxCOut;	reg [7:0] MuxCOut;
    reg [7:0] TotalError=0, TotalLine=0, LineError=0, LineCheck=0; 
        
    //Test Bench Connection of ALU System
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
    .Clock(Clock)
    );
    
    //Test Vector Variables
    reg [31:0] VectorNum; 
    reg [145:0] TestVectors[200:0];
    reg Reset, Operation;
    
    //Clock Signal Generation
    always 
    begin
        Clock = 1; #5; Clock = 0; #5; // 10ns period
    end
    
    //Read Test Bench Values
    initial begin
        $readmemb("TestBench.mem", TestVectors); // Read vectors
        VectorNum = 0; Reset=0;// Initialize
    end
    
    // Apply test vectors on rising edge of clock
    always @(posedge Clock)
    begin
        #1; 
        {Operation, RF_OutASel, RF_OutBSel, RF_FunSel, 
        RF_RegSel, ALU_FunSel, ARF_OutCSel, ARF_OutDSel, 
        ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, 
        Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel, 
        Check_AOut, 	AOut, 	Check_BOut, 	BOut, 	
        Check_ALUOut, 	ALUOut, 	Check_ALUOutFlag, 	ALUOutFlag,
        Check_Z, 	Z, 	Check_C, 	C, 	Check_N,
        N, 	Check_O, 	O, 	Check_ARF_COut, 	ARF_COut,
        Check_Address, 	Address, 	Check_MemoryOut, 	MemoryOut, 	
        Check_IROut, 	IROut, 	Check_MuxAOut, 	MuxAOut, 	
        Check_MuxBOut, 	MuxBOut, 	Check_MuxCOut, 	MuxCOut} = TestVectors[VectorNum];
    end
    
    // Check results on falling edge of clk
    always @(negedge Clock)
        if (~Reset) // skip during reset
        begin
            
        
            $display("Input Values:");
            $display("Operation: %d", Operation);
            $display("Register File: OutASel: %d, OutBSel: %d, FunSel: %d, Regsel: %d", RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel);            
            $display("ALU FunSel: %d", ALU_FunSel);
            $display("Addres Register File: OutCSel: %d, OutDSel: %d, FunSel: %d, Regsel: %d", ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel);            
            $display("Instruction Register: LH: %d, Enable: %d, FunSel: %d", IR_LH, IR_Enable, IR_Funsel);            
            $display("Memory: WR: %d, CS: %d", Mem_WR, Mem_CS);
            $display("MuxASel: %d, MuxBSel: %d, MuxCSel: %d", MuxASel, MuxBSel, MuxCSel);
            
            $display("");
            $display("Ouput Values:");
            $display("Register File: AOut: %d, BOut: %d", _ALUSystem.AOut, _ALUSystem.BOut);            
            $display("ALUOut: %d, ALUOutFlag: %b, ALUOutFlags: Z:%d, C:%d, N:%d, O:%d,", _ALUSystem.ALUOut, _ALUSystem.ALUOutFlag, _ALUSystem.ALUOutFlag[3],_ALUSystem.ALUOutFlag[2],_ALUSystem.ALUOutFlag[1],_ALUSystem.ALUOutFlag[0]);
            $display("Address Register File: COut: %d, DOut (Address): %d", _ALUSystem.ARF_COut, _ALUSystem.Address);            
            $display("Memory Out: %b", _ALUSystem.MemoryOut);            
            $display("Instruction Register: IROut: %d", _ALUSystem.IROut);            
            $display("MuxAOut: %d, MuxBOut: %d, MuxCOut: %d", _ALUSystem.MuxAOut, _ALUSystem.MuxBOut, _ALUSystem.MuxCOut);
            //Check Functions
            if (Operation)
            begin
                TotalLine=TotalLine+1;
                LineError=0;
                LineCheck=0;
                $display("##############################################");

                
                $display("%d Line Check Started To Test",TotalLine);
                //CheckAOut
                if(Check_AOut)
                begin
                    LineCheck=LineCheck+1;
                    if(AOut!=_ALUSystem.AOut)
                    begin
                        $display("AOut Error: Expected: %d, Actual: %d",AOut,_ALUSystem.AOut);
                        LineError=LineError+1;
                    end
                end
                
                //CheckBOut
                if(Check_BOut)
                begin
                    LineCheck=LineCheck+1;
                    if(BOut!=_ALUSystem.BOut)
                    begin
                        $display("BOut Error: Expected: %d, Actual: %d",BOut,_ALUSystem.BOut);
                        LineError=LineError+1;
                    end
                end
                
                
                //CheckALUOut
                if(Check_ALUOut)
                begin
                    LineCheck=LineCheck+1;
                    if(ALUOut!=_ALUSystem.ALUOut)
                    begin
                        $display("ALUOut Error: Expected: %d, Actual: %d",ALUOut,_ALUSystem.ALUOut);
                        LineError=LineError+1;
                    end
                end
                
                //CheckALUOut
                if(Check_ALUOutFlag)
                begin
                    LineCheck=LineCheck+1;
                    if(ALUOutFlag!=_ALUSystem.ALUOutFlag)
                    begin
                        $display("ALUOutFlag Error: Expected: %d, Actual: %d",ALUOutFlag,_ALUSystem.ALUOutFlag);
                        LineError=LineError+1;
                    end
                end
                
                //Check_Z
                if(Check_Z)
                begin
                    LineCheck=LineCheck+1;
                    if(Z!=_ALUSystem.ALUOutFlag[3])
                    begin
                        $display("Z Flag Error: Expected: %d, Actual: %d",Z,_ALUSystem.ALUOutFlag[3]);
                        LineError=LineError+1;
                    end
                end
                
                //Check_C
                if(Check_C)
                begin
                    LineCheck=LineCheck+1;
                    if(C!=_ALUSystem.ALUOutFlag[2])
                    begin
                        $display("C Flag Error: Expected: %d, Actual: %d",C,_ALUSystem.ALUOutFlag[2]);
                        LineError=LineError+1;
                    end
                end
                
                //Check_N
                if(Check_N)
                begin
                    LineCheck=LineCheck+1;
                    if(N!=_ALUSystem.ALUOutFlag[1])
                    begin
                        $display("N Flag Error: Expected: %d, Actual: %d",N,_ALUSystem.ALUOutFlag[1]);
                        LineError=LineError+1;
                    end
                end
                
                //Check_O
                if(Check_O)
                begin
                    LineCheck=LineCheck+1;
                    if(O!=_ALUSystem.ALUOutFlag[0])
                    begin
                        $display("O Flag Error: Expected: %d, Actual: %d",O,_ALUSystem.ALUOutFlag[0]);
                        LineError=LineError+1;
                    end
                end
                
                //Check_ARF_COut
                if(Check_ARF_COut)
                begin
                    LineCheck=LineCheck+1;
                    if(ARF_COut!=_ALUSystem.ARF_COut)
                    begin
                        $display("ARF_COut Error: Expected: %d, Actual: %d",ARF_COut,_ALUSystem.ARF_COut);
                        LineError=LineError+1;
                    end
                end
                
                //Check_Address
                if(Check_Address)
                begin
                    LineCheck=LineCheck+1;
                    if(Address!=_ALUSystem.Address)
                    begin
                        $display("Address Error: Expected: %d, Actual: %d",Address,_ALUSystem.Address);
                        LineError=LineError+1;
                    end
                end
                
                //Check_MemoryOut
                if(Check_MemoryOut)
                begin
                    LineCheck=LineCheck+1;
                    if(MemoryOut!=_ALUSystem.MemoryOut)
                    begin
                        $display("MemoryOut Error: Expected: %d, Actual: %d",MemoryOut,_ALUSystem.MemoryOut);
                        LineError=LineError+1;
                    end
                end
                
                
                //Check_IROut
                if(Check_IROut)
                begin
                    LineCheck=LineCheck+1;
                    if(IROut!=_ALUSystem.IROut)
                    begin
                        $display("IROut Error: Expected: %d, Actual: %d",IROut,_ALUSystem.IROut);
                        LineError=LineError+1;
                    end
                end
                    
                //Check_MuxAOut
                if(Check_MuxAOut)
                begin
                    LineCheck=LineCheck+1;
                    if(MuxAOut!=_ALUSystem.MuxAOut)
                    begin
                        $display("MuxAOut Error: Expected: %d, Actual: %d",MuxAOut,_ALUSystem.MuxAOut);
                        LineError=LineError+1;
                    end
                end 
                
                //Check_MuxBOut
                if(Check_MuxBOut)
                begin
                    LineCheck=LineCheck+1;
                    if(MuxBOut!=_ALUSystem.MuxBOut)
                    begin
                        $display("MuxBOut Error: Expected: %d, Actual: %d",MuxBOut,_ALUSystem.MuxBOut);
                        LineError=LineError+1;
                    end
                end   
                
                //Check_MuxCOut
                if(Check_MuxCOut)
                begin
                    LineCheck=LineCheck+1;
                    if(MuxCOut!=_ALUSystem.MuxCOut)
                    begin
                        $display("MuxCOut Error: Expected: %d, Actual: %d",MuxCOut,_ALUSystem.MuxCOut);
                        LineError=LineError+1;
                    end
                end 
                           
                
                $display("");
                //Check All Messages
                if(LineError>8'd0)
                begin
                     TotalError=TotalError+1;
                     $display("LineError: %d/%d, Total Error: %d/%d",LineError, LineCheck,TotalError,TotalLine);
                end
                else
                begin
                     $display("Line passed the test");
                end
                $display("##############################################");
            end
            
            
            // increment array index and read next testvector
            VectorNum = VectorNum + 1;
            if (TestVectors[VectorNum] === 146'bx)
            begin
                $display("%d tests completed with %d errors.",
                VectorNum, TotalError);
                $finish; // End simulation
            end
        end
endmodule

module Sim_Control_Unit;
    wire [1:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    wire [3:0] RF_RegSel, ALU_FunSel;
    wire [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel;
    wire [2:0] ARF_RegSel;
    wire IR_LH, IR_Enable;
    wire [1:0] IR_Funsel;
    wire Mem_WR, Mem_CS;
    wire [1:0] MuxASel, MuxBSel;
    wire MuxCSel;
    reg [3:0] ALUOutFlag;
    reg [15:0] IROut;
    reg Clock;
    ControlUnit CU (Clock, ALUOutFlag, IROut, RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, ALU_FunSel, ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel);
    always begin
        Clock = 1; #5; Clock = 0; #5; // 10ns period
    end
    initial begin
        IROut <= 16'b0000010011111111; #40;
        IROut <= 16'b0001010011111111; #40;
        IROut <= 16'b0010000011111111; #40;
    end
endmodule

module Sim_CPU;
    reg Clock;
    always begin
        Clock = 1; #5; Clock = 0; #5; // 10ns period
    end
    CPU _CPU(Clock);
endmodule

/*
module Sim_Control_Unit;
    wire [1:0] RF_OutASel, RF_OutBSel, RF_FunSel;
    wire [3:0] RF_RegSel, ALU_FunSel;
    wire [1:0] ARF_OutCSel, ARF_OutDSel, ARF_FunSel;
    wire [2:0] ARF_RegSel;
    wire IR_LH, IR_Enable;
    wire [1:0] IR_Funsel;
    wire Mem_WR, Mem_CS;
    wire [1:0] MuxASel, MuxBSel;
    wire MuxCSel;
    reg [3:0] ALUOutFlag;
    reg [15:0] IROut;
    reg Clock;
    ControlUnit CU (Clock, ALUOutFlag, IROut, RF_OutASel, RF_OutBSel, RF_FunSel, RF_RegSel, ALU_FunSel, ARF_OutCSel, ARF_OutDSel, ARF_FunSel, ARF_RegSel, IR_LH, IR_Enable, IR_Funsel, Mem_WR, Mem_CS, MuxASel, MuxBSel, MuxCSel);
    always begin
        Clock = 1; #5; Clock = 0; #5; // 10ns period
    end
    initial begin
        IROut <= 16'b0000010011111111; #40;
        IROut <= 16'b0001010011111111; #40;
        IROut <= 16'b0010000011111111; #40;
    end
endmodule

module Sim_CPU;
    reg Clock, Reset;
    initial begin
        Reset <= 1; #10;
        Reset <= 0;
    end
    always begin
        Clock = 1; #5; Clock = 0; #5; // 10ns period
    end
    CPU _CPU(Clock, Reset);
endmodule
*/