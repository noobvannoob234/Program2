#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>

int main()
{
	   char test[5];
	   test[0] = 0;
     char testid[4];
	   int intid = 323232; 
     uint16_t uintid = htons(intid);
     memcpy(test+1, &uintid, sizeof(uint16_t));	   
     for(int i = 0; i < 5; i++)
       {
         printf("%02x ", test[i]); 
       }
return 0; 
}