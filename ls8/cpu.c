#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

int cpu_ram_read(struct cpu *cpu, int index)
{
  if (index > 256 || index < 0)
  {
    printf("Index out of range. \n");
    return (0);
  }

  printf("%d\n", cpu->ram[index]);
  return cpu->ram[index];
}

void cpu_ram_write(struct cpu *cpu, int element, int index)
{
  if (index > 256 || index < 0)
  {
    printf("Index out of range. \n");
  }

  cpu->ram[index] = element;
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  unsigned char ir;

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    ir = cpu->ram[cpu->pc];
    // ir = cpu->ram[5];
    unsigned char operandA;
    unsigned char operandB;

    if (ir > 128)
    {

      operandA = cpu->ram[cpu->pc + 1];
      operandB = cpu->ram[cpu->pc + 2];
    }
    else if (ir > 64 && ir < 64)
    {
      operandA = cpu->ram[cpu->pc + 1];
    }

    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    switch (ir)
    {
    case LDI:
      cpu->registers[operandA] = operandB;
      cpu->pc += 3;
      break;
    case PRN:
      printf("%d\n", cpu->registers[operandA]);
      cpu->pc += 2;
      break;
    case HLT:
      running = 0;
      break;
    default:
      printf("Unknown instructrion %02 at address %02\n", ir, cpu->pc);
    }
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // cpu = malloc(sizeof(cpu));
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;

  // set each index in registers to 0
  memset(cpu->registers, 0, 8 * sizeof(unsigned char));

  // set each position in ram to 0
  memset(cpu->ram, 0, 256 * sizeof(unsigned char));
}
