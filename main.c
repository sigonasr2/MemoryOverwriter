#include <stdio.h>
#include <sys/uio.h>

unsigned long strToLong(char*str) {
    int counter=0;
    char c;
    unsigned long val=0;
    while ((c=str[counter++])!='\0') {
        val*=10;
        val+=c-'0';
    }
    return val;
}

int main(int argc,char**argv) {
    unsigned int pid;
    unsigned long addr;
    unsigned long val;
    if (argc<3) {
        printf("3 arguments required! Only %d specified.",argc);
    } else {
        for (int i=1;i<argc;i++) {
            printf("\nArg %d: %lu",i+1,strToLong(argv[i]));
        }
    }
    printf("\nHello World!");
}