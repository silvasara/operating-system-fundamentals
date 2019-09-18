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
}

void show_lower_case_letters(){
    printf("Sem letras maiúsculas: \n");

    for(int i = 0; i < strlen(S); i++){
        if(islower(S[i]))
            printf("%c", S[i]);
    }

    printf("\n");
}

void show_consonants(){
    printf("Sem vogais: \n");

    for(int i = 0; i < strlen(S); i++){
        if(S[i] != 'a' && S[i] != 'e' && S[i] != 'i' && S[i] != 'o' && S[i] != 'u' &&
                S[i] != 'A' &&  S[i] != 'E' && S[i] != 'I' && S[i] != 'O' && S[i] != 'U')
            printf("%c", S[i]);
    }

    printf("\n");
}

void execute_1002(){
        pid_t p1004 = fork(); 

        if(pid1004 == 0) // child 1004
            signal(SIGTERM, show_upper_case_letters);
			
        pid_t pid7 = fork();

        wait(&status);

        pid_t pid6 = fork(); // child 1006

        if(pid6 == 0)
            kill(getpid(), SIGTERM);
        if(pid7 == 0) // child 1007
            kill(getpid(), SIGUSR1);

}

void execute_1003(){
		int len;
		pid_t p1005 = fork();

		if(p1005 == 0) // child 1005
			exit(strlen(S);
		else{
			wait(&len);
			exit(len);
		}
}

int main(){
    signal(SIGUSR2, show_lower_case_letters);
    signal(SIGUSR1, show_consonants);
    signal(SIGTERM, show_upper_case_letters);

    int status;

    scanf("%s", S);

    pid_t p1002 = fork(); 

    if(p1002 == 0) // child 1002
		execute_1002();
    else
        pid_t p1003 = fork(); 
    
	if(pid3 == 0) // child 1003
		execute_1003();
	
	sleep(1);
	wait(&status);

	printf("Tamanho da string S: %d\n", status);
	
	sleep(1);
    return 0;
}
