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
  uint32_t peerid = 12; 
  char ccid[5]; 
  sprintf(ccid,"%d",peerid);
  char *msg = malloc( sizeof(char) * ( 6 ));
  msg[0] = '0'; //0 for join action
  int count = 4 - strlen(ccid); 
  printf("%d\n", count);
  for (int i = 0; i < 5; i++)
    {
      if (ccid[i] == 0)
      {
        printf(" "); 
      }
      printf("%c", ccid[i]); 
    }  
  printf("\n"); 
  strcat(msg,ccid); 
  for (int i = 0; i < 5; i++)
    {
      if (msg[i] == 0)
      {
        printf(" "); 
      }
      printf("%c", msg[i]); 
    }
return 0; 
}