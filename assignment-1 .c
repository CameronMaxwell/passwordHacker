#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>   
#include <string.h>
#include "checkPassword.h"

void generateAnswer(int startPos){
    int loopBreak = 0;
    for(int x=126; x >= 33 && loopBreak==0;x--){
         for(int y=126; y >= 33&& loopBreak==0;y--){
             for(int z=126; z >= 33&& loopBreak==0;z--){
                char attemp[4] = {x,y,z,0};
                //printf("%s\n",attemp);
                int try =  checkPassword(attemp,startPos);
                if(try != -1){
                    printf("%s\n",attemp);
                    loopBreak = 1;
                }
             }
         }
    }

}

int main(int argc, char* argv[]){
int forkActivate = 0;
int callActivate = 0;

/* accept an optional command-line argument*/

for (int x = 0; x < argc; x++){
    if(strcmp(argv[x], "-f" ) == 0){
        forkActivate = 1;
        }
    if(strcmp(argv[x], "-p") == 0){
        callActivate = 1;
    }
}

if(forkActivate == 1){
     int fork1= fork();
     int fork2= fork();

    if(fork1 == 0){
        if(fork2 == 0){
            // grandchild
            printf("PID IS 1.1.1 %d. PPID 1.1 IS %d\n",getpid(),getppid());
            generateAnswer(9);
        }
        else{
            //first child 
            printf("PID IS 1.1 %d. PPID 1 IS %d\n",getpid(),getppid());
            printf("PID IS 1.1 %d. CHILD IS 1.1.1 IS %d\n",getpid(),fork2);
            generateAnswer(6);
            wait(&fork2);
        }
    }
    else{
        if(fork2 == 0){
            //secondchild
            printf("PID IS 1.2 %d. PPID 1 IS %d\n",getpid(),getppid());
            generateAnswer(3);
        }
        else{
            printf("PID IS 1.0 %d. CHILD IS 1.1 IS %d\n",getpid(),fork1);
            printf("PID IS 1.0 %d. CHILD IS 1.2 IS %d\n",getpid(),fork2);
            generateAnswer(0);
 
            wait(&fork1);
            wait(&fork2);
            if(callActivate==1){
                ; //execl("hackme","",NULL);
            }
        }
    }



}
else{

    generateAnswer(0);
    generateAnswer(3);
    generateAnswer(6);
    generateAnswer(9);
     if(callActivate==1){
                ;// execl("hackme","",NULL);
            }
}

return 0;

}
