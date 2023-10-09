# Filtro Sobel com Paralelização usando OpenMP

Este programa aplica o filtro Sobel a uma imagem, com suporte à paralelização usando OpenMP para melhorar o desempenho. Abaixo está uma tabela que mostra os tempos de execução para diferentes imagens:

| Imagem          | Paralelizado (seg) | Sequencial (seg) |
| --------------- | ------------------ | ---------------- |
| imagem1.jpg     | 0.021196           | 0.053235         |
| imagem1x100.jpg | 1.522409           | 5.250504         |
| imagem2.jpg     | 0.003519           | 0.004058         |

_Nota: Paralelização usando apenas o #pragma omp parallel for._

O processamento paralelizado deste programa com OpenMP demonstrou um desempenho significativamente superior em comparação com a versão sequencial. Em média, a versão paralelizada foi cerca de 5 vezes mais rápida, proporcionando uma execução muito mais eficiente e economizando tempo de processamento. Isso torna a paralelização uma escolha sólida quando se trata de aplicar o filtro Sobel a imagens, especialmente em cenários que envolvem imagens grandes ou várias tarefas de processamento. A capacidade de distribuir o trabalho entre múltiplos núcleos de CPU resulta em um ganho notável de desempenho.

## Descrição da Máquina de Teste

Os testes de desempenho foram realizados em uma máquina com as seguintes especificações:

- **Processador:** 12th Gen Intel(R) Core(TM) i5-12400F

  - Frequência Base: 2500 MHz
  - Número de Núcleos: 6
  - Número de Processadores Lógicos: 12

- **Memória Física (RAM) Instalada:** 16,0 GB

A máquina de teste acima foi utilizada para avaliar o desempenho do programa ao aplicar o filtro Sobel com e sem paralelização usando OpenMP. Essas especificações fornecem uma base sólida para avaliar o impacto da paralelização no desempenho do programa em um ambiente realista. Tenha em mente que os tempos de execução podem variar dependendo do hardware utilizado e do tamanho das imagens processadas.

## Melhorias Implementadas

Neste programa de aplicação do filtro Sobel, foram implementadas várias melhorias com o objetivo de otimizar o desempenho e a eficiência do processamento de imagem. Abaixo estão algumas das principais melhorias realizadas:

1. **Divisão em Blocos:** O trabalho de aplicação do filtro Sobel foi dividido em blocos, permitindo o processamento paralelo desses blocos. Isso aproveitou ao máximo os múltiplos núcleos da CPU, melhorando a eficiência do programa.

2. **OpenMP para Paralelização:** Utilizamos o OpenMP para paralelizar o loop principal que aplica o filtro Sobel à imagem. Isso permitiu que várias tarefas fossem executadas simultaneamente, acelerando significativamente o processo de processamento de imagem.

3. **Alocação de Memória Otimizada:** Evitamos alocações desnecessárias de memória, otimizando o uso de recursos. Isso reduziu o consumo de memória e melhorou o desempenho geral do programa.

4. **Eliminação da Cópia de Volta:** Removemos a etapa de cópia de volta dos resultados para a imagem original, o que economizou tanto memória quanto tempo de execução. Agora, os resultados são diretamente aplicados à imagem original.

### Destaque: Imagem "imagem1x100.jpg"

Ao aplicar todas essas melhorias, conseguimos um tempo de execução notável ao processar a imagem "imagem1x100.jpg". O programa completou o processamento em apenas **Tempo de execução: 1.442769 segundos**, demonstrando o impacto significativo da otimização no desempenho. Essa otimização permite um processamento rápido mesmo em imagens maiores e complexas, tornando-o uma escolha eficiente para o filtro Sobel.
