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

int main( int argc, char *argv[] )
{
  char ccount[5]; 
  int count = 12; 
  sprintf(ccount, "%d", count);
  for (int i = 0; i < 5; i++)
    {
      if (ccount[i] == nullptr)
      {
        printf(" "); 
      }
      printf("%c", ccount[i]); 
    }
return 0; 
}