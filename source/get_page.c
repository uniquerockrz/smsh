/*********************************************
 *  smsh - SMS Shell
 * File: get_page.c; Created by: Krishnashish Gogoi
 * Released under GPLv3.
 * Check COPYING for a full text of the license.
 * Original author: Saurav Modak
 * 
 * Send some love by fixing this program. Very buggeh atm.
 * 
 * 
 * ******************************************/


// Basic libcurl code for downloading pages.
// I added a few checks and stuff from the previous 
// version. 

#include <stdio.h>
#include <curl/curl.h>
#include "get_page.h"

int get_page(const char* url, const char* file_name)
{
	/* get_page()
	* function to download the RSS feed specified by url and
	* save it by file_name
	*/
	CURL *easyhandle; 
	CURLcode result;
	FILE *file;
    
	// Initialize the handle
	easyhandle = curl_easy_init();
    
	// Checking if easyhandle initialized okay.
	if (easyhandle) {
		curl_easy_setopt( easyhandle, CURLOPT_URL, url ) ;
		 
		file = fopen( file_name, "w");
		if (file == NULL) printf("\nCouldn't open file.\n");
		
		curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
		result = curl_easy_perform( easyhandle );
		fclose(file);
		
		if (result != CURLE_OK) {
			fprintf(stderr, "\n\ncurl_easy_perform() failed: %s\n", curl_easy_strerror(result));
			return 1;
		}
	} else {
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}
    
	// Cleaning up because I try to hide the fact that 
	// I lead a very unhygenic real life by doing cleanups
	// in my code. :)
	curl_easy_cleanup( easyhandle );
	curl_global_cleanup();
    
	return 0;
}
