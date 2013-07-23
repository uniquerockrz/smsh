/*********************************************
 *  smsh - SMS Shell
 * File: start.c; Created by: Krishnashish Gogoi
 * Released under GPLv3.
 * Check COPYING for a full text of the license.
 * Original author: Saurav Modak
 * 
 * Send some love by fixing this program. Very buggeh atm.
 * 
 * 
 * ******************************************/

#include <stdio.h>
#include <time.h>
#include "start.h"
#include "get_page.h"
#include "trim.h"
#include "analyze.h"


void start (char *url)
{
	// Prints time before doing everything because 
	// I love pretending to be a person who values his time.
	time_t currenttime;
    struct tm *loctime;
    currenttime=time(NULL);
    loctime= localtime(&currenttime);
    fputs(asctime(loctime), stdout); // printing time
    
    printf("Checking inbox now.... ");
    
    // variables for return codes from the functions.
    // Not really sure why I did this.
    int pageStatus, analyzeStatus;
    
    pageStatus = get_page( url, ".downloaded_feed" );
    
    if (pageStatus == 0) {
		printf("done\n");
		printf("Looking for any new message... ");
		
		
		trimfeed();
    
		analyzeStatus = analyzefeed();
		if (analyzeStatus != 0) 
			printf("\nCould not analyze XML feed.\n");
		
		
		
	} else 
		printf("Could not download page.\n");

}

