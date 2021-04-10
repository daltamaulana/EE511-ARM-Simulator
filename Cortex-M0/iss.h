/*********************************************************
 *                                                       *
 *  EE511 Project 1                                      *
 *                                                       *
 *  C simulator for Cortex-M0                            *
 *                                                       *
 *********************************************************/

#ifndef ISS_H
#define ISS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


// Registers
uint32_t R[16];

struct APSR {
  int N;
  int Z;
  int C;
  int V;
} APSR;


#define SP R[13]
#define LR R[14]
#define PC R[15]

#define MEM_SIZE  0x4000000
uint8_t *mem;


// BRANCH should be set to 1 whenever branch occurs
int branch;
//instruction address for EXE pipeline stage(PC-4)
uint32_t EXE_PC;

uint16_t fetch(void);
void process(uint16_t inst);
void updatePC(void);

uint32_t extract32(uint32_t data, int end, int start);
uint32_t extract32_(uint32_t data, int pos);
uint16_t extract16(uint16_t data, int end, int start);
uint16_t extract16_(uint16_t data, int pos);
uint32_t sign_extend(uint32_t a, int length);

/* Shorthand for extracting bits in inst. */
#define INST(x, y) extract16(inst, x, y)
#define INST_(x) extract16_(inst, x)

#define INST32(x, y) extract32(inst, x, y)
#define INST32_(x) extract32_(inst, x)

#define MSB(x) extract32_(x, 31)

// Sign extension
#define zeroExtend32(x) (x)
#define signExtend32(x, n) (((((x) >> ((n)-1)) & 0x1) != 0) ? (~((unsigned int)0) << (n)) | (x) : (x))

/* Memory access functions. */
uint32_t read_word(uint32_t addr);
uint32_t read_halfword(uint32_t addr);
uint32_t read_byte(uint32_t addr);

void write_word(uint32_t addr, uint32_t value);
void write_halfword(uint32_t addr, uint32_t value);
void write_byte(uint32_t addr, uint32_t value);

/////////////////////////////////////////////////////////////////////////////////////////////////
//                                     Function Declaration                                    //
/////////////////////////////////////////////////////////////////////////////////////////////////
void imm_inst(uint16_t inst);
void data_proc_inst(uint16_t inst);
void spec_data_inst(uint16_t inst);
void load_store_inst(uint16_t inst);
void load_imm_word_inst(uint16_t inst);
void load_imm_half_inst(uint16_t inst);
void misc_inst(uint16_t inst);
void load_store_mul_inst(uint16_t inst);
void cond_branch_inst(uint16_t inst);

void lsl_imm(uint16_t inst);
void lsr_imm(uint16_t inst);
void asr_imm(uint16_t inst);
void add_reg(uint16_t inst);
void sub_reg(uint16_t inst);
void add_imm_3(uint16_t inst);
void sub_imm_3(uint16_t inst);
void move_imm(uint16_t inst);
void comp_imm(uint16_t inst);
void add_imm_8(uint16_t inst);
void sub_imm_8(uint16_t inst);

void and_reg(uint16_t inst);
void xor_reg(uint16_t inst);
void lsl_reg(uint16_t inst);
void lsr_reg(uint16_t inst);
void asr_reg(uint16_t inst);
void add_carry(uint16_t inst);
void sub_carry(uint16_t inst);
void ror_reg(uint16_t inst);
void tst_and(uint16_t inst);
void rsb_imm(uint16_t inst);
void cmp_reg(uint16_t inst);
void orr_reg(uint16_t inst);
void mul_reg(uint16_t inst);
void bic_reg(uint16_t inst);
void mvn_reg(uint16_t inst);

void add_reg(uint16_t inst);
void comp_reg_2(uint16_t inst);
void mov_reg(uint16_t inst);
void b_exchange(uint16_t inst);
void bl_exchange(uint16_t inst);

void ld_pool(uint16_t inst);

void str_reg(uint16_t inst);
void strh_reg(uint16_t inst);
void strb_reg(uint16_t inst);
void ldsrb_reg(uint16_t inst);
void ldr_reg(uint16_t inst);
void ldrh_reg(uint16_t inst);
void ldrb_reg(uint16_t inst);
void ldsrb_reg(uint16_t inst);
void str_imm(uint16_t inst);
void ldr_imm(uint16_t inst);
void strb_imm(uint16_t inst);
void ldrb_imm(uint16_t inst);
void strh_imm(uint16_t inst);
void ldrh_imm(uint16_t inst);
void str_sp_imm(uint16_t inst);
void ldr_sp_imm(uint16_t inst);

void adr_imm(uint16_t inst);
void add_sp_imm(uint16_t inst);

void add_sp_imm_2(uint16_t inst);
void sub_sp_imm(uint16_t inst);
void sxth_reg(uint16_t inst);
void sxtb_reg(uint16_t inst);
void uxth_reg(uint16_t inst);
void uxtb_reg(uint16_t inst);
void push_reg(uint16_t inst);
void rev_reg(uint16_t inst);
void rev16_reg(uint16_t inst);
void revsh_reg(uint16_t inst);
void pop_reg(uint16_t inst);

void store_mul(uint16_t inst);
void load_mul(uint16_t inst);

void b_conditional(uint16_t inst);

uint32_t bit_count(uint32_t bit_string, uint32_t bit_length);

#endif
