// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.


// Caleb Knight

//R2=0
  @R2
  M=0

//Load R0 and set value to Data
  @R0
  D=M
  @INFINITE_LOOP
  D;JEQ //If R0 == 0 Jump out

//Load R1 and set value to Data
  @R1
  D=M
  @INFINITE_LOOP
  D;JEQ //If R1 == 0 Jump out

//Loop through adding R1 Data to R2
(LOOP)
  @R1
  D=M
  @R2
  M=D+M
  @R0
  D=M-1
  M=D
  @LOOP
  D;JGT
(INFINITE_LOOP)
  @INFINITE_LOOP
  0;JMP
