# Proj02 - Animação Multithread com Semáforos
## Festival de Cinema

Problema inspirado no problema clássico dos Leitores-Escritores. Suponha uma sala em um festival de cinema. Esta sala tem um total de N vagas. Enquanto houver vagas, espectadores podem entrar na sala, assistir o que está sendo exibido e sair quando quiser.
Além disso, o lanterninha responsável pela sala pode adentrar para fazer a manutenção adequeada e trocar o filme quando necessário.

## Regras do Festival
- Sendo N o número de vagas na sala de cinema, N espectadores podem assistir ao filme simultaneamente
- Caso um espectador tente entrar em uma sala lotada, deve esperar alguma vaga ser liberada
- O lanterninha deve esperar a sala esvaziar para adentrar a sala
- Assim que o lanterninha precisar dar manutenção à sala ele deve esperar a sala ficar vazia e impede a entrada de novos espectadores até que a manuenção seja finalizada
