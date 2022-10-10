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
  uint64_t templen = 0, tempcount = 0;
  uint64_t* len = &templen; 
  uint64_t* count = &tempcount;
  unsigned char * msg; 

  DIR *d = opendir("SharedFiles");
  char* finalS = malloc( sizeof( char) * 100);
  printf("size of finalS: %d \n", sizeof(finalS));
  struct dirent *dir;
  if(d){
    while((dir = readdir(d)) != NULL){
      if(dir-> d_type != DT_DIR){
        //*len = *len + (int)strlen(dir->d_name) +1;
        char dirC[100];
        memset(dirC, 0, 100);
        //printf("string cpu");
        print(dir->d_name);
        printf("\nno cat: '%s'\n",dirC);

       
        strcat(dirC,dir->d_name);
        print(dirC);
        printf("\ncat: '%s'\n",dirC);
        int currlength = strlen(dirC) +1;
        printf("\nlength of string: %d\n", currlength);
        print(dirC);
        
        //strcat(finalS, dir->d_name);
        //printf("%d",*len);
        //strcat(finalS,'\0');
        printf("length of string: %ld\n", templen);
        memcpy(finalS + templen, dirC, currlength);
        templen = templen + currlength;
        memcpy(&finalS[4], dirC, currlength);
        printf("length of string: %ld\n", templen);
        //finalS[templen] = '\0';
        //templen = templen +1;
        tempcount = tempcount +1; 
        printf("\nfinal: ");
        print(finalS);
        printf("\n");
      }
    }
    closedir(d);
    printf("count of files: %ld\n", *count);
    int i;
    for (i = 0; i < sizeof(1200); i++)
        if (finalS[i] == 0)
            printf("!");
        else
            printf("%c", finalS[i]);
    printf("\nlength is: %ld", templen);
    msg = malloc(  sizeof(unsigned char) * (1200));
          
    printf("allocated msg\n");
    msg[0] = '1';
          
    printf("assigning action\n");
    unsigned char* t = templen + '0';
    memcpy(msg+1,&templen, sizeof(templen));
         
    printf("memcpy size\n");
          
    printf("size of integer size: %ld\n", sizeof(templen));
          
          //printf("size of character size: %d\n", sizeof(t));
    memcpy(msg+1+sizeof(templen),finalS,sizeof(finalS));
          //strcat temp + null as many files as there are in count; 
          
    printf("memcpy Dir string\n");
    
  }
  
  int i;
    for (i = 0; i <= sizeof(1200); i++)
        if (msg[i] == 0)
            printf("!");
        else
            printf("%c", msg[i]);
  return 0;
}

// int main()
// {
//   uint64_t templen = 0, tempcount = 0;
//   uint64_t* len = &templen; 
//   uint64_t* count = &tempcount;
//   unsigned char * msg; 

//   DIR *d = opendir("SharedFiles");
//   char* finalS = malloc( sizeof(unsigned char) * (  1495 ));
//   struct dirent *dir;
//   if(d){
//     while((dir = readdir(d)) != NULL){
//       if(dir-> d_type != DT_DIR){
//         //*len = *len + (int)strlen(dir->d_name) +1;
//         char dirC[100];
//         memset(dirC, 0, 100);
//         //printf("string cpu");
//         print(dir->d_name);
//         printf("\nno cat: '%s'\n",dirC);

//         strcat(dirC,dir->d_name);
//         printf("\ncat: '%s'\n",dirC);
//         int currlength = strlen(dirC);
//         printf("\nlength of string: %d\n", currlength);
//         print(dirC);
        
//         //strcat(finalS, dir->d_name);
//         //printf("%d",*len);
//         //strcat(finalS,'\0');
//         printf("length of string: %ld\n", templen);
//         memcpy(finalS+ templen, dirC, currlength);
//         templen = templen + currlength;
//         printf("length of string: %ld\n", templen);
//         finalS[templen] = '\0';
//         templen = templen +1;
//         tempcount = tempcount +1; 
//         printf("\nfinal: ");
//         print(finalS);
//         printf("\n");
//       }
//     }
//     closedir(d);
//     printf("count of files: %ld\n", *count);
//     int i;
//     for (i = 0; i < sizeof(finalS); i++)
//         if (finalS[i] == 0)
//             printf("!");
//         else
//             printf("%c", finalS[i]);
//     printf("\nlength is: %ld", templen);
//     msg = malloc(  sizeof(unsigned char) * (1200));
          
//     printf("allocated msg\n");
//     msg[0] = '1';
          
//     printf("assigning action\n");
//     unsigned char* t = templen + '0';
//     memcpy(msg+1,&templen, sizeof(templen));
         
//     printf("memcpy size\n");
          
//     printf("size of integer size: %ld\n", sizeof(templen));
          
//           //printf("size of character size: %d\n", sizeof(t));
//     memcpy(msg+1+sizeof(templen),finalS,sizeof(finalS));
//           //strcat temp + null as many files as there are in count; 
          
//     printf("memcpy Dir string\n");
    
//   }
  
//   int i;
//     for (i = 0; i <= sizeof(msg); i++)
//         if (msg[i] == 0)
//             printf("!");
//         else
//             printf("%c", msg[i]);
//   return 0;
// }

void print(char *t){
  printf("'");
  int i;
    for (i = 0; i <= sizeof(t); i++)
        if (t[i] == 0)
            printf("!");
        else
            printf("%c", t[i]);
  printf("'\n");
  return 0;  
}