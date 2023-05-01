#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


char *readline() {
    const size_t BSIZE = 100;
    char *line = NULL;
    size_t capacity = 0;

    do {
        capacity += BSIZE;
        line = (char *) realloc(line, (capacity + 1) * sizeof(char));
        if (line == NULL)
            return line;

        if (fgets(line + capacity - BSIZE, BSIZE + 1, stdin) == NULL) {
            free(line);
            return NULL;
        }
    } while (strlen(line + capacity - BSIZE) >= BSIZE
             && line[capacity - 1] != '\n');
    return line;
}

////////////////////////////////////////////////////////////////

void a_switch(char pole[],int i);

void c_switch(char pole[]);

void u_switch(char pole[]);

void l_switch(char pole[]);

void r_switch(char *src, char *str, char *rep);

void no_r_switch(char pole[], char parameter[]);

int main(int argc, char* argv[]) {
    int c,prepinac_a = 0, prepinac_c = 0, prepinac_u = 0, prepinac_l = 0, prepinac_r = 0;
    int str_index=0;
    char random_stringy[20][100];
    char * argument;
    while((c = getopt (argc, argv, ":aculr:"))!=-1) {
        switch(c){
            case 'a':
                prepinac_a++;
                break;
            case'c':
                prepinac_c++;
                break;
            case'u':
                prepinac_u++;
                break;
            case'l':
                prepinac_l++;
                break;
            case'r':
                prepinac_r++;
                argument=optarg;
                break;
            case'?':
                return 1;
            case':':
                return 2;
            default:
                break;
            }
        }
    if(prepinac_u==1&&prepinac_l==1){
        return 3;
    }
    for (int dada = optind; dada < argc; dada++){
        strcpy(random_stringy[str_index],argv[dada]);
        str_index++;
}
    while(1){
    char * string=readline();
    if(string[0]=='\n')             //enter podmienka
    {
        return 0;
    }
    if(prepinac_a==1){
        a_switch(string,strlen(string));
    }
    if(prepinac_c==1){
        c_switch(string);
    }
    if(prepinac_u==1){
        u_switch(string);
    }
    if(prepinac_l==1){
        l_switch(string);
    }
    if(prepinac_r==1){
        for(int i=0;i<str_index;i++){
            r_switch(string, random_stringy[i], argument);
        }
    }
    else {
        for (int i = 0; i < str_index; i++) {
            no_r_switch(string, random_stringy[i]);
        }
    }
    printf("%s",string);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


void a_switch(char pole[],int i){
    char c;
    for(int x=0;x<i;x++){
        c=pole[x];
        if(isalpha(c)==0)
        {
            //printf("%c",c);
            pole[x]=' ';
        }
    }
    pole[i-1]='\n';
}

void c_switch(char pole[]){
    int count=0;
    int y,index=0;
    int f=strlen(pole);
    while(pole[index]!='\0') {
        if (isalpha(pole[index])) {
            index++;
        }
        else {
            for (y = index; y < strlen(pole); y++) {
                pole[y] = pole[y + 1];
                }
            count++;
            }
        }
    pole[f-count]='\n';
    pole[f-count+1]='\0';
    }

void u_switch(char pole[]){
    int i=strlen(pole);
    for(int x=0;x<i;x++){
        pole[x]=toupper(pole[x]);
    }
}

void l_switch(char pole[]){
    int i=strlen(pole);
    for(int x=0;x<i;x++){
        pole[x]=tolower(pole[x]);
    }
}

void no_r_switch(char pole[], char parameter[]){
    char *result;
    int dlzka_argumentu=strlen(parameter);
    while(1){
        result=strstr(pole, parameter);
        if(result==NULL){
            break;
        }
        for(int i=0;i<dlzka_argumentu;i++){
            *result='*';
            result++;
        }
    }
}

void r_switch(char *src, char *str, char *rep)
{
    char *p = strstr(src, str);
    if (p)
    {
        int len = strlen(src)+strlen(rep)-strlen(str);
        char r[len];
        memset(r, 0, len);
        if ( p >= src ){
            strncpy(r, src, p-src);
            r[p-src]='\0';
            strncat(r, rep, strlen(rep));
            strncat(r, p+strlen(str), p+strlen(str)-src+strlen(src));
            strcpy(src, r);
            r_switch(p+strlen(rep), str, rep);
        }
    }
}