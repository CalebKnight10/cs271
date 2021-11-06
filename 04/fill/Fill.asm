// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

//Caleb Knight

(LOOP)
//Set the screen starting in R0
  @SCREEN
  D=A
  @0
  M=D

//Find if a key is pressed
(KBCHK)
  @KBD
  D=M
//If it is, go to FILL_BLACK
  @FILL_BLACK
  D;JGT
//Else, go to FILL_WHITE
  @FILL_WHITE
  D;JMP

//Define FILL_BLACK
(FILL_BLACK)
  //Indicate that black is being used and fill screen with -1
  @R0
  M=-1
  //FILL Black
  @FILL
  0;JMP
//Define FILL_WHITE
(FILL_WHITE)
  //Indicate that white is being used and fill screen with 0
  @R0
  M=0
  //FILL White
  @FILL
  0;JMP

//Check FILL and decide what to do based off of D
(FILL)
  //Checks R0(D) to see if it is gonna be Black or White
  @R0
  D=M

  //Access the address of the start pixel
  //Places D (Black or White) into M (represents the address A)
  @R0
  A=M
  M=D

  //Increment to the next memory address
  @R0
  D=M+1
  M=D

  //
  @R0
  M=M+1
  A=M

  //Run Fill again
  //If address == 0 then exit because entire screen is black
  @FILL
  D;JGT

//Infitely Loop This
  @LOOP
  0;JMP
