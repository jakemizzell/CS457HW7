#include <stdio.h>
#include <stdlib.h>

void getDB(char*,FILE*,int);
void getKeys(char*,char*,FILE*,int);
int testForm(char*,char*,char*,FILE*,int);
int checkEqual(char*,char*,int,int);

int main(void) {
    int i;
    int form = 0;
    FILE *fp = fopen("HW7in.txt", "r");
    //error message
    if (fp == NULL) {
        printf("Error in opening input file.\n");
        exit(1);
    }
    FILE *output = fopen("HW7jbmizzell1.txt", "w");
    if (output == NULL) {
        printf("Error in opening output file.\n");
        exit(1);
    }
    //set up 3 arrays to hold stuff
    char db[100] = {0};
    char key[100] = {0};
    char candidate[100] = {0};
    int c = getc(fp);
    while(c != EOF) {
        getDB(db, fp, c);
        c = getc(fp);
        getKeys(key, candidate, fp, c);
        c = getc(fp);
        if(c == ';')
            break;
        form = testForm(db,key,candidate,fp,c);
        for(i = 0; i < sizeof(db); i++) {
            db[i] = 0;
            key[i] = 0;
            candidate[i] = 0;
        }
        if(form == 3) {
            printf("3NF\n");
            fprintf(output,"3NF\n");
        }
        else if (form == 2) {
            printf("2NF\n");
            fprintf(output,"2NF\n");
        }
        else {
            printf("1NF\n");\
            fprintf(output,"1NF\n");
        }
        c = getc(fp);
        //read up anything until the next DB or EOF
        while((c < 64 || c > 91) && c != EOF)
            c = getc(fp);
    }
    fclose(fp);
    fclose(output);
    return 0;
}

int testForm(char *db, char *key, char *can, FILE *fp, int c) {
    //if there is a candidate key then probably a partial dependency, just set 1NF and read the rest of the stuff
    if(can[0] != 0) {
        while(c != 'x')
            c = getc(fp);
        return 1;
    }
    int i;
    int test1 = 0;
    int test2 = 0;
    char temp1[100] = {0};
    char temp2[100] = {0};
    int form = 3;
    while(c != 'x') {
        //eat up past the first paretheses
        while (c != '(') {
            if(c == 'x')
                return form;
            c = getc(fp);
        }
        c = getc(fp);
        //add everything to a temp array
        for (i = 0; c != ')'; i++) {
            temp1[i] = c;
            c = getc(fp);
        }
        /*for(i = 0; temp1[i] != 0; i++)
            printf("%c ",temp1[i]);*/
        //test if key is a subset of temp
        test1 = checkEqual(temp1, key, sizeof(temp1), sizeof(key));
        //printf("Equal1: %d  ", test1);
        while (c != '(')
            c = getc(fp);
        c = getc(fp);
        //add everything to a temp array
        for (i = 0; c != ')'; i++) {
            temp2[i] = c;
            c = getc(fp);
        }
        /*for(i = 0; temp2[i] != 0; i++)
            printf("%c ",temp2[i]);*/
        //test if key is a subset of temp
        test2 = checkEqual(temp2, key, sizeof(temp2), sizeof(key));
        //printf("Equal2: %d  ", test2);
        if (test1 == 0 && test2 == 0)
            form = 2;
        //printf("Form: %d\n", form);
        c = getc(fp);
    }
    return form;
}

int checkEqual(char *a1,char *a2 , int m, int n) {
    int i = 0;
    int j = 0;
    for (i=0; i<n; i++) {
        for (j = 0; j<m; j++) {
            if(a2[i] == a1[j])
                break;
        }
        if (j == m)
            return 0;
    }
    return 1;

}
void getDB(char *db, FILE *fp, int c) {
    for (int i = 0; c != EOF; i++) {
        if(c == ' ') {
            /*printf("DB: ");
            for(i = 0; db[i] != 0; i++)
                printf("%c",db[i]);*/
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
            /*printf("\nKey: ");
            for(i = 0; key[i] != 0; i++)
                printf("%c",key[i]);
            printf("\nCandidate: ");
            for(i = 0; i < 3; i++)
                printf("%c",candidate[i]);
            printf("\n");*/
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
