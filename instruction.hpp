#pragma once

#include <iostream>
#include <cstdint>
#include <iomanip>

using namespace std;

enum class Opcode : uint32_t {
    LUI    = 0x37, // 0110111
    AUIPC  = 0x17, // 0010111
    JAL    = 0x6F, // 1101111
    JALR   = 0x67, // 1100111
    BRANCH = 0x63, // 1100011
    LOAD   = 0x03, // 0000011
    STORE  = 0x23, // 0100011
    I_TYPE = 0x13, // 0010011 (OP-IMM)
    R_TYPE = 0x33, // 0110011 (OP)
    FENCE  = 0x0F, // 0001111 (MISC-MEM)
    SYSTEM = 0x73  // 1110011 (ECALL, EBREAK)
};

enum class Funct3 : uint32_t {
    ADD_SUB_ADDI = 0x0,
    SLL_SLLI     = 0x1,
    SLT_SLTI     = 0x2,
    SLTU_SLTIU   = 0x3,
    XOR_XORI     = 0x4,
    SR_SRLI_SRAI = 0x5,
    OR_ORI       = 0x6,
    AND_ANDI     = 0x7,

    BEQ  = 0x0,
    BNE  = 0x1,
    BLT  = 0x4,
    BGE  = 0x5,
    BLTU = 0x6,
    BGEU = 0x7,

    LB  = 0x0,
    LH  = 0x1,
    LW  = 0x2,
    LBU = 0x4,
    LHU = 0x5,

    SB = 0x0,
    SH = 0x1,
    SW = 0x2,

    PRIV = 0x0
};

enum class Funct7 : uint32_t {
    BASE = 0x00, // ADD, SLL, SRL, etc.
    ALT  = 0x20  // SUB, SRA
};

struct Instruction {
    uint32_t address;
    uint32_t raw_inst;
    
    Opcode opcode;
    uint32_t rd, rs1, rs2;
    Funct3 funct3;
    Funct7 funct7;

    int32_t imm_I;
    int32_t imm_S;
    int32_t imm_B;
    int32_t imm_U;
    int32_t imm_J;

