#include <stdio.h>
#include <stdlib.h>

void getDB(char*,FILE*,int);
void getKeys(char*,char*,FILE*,int);
int testForm(char*,char*,char*,FILE*,int);
int checkKey(char*,int);

int main(void) {
    int flag = 0;
    int form = 0;
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
        if(c == ';')
            break;
        form = testForm(db,key,candidate,fp,c);
        break;
        printf("%c",c);
        c = getc(fp);
    }
    //print out the stuff
    fclose(fp);
    printf("\n");
    return 0;
}

int testForm(char *db, char *key, char *can, FILE *fp, int c) {
    char *temp[15] = {0};
    int form = 3;
    int flag;
    //eat up past the first paretheses
    c = getc(fp);
    c = getc(fp);
    c = getc(fp);
    printf("%c",c);
    for(int i = 0; key[i] != 0; i++) {
        if(key[i] == c)
            flag = 1;
    }
    //if(flag == 0)

    c =

    //while (c != EOF) {
        //if (c != '(' || c != ')') {

        //}
        //c = getc(fp);
    //}
    return form;
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
            printf("\nKey: ");
            for(i = 0; key[i] != 0; i++)
                printf("%c",key[i]);
            printf("\nCandidate: ");
            for(i = 0; i < 3; i++)
                printf("%c",candidate[i]);
            printf("\n");
            return;
        }
        //if there's a space there is now a candidate key to get
        if(c == ' ') {
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
