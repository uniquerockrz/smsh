#include <curl/curl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define wait 60
int main()
{
    /*
     * main() function
     * just calls start() which handles all the work
     */
    void start();
    printf("Starting smsh - the sms shell for Linux remote computing\n");
    printf("===========================================================\n");
    start();
    return 0;
}
void start(){
    /*
     * start() function
     * recursively calls itself, used for checking
     * the feed at regular interverls as defined
     * by wait
     */
    void downloadfeed();
    void trimfeed();
    int analyzefeed();
    int n=1, w=wait; // n is a flag, which when 1, this function recursively calls itself; wait is the wait time before next message check
    // for displaying time in the beginning of messege check
    time_t curtime;
    struct tm *loctime;
    curtime=time(NULL);
    loctime= localtime(&curtime);
    fputs(asctime(loctime), stdout); // printing time
    printf("Checking inbox now.... ");
    downloadfeed(); // calling function to download the RSS feed of SMS blog
    printf("Looking for any new message... ");
    trimfeed();
    n=analyzefeed();
    while(n){
        printf("Waiting %d seconds for the next check\n\n", w);
        sleep(w); // waits for w seconds
        start();
    }
}
void get_page(const char* url, const char* file_name)
{
    /* get_page()
     * function to download the RSS feed specified by url and
     * save it by file_name
     */
    CURL* easyhandle = curl_easy_init();
    curl_easy_setopt( easyhandle, CURLOPT_URL, url ) ;
    FILE* file = fopen( file_name, "w");
    curl_easy_setopt( easyhandle, CURLOPT_WRITEDATA, file) ;
    curl_easy_perform( easyhandle );
    curl_easy_cleanup( easyhandle );
    fclose(file);
}
void downloadfeed()
{
    /* downloadfeed()
     * function to download the feed and store it
     * in a file
     */
    get_page( "http://tagg.in/Rss/sauravmodak", "sauravmodak" ) ;
    printf("done\n");
}
void trimfeed(){
    /* this function removes the white spaces
     * in the feed which may cause trouble
     * while analyzing
     */
    FILE *fp1, *fp2;
    char str1[200], str2[200];
    void trim(char *, char *);
    fp1=fopen("sauravmodak", "r");
    if(fp1==NULL){
        printf("Cannot open file.. Check your internet connectivity");
        exit(0);
    }
    fp2=fopen("feed.txt", "w");
    while(fgets(str1, 200, fp1)){
        trim(str1, str2);
        fprintf(fp2, "%s", str2);
    }
    fclose(fp1);
    fclose(fp2);
}
void trim(char src[200], char dest[200]){
    /* trims the src and fills the
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
int analyzefeed(){
    // feed parser
    char str[200], command[200], thisDate[80], lastDate[80];
    FILE *fp, *fp1, *fp2;
    void extractCommand(char *, char *);
    void substring(char *, char *, int, int);
    fp=fopen("feed.txt", "r");
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
    strcpy(thisDate, str);
    fp1=fopen("lastmsg.txt", "r");
    if(fp1==NULL){
        fclose(fp1);
        fp2=fopen("lastmsg.txt", "w");
        fclose(fp2);
        fp1=fopen("lastmsg.txt", "r");
    }
    fgets(lastDate, 80, fp1);
    fclose(fp1);
    if(strcmp(thisDate, lastDate)==0){
        printf("No new message\n");
        return 1;
    }
    else{
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
        return 1;
    }
}
void extractCommand(char src[200], char dest[200]){
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
