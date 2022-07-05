#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

unsigned long long strToLong(char*str) {
    int counter=0;
    char c;
    unsigned long val=0;
    int base=10;
    while ((c=str[counter++])!='\0') {
        if (c=='0'&&val==0&&base==10) {
            base=8;
            continue;
        } else
        if (c=='x'&&val==0&&base==8) {
            base=16;
            continue;
        }
        val*=base;
        if (base==16&&c>='A'&&c<='F') {
            val+=c-'A'+10;
        } else
        if (base==16&&c>='a'&&c<='f') {
            val+=c-'a'+10;
        } else {
            val+=c-'0';
        }
    }
    return val;
}

int main(int argc,char**argv) {
    long unsigned int pid;
    unsigned long long addr;
    unsigned long val;
    unsigned int interval=1000;
    if (argc<4) {
        printf("3 arguments required! %d specified.",argc-1);
        printf(" Format: memovr <pid> <addr> <val> [interval (ms)]");
    } else {
        pid=strToLong(argv[1]);
        addr=strToLong(argv[2]);
        val=strToLong(argv[3]);
        if (argc>=5) {
            interval=strToLong(argv[4]);
        }
        printf("\nPID: %lu",pid);
        printf("\nAddress: 0x%08llx",addr);
        printf("\nValue: %lu",val);
        printf("\nInterval: %d",interval);

        char*proc_mem = malloc(50);
        sprintf(proc_mem,"/proc/%ld/mem",pid);
        int fd_proc_mem=open(proc_mem,O_RDWR);
        if (fd_proc_mem==-1) {
            printf("Could not open %s\n",proc_mem);
            exit(1);
        }
        char*buf=malloc(sizeof(unsigned int));
        lseek(fd_proc_mem,addr,SEEK_SET);
        read(fd_proc_mem,buf,sizeof(unsigned int));
        while (1) {
            sprintf(buf,"%d",(int)val++);
            lseek(fd_proc_mem,addr,SEEK_SET);
            if (write(fd_proc_mem,buf,sizeof(unsigned int))==-1) {
                printf("Error while writing\n");
                exit(1);
            }
            printf("\nWrite %d",(int)val-1);
            sleep(2);
        }

        free(buf);
        free(proc_mem);
    }
}