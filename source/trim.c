/*********************************************
 *  smsh - SMS Shell
 * File: trim.c; Created by: Krishnashish Gogoi
 * Released under GPLv3.
 * Check COPYING for a full text of the license.
 * Original author: Saurav Modak
 * 
 * Send some love by fixing this program. Very buggeh atm.
 * 
 * 
 * ******************************************/


#include <stdio.h>
#include "trim.h"
#include <stdlib.h>


/* Note from Krishnashish -
 * I still haven't checked this part of the code yet.
 * It works alright for the most part so I haven't bothered 
 * with it yet. Maybe next time. Or maybe just replace
 * it with an actual XML parser library like expat or 
 * libxml2. 
 * */


void trimfeed(){
     // this function removes the white spaces
     // in the feed which may cause trouble
     // while analyzing
     
    FILE *fp1, *fp2;
    char str1[200], str2[200];
    
    fp1=fopen(".downloaded_feed", "r");
    if(fp1==NULL){
        printf("Cannot open file.. Check your internet connectivity");
        exit(0);
    }
    fp2=fopen(".feed", "w");
    while(fgets(str1, 200, fp1)){
        trim(str1, str2);
        fprintf(fp2, "%s", str2);
    }
    fclose(fp1);
    fclose(fp2);
}

void trim(char *src, char *dest){
    /*  trims the src and fills the
     * result in dest
     */
    int i,j;
    i=j=0;
    while(src[i]==' ' || src[i]=='\t')
        i++;
    while(src[i])
        dest[j++]=src[i++];
    dest[j]='\0';
}
