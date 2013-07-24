/*********************************************
 *  smsh - SMS Shell
 * File: analyze.c; Created by: Krishnashish Gogoi
 * Released under GPLv3.
 * Check COPYING for a full text of the license.
 * Original author: Saurav Modak
 * 
 * Send some love by fixing this program. Very buggeh atm.
 * 
 * 
 * ******************************************/





// It just doesn't move with the strptime() function without 
// these _XOPEN_SOURCE defines. Didn't figure it out till
// I read it in the man page.
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "analyze.h"
#include <stdlib.h>
#endif



/*
 * Hello fellow coder,
 * 
 * If you're reading this, I must warn you of the 
 * upcoming dangers and perils of the code ahead.
 * 
 * If you're an experienced coder, the appropriate reaction
 * through this section should be, "Who let this guy code?"
 * After which, you shall proceed to spend the upcoming nights
 * of your life trying to make this better, turning your coffee 
 * into nimble bytes of code that reek of hope and optimization.
 * I have deep respect for you, my brother.
 * 
 * If you're a new coder, turn away now. It's still not too late.
 * There are other good examples of code out there in the internets.
 * However, if you do take the journey, all mental harrassments and 
 * emotional pain that you'll have to face is your own 
 * responsibility. I wish you the bestest of luck, my brother.
 * 
 * Either way, you should update the counter variables that follow
 * for anyone that may undertake this journey of madness after you.
 * 
 * no_of__hours_wasted = 28;
 * no_of_coffee_cups = 21;
 * 
 * Yours sincerely,
 * The coder who took this journey before you.
 * 
 * May the caffeine be with you.
 * 
 * */

int analyzefeed() 
{
	char str[200], str2[200], command[200], thisDate[80], lastDate[80];
	FILE *fp, *fp1;
	fp=fopen(".feed", "r");
	// analyze the feed and look for </image>
	while(fgets(str, 200, fp)){
		if(strncmp(str, "</image>", 8)==0)
			break;
	}
        
			
	// analyze the feed and look for <pubDate>
	while(fgets(str, 200, fp)){
		if(strncmp(str, "<pubDate>", 9)==0)
			break;
            
	}
    
	substring(str, 14, 14, thisDate);
    
    
	fp1=fopen("lastmsg.txt", "r");
	fgets(str2, 80, fp1);
	fclose(fp1);
	
	
	
	if(compareTime(thisDate, lastDate)==0){
		printf("No new message\n");
		return 0;
	} else if (compareTime(thisDate, lastDate) < 0){
		printf("No new message\n");
		return 0;
	} else {
		printf("1 New Message\n");
		fp1=fopen("lastmsg.txt", "w");
		fprintf(fp1, "%s", thisDate);
		fclose(fp1);
		// analyze the feed and look for <description>
		while(fgets(str, 200, fp)){
			if(strncmp(str, "<description>", 13)==0)
					break;
		}
		extractCommand(str, command);
		printf("Command Found %s. Executing now\n", command);
		system(command);
		return 0;
	}
}



void substring(char *src, int stripFromBewb, int stripFromAss, char *dest)
{
		
	for (int destIndex = 0; stripFromBewb <= (strlen(src)-1-stripFromAss); 
		stripFromBewb++, destIndex++)
		dest[destIndex] = src[stripFromBewb];
}


int compareTime (char *date1, char *date2)
{
	
	/* This little function here compares time.
	 * Since I'm stupid, it took me some time
	 * to figure out and then a thread at 
	 * SO said that the structs should be initialized
	 * and I was like "yey".
	 * 
	 * So yeah, it uses stuff from <time.h>. 
	 * Initializes the t structs, then takes the
	 * date1 and date2 character strings and formats
	 * them into the tm structures using strptime. Then
	 * it calls mktime() to turn those structures into
	 * time_t's. After that, difftime() takes the difference
	 * of the time_t variables. Et voila. */
	 
	struct tm datestruct1, datestruct2;
	time_t time1, time2;
	
	// Initializing the structures
	memset(&datestruct1, 0, sizeof(struct tm));
	memset(&datestruct2, 0, sizeof(struct tm));
	
	strptime(date1, "%d %b %Y %H:%M:%S", &datestruct1);
	strptime(date2, "%d %b %Y %H:%M:%S", &datestruct2);
	
	// Create time_t values from tm structures
	time1 = mktime(&datestruct1);
	time2 = mktime(&datestruct2);
	
	double diff;
	diff = difftime(time1, time2);
	
	if (diff == 0.0)
		return 0;
	else if (diff > 0)
		return 1;
	else 
		return -1;
}

/*
* For the brave souls who get this far: You are the chosen ones,
* the valiant knights of programming who toil away, without rest,
* fixing our most awful code. To you, true saviors, kings of men,
* I say this: never gonna give you up, never gonna let you down,
* never gonna run around and desert you. Never gonna make you cry,
* never gonna say goodbye. Never gonna tell a lie and hurt you.
*/


void extractCommand(char *src, char *dest)
{
	/* extracts the command to be
	* executed from XML
	*/
	int i=22, j=0, flag=1;
	while(flag){
		dest[j]=src[i];
		if(src[i+1]==']' && src[i+2]==']')
			flag=0;
			j++;
			i++;
	}
	dest[j++]='\0';
}
