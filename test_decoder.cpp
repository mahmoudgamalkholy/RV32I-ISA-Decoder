#include <gtest/gtest.h>
#include "instruction.hpp" 

TEST(InstructionDecoderTest, DecodeAddiNegativeImm) {
    Instruction inst;
    
    inst.decode(0xfe010113, 0x10094);

    EXPECT_EQ(inst.opcode, Opcode::I_TYPE);       
    EXPECT_EQ(inst.funct3, Funct3::ADD_SUB_ADDI); 
    EXPECT_EQ(inst.rd, 2);                        
    EXPECT_EQ(inst.rs1, 2);                       
    EXPECT_EQ(inst.imm_I, -32);                   
}


TEST(InstructionDecoderTest, DecodeJalInstruction) {
    Instruction inst;
    
    inst.decode(0x0fe000ef, 0x0);

    EXPECT_EQ(inst.opcode, Opcode::JAL);
    EXPECT_EQ(inst.rd, 1);     
    EXPECT_EQ(inst.imm_J, 254); 


}