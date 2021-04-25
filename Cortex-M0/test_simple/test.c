/*********************************************************
 *                                                       *
 *  EE511 Project 1                                      *
 *                                                       *
 *  C test code                                          *
 *                                                       *
 *********************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
  // Declare variable
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
  uint32_t f;

  /////////////////////////////////////////////////////////////////////////////////////////////////
  //                                Addition Instruction Test                                    //
  /////////////////////////////////////////////////////////////////////////////////////////////////
  // Assign value to variable
  a = 0x7FFFFFFF;
  b = 0x00000002;
  c = 0xEFFFFFFF;
  d = 0x10000001;
  // Load value to register
  asm volatile("ADD: mov r4, %[value]" :: [value] "r" (a));
  asm volatile("mov r5, %[value]" :: [value] "r" (b));
  asm volatile("add r4, r4, r5"); // Overflow test
  
  asm volatile("mov r4, %[value]" :: [value] "r" (c));
  asm volatile("mov r5, %[value]" :: [value] "r" (d));
  asm volatile("add r4, r4, r5");
  asm volatile("b SUB");
  /////////////////////////////////////////////////////////////////////////////////////////////////
  //                                Substraction Instruction Test                                //
  /////////////////////////////////////////////////////////////////////////////////////////////////
  // Assign value to variable
  a = 0x23;
  b = 0x25;
  c = 0x25;
  d = 0x23;
  // Load value to register
  asm volatile("SUB: mov r4, %[value]" :: [value] "r" (a));
  asm volatile("mov r5, %[value]" :: [value] "r" (b));
  asm volatile("sub r4, r4, r5");

  asm volatile("mov r4, %[value]" :: [value] "r" (c));
  asm volatile("mov r5, %[value]" :: [value] "r" (d));
  asm volatile("sub r4, r4, r5");

  /////////////////////////////////////////////////////////////////////////////////////////////////
  //                                   Branch Instruction Test                                   //
  /////////////////////////////////////////////////////////////////////////////////////////////////
  // Assign value to variable
  a = 0x0;
  b = 0x15;
  c = 0x15;
  d = 0x20;
  e = 0x10;
  f = 0xEFFFFFFF;

  // Load value to register
  asm volatile("SET: mov r0, %[value]" :: [value] "r" (a));
  asm volatile("mov r2, %[value]" :: [value] "r" (f));
  asm volatile("mov r4, %[value]" :: [value] "r" (b));
  asm volatile("mov r5, %[value]" :: [value] "r" (c));
  asm volatile("mov r6, %[value]" :: [value] "r" (d));
  asm volatile("mov r7, %[value]" :: [value] "r" (e));
  asm volatile("b EQ");

  // Branching logic 
  // Branch if equal
  asm volatile (
    "EQ: add r3, r0, #1\n\t"
    "cmp r4, r5\n\t"
    "beq NE\n\t"
    "add r0, #1"
  );
  // Branch if not equal
  asm volatile (
    "NE: add r3, r0, #1\n\t"
    "cmp r4, r6\n\t"
    "bne CS\n\t"
    "add r0, #1"
  );
  // Branch if carry set
  asm volatile (
    "CS: add r3, r0, #1\n\t"
    "sub r1, r4, r7\n\t"
    "bcs CC\n\t"
    "add r0, #1"
  );
  // Branch if carry clear
  asm volatile (
    "CC: add r3, r0, #1\n\t"
    "add r1, r4, r5\n\t"
    "bcc MI\n\t"
    "add r0, #1"
  );
  // Branch if minus negative
  asm volatile (
    "MI: add r3, r0, #1\n\t"
    "sub r1, r4, r6\n\t"
    "bmi PL\n\t"
    "add r0, #1"
  );
  // Branch if positive
  asm volatile (
    "PL: add r3, r0, #1\n\t"
    "sub r1, r6, r4\n\t"
    "bpl VS\n\t"
    "add r0, #1"
  );
  // Branch if overflow set
  asm volatile (
    "VS: add r3, r0, #1\n\t"
    "sub r1, r4, r6\n\t"
    "bvs VC\n\t"
    "add r0, #1"
  );
  // Branch if overflow clear
  asm volatile (
    "VC: add r3, r0, #1\n\t"
    "sub r1, r6, r4\n\t"
    "bvc HI\n\t"
    "add r0, #1"
  );
  // Branch if unsigned higher
  asm volatile (
    "HI: add r3, r0, #1\n\t"
    "sub r1, r4, r7\n\t"
    "bhi LS\n\t"
    "add r0, #1"
  );
  // Branch if unsigned lower or same
  asm volatile (
    "LS: add r3, r0, #1\n\t"
    "sub r1, r4, r4\n\t"
    "bls GE\n\t"
    "add r0, #1"
  );
  // Branch if signed greater or equal
  asm volatile (
    "GE: add r3, r0, #1\n\t"
    "sub r1, r4, r4\n\t"
    "bge LT\n\t"
    "add r0, #1"
  );
  // Branch if signed less than
  asm volatile (
    "LT: add r3, r0, #1\n\t"
    "sub r1, r2, r5\n\t"
    "blt GT\n\t"
    "add r0, #1"
  );
  // Branch if signed greater
  asm volatile (
    "GT: add r3, r0, #1\n\t"
    "sub r1, r6, r4\n\t"
    "bgt LE\n\t"
    "add r0, #1"
  );
  // Branch if signed less than or equal
  asm volatile (
    "LE: add r3, r0, #1\n\t"
    "sub r1, r4, r4\n\t"
    "ble END\n\t"
    "add r0, #1"
  );
  // End branch testing
  asm volatile (
    "END: mov r4, #0\n\t"
    "mov r4, #0\n\t"
    "mov r5, #0\n\t"
    "mov r6, #0\n\t"
    "mov r7, #0\n\t"
  );

  // Return value
  return 0;
}

