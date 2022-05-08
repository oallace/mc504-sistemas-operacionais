// Autor: Wallace G S Lima, RA 195512
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

// Hiperparâmetros da aplicação
#define SLEEP_MAX 2
#define N_VAGAS 3

// Semáforos usados durante a aplicação
sem_t mutex, haVaga, salaVazia, impressaoLiberada;
// Contador de pessoas no cinema
int espectadores = 0;
int emExibcao = 1;

void imprime_cinema()
{
    sem_wait(&impressaoLiberada);
    // Imprime a tela do cinema
    putchar('|');
    for (int _ = 0; _ < N_VAGAS - 3; _++)
        putchar('=');
    putchar('|');
    if (emExibcao)
        printf(".....");
    else
        printf("#####");
    putchar('|');
    for (int _ = 0; _ < N_VAGAS - 3; _++)
        putchar('=');
    putchar('|');
    // 
    putchar('\n');
    putchar('|');
    printf("%*s", N_VAGAS, "");
    if (emExibcao)
        putchar(' ');
    else
        putchar('L');
    printf("%*s", N_VAGAS, "");
    putchar('|');
    // Imprime as cadeiras
    putchar('\n');
    putchar('|');
    for (int _ = 0; _ < espectadores; _++)
        printf(" *");
    for (int _ = 0; _ < N_VAGAS - espectadores; _++)
        printf(" _");
    putchar(' ');
    putchar('|');
    putchar('\n');
    // Imprime parede de trás
    putchar('|');
    for (int _ = 0; _ < N_VAGAS * 2 + 1; _++)
        putchar('_');
    putchar('|');
    putchar('\n');
    putchar('\n');
    sem_post(&impressaoLiberada);
}

void *lanterninha(void *vgarp)
{
    // Indica que nao há vaga no cinema devido à manutenção da sala
    sem_wait(&haVaga);
    // Aguarda a saída de todos os espectadores da sala
    sem_wait(&salaVazia);

    // Troca o filme em exibição
    emExibcao = 0;
    imprime_cinema();
    sleep(rand() % SLEEP_MAX);
    emExibcao = 1;
    imprime_cinema();
    // Sai da Sala
    sem_post(&salaVazia);
    // Retoma as atividades da sala
    sem_post(&haVaga);
    return NULL;
}

void *espectador(void *vgarp)
{

    // Espera uma vaga no cinema
    sem_wait(&haVaga);
    // Alterações na contagem de espectadores
    sem_wait(&mutex);
    espectadores++;
    if (espectadores == 1)
        sem_wait(&salaVazia); // Indica que a sala não está mais vazia
    if (espectadores < N_VAGAS)
        sem_post(&haVaga);
    imprime_cinema();
    sem_post(&mutex);

    // Entra na sala
    // Assiste ao filme
    sleep(rand() % SLEEP_MAX);
    
    // Sai na sala
    sem_wait(&mutex);
    espectadores--;
    if (espectadores == 0)
        sem_post(&salaVazia); // Indica que a sala está vazia
    if (espectadores == N_VAGAS - 1) // Liberou uma cadeira na sala
        sem_post(&haVaga);
    imprime_cinema();
    sem_post(&mutex);
    return NULL;
}

int main() {
    // Inicia os semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&haVaga, 0, 1);
    sem_init(&salaVazia, 0, 1);
    sem_init(&impressaoLiberada, 0, 1);

    // Exemplo de um dia de cinema
    pthread_t e1, e2, e3, e4, e5, e6, e7;
    pthread_t l1, l2, l3;
    printf("Dia de Cinema:\n\n");
    imprime_cinema();
    pthread_create(&e1,NULL, espectador,NULL);
    pthread_create(&e2,NULL, espectador,NULL);
    pthread_create(&l1,NULL, lanterninha,NULL);
    pthread_create(&e3,NULL, espectador,NULL);
    pthread_create(&l2,NULL, lanterninha,NULL);
    pthread_create(&e4,NULL, espectador,NULL);
    pthread_create(&e5,NULL, espectador,NULL);
    pthread_create(&e6,NULL, espectador,NULL);
    pthread_create(&e7,NULL, espectador,NULL);
    pthread_join(e1,NULL);
    pthread_join(e2,NULL);
    pthread_join(e3,NULL);
    pthread_join(e4,NULL);
    pthread_join(e5,NULL);
    pthread_join(e6,NULL);
    pthread_join(e7,NULL);
    pthread_join(l1,NULL);
    pthread_join(l2,NULL);
    // Destrói os semáforos utilizados
    sem_destroy(&mutex);
    sem_destroy(&haVaga);
    sem_destroy(&salaVazia);
    sem_destroy(&impressaoLiberada);

    return 0;
}