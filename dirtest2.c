int main()
{
  int len = 0, count = 0; 
  DIR *d = opendir("SharedFiles");
  char* final = malloc( sizeof(char) * (  2000 ));
  struct dirent *dir;
  if(d){
    while((dir = readdir(d)) != NULL){
      if(dir-> d_type != DT_DIR){
        len = len + (int)strlen(dir->d_name) +1; 
        strcat(final, dir->d_name);
        strcat(final,"1");
        final[len] = '\0'
        count++; 
      }
    }
    closedir(d);
  }
  return 0; 
}