    void decode(uint32_t inst, uint32_t addr) {
        address = addr;
        raw_inst = inst;

        opcode = static_cast<Opcode>(inst & 0x7F);
        rd     = (inst >> 7) & 0x1F;
        funct3 = static_cast<Funct3>((inst >> 12) & 0x7);
        rs1    = (inst >> 15) & 0x1F;
        rs2    = (inst >> 20) & 0x1F;
        funct7 = static_cast<Funct7>((inst >> 25) & 0x7F);

        imm_I = (int32_t)inst >> 20; 
        
        imm_S = (((int32_t)inst >> 25) << 5) | ((inst >> 7) & 0x1F);
        
        imm_B = (((int32_t)inst >> 31) << 12) | 
                (((inst >> 7) & 0x1) << 11) | 
                (((inst >> 25) & 0x3F) << 5) | 
                (((inst >> 8) & 0xF) << 1);
                
        imm_U = inst & 0xFFFFF000;
        
        imm_J = (((int32_t)inst >> 31) << 20) | 
                (((inst >> 12) & 0xFF) << 12) | 
                (((inst >> 20) & 0x1) << 11) | 
                (((inst >> 21) & 0x3FF) << 1);
    }

const string ABI_REG[32] = {
    "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
    "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
    "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

    void print() {
        cout << hex << "0x" << address << " | 0x" << setfill('0') << setw(8) << raw_inst << " | ";

        switch (opcode) {
            case Opcode::LUI:
                cout << "LUI " << ABI_REG[rd] << ", 0x" << hex << (imm_U >> 12) << endl;
                break;
                
            case Opcode::AUIPC:
                cout << "AUIPC " << ABI_REG[rd] << ", 0x" << hex << (imm_U >> 12) << endl;
                break;
                
            case Opcode::JAL:
                cout << "JAL " << ABI_REG[rd] << ", 0x" << hex << imm_J << endl;
                break;
                
            case Opcode::JALR:
                cout << "JALR " << ABI_REG[rd] << ", " << ABI_REG[rs1] << ", 0x" << hex << imm_I << endl;
                break;
                
            case Opcode::BRANCH:
                switch (funct3) {
                    case Funct3::BEQ:  cout << "BEQ "; break;
                    case Funct3::BNE:  cout << "BNE "; break;
                    case Funct3::BLT:  cout << "BLT "; break;
                    case Funct3::BGE:  cout << "BGE "; break;
                    case Funct3::BLTU: cout << "BLTU "; break;
                    case Funct3::BGEU: cout << "BGEU "; break;
                    default: cout << "UNKNOWN_BRANCH "; break;
                }
                cout << " " << ABI_REG[rs1] << ", " << ABI_REG[rs2] << ", 0x" << hex << imm_B << endl;
                break;
                
            case Opcode::LOAD:
                switch (funct3) {
                    case Funct3::LB:  cout << "LB "; break;
                    case Funct3::LH:  cout << "LH "; break;
                    case Funct3::LW:  cout << "LW "; break;
                    case Funct3::LBU: cout << "LBU "; break;
                    case Funct3::LHU: cout << "LHU "; break;
                    default: cout << "UNKNOWN_LOAD "; break;
                }
                cout << " " << ABI_REG[rd] << ", " << dec << imm_I << "(" << ABI_REG[rs1] << ")" << endl;
                break;
                
            case Opcode::STORE:
                switch (funct3) {
                    case Funct3::SB: cout << "SB "; break;
                    case Funct3::SH: cout << "SH "; break;
                    case Funct3::SW: cout << "SW "; break;
                    default: cout << "UNKNOWN_STORE "; break;
                }
                cout << " " << ABI_REG[rs2] << ", " << dec << imm_S << "(" << ABI_REG[rs1] << ")" << endl;
                break;
                
            case Opcode::I_TYPE:
                switch (funct3) {
                    case Funct3::ADD_SUB_ADDI: cout << "ADDI "; break;
                    case Funct3::SLL_SLLI:     cout << "SLLI "; break;
                    case Funct3::SLT_SLTI:     cout << "SLTI "; break;
                    case Funct3::SLTU_SLTIU:   cout << "SLTIU "; break;
                    case Funct3::XOR_XORI:     cout << "XORI "; break;
                    case Funct3::SR_SRLI_SRAI: 
                        if (funct7 == Funct7::BASE) cout << "SRLI ";
                        else cout << "SRAI ";
                        break;
                    case Funct3::OR_ORI:       cout << "ORI "; break;
                    case Funct3::AND_ANDI:     cout << "ANDI "; break;
                }
                if (funct3 == Funct3::SLL_SLLI || funct3 == Funct3::SR_SRLI_SRAI) {
                    cout << " " << ABI_REG[rd] << ", " << ABI_REG[rs1] << ", " << (imm_I & 0x1F) << endl;
                } else {
                    cout << " " << ABI_REG[rd] << ", " << ABI_REG[rs1] << ", " << dec << imm_I << endl;
                }
                break;

            case Opcode::R_TYPE:
                switch (funct3) {
                    case Funct3::ADD_SUB_ADDI: 
                        if (funct7 == Funct7::BASE) cout << "ADD ";
                        else cout << "SUB ";
                        break;
                    case Funct3::SLL_SLLI:     cout << "SLL "; break;
                    case Funct3::SLT_SLTI:     cout << "SLT "; break;
                    case Funct3::SLTU_SLTIU:   cout << "SLTU "; break;
                    case Funct3::XOR_XORI:     cout << "XOR "; break;
                    case Funct3::SR_SRLI_SRAI: 
                        if (funct7 == Funct7::BASE) cout << "SRL ";
                        else cout << "SRA ";
                        break;
                    case Funct3::OR_ORI:       cout << "OR "; break;
                    case Funct3::AND_ANDI:     cout << "AND "; break;
                }
                cout << " " << ABI_REG[rd] << ", " << ABI_REG[rs1] << ", " << ABI_REG[rs2] << endl;
                break;
                
            case Opcode::FENCE:
                cout << "FENCE (or PAUSE)" << endl;
                break;
                
            case Opcode::SYSTEM:
                if (imm_I == 0) cout << "ECALL" << endl;
                else if (imm_I == 1) cout << "EBREAK" << endl;
                else cout << "SYSTEM_INST" << endl;
                break;

            default:
                cout << "UNKNOWN_OPCODE" << endl;
                break;
        }
    }
};