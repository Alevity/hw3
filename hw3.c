#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void sigint_handler_sigint(int sig){
  char msg[] = "\nCaught sigint\n";
  write(1, msg, sizeof(msg));
  exit(0);
}

void sigint_handler_sigtstp(int sig){
  char msg[] = "\nCaught sigstp\n";
  write(1, msg, sizeof(msg));
  exit(0);
}

shell(){
    char line[500];
    char *argsarray[20];
    int pid;
    int status;
    while(1){
         printf("CS361 > ");

        fgets(line, 500, stdin);
        line[strlen(line) - 1] = '\0';
        //break the string up into words
        char *word = strtok(line, " ");
        int i = 0;
        
		//Check for exit
         if(!strcmp(argsarray[0], "exit")){
            exit(0);
            return 0;
         }
         
        pid = fork();
        if (!(pid = fork())){
            for (i = 0; argsarray[i] != '\0'; i++){
                if (!strcmp(argsarray[i], ";")){
                
                }
                if (!strcmp(argsarray[i], "<")){
                    int fd1 = open(argsarray[i + 1], O_RDONLY, 0);
                    dup2(fd1, 0);
                    close(fd1);
                }
                else if (!strcmp(argsarray[i], ">")){
                    int fd1 = open(argsarray[i + 1], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR|S_IROTH);
                    dup2(fd1, 1);
                    close(fd1);
                }
            }
        }
        exit(execv(argsarray[0],argsarray));
        wait(&status);
        printf("pid:%i status:%i\n", pid, status,  WEXITSTATUS(status));
    }
}

int main(){
    signal(SIGINT, sigint_handler_sigint);
    signal(SIGTSTP, sigint_handler_sigtstp);
    shell();
    

}
