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
    exit(1);
}

void show_lower_case_letters(){
    printf("Sem letras maiúsculas: \n");

    for(int i = 0; i < strlen(S); i++){
        if(islower(S[i]))
            printf("%c", S[i]);
    }

    printf("\n");
    exit(1);
}

void show_consonants(){
    printf("Sem vogais: \n");

    for(int i = 0; i < strlen(S); i++){
        if(S[i] != 'a' && S[i] != 'e' && S[i] != 'i' && S[i] != 'o' && S[i] != 'u' &&
                S[i] != 'A' &&  S[i] != 'E' && S[i] != 'I' && S[i] != 'O' && S[i] != 'U')
            printf("%c", S[i]);
    }

    printf("\n");
    exit(1);
}

int main(){
    signal(SIGUSR2, show_lower_case_letters);
    signal(SIGUSR1, show_consonants);
    signal(SIGTERM, show_upper_case_letters);

    int status;

    scanf(" %s", S);

    pid_t pid1 = fork(); 

    if(pid1 == 0){ // child 1002
        pid_t pid4 = fork(); 

        if(pid4 == 0) // child 1004
            kill(getpid(), SIGUSR2);

        wait(&status);

        pid_t pid7 = fork();

        if(pid7 == 0) // child 1007
            kill(getpid(), SIGUSR1);

        wait(&status);

        pid_t pid6 = fork(); // child 1006

        if(pid6 == 0)
            kill(getpid(), SIGTERM);
    } 
    else {
        pid_t pid3 = fork(); // create - 1003

        if(pid3 == 0){ // child 1005
            printf("Tamanho da string S: %ld\n", strlen(S));
        }
    }

    return 0;
}
