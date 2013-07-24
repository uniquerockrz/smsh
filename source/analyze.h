/*********************************************
 *  smsh - SMS Shell
 * File: analyze.h; Created by: Krishnashish Gogoi
 * Released under GPLv3.
 * Check COPYING for a full text of the license.
 * Original author: Saurav Modak
 * 
 * Send some love by fixing this program. Very buggeh atm.
 * 
 * 
 * ******************************************/

// Header files are ridiculous. No idea why I or other people
// even make them. 


// Include guards, ladies and djentlemen, include guards.
#ifndef __ANALYZE_H__
#define __ANALYZE_H__


int analyzefeed();
void extractCommand(char *, char *);
void substring(char *, int, int, char *);
int compareTime (char *, char *);

#endif
