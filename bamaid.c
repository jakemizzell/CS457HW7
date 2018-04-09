#include <stdio.h>
#include <stdlib.h>

void getDB(char*,FILE*,int);
void getKeys(char*,char*,FILE*,int);

int main(void) {
    int flag = 0;
    FILE *fp;
    fp = fopen("HW7in.txt", "r");
    //error message
    if (fp == NULL) {
        printf("Error in opening file.\n");
        exit(1);
    }
    //set up 3 arrays to hold stuff
    char db[15] = {0};
    char key[10] = {0};
    char candidate[10] = {0};
    int c = getc(fp);
    while(c != EOF) {
        if (flag == 0) {
            getDB(db, fp, c);
            c = getc(fp);
            getKeys(key, candidate, fp, c);
            flag = 1;
            c = getc(fp);
        }
        if(c == 'x')
            break;
        printf("%c",c);
        c = getc(fp);
    }
    //print out the stuff
    fclose(fp);
    printf("\n");
    return 0;
}

void getDB(char *db, FILE *fp, int c) {
    for (int i = 0; c != EOF; i++) {
        if(c == ' ') {
            printf("DB: ");
            for(i = 0; db[i] != 0; i++)
                printf("%c",db[i]);
            return;
        }
        db[i] = c;
        c = getc(fp);
    }
}

void getKeys(char *key, char *candidate, FILE *fp, int c) {
    int flag = 0;
    for (int i = 0; c != EOF; i++) {
        //thats the end of line
        if(c == ';') {
            printf("\nCandidate: ");
            for(i = 0; i < 3; i++)
                printf("%c",candidate[i]);
            return;
        }
        //if there's a space there is now a candidate key to get
        if(c == ' ') {
            printf("\nKey: ");
            for(i = 0; key[i] != 0; i++)
                printf("%c",key[i]);
            flag = 1;
            i = 0;
            c = getc(fp);
        }
        if (flag == 0)
            key[i] = c;
        if(flag == 1)
            candidate[i] = c;
        c = getc(fp);
    }
}
