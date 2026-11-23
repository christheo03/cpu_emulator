#include <stdio.h>
#include <stdlib.h>

    using Byte = unsigned char; // 8-bit
    using Word = unsigned short; // 16-bit

    using u32 = unsigned int; // 32-bit

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64; // 16-bits need 2^16 size = 64 Kib 
    Byte Data[MAX_MEM] ;   // Data array

    //  When Initialise Data array is set to 0 in every location
    void Initialise()
    {
        for (u32 i =0; i<MAX_MEM ; i++){
            Data[i] = 0;
        }
    }
    
    // Read memory from Address (1-Byte)
    Byte operator[] (u32 Address)
    {
        return Data[Address];
    }

};

struct CPU
{


    Word PC; //Program Counter 
    Word SP; //Stack Pointer

    Byte A,X,Y; // Registers
    
    // Proccessor Status Flags
    Byte C :1;  // Carry Flag
    Byte Z :1;  // Zero Flag
    Byte I :1;  // Interrupt Disable 
    Byte D :1;  // Decimal Mode
    Byte B :1;  // Break Command
    Byte V :1;  // Overflow Flag
    Byte N :1;  // Negative Flag

    // Reset the CPU, Registers etc. if restart power on happens
    void Reset(Mem& memory)
    {
        SP = 0x0100;    // SP points to that location in the mem
        PC = 0xFFFC;    // PC points to that location in mem
        C = Z = I = B = V = N = D = 0;  // Flags set to 0
        A = X = Y = 0;  // Registerrs are set to 0
        memory.Initialise();    // Memory is Initialised

    }
    
    // Fetch from memory the data
    Byte FetchByte(u32& Cycles, Mem& mem)
    {
        Byte Data = mem[PC]; // PC tells us what should it be fetched
        PC++;   // After fetch PC moves to next location
        Cycles--;   //  Cycles get -1

        return Data;
    }

    //   Execute an Instruction.
    //  Cycles: number of cycles needed to execute that instruction
    //  Mem: 
    void Execute(u32 Cycles, Mem& mem)
    {
        while (Cycles>0)
        {
            Byte Instr = FetchByte(Cycles,mem);
        }
    }
};

int main ()
{
    Mem mem;    //  Create Memory obj
    CPU cpu;    //  Create cpu obj
    cpu.Reset(mem);    //   Reset 
    cpu.Execute(2, mem);    // Execute an instruction 
    return 0;
}