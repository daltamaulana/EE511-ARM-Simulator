/*********************************************************
 *                                                       *
 *  EE511 Project 1                                      *
 *                                                       *
 *  C simulator for Cortex-M0                            *
 *                                                       *
 *********************************************************/


#include "iss.h"

void b_unconditional(uint16_t inst);
void bl(uint32_t inst);

void process(uint16_t inst)
{
  uint16_t inst2;
  uint32_t inst32;

  // Decode Instruction Set
  if (0) {
    // Check for Immediate Instruction
    if (INST(15, 14) == 0x0) {

    }
    // Check for Data Processing Instruction
    else if (INST(15, 10) == 0x10) {

    }
    // Check for Special Data and Branch Instruction
    else if (INST(15, 10) == 0x11) {

    }
    // Check for Load from Pool Instruction
    else if (INST(15, 11) == 0x9) {

    }
    // Check for Load and Store Instruction (Register)
    else if ((INST(15, 12) == 0x5)) {
      
    }
    // Check for Load and Store Instruction with Immediate (Word and Byte)
    else if ((INST(15, 13) == 0x3)) {
      
    }
    // Check for Load and Store Instruction with Immediate (Word and Byte)
    else if ((INST(15, 13) == 0x4)) {
      
    }
    // Check for PC Relative Address Generator Instruction
    else if ((INST(15, 11) == 0x14)) {
      
    }
    // Check for SP Relative Address Generator Instruction
    else if ((INST(15, 11) == 0x15)) {
      
    }
    // Check for 16-bit Miscellaneous Instruction
    else if ((INST(15, 12) == 0xB)) {
      
    }
    // Check for Multiple registers Store and Load Instruction
    else if ((INST(15, 12) == 0xC)) {
      
    }
    // Check for Conditional Branch Instruction
    else if ((INST(15, 12) == 0xD)) {
      
    }
    // Invalid Instruction
    else {
      printf("[Error] %x is an invalid instruction! Please check the instruction!\n", inst);
    }
  }
  else if (INST(15, 11) == 0x1C) {
    b_unconditional(inst);
  }
  else if (INST(15, 11) == 0x1E) {
    inst2 = read_halfword(EXE_PC + 2);
    inst32 = ((uint32_t) inst << 16) | ((uint32_t) inst2);
    if (extract16_(inst2, 14) && extract16_(inst2, 12))
      bl(inst32);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                          Define Function for Immediate Instruction                          //
/////////////////////////////////////////////////////////////////////////////////////////////////
// Logical Shift Left (Immediate) Instruction
void lsl_imm(uint16_t inst)
{
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t reg_data;
  uint32_t carry_out;

  // Read data from register
  reg_data = R[rm];

  // Performs shifting operation
  carry_out = extract32_(reg_data, 31);
  reg_data = (reg_data << imm5);

  // Write data to register
  R[rd] = reg_data;

  // Write value to APSR (status register)
  APSR.N = extract32_(reg_data, 31);
  APSR.Z = (reg_data == 0) ? 1 : 0;
  APSR.C = carry_out;
  APSR.V = APSR.V;
}

// Logical Shift Right (Immediate) Instruction
void lsr_imm(uint16_t inst)
{
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t reg_data;
  uint32_t carry_out;

  // Read data from register
  reg_data = R[rm];

  // Performs shifting operation
  reg_data = (reg_data >> (imm5-1));
  carry_out = extract32_(reg_data, 0);
  reg_data = (reg_data >> (1));

  // Write data to register
  R[rd] = reg_data;

  // Write value to APSR (status register)
  APSR.N = extract32_(reg_data, 31);
  APSR.Z = (reg_data == 0) ? 1 : 0;
  APSR.C = carry_out;
  APSR.V = APSR.V;
}

// Arithmetic Shift Right (Immediate) Instruction
void asr_imm(uint16_t inst)
{
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t reg_data;
  uint32_t carry_out;

  // Read data from register
  reg_data = R[rm];

  // Performs shifting operation
  reg_data = (reg_data >> (imm5-1));
  carry_out = extract32_(reg_data, 0);
  reg_data = (reg_data >> (1));
  reg_data = sign_extend(reg_data, (32-(imm5)));

  // Write data to register
  R[rd] = reg_data;

  // Write value to APSR (status register)
  APSR.N = extract32_(reg_data, 31);
  APSR.Z = (reg_data == 0) ? 1 : 0;
  APSR.C = carry_out;
  APSR.V = APSR.V;
}

// Add Register Instruction
void add_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  // Unsigned data variable
  uint32_t u_rm_data;
  uint32_t u_rn_data;
  uint32_t unsigned_sum;
  // Signed data variable
  int32_t s_rm_data;
  int32_t s_rn_data;
  int32_t signed_sum;

  // Read data from register
  // Unsigned data
  u_rm_data = R[rm];
  u_rn_data = R[rn];
  // Signed data
  s_rm_data = R[rm];
  s_rn_data = R[rn];

  // Add operation
  unsigned_sum = u_rm_data + u_rn_data; // Unsigned add
  signed_sum = s_rm_data + s_rn_data; // Signed add

  // Write data to register
  R[rd] = unsigned_sum;

  // Write value to APSR (status register)
  APSR.N = extract32_(unsigned_sum, 31);
  APSR.Z = (unsigned_sum == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Sub Register Instruction
void sub_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  // Unsigned data
  rm_data = R[rm];
  rn_data = R[rn];

  // Add operation
  result = rn_data + ~(rm_data) + 1; // Two's complement substraction

  // Write data to register
  R[rd] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Add 3-bit Immediate Instruction
void add_imm_3(uint16_t inst)
{
  // Declare local variables
  uint32_t imm3 = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  // Unsigned data variable
  uint32_t u_rn_data;
  uint32_t unsigned_sum;
  // Signed data variable
  int32_t s_rn_data;
  int32_t signed_sum;

  // Read data from register
  // Unsigned data
  u_rn_data = R[rn];
  // Signed data
  s_rn_data = R[rn];

  // Add operation
  unsigned_sum = u_rn_data + imm3; // Unsigned add
  signed_sum = s_rn_data + (int32_t)imm3; // Signed add

  // Write data to register
  R[rd] = unsigned_sum;

  // Write value to APSR (status register)
  APSR.N = extract32_(unsigned_sum, 31);
  APSR.Z = (unsigned_sum == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Sub 3-bit Immediate Instruction
void sub_imm_3(uint16_t inst)
{
  // Declare local variables
  uint32_t imm3 = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rn_data = R[rn];

  // Add operation
  result = rn_data + ~(imm3) + 1; // Two's complement substraction

  // Write data to register
  R[rd] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Move Immediate Operation
void move_imm(uint16_t inst)
{
  // Declare local variables
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t rd = zeroExtend32(INST(10, 8));

  // Write value to register
  R[rd] = imm8;

  // Write value to APSR (status register)
  APSR.N = extract32_(imm8, 31);
  APSR.Z = (imm8 == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Compare Immediate Operation
void comp_imm(uint16_t inst)
{
  // Declare local variables
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t rn = zeroExtend32(INST(10, 8));
  uint32_t rn_data;
  uint32_t result;

  // Read value from register
  rn_data = R[rn];

  // Perform substraction
  result = rn_data + ~(imm8) + 1;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Add 8-bit Immediate Instruction
void add_imm_8(uint16_t inst)
{
  // Declare local variables
  uint32_t rdn = zeroExtend32(INST(10, 8));
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  // Unsigned data variable
  uint32_t u_rn_data;
  uint32_t unsigned_sum;
  // Signed data variable
  int32_t s_rn_data;
  int32_t signed_sum;

  // Read data from register
  // Unsigned data
  u_rn_data = R[rdn];
  // Signed data
  s_rn_data = R[rdn];

  // Add operation
  unsigned_sum = u_rn_data + imm8; // Unsigned add
  signed_sum = s_rn_data + (int32_t)imm8; // Signed add

  // Write data to register
  R[rdn] = unsigned_sum;

  // Write value to APSR (status register)
  APSR.N = extract32_(unsigned_sum, 31);
  APSR.Z = (unsigned_sum == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Sub 8-bit Immediate Instruction
void sub_imm_8(uint16_t inst)
{
  // Declare local variables
  uint32_t rdn = zeroExtend32(INST(10, 8));
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rn_data = R[rdn];

  // Add operation
  result = rn_data + ~(imm8) + 1; // Two's complement substraction

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                       Define Function for Data Processing Instruction                       //
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
//                   Define Function for Unconditional Branch Instruction                      //
/////////////////////////////////////////////////////////////////////////////////////////////////
// Unconditional Branch Instruction
void b_unconditional(uint16_t inst)
{
  uint32_t imm11 = INST(10, 0);
  uint32_t address;

  address = PC + signExtend32((imm11 << 1), 12);
  branch = 1;
  PC = address & 0xFFFFFFFE;
}

// Branch with Link Instruction
void bl(uint32_t inst)
{
  uint32_t S = INST32_(10 + 16);
  uint32_t imm10 = INST32(9 + 16, 0 + 16);
  uint32_t J1 = INST32_(13);
  uint32_t J2 = INST32_(11);
  uint32_t imm11 = INST32(10, 0);
  uint32_t I1, I2, imm32, address;
  
  I1 = !(J1 ^ S);
  I2 = !(J2 ^ S);
  imm32 = sign_extend((S << 24) | (I1 << 23) | (I2 << 22) | (imm10 << 12) | (imm11 << 1), 25);

  LR = PC | 0x00000001;

  address = PC + imm32;
  branch = 1;
  PC = address & 0xFFFFFFFE;
}

