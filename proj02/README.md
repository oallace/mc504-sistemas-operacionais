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
```
// Hiperparâmetros da aplicação
#define SLEEP_MAX 2
#define N_VAGAS 3

// Semáforos usados durante a aplicação
sem_t mutex, haVaga, vendaIngresso, salaVazia, impressaoLiberada;
// Contador de pessoas no cinema
int espectadores = 0;
int emExibcao = 1;

```c++

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
