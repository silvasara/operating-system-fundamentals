#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <stdlib.h>

char S[101];

void show_upper_case_letters(){
    printf("Sem letras minúsculas: \n");

    for(int i = 0; i < strlen(S); i++){
        if(isupper(S[i]))
            printf("%c", S[i]);
    }

    printf("\n");
    
    exit(0);
}

void show_lower_case_letters(){
    printf("Sem letras maiúsculas: \n");

    for(int i = 0; i < strlen(S); i++){
        if(islower(S[i]))
            printf("%c", S[i]);
    }

    printf("\n");

    exit(0);
}

void show_consonants(){
    printf("Sem vogais: \n");

    for(int i = 0; i < strlen(S); i++){
        if(S[i] != 'a' && S[i] != 'e' && S[i] != 'i' && S[i] != 'o' && S[i] != 'u' &&
                S[i] != 'A' &&  S[i] != 'E' && S[i] != 'I' && S[i] != 'O' && S[i] != 'U')
            printf("%c", S[i]);
    }

    printf("\n");
    
    exit(0);
}

void execute_1002(){
    pid_t p1006 = fork(); 
    
    if(p1006 == 0){ // child 1006
        signal(SIGUSR2, show_lower_case_letters);
        pause();
    }
    else{
        sleep(1);
        kill(p1006, SIGUSR2);
    
        pid_t p1007 = fork();

        if(p1007 == 0){ // child 1007
            show_consonants();
        }
        else{
            sleep(1);
            pid_t p1004 = fork(); 
            if(p1004 == 0){ // child 1004
                show_upper_case_letters();
            }
        }
    }
}

void execute_1003(){
    pid_t p1005 = fork();

    if(p1005 == 0){ // child 1005
        exit(strlen(S));
    }
    else{
        int len;
        wait(&len);
        len = WEXITSTATUS(len);
        exit(len);
    }
}

int main(){
    scanf("%s", S);
    
    pid_t p1003 = fork(); 

	if(p1003 == 0) // child 1003
		execute_1003();
    else{
        int status;
	    wait(&status);
        int len = WEXITSTATUS(status);
	    printf("Tamanho da string S: %d\n", len);
        
        pid_t p1002 = fork(); 

        if(p1002 == 0){ // child 1002
            signal(SIGUSR1, execute_1002);
            pause();
        }
        else{
            sleep(1);
            kill(p1002, SIGUSR1);
        }
    }
    
    return 0;
}
