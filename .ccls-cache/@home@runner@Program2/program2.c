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

char* getDirString(int *len);
int lookup_and_connect(const char *host, const char *service, const char * peerid);
int main( int argc, char *argv[] )
{
  int s;
  const char *host = argv[1]; 
  const char *port = argv[2]; 
  const char *id = argv[3]; 
  if (strlen(id) > 4)
  {
    printf("invalid id"); 
    return 0; 
  }
  if ((s = lookup_and_connect(host, port, id)) < 0) {
    exit(1);
  }
  close(s);
  return 0;
  return 0;
}

int lookup_and_connect(const char *host, const char *service, const char * peerid) {
  struct addrinfo hints;
  struct addrinfo *rp, *result;
  int s;

  /* Translate host name into peer's IP address */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  if ((s = getaddrinfo(host, service, &hints, &result)) != 0) {
    fprintf(stderr, "stream-talk-client: getaddrinfo: %s\n", gai_strerror(s));
    return -1;
  }

  /* Iterate through the address list and try to connect */
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    if ((s = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) {
      continue;
    }

    if (connect(s, rp->ai_addr, rp->ai_addrlen) != -1) {
      break;
    }

    close(s);
  }
  if (rp == NULL) {
    perror("stream-talk-client: connect");
    return -1;
  }
  printf("DEBUG: connection succes, menu loop next\n"); 
  // Menu loop for registry actions
  
  char stringid[4]; //hold peerid as a char array 
  sprintf(stringid, "%s", peerid); //convert peerid to char array
  char choice[10]; 
  char * msg; 
  char filename[15]; 
  int size; 
  bool joined = false; 
  bool exit = true; 
  while (exit == false)
    {
      //get user input and remove newline from that input
      fgets(choice, sizeof(choice), stdin);
      char * p = strchr( choice, '\n' );
      if (p) *p = '\0'; 
      if (strcmp(choice, "JOIN") == false)
      {
        if (joined == false)
        {
    // allocate memory for the msg to send, set the action byte to 0 for join, cat peerid to it, then send
          msg = malloc( sizeof(char) * ( 5 ));
          msg[0] = '0'; //0 for join action
          strcat(msg,stringid); //append id 
          if (send(s,msg, 5, 0) < 0)
          {
            free(msg); 
            return -1; 
          }
          free(msg); 
          msg = NULL; 
        }
        //else do nothing if already joined
      }
      else if (strcmp(choice, "PUBLISH") == false)
      {
        if (joined == true)
        {
          // do PUBLISH
          // get all names in SharedFiles
        }
        // do nothing if not joined
      }
      else if (strcmp(choice, "SEARCH") == false)
      {
        if (joined == true)
        {
          printf("Enter File to Search: "); 
          fgets(filename, sizeof(filename), stdin);
          p = strchr(filename, '\n' );
          if (p) *p = '\0';
          size = (int) strlen(filename) + 2; // 1 for null term, another 1 byte for action byte; 
          msg = malloc( sizeof(char) * (  1 + size ));
          msg[0] = '2'; 
          strcat(msg, filename);
          msg[size-1] = '\0'; 
          if (send(s,msg,size, 0) < 0)
          {
            free(msg); 
            return -1; 
          }
          free(msg); 
        }
        // nothing happens if not joined
      }
      else if (strcmp(choice, "EXIT") == false)
      {
        exit = true; 
      }
      // "reset" the char array
      memset(choice, 0, sizeof(choice)); 
    }  
  freeaddrinfo(result);  
  return 0; 
}


char* getDirString(int * len){
  DIR *d = opendir("SharedFiles");
  char* final = malloc( sizeof(char) * (  2000 ));
  struct dirent *dir;
  if(d){
    while((dir = readdir(d)) != NULL){
      if(dir-> d_type != DT_DIR){
        *len = *len + (int)strlen(dir->d_name) +1; 
        strcat(final, dir->d_name);
        strcat(final,"\0");
      }
    }
    closedir(d);
  }
  return final;
}