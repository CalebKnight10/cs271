//Test file to test various errors
//Caleb Knight

// EXIT_INCORRECT_ARGUMENTS
  // ./main gives wrong number of arguments (no file specified)

// EXIT_CANNOT_OPEN_FILE
  //Provide file not in directory

// EXIT_TOO_MANY_INSTRUCTIONS
  //if greater than int16_max (32767)
// EXIT_INVALID_LABEL
@0
D=M
@INFINITE_LOOP
D;JLE
@counter
M=D
@SCREEN
D=A
@address
M=D
(LOOP)

// EXIT_SYMBOL_ALREADY_EXISTS

// EXIT_INVALID_A_INSTRUCTION
@numb3ers
D=A
@2
D=D+M
@1
M=D
