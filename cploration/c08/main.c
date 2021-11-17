#include "parser.h"
#include "error.h"

int main(int argc, const char *argv[]) {
  if (argc != 2) {
    //incorrect number of arguments
    exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
  }
  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    perror("Unable to open file!");
    exit(EXIT_FAILURE);
  } 

  parse(file);
  fclose(file);
}