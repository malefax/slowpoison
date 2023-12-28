#include <stdio.h>
int main(int argc, char*argv[]) {
char raw_shell[] =  "\x41\x41\x41\x41\x41\x41";
int i;
char key = '!';
printf("encrypted buffer\n");
for ( i = 0; i < sizeof(raw_shell); i++)
{
    printf("\\x%02x", raw_shell[i]^key);//xor encryption 
}
// copy the encrypted shellcode to the shellcode variable in new.c file

}