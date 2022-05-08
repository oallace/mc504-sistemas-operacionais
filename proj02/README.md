# Proj02 - Animação Multithread com Semáforos
## Festival de Cinema

Problema inspirado no problema clássico dos Leitores-Escritores. Suponha uma sala em um festival de cinema. Esta sala tem um total de N vagas. Enquanto houver vagas, espectadores podem entrar na sala, assistir o que está sendo exibido e sair quando quiser.
Além disso, o lanterninha responsável pela sala pode adentrar para fazer a manutenção adequeada e trocar o filme quando necessário.

### Regras do Festival

- Sendo N o número de vagas na sala de cinema, N espectadores podem assistir ao filme simultaneamente
- Caso um espectador tente entrar em uma sala lotada, deve esperar alguma vaga ser liberada
- O lanterninha deve esperar a sala esvaziar para adentrar a sala
- Assim que o lanterninha precisar dar manutenção à sala, ele impede a entrada de novos espectadores  e espera o esvaziamento da sala. Após a manutenção, retoma as atividades da sala

## Animação

o código [cinema.c](./cinema.c) propõe uma animação com caracteres conforme exemplificado abaixo:

```
||.....||
|       |
| * _ _ |
|_______|
```
- Indica que há um filme em exibição em uma sala com 3 vagas e que uma pessoa assiste naquele momento.
  - __*__ são pessoas assistindo ao filme
  - **_** indica cadeiras vazias

```
||#####||
|       |
| _ _ _ |
|_______|
```
- Indica que a sala está em manutenção. Idealmente todas as cadeiras devem estar vazias.

## Solução
O código com uma solução do problema pode ser encontrado em [./cinema.c](./cinema.c). Para compilá-lo, utilizado o arquivo [Makefile](./Makefile) disponibilizado.

### Destrinchando o código
```c
// Hiperparâmetros da aplicação
#define SLEEP_MAX 2
#define N_VAGAS 3

// Semáforos usados durante a aplicação
sem_t mutex, haVaga, vendaIngresso, salaVazia, impressaoLiberada;
// Contador de pessoas no cinema
int espectadores = 0;
int emExibcao = 1;
```
- O problema proposto trata de uma sala de cinema com 3 cadeiras. Para alterar o número de cadeiras da sala basta alterar o parâmetro `N_VAGAS`.
- O código usa 5 semáforos e 2 variáveis globais para guardar informações pertinentes, sendo:
  - `espectadores`: Número de espectadores presentes na sala
  - `emExibicao`: Igual a 1 quando o filme está sendo exibido. Quando a sala está em manutenção é igual a 0
  - `mutex`: Semáforo utilizado para ler e escrever a variável `espectadores`
  - `haVaga`: Semáforo que indica se há cadeiras disponíveis na sala de cinema
  - `vendaIngresso`: 1 quando a venda de ingressos está ativa, ou seja, quando o lanterninha permite a entrada de espectadores na sala
  - `salaVazia`: Utilizado para saber se a sala está vazia
  - `impressaoLiberada`: Utilizado para sincronizar a impressão da animação. Evita sobreposição.

```c
void *lanterninha(void *vgarp)
{
    // Interrompe a venda de ingressos
    sem_wait(&vendaIngresso);
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
    sem_post(&vendaIngresso);
    return NULL;
}
```
Função da thread lanterninha. a operação de manutenção da sala foi realizada com um sleep aleatório.

```c
void *espectador(void *vgarp)
{

    // Espera uma vaga no cinema
    sem_wait(&haVaga);
    // Compra um ingresso
    sem_wait(&vendaIngresso);
    sem_post(&vendaIngresso);
    // Alterações na contagem de espectadores
    sem_wait(&mutex);
    espectadores++;
    if (espectadores == 1)
        sem_wait(&salaVazia); // Indica que a sala não está mais vazia
    if (espectadores < N_VAGAS)
        sem_post(&haVaga);
    // Mostra o estado do cinema com a entrada do espectador
    imprime_cinema();
    sem_post(&mutex);

    // Entra na sala
    // Assiste ao filme
    sleep(SLEEP_MAX);
    
    // Sai na sala
    sem_wait(&mutex);
    espectadores--;
    if (espectadores == 0)
        sem_post(&salaVazia); // Indica que a sala está vazia
    if (espectadores == N_VAGAS - 1) // Liberou uma cadeira na sala
        sem_post(&haVaga);
    // Mostra o estado do cinema com a saída do espectador
    imprime_cinema();
    sem_post(&mutex);
    return NULL;
}
```
Função da thread espectador.

c```
int main() {
    // Inicia os semáforos
    sem_init(&mutex, 0, 1);
    sem_init(&vendaIngresso, 0, 1);
    sem_init(&haVaga, 0, 1);
    sem_init(&salaVazia, 0, 1);
    sem_init(&impressaoLiberada, 0, 1);

    // Exemplo de um dia de cinema
    pthread_t e1, e2, e3, e4, e5, e6, e7;
    pthread_t l1, l2;
    printf("Dia de Cinema:\n\n");
    imprime_cinema();
    pthread_create(&e1,NULL, espectador,NULL);
    pthread_create(&e2,NULL, espectador,NULL);
    pthread_create(&e3,NULL, espectador,NULL);
    pthread_create(&e4,NULL, espectador,NULL);
    sleep(1);
    pthread_create(&l1,NULL, lanterninha,NULL);
    pthread_create(&e5,NULL, espectador,NULL);
    sleep(1);
    pthread_create(&e6,NULL, espectador,NULL);
    sleep(1);
    pthread_create(&l2,NULL, lanterninha,NULL);
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
    sem_destroy(&vendaIngresso);
    sem_destroy(&haVaga);
    sem_destroy(&salaVazia);
    sem_destroy(&impressaoLiberada);

    return 0;
}
```
Função main com um exemplo.

Sobre o exemplo proposto:
- 4 espectadores tentam entrar na sala de cinema. Somente 3 devem conseguir entrar e um deve esperar a sua vez
- Após um tempo menor do que o tempo de permanência dos espectadores na sala, o lanterninha decide dar a manutenção da sala, portanto interrompe a venda de ingressos. Por isso, o espectador que estava esperando deve esperar agora o fim da manutenção para poder entrar na sala
- Um outro espectador decide entrar na sala
- Após um tempo, mais um espectador resolve entrar na sala
- Após um tempo, há novamente a manutenção da sala
- Por fim, mais um último espectador tenta entrar na sala

## Saída

```
Dia de Cinema:

||.....||
|       |
| _ _ _ |
|_______|

||.....||
|       |
| * _ _ |
|_______|

||.....||
|       |
| * * _ |
|_______|

||.....||
|       |
| * * * |
|_______|

||.....||
|       |
| * * _ |
|_______|

||.....||
|       |
| * _ _ |
|_______|

||.....||
|       |
| _ _ _ |
|_______|

||#####||
|       |
| _ _ _ |
|_______|

||.....||
|       |
| _ _ _ |
|_______|

||.....||
|       |
| * _ _ |
|_______|

||.....||
|       |
| _ _ _ |
|_______|

||#####||
|       |
| _ _ _ |
|_______|

||.....||
|       |
| _ _ _ |
|_______|

||.....||
|       |
| * _ _ |
|_______|

||.....||
|       |
| * * _ |
|_______|

||.....||
|       |
| * * * |
|_______|

||.....||
|       |
| * * _ |
|_______|

||.....||
|       |
| * _ _ |
|_______|

||.....||
|       |
| _ _ _ |
|_______|
```
