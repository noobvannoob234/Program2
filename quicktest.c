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
  int templen = 0, tempcount = 0;
  int* len = &templen; 
  int* count = &tempcount;
  DIR *d = opendir("SharedFiles");
  char* finalS = malloc( sizeof(char) * (  2000 ));
  struct dirent *dir;
  if(d){
    while((dir = readdir(d)) != NULL){
      if(dir-> d_type != DT_DIR){
        //*len = *len + (int)strlen(dir->d_name) +1; 
        int currlength = (int)strlen(dir->d_name);
        strcat(finalS, dir->d_name);
        //printf("%d",*len);
        strcat(finalS,'\0');
        //final[*len] = '\0';
        //memcpy(finalS, dir->d_name, currlength);
        
        //memcpy(finalS,'\0', 1);
        //count++; 
        //*len = *len + currlength +1;

      }
    }
    closedir(d);
  }
  int i;
    for (i = 0; i <= 2000; i++)
        if (finalS[i] == 0)
            printf("\\0");
        else
            printf("%c", finalS[i]);
  return 0;;
}