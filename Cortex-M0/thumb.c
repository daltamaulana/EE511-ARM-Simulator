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

  // Sub operation
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

  // Sub operation
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
// Bitwise AND Instruction
void and_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // AND operation
  result = rm_data & rn_data;

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Bitwise XOR Instruction
void xor_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // XOR operation
  result = rm_data ^ rn_data;

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Logical Shift Left (Register) Instruction
void lsl_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;
  uint32_t carry_out;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Performs shifting operation
  carry_out = extract32_(rn_data, 31);
  result = (rn_data << rm_data);

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Logical Shift Right (Register) Instruction
void lsr_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;
  uint32_t carry_out;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Performs shifting operation
  result = (rn_data >> (rm_data-1));
  carry_out = extract32_(result, 0);
  result = (result >> (1));

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Arithmetic Shift Right (Register) Instruction
void asr_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;
  uint32_t carry_out;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Performs shifting operation
  result = (rn_data >> (rm_data-1));
  carry_out = extract32_(result, 0);
  result = (result >> (1));
  result = sign_extend(result, (32-(rm_data)));

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Add with Carry Instruction
void add_carry(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
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
  u_rn_data = R[rdn];
  // Signed data
  s_rm_data = R[rm];
  s_rn_data = R[rdn];

  // Add operation
  unsigned_sum = u_rm_data + u_rn_data + APSR.C; // Unsigned add
  signed_sum = s_rm_data + s_rn_data + APSR.C; // Signed add

  // Write data to register
  R[rdn] = unsigned_sum;

  // Write value to APSR (status register)
  APSR.N = extract32_(unsigned_sum, 31);
  APSR.Z = (unsigned_sum == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Add with Carry Instruction
void sub_carry(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Sub operation
  result = rn_data + ~(rm_data) + APSR.C; // Two's complement substraction

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Rotate Right (Register) Instruction
void ror_reg(uint16_t inst)
{
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t temp;
  uint32_t result;
  uint32_t carry_out;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Rotate operation
  temp = extract32(rn_data, 0, (rm_data-1));
  temp = (temp << (32-rm_data));
  result = (rn_data >> rm_data);
  result = result ^ temp;
  carry_out = extract32_(result, 31);

  // Write data to register
  R[rdn] = result;
}

// Test Logical AND (Register) Instruction
void tst_and(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Logical AND Operation
  result = rm_data & rn_data;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Reverse Substract (Register) Instruction
void rsb_imm(uint16_t inst) {
  // Declare local variables
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rn_data;
  uint32_t imm32 = 0;
  uint32_t result;

  // Read data from register
  rn_data = R[rn];

  // Sub operation
  result = ~(rn_data) + imm32 + 1; // Two's complement substraction

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Compare Register Instruction
void cmp_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Sub operation
  result = rn_data + ~(rm_data) + 1; // Two's complement substraction

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Compare Negative Register Instruction
void cmn_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Sub operation
  result = rn_data + rm_data; // Two's complement addition

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Logical OR (Register) Instruction
void orr_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Bitwise OR operation
  result = rn_data | rm_data;

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V; //NOTE: Fix status register
}

// Multiply (Register) Instruction
void mul_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rdm = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rdm];
  rn_data = R[rn];

  // Multiplication operation
  result = rn_data * rm_data;

  // Write data to register
  R[rdm] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C;
  APSR.V = APSR.V;
}

// Bit Clear (Register) Instruction
void bic_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rdn = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rdn];

  // Bitwise AND operation
  result = rn_data & ~(rm_data);

  // Write data to register
  R[rdn] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V;
}

// Bitwise NOT (Register) Instruction
void mvn_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];

  // Bitwise AND operation
  result = ~(rm_data);

  // Write data to register
  R[rd] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                   Define Function for Special Data and Branch Instruction                   //
/////////////////////////////////////////////////////////////////////////////////////////////////
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

// Move (Register) Instruction
void mov_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t result;

  // Read data from register
  rm_data = R[rm];

  // Bitwise AND operation
  result = rm_data;

  // Write data to register
  R[rd] = result;

  // Write value to APSR (status register)
  APSR.N = extract32_(result, 31);
  APSR.Z = (result == 0) ? 1 : 0;
  APSR.C = APSR.C; //NOTE: Fix status register
  APSR.V = APSR.V;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                      Define Function for Load and Store Instruction                         //
