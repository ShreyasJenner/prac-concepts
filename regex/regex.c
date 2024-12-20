#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char **argv) {
    int err, i;
    regex_t reg;
    char inp[100];
    char word_arr[10][20] = {
        "the world is mine",
        "illmatic",
        "NAS nas",
        "A$AP rocky",
        "At.Long.Last.A$AP",
        "Long.Live.A$AP",
        "nigs boson"
    };

    /* compile regex for matching ascii chars */
    scanf("%s",inp);
    err = regcomp(&reg, inp, REG_ICASE);
    if(err!=0) {
        printf("reg comp error\n");
        exit(1);
    }

    
    /*  */
    for(i=0;i<6;i++) {
        err = regexec(&reg, word_arr[i], 0, NULL, 0);
        if(err==0) {
            printf("Pattern matched:%d\n",i);
        } else if(err == REG_NOMATCH) {
            printf("No match:%d\n",i);
        } else {
            printf("Error ocurred\n");
        }
    }
    

    regfree(&reg);

    return 0;
}
