#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

char S[101];

void show_upper_case_letters(){
    for(int i = 0; i < strlen(S); i++){
        if(isupper(S[i]))
            printf("%c", S[i]);
    }

    printf("\n");
}

void show_lower_case_letters(){
    for(int i = 0; i < strlen(S); i++){
        if(islower(S[i]))
            printf("%c", S[i]);
    }

    printf("\n");
}

void show_consonants(){
    for(int i = 0; i < strlen(S); i++){
        if(S[i] != 'a' && S[i] != 'e' && S[i] != 'i' && S[i] != 'o' && S[i] != 'u' &&
           S[i] != 'A' &&  S[i] != 'E' && S[i] != 'I' && S[i] != 'O' && S[i] != 'U')
            printf("%c", S[i]);
    }

    printf("\n");
}

int main(){

    scanf("%s", S);

    pid_t pid = fork();

    if(pid > 0){
        pid_t pid3 = fork();

        if(pid3 > 0){ // parent 1001
            printf("(1001)I'm the %d and I'm parent of (1003) %d\n", getpid(),  pid3); 
        }
        else{ // child 1003
            printf("(1003)I'm the child: %d and my parent is (1001) %d\n", getpid(), getppid());

            pid_t pid5 = fork();

            if(pid5 > 0){ // parent 1003
                printf("(1003)I'm the %d and I'm parent of (1005) %d\n", getpid(),  pid5); 
            }
            else{ // child 1005
                printf("(1005)I'm the child: %d and my parent is (1003) %d\n", getpid(), getppid());
                printf("Tamanho da string S: %d\n", strlen(S));
            }
        }
    }
    else{ // child 1002
        pid_t pid2 = fork();

        if(pid2 > 0){ // parent 1002 
            printf("(1002)I'm the child: %d and my parent is (1001)%d\n", getpid(), getppid());

            pid_t pid6 = fork();

            if(pid6> 0){ // parent 1002
                printf("(1002)I'm the %d and I'm parent of (1006)%d\n", getpid(),  pid6); 

                pid_t pid7 = fork();

                if(pid7 > 0){ // parent 1002
                    printf("(1002)I'm the %d and I'm parent of (1007)%d\n", getpid(),  pid7); 
                }
                else{ // child 1007
                    printf("(1007)I'm the child: %d and my parent is (1002) %d\n", getpid(), getppid());
                    show_consonants();
                }

            }
            else{ // child 1006
                printf("(1006)I'm the child: %d and my parent is (1002)%d\n", getpid(), getppid());
                show_lower_case_letters();
            }
        }
        else{ // child 1004
            printf("(1004)I'm the child: %d and my parent is (1002)%d\n", getpid(), getppid());
            show_upper_case_letters();
        }
    }

    return 0;
}
