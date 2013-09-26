#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLEN 256
#define MAXARGS 10


  int main(){
  char command[MAXLEN];  
  char *words[MAXARGS];   
  char *token; 

  int count;
  strcmp(command, ""); 

  while ( 1 ){ 

    
    printf("Shell>");
    fgets (command, MAXLEN, stdin);
    command[strlen(command)-1] = '\0'; 

    if ( strcmp(command, "exit") == 0 ){
      exit(1);
    }
    
    int pid = fork();
    int pidstatus;
    if ( pid ==0){  /* Child process. */
        count = 0;
        token = strtok(command, " 	");
        while ( token != NULL ){
        words[count] = (char *) malloc(strlen(token)+1);
        strcpy(words[count++], token);
        token = strtok(NULL, " 	");
      }
      words[count] = NULL;

      if(execvp(words[0],words) < 0)
	{
     	fprintf(stderr, "Error executing command.\n");
     	exit(1);	
        }
    }

    else{ /* Parent process. */
       while (wait(&pidstatus) != pid) ;
   }
 exit(0);
  }  
}

