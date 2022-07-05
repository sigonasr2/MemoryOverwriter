#include <stdio.h>
#include <sys/uio.h>

unsigned long strToLong(char*str) {
    int counter=0;
    char c;
    unsigned long val=0;
    int base=10;
    while ((c=str[counter++])!='\0') {
        if (counter==1&&c=='0') {
            base=8;
            continue;
        } else
        if (counter==2&&c=='x') {
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
    unsigned int pid;
    unsigned long addr;
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
            printf("\nAddress: %lu",addr);
            printf("\nValue: %lu",val);
            printf("\nInterval: %lu",interval);
    }
}