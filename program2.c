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

#define MAX_PUBLISH_PACKET_SIZE 1200

char* getDirString(int *len, int *count);
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
  uint32_t intid = atoi(peerid);
  char choice[10]; 
  unsigned char * msg; 
  char filename[100]; 
  int size, count;
  int total = 0,tempi = 0; 
  intid = htonl(intid);   
  bool joined = false; 
  bool exit = false; 
  while (exit == false)
    {
      //get user input and remove newline from that input
      fgets(choice, sizeof(choice), stdin);
      char * p = strchr( choice, '\n' );
      if (p) *p = '\0'; 

      //join command
      if (strcmp(choice, "JOIN") == false)
      {
    // allocate memory for the msg to send, set the action byte to 0 for join, cat peerid to it, then send
          msg = malloc( sizeof(unsigned char) * ( 6 ));
          msg[0] = 0; //0 for join action

          msg[1] = (intid >> 24) & 0xFF;
          msg[2] = (intid >> 16) & 0xFF;
          msg[3] = (intid >> 8) & 0xFF;
          msg[4] = intid & 0xFF;

          total = 0;
          tempi = 0; 
          while (total != 5) //send to handle partial send(); 
          {
            tempi = send(s,msg,5,0);
            if (tempi <0)
            {
              free(msg); 
              return -1; //if error
            }
            total = tempi + total;
          }
          free(msg); 
          msg = NULL; 
	        joined = true;
        //else do nothing if already joined
      }
      else if (strcmp(choice, "PUBLISH") == false)
      {
        if (joined == true)
        { 
          size = 0;
          count = 0;
          unsigned char ccount[5];
          sprintf(ccount, "%d", count);
          unsigned char* temp; 
          printf("before\n");
          temp = getDirString(&size, &count);
          printf("after\n");          
          if(size == -1){
            printf("WARNING: Too many files, Packet Size will exceede 1200B!");
              continue;
          }
          // count tracks the # of files.  convert to string and then count the digits, then lead with 0 when addiing to messasge (4 bytes after action).  
          // msg = malloc 5 + size
          msg = malloc( sizeof(unsigned char) * (1200));
          
            printf("allocated msg\n");
          msg[0] = '1';
          
            printf("assigning action\n");
          //unsigned char t = (char)size;
          memcpy(msg+1,(char *) size, sizeof(size));
         
          printf("memcpy size\n");
          
          printf("size of integer size: %d\n", sizeof(size));
          
          //printf("size of character size: %d\n", sizeof(t));
          memcpy(msg+1+sizeof(size),temp,size);
          //strcat temp + null as many files as there are in count; 
          
            printf("memcpy Dir string\n");
          int totalsentBytes = 0;
          int sentBytes = 0; 
          while (totalsentBytes != (int)(sizeof(msg))){ //send to handle partial send(); 
          
	          printf("sending loop\n"); 
            sentBytes = send(s,msg, sizeof(msg),0);
            if (sentBytes <0) {
              free(msg); 
              return -1; //if error
            }
            totalsentBytes = sentBytes + totalsentBytes;
 	          printf("Total: %d\n", totalsentBytes);  
          }
          free(temp); 
          free(msg); 
        }
        // do nothing if not joined
      }
      // Search Function.  1 byte + n bytes file name + NULL terminator
      else if (strcmp(choice, "SEARCH") == false)
      {
        if (joined == true)
        {
          printf("Enter File to Search: "); 
          fgets(filename, sizeof(filename), stdin);
          p = strchr(filename, '\n' );
          if (p) *p = '\0';
          size = (int) strlen(filename) + 2; // 1 byte for action byte; 
          msg = malloc( sizeof(unsigned char) * ( size ));
          msg[0] = 2; 
          for(int i = 0; i < size-2; i++)
            {
              msg[i+1] = filename[i];
            }       
          msg[size-1] = '\0'; // should already be null but just in case
          total = 0;      
          tempi = 0; 
          unsigned char buf[10]; 
          count = 0; 
          while (total < size) //send to handle partial send(); 
          { 
            tempi = send(s,msg,size,0);
            if (tempi <0)
            {
              free(msg); 
              return -1; //if error
            }
            if(count >10)
            {
              break; 
            }
            count++; 
            total = tempi + total; 
          }
          tempi = recv(s,buf,10,0); 
          total = 0; 
          // check if buf is empty
          for (int i = 0; i < 10; i++)
            {
              if(buf[i] !=0)
              {
                total = 1; 
              }
            }
          if(total == 1)
          {
            uint32_t recid; 
            // manually assign to uint32_t by position
        	  recid = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]);
        	  printf("File found at\n Peer %u\n ", recid);
            for (int i = 0; i < 4; i++){
              printf("%u",buf[4+i]);
              if( i == 3)
              {
                printf(":"); 
              }
              else{
                printf("."); 
              }
            }
            // manually assign to uint16_t by position
            uint16_t recport = (buf[8] << 8) | (buf[9]);
            printf("%u\n", recport); 
          } 
          else{
            printf("File not indexed by registry\n");
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


char* getDirString(int *len, int *count){
  DIR *d = opendir("SharedFiles");
  char* finalS = malloc( sizeof(char) * (  MAX_PUBLISH_PACKET_SIZE-5 ));
  struct dirent *dir;
  if(d){
    while((dir = readdir(d)) != NULL){
      if(dir-> d_type != DT_DIR){
        int currlength = (int)strlen(dir->d_name);
        //printf("length of string: %d  %s\n", currlength,dir->d_name );
        if(*len + currlength+1 > MAX_PUBLISH_PACKET_SIZE-5){
          *len = -1;
          *count = -1;
          return finalS;
        }
        memcpy(finalS+ (*len), dir->d_name, currlength);
        *len = *len + currlength;
        finalS[*len] = '\0';
        *len = *len +1;
        *count = *count +1; 

      }
    }
    closedir(d);
  }
  return finalS;
}