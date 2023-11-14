#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int main (int argc, char* argv[])
{
char* filepath = “/Users/3PO/Documents/Programming/YourDirHere/”;
int returnval;
char * strvar=””;
printf(“\nProvide a name of the file or directory:\n”);
fgets (strvar, 100, stdin);
const char* n = “\n”;
strtok(strvar, n);
// Combine 2 Chars
char * finalpath = (char *) malloc(1 + strlen(filepath)+ strlen(strvar) );
strcpy(finalpath, filepath);
strcat(finalpath, strvar);
filepath = finalpath;
// Check file existence
returnval = access (filepath, F_OK);
if (returnval == 0)
printf (“\n %s exists\n”, strvar);
else
{
if (errno == ENOENT)
printf (“%s No such file or directory.\n”, filepath);
else if (errno == EACCES)
printf (“%s Permission denied.\n”, filepath);
}
// Check read access
returnval = 0;
returnval = access (filepath, R_OK);
if (returnval == 0)
printf (“\n %s has Read permissions.\n”, filepath);
else
{
if (errno == ENOENT)
printf (“%s No such file or directory.\n”, filepath);
else if (errno == EACCES)
printf (“%s Read Permission denied.\n”, filepath);
}
// Check write access
returnval = 0;
returnval = access (filepath, W_OK);
if (returnval == 0)
printf (“\n %s has Write permissions.!\n”, filepath);
else
{
if (errno == ENOENT)
printf (“%s No such file or directory.\n”, filepath);
else if (errno == EACCES)
printf (“%s Write Permission denied.\n”, filepath);
}
// Check execute access
returnval = 0;
returnval = access (filepath, X_OK);
if (returnval == 0)
printf (“\n %s has Execute permissions.!\n”, filepath);
else
{
if (errno == ENOENT)
printf (“%s No such file or directory.\n”, filepath);
else if (errno == EACCES)
printf (“%s Execute Permission denied.\n”, filepath);
}