/////////////////////////////////////////////////////////////////////////////////////////////////
// Store Word (Register) Instruction
void str_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];
  rt_data = R[rt];

  // Bitwise AND operation
  addr_offset = rn_data + rm_data;

  // Write data to memory
  write_word(addr_offset, rt_data);
}

// Store Halfword (Register) Instruction
void strh_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];
  rt_data = extract32(R[rt], 0, 15); // Get Halfword from bit 0 - bit 15

  // Bitwise AND operation
  addr_offset = rn_data + rm_data;

  // Write data to memory
  write_halfword(addr_offset, rt_data);
}

// Store Byte (Register) Instruction
void strb_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];
  rt_data = extract32(R[rt], 0, 8); // Get Byte from bit 0 - bit 8

  // Bitwise AND operation
  addr_offset = rn_data + rm_data;

  // Write data to memory
  write_byte(addr_offset, rt_data);
}

// Load Signed Byte (Register) Instruction
void ldsrb_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + rm_data;

  // Read data from memory
  rt_data = read_byte(addr_offset);
  rt_data = sign_extend(rt_data, 8);

  // Write data to register
  R[rt] = rt_data;
}

// Load Word (Register) Instruction
void ldr_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + rm_data;

  // Read data from memory
  rt_data = read_word(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

// Load Halfword (Register) Instruction
void ldrh_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + rm_data;

  // Read data from memory
  rt_data = read_halfword(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

// Load Byte (Register) Instruction
void ldrb_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + rm_data;

  // Read data from memory
  rt_data = read_byte(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

// Load Signed Halfword (Register) Instruction
void ldsrb_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(8, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rm_data = R[rm];
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + rm_data;

  // Read data from memory
  rt_data = read_halfword(addr_offset);
  rt_data = sign_extend(rt_data, 16);

  // Write data to register
  R[rt] = rt_data;
}

// Store Word (Immediate) Instruction
void str_imm(uint16_t inst) {
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = R[rn];
  rt_data = R[rt];

  // Bitwise AND operation
  addr_offset = rn_data + imm5;

  // Write data to memory
  write_word(addr_offset, rt_data);
}

// Load Word (Immediate) Instruction
void ldr_imm(uint16_t inst) {
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + imm5;

  // Read data from memory
  rt_data = read_word(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

// Store Byte (Immediate) Instruction
void strb_imm(uint16_t inst) {
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = R[rn];
  rt_data = extract32(R[rt], 0, 8); // Get Byte from bit 0 - bit 8

  // Bitwise AND operation
  addr_offset = rn_data + imm5;

  // Write data to memory
  write_byte(addr_offset, rt_data);
}

// Load Word (Immediate) Instruction
void ldrb_imm(uint16_t inst) {
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + imm5;

  // Read data from memory
  rt_data = read_byte(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

// Store Halfword (Immediate) Instruction
void strh_imm(uint16_t inst) {
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = R[rn];
  rt_data = extract32(R[rt], 0, 16); // Get Byte from bit 0 - bit 16

  // Bitwise AND operation
  addr_offset = rn_data + imm5;

  // Write data to memory
  write_halfword(addr_offset, rt_data);
}

// Load Halfword (Immediate) Instruction
void ldrh_imm(uint16_t inst) {
  // Declare local variables
  uint32_t imm5 = zeroExtend32(INST(10, 6));
  uint32_t rn = zeroExtend32(INST(5, 3));
  uint32_t rt = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = R[rn];

  // Calculate address offset
  addr_offset = rn_data + imm5;

  // Read data from memory
  rt_data = read_halfword(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

// Store Word Stack Pointer (Immediate) Instruction
void str_sp_imm(uint16_t inst) {
  // Declare local variables
  uint32_t rt = zeroExtend32(INST(10, 8));
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = SP; // Get base pointer from stack pointer R[13]
  rt_data = R[rt];

  // Bitwise AND operation
  addr_offset = rn_data + imm8;

  // Write data to memory
  write_word(addr_offset, rt_data);
}

// Load Word Stack Pointer (Immediate) Instruction
void ldr_sp_imm(uint16_t inst) {
  // Declare local variables
  uint32_t rt = zeroExtend32(INST(10, 8));
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t rn_data;
  uint32_t rt_data;
  uint32_t addr_offset;

  // Read data from register
  rn_data = SP; // Get base pointer from stack pointer R[13]

  // Calculate address offset
  addr_offset = rn_data + imm8;

  // Read data from memory
  rt_data = read_word(addr_offset);

  // Write data to register
  R[rt] = rt_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                    Define Function for SP and PC Generator Instruction                      //
/////////////////////////////////////////////////////////////////////////////////////////////////
// Offset PC value with Immediate Instruction
void adr_imm(uint16_t inst) {
  // Declare local variables
  uint32_t rd = zeroExtend32(INST(10, 8));
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t result;

  // Calculate PC offset
  result = PC + imm8;

  // Write data to register
  R[rd] = result;
}

// Offset SP value with Immediate Instruction
void add_sp_imm(uint16_t inst) {
  // Declare local variables
  uint32_t rd = zeroExtend32(INST(10, 8));
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t result;

  // Calculate PC offset
  result = SP + imm8;

  // Write data to register
  R[rd] = result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                   Define Function for Miscellaneous 16-bit Instruction                      //
/////////////////////////////////////////////////////////////////////////////////////////////////
// Signed Extend Halfword Instruction
void sxth_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rd_data;

  // Read data from register
  rm_data = extract32(R[rm], 0, 15);

  // Sign extend data
  rd_data = sign_extend(rm_data, 15);

  // Write data to register
  R[rd] = rd_data;
}

// Signed Extend Byte Instruction
void sxtb_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rd_data;

  // Read data from register
  rm_data = extract32(R[rm], 0, 7);

  // Sign extend data
  rd_data = sign_extend(rm_data, 7);

  // Write data to register
  R[rd] = rd_data;
}

// Unsigned Extend Halfword Instruction
void uxth_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rd_data;

  // Read data from register
  rm_data = extract32(R[rm], 0, 15);

  // Sign extend data
  rd_data = zeroExtend32(rm_data);

  // Write data to register
  R[rd] = rd_data;
}

// Unsigned Extend Byte Instruction
void uxtb_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data;
  uint32_t rd_data;

  // Read data from register
  rm_data = extract32(R[rm], 0, 7);

  // Sign extend data
  rd_data = zeroExtend32(rm_data);

  // Write data to register
  R[rd] = rd_data;
}

// Push Multiple Register Instruction
void push_reg(uint16_t inst) {
  // Declare local variables
  int i;
  uint32_t mem_addr;
  uint32_t reg_count;
  uint32_t pc_write = zeroExtend32(INST_(8));
  uint32_t reg_list = zeroExtend32(INST(7, 0));

  // Calculate bit count value
  reg_count = (pc_write == 1) ? bit_count(reg_list, 8)+1 : bit_count(reg_list, 8);

  // Calculate memory address
  mem_addr = SP - (4 * reg_count);

  // Store general register value
  for (i=0; i<8; i++) {
    // Check bit
    if (extract32_(reg_list, i) == 1) {
      // Write to memory
      write_word(mem_addr, R[i]);
      // Increment address
      mem_addr += 4;
    }
  }

  // Store link register value
  if (pc_write == 1) {
    // Write to memory
    write_word(mem_addr, R[i]);
  }

  // Update stack pointer
  SP = SP - (4 * reg_count);
}

// Pop Multiple Register Instruction
void pop_reg(uint16_t inst) {
  // Declare local variables
  int i;
  uint32_t mem_addr;
  uint32_t reg_count;
  uint32_t pc_load = zeroExtend32(INST_(8));
  uint32_t reg_list = zeroExtend32(INST(7, 0));

  // Calculate bit count value
  reg_count = (pc_load == 1) ? bit_count(reg_list, 8)+1 : bit_count(reg_list, 8);

  // Calculate memory address
  mem_addr = SP;

  // Loop through register list
  for (i=0; i<8; i++) {
    // Check bit
    if (extract32_(reg_list, i) == 1) {
      // Read from memory
      R[i] = read_word(mem_addr);
      // Increment address
      mem_addr += 4;
    }
  }

  // Check for PC load variable
  if (pc_load == 1) {
    PC = read_word(mem_addr);
  }

  // Update stack pointer
  SP = SP + (4 * reg_count);
}

// Byte Reverse Word Instruction
void rev_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data_0;
  uint32_t rm_data_1;
  uint32_t rm_data_2;
  uint32_t rm_data_3;
  uint32_t result;

  // Read data from register
  rm_data_0 = extract32(R[rm], 0, 7); // First byte
  rm_data_1 = extract32(R[rm], 8, 15); // Second byte
  rm_data_2 = extract32(R[rm], 16, 23); // Third byte
  rm_data_3 = extract32(R[rm], 24, 31); // Fourth byte

  // Reverse byte ordering
  result = (rm_data_0 << 24) | (rm_data_1 << 16) | (rm_data_2 << 8) | (rm_data_3); 

  // Write data to register
  R[rd] = result;
}

// Byte Reverse Packed Halfword Instruction
void rev16_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data_0;
  uint32_t rm_data_1;
  uint32_t rm_data_2;
  uint32_t rm_data_3;
  uint32_t result;

  // Read data from register
  rm_data_0 = extract32(R[rm], 0, 7); // First byte
  rm_data_1 = extract32(R[rm], 8, 15); // Second byte
  rm_data_2 = extract32(R[rm], 16, 23); // Third byte
  rm_data_3 = extract32(R[rm], 24, 31); // Fourth byte

  // Reverse byte ordering
  result = (rm_data_2 << 24) | (rm_data_3 << 16) | (rm_data_0 << 8) | (rm_data_1); 

  // Write data to register
  R[rd] = result;
}

// Byte Reverse Packed Halfword Instruction
void revsh_reg(uint16_t inst) {
  // Declare local variables
  uint32_t rm = zeroExtend32(INST(5, 3));
  uint32_t rd = zeroExtend32(INST(2, 0));
  uint32_t rm_data_0;
  uint32_t rm_data_1;
  uint32_t result;

  // Read data from register
  rm_data_0 = extract32(R[rm], 0, 7); // First byte
  rm_data_0 = sign_extend(rm_data_0, 8); // Sign extend
  rm_data_1 = extract32(R[rm], 8, 15); // Second byte

  // Reverse byte ordering
  result = (rm_data_0 << 24) | (rm_data_1); 

  // Write data to register
  R[rd] = result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                  Define Function for Multiple Store and Load Instruction                    //
/////////////////////////////////////////////////////////////////////////////////////////////////
// Store Multiple Register Instruction
void store_mul(uint16_t inst) {
  // Declare local variables
  int i;
  uint32_t mem_addr;
  uint32_t reg_count;
  uint32_t rn = zeroExtend32(INST(10, 8));
  uint32_t reg_list = zeroExtend32(INST(7, 0));

  // Calculate memory address
  mem_addr = R[rn];

  // Calculate bit count value
  reg_count = bit_count(reg_list, 8);

  // Loop through register list
  for (i=0; i<8; i++) {
    // Check bit
    if (extract32_(reg_list, i) == 1) {
      // Write to memory
      write_word(mem_addr, R[i]);
      // Increment address
      mem_addr += 4;
    }
  }

  // Update memory address in register
  R[rn] = R[rn] + (4 * reg_count);
}

// Load Multiple Register Instruction
void load_mul(uint16_t inst) {
  // Declare local variables
  int i;
  uint32_t wback;
  uint32_t mem_addr;
  uint32_t reg_count;
  uint32_t rn = zeroExtend32(INST(10, 8));
  uint32_t reg_list = zeroExtend32(INST(7, 0));

  // Get write back info
  wback = (R[rn] == 0) ? 1 : 0;

  // Calculate memory address
  mem_addr = R[rn];

  // Calculate bit count value
  reg_count = bit_count(reg_list, 8);

  // Loop through memory
  for (i=0; i<8; i++) {
    R[i] = read_word(mem_addr);
    mem_addr += 4;
  }

  // Check for source register update
  if (wback && (R[rn] == 0)) {
    R[rn] = R[rn] + (4 * reg_count);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//                    Define Function for Conditional Branch Instruction                       //
/////////////////////////////////////////////////////////////////////////////////////////////////
void b_conditional(uint16_t inst) {
  // Declare Local Variables
  uint32_t imm8 = zeroExtend32(INST(7, 0));
  uint32_t imm32;

  // Calculate imm32 value
  imm32 = sign_extend((imm8 << 1), 9);

  // Write new PC value
  PC = PC + imm32;
}

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

/////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Define Helper Function                                    //
/////////////////////////////////////////////////////////////////////////////////////////////////
uint32_t bit_count(uint32_t bit_string, uint32_t bit_length) {
  // Declare local variable
  int i;
  uint32_t temp = 0;
  uint32_t count = 0;

  // Loop through bitstring
  for (i=0; i<bit_length; i++) {
    // Shift data
    temp = (bit_string >> i) & (0x1);
    // Check bit
    if (temp == 1) {
      count++;
    }
  }

  // Return value
  return count;
}
