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

o código proposto, [cinema.c](./cinema.c), propõe uma animação com caracteres conforme exemplificado abaixo:

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
- Indica que a sala está em manutenção. Idealmente todas as cadeiras devem estar vazias
