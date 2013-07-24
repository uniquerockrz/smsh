/*********************************************
 *  smsh - SMS Shell
 * File: main.c; Created by: Krishnashish Gogoi
 * Released under GPLv3.
 * Check COPYING for a full text of the license.
 * Original author: Saurav Modak
 * 
 * Send some love by fixing this program. Very buggeh atm.
 * 
 * 
 * ******************************************/


#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "start.h"

#define WAIT 60

int main (int argc, char *argv[])
{
	int iterflag = 1;
	
	// Starting banner and stuff
	printf("Starting smsh - the sms shell for Linux remote computing\n");
    printf("===========================================================\n\n");
    printf("This is a very crude and rude version of the program.\n");
    printf("It sometimes works, it sometimes doesn't. DO NOT COMPLAIN.\n");
    printf("Original Author: Saurav Modak.\n\n");
    printf("... Krishnashish Gogoi ...\n");
    
    // Sets the current time in a certain format in lastmsg.txt.
    // This is later used in analyze.c to compare time.
    // Any time before starting the program is irrelevant,
    // hence the starting time.
    time_t curtime;
    struct tm *loctime;
    char setDate[30];
    FILE *fp;
    fp = fopen("lastmsg.txt", "w");
    curtime=time(NULL);
    loctime= localtime(&curtime);
    
    
    
    // Writing current date and time to lastmsg.txt
    // with a proper format for compareTime()
    strftime(setDate, 30, "%d %b %Y %H:%M:%S", loctime);
    fputs(setDate, fp);
    fclose(fp);
    
    char lineBuff[30];
    char urlBuff[80] = "http://tagg.in/Rss/";
    int urlLength = strlen(urlBuff);
    int loopFlag = 1;
    
    // Reads input. Silly little loop.
    do {
		printf("\n\nEnter your tagg.in username: ");
    
		// Read Input 
		if (fgets(lineBuff, sizeof(lineBuff), stdin) != NULL) {
			memcpy(urlBuff + urlLength, lineBuff, strlen(lineBuff));
			urlBuff[strlen(urlBuff)] = '\0';
			loopFlag = 0;
		} else 
			printf("\nPlease enter a username.\n");
	} while (loopFlag == 1);
    
    
    // Main program loop. Calls start(), waits WAIT no. of secs,
    // calls again. Silly I know, but an improvement over the
    // previous recursion I believe. 
    while (iterflag) {
		start(urlBuff);
		printf("Waiting %d seconds for the next check\n\n", WAIT);
        sleep(WAIT);
	}
    
    return 0;
}
	

