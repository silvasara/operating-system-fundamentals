#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

int a[2000][2000];
int b[2000][2000];
int c[2000][2000];

int N = 0;

int pronto1 = 0, pronto2 = 0;

int metade = 0;

void filho1_pronto(){
    pronto1 = 1;
    fprintf(stderr, "pronto1 recebido\n");
}

void filho2_pronto(){
    pronto2 = 1;
    fprintf(stderr, "pronto2 recebido\n");
}

void imprime_parte1(){
    fprintf(stderr, "entree em imprime_parter1()\n");
    int j = 0;
    //int lim = (N%2) ? (N/2)+1 : N/2;
    //int lim = (N%2) ? metade+1 : metade;
    for(int i=0; i<metade; i++){
        j = 0;
        printf("%d", c[i][j]);
        for(j=1; j<N; j++){
            printf(" %d", c[i][j]);
        }
        printf("\n");
    }
}

void imprime_parte2(){
    fprintf(stderr, "entree em imprime_parter2()\n");
    int j = 0;
    
    //for(int i = (N%2) ? (N/2)+1 : N/2; i<N; i++){
    for(int i = metade; i<N; i++){
        j = 0;
        printf("%d", c[i][j]);
        for(int j=1; j<N; j++){
            printf(" %d", c[i][j]);
        }
        printf("\n");
    }
}

void trata_filho1(){
    fprintf(stderr, "entree em trata_filho1()\n");
    signal(SIGUSR1, imprime_parte1);     
    while(!N) sleep(1);
    for(int j=0; j<N; j++){
        //for(int i=0; i<=N/2; i++){
        for(int i=0; i< metade; i++){
            int soma = 0;
            for(int k=0; k<N; k++){
                soma += a[i][k]*b[k][j];
                //printf("@ %d\n", c[i][j]);
            }
                c[i][j] = soma;
        }
    }
    kill(getppid(), SIGUSR1);
    pause();
}

void trata_filho2(){
    fprintf(stderr, "entree em trata_filho2()\n");
    signal(SIGUSR1, imprime_parte2);     

    while(!N) sleep(1);
    for(int j=0; j<N; j++){
        //for(int i=N-N/2; i<N; i++){
        for(int i=metade; i<N; i++){
            int soma = 0;
            for(int k=0; k<N; k++){
                soma += a[i][k]*b[k][j];
                //printf("# %d\n", c[i][j]);
            }
                c[i][j] = soma;
        }
    }

    fprintf(stderr,"2Enviando para %d \n", getppid());
    kill(getppid(), SIGUSR2);
    pause();
}

int main(){
    signal(SIGUSR1, filho1_pronto);
    signal(SIGUSR2, filho2_pronto);

    scanf("%d", &N);
    
    metade = N/2 + (N%2!=0);

    memset(a, -1, sizeof(a));
    memset(b, -1, sizeof(b));
    memset(c, -1, sizeof(c));

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &a[i][j]); 
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &b[i][j]); 
        }
    }
    
    
    pid_t filho1 = fork();

    if(filho1 == 0){
        trata_filho1();
    }
    else{
        pid_t filho2 = fork();
        if(filho2 == 0){
            trata_filho2();
        }
        else{
           fprintf(stderr, "%d esperando\n", getpid());
           while(!pronto1 || !pronto2) sleep(1);

           kill(filho1, SIGUSR1);
           int status = 0;
           wait(&status);

           kill(filho2, SIGUSR1);
           wait(&status);
           fprintf(stderr, "final do pai\n");
        }
    }
    

    return 0;
}
