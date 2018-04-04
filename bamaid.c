#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    fp = fopen("HW7in.txt", "r");
    //error message
    if (fp == NULL) {
        printf("Error in opening file.\n");
        exit(1);
    }
    int c = getc(fp);
    while(c != EOF) {
        printf("%c",c);
        c = getc(fp);
    }
    return 0;
}