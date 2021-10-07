// Caleb Knight 
// Cploration 02

#include <stdio.h> 
#include <string.h>
#define MAX_LIMIT 100

int main() {
/** WARMUP **/
// declare a string with value
char hello[] = "Hello";
// declare an empty string
char name[MAX_LIMIT];
// prompt user
printf("What is your name? ");
// read in a string from user and save in variable
// [^\n] means to discard the newline character
scanf("%[^\n]s", name);
// print out "hello <name>"
printf("%s %s!\n\n", hello, name);

/** Exercise 1 **/ 
// new empty string
char welcome[MAX_LIMIT];
// copy hello variable to welcome
strcpy(welcome, hello);
// concat " " onto welcome
strcat(welcome, " ");
// concat name onto welcome
strcat(welcome, name);
// print welcome with a new line
printf("%s!\n", welcome);

/** Exercise 2 **/ 
int len;
// determine len of name
len = strlen(name);
// print char length of name 
printf("Your name is %d characters long. \n\n", len);

/** Exercise 3 **/ 
// String to compare to 
char prof[8] = {'P','a','t','r','i','c','k','\0'};
// the result of the strign comparison
int result;
// assigning the comparison value to result
result = strcmp(name, prof);
// print result
// printf("%d\n", result);
// decides if the name comes before the professor
if (result < 0)
{
	// prints the name before the professor
	printf("%s is before %s. \n", name, prof);
}
// decides if the name comes after the professor
else if (result > 0)
{
	printf("%s is after %s. \n", name, prof);
}
else if (result == 0)
{
	printf("%s is %s. \n", name, prof);
}
}
