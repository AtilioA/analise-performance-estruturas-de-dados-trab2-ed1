#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define UNUSED " \n^´"

int charcmp(char c){
    for(int i = 0; i < strlen(UNUSED); i++){
        if(c == UNUSED[i]){
            return 1;
        }
    }
    return 0;
}

char *leP(int t){
    char *str = malloc(sizeof(char) * t);
    char c;
    for(int i = 0; i < t; i++){
        scanf("%c", &c);
        if(!charcmp(c)){
            str[i] = c;
        }else{
            str[i] = '\0';
            break;
        }
    }
    return str;
}

int main(){
    char c[80];
    for(int i = 0; i < 10; i++){
        strcpy(c, leP(80));
        printf("%s ", c);
    }
    return 0;
}
