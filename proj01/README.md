# proj01 - Aplicação em Multithreads

## Enunciado

Este projeto visa o desenvolvimento de uma primeira aplicação utilizando  pthreads, com escolha de tema livre, sem necessidade do uso de  mecanismos de sincronização. É necessário indicar o tema, a estrutura de dados principal e a estratégia de divisão de trabalho entre as threads. Também devem ser indicados links para o código e documentação.

## Tema

Aplicação de Filtros 2d em uma imagem PGMB.

## Estruturas de dados
A Estrutura de Dados principal empregada no trabalho é a estrutura PGMImage, estrutura que foi utilizada para armazenar os dados de uma imagem PGMB. A estrutura possui campos para o armazenamento das informações pertinentes da imagem, como o tipo de imagem, o valor máximo por pixel, a altura e a largura. Além disso, possui um campo para armazenar os valores dos pixels da imagem:

    PGMimage.pgmType: descritor do arquivo pgmb;
    PGMimage.height: altura da imagem;
    PGMimage.width: largura da imagem;
    PGMimage.maxValue: valor máximo de um pixel da imagem;
    PGMimage.data: matriz que guarda os pixels da imagem.

## Divisão de Trabalho das Threads

O projeto consiste na aplicação de um filtro 2D a uma imagem. A estratégia adotada para isso foi que cada uma das N (N = 3) threads especificadas fica responsável por linhas intercaladas. Ou seja, a thread X aplica o filtro aos pixels das linhas tais que: `i mod N = X`, onde i é o índice da linha.

## Compilando

Pode-se compilar o programa _filter_ por meio de comando `make`.

## Organização do projeto
### PGM reader/writer

Para a leitura e escrita de arquivos de imagem PGMB no projeto, foi utilizado o código de [pgm.c](./pgm.c), referenciado por [pgm.h](./pgm.h). Arquivos estes inspirados [nesta leitura](https://www.geeksforgeeks.org/how-to-read-a-pgmb-format-image-in-c/).

### Aplicador de Filtro

O código [filter.c](./filter.c) é o aplicador de filtros. O filtro definido para a execução da forma como está escrito é um filtro detector de bordas, entretanto pode-se muda-lo apenas comentando e descomentando a atribuição da variável global `filter`.

## Exemplo de aplicação

O programa foi compilado e rodado sobre a imagem [baboon.pgm](data/baboon.pgm) para os 3 filtros: desfoque, realçador de forma, detector de bordas. O resultado pode ser encontrado [na pasta](output_examples)
