#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// Função executada pelo processo filho
void child_process(){
    printf("CHILD (PID: %d) em execução...\n", getpid()); // Imprime mensagem indicando que o processo filho está em execução
    sleep(1); // Aguarda por 1 segundo para que o processo filho exiba sua mensagem
    printf("CHILD (PID: %d) entrando em pausa...\n", getpid()); // Imprime mensagem indicando que o processo filho está entrando em pausa
    while(1) pause(); // Fica em pausa indefinidamente até que o processo filho receba um sinal que encerre seu processo 
}

// Função executada pelo processo pai
void parent_process(pid_t child_pid){
    printf("PARENT (PID: %d) em execução...\n", getpid()); // Imprime mensagem indicando que o processo pai está em execução
    sleep(2); // Aguarda por 2 segundos para que o processo pai exiba sua mensagem
    printf("CHILD (PID %d) Enviando SIGTERM para CHILD em instantes...\n", getpid()); // Imprime mensagem indicando que o processo pai enviará um sinal SIGTERM para o processo filho em breve
    sleep(5); // Aguarda por 5 segundos para que o processo pai exiba sua mensagem
    printf("PARENT (PID %d) Enviando SIGTERM para CHILD...\n",getpid()); // Imprime mensagem indicando que o processo pai está enviando um sinal SIGTERM para o processo filho
    kill(child_pid, SIGTERM); // Envia um sinal SIGTERM para o processo filho
    wait(NULL); // Espera pelo término do processo filho
}

int main(){
    pid_t pid = fork(); // Cria um novo processo que identifica o processo do pai
    if(pid == 0){ // Se o processo atual é o processo filho
        signal(SIGCONT, SIG_IGN); // Ignora o sinal SIGCONT
        signal(SIGTERM, SIG_IGN); // Ignora o sinal SIGTERM
        child_process(); // Chama a função que define o comportamento do processo filho
    }
    else if(pid > 0) parent_process(pid); // Se o processo atual é o processo pai
    else{ // Se ocorreu um erro ao criar o processo
        perror("fork"); // Imprime uma mensagem de erro
        exit(EXIT_FAILURE); // Encerra o programa com status de falha
    }
    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
