#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void filtroSobel(unsigned char *imagem, int largura, int altura)
{
    int mascaraHorizontal[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int mascaraVertical[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    unsigned char *imagemTemp = malloc(largura * altura * 3);

// Aplicar o filtro Sobel de forma paralela em blocos
#pragma omp parallel
    {
        int numThreads = omp_get_num_threads();
        int blockSize = altura / numThreads;
        int tid = omp_get_thread_num();
        int startY = tid * blockSize;
        int endY = (tid == numThreads - 1) ? altura : startY + blockSize;

        for (int y = startY + 1; y < endY - 1; y++)
        {
            for (int x = 1; x < largura - 1; x++)
            {
                int somaHorizontal = 0;
                int somaVertical = 0;

                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        int pixel = imagem[3 * ((y + i) * largura + (x + j))];
                        somaHorizontal += pixel * mascaraHorizontal[i + 1][j + 1];
                        somaVertical += pixel * mascaraVertical[i + 1][j + 1];
                    }
                }

                int valor = sqrt(somaHorizontal * somaHorizontal + somaVertical * somaVertical);
                imagemTemp[3 * (y * largura + x)] = (unsigned char)valor;
                imagemTemp[3 * (y * largura + x) + 1] = (unsigned char)valor;
                imagemTemp[3 * (y * largura + x) + 2] = (unsigned char)valor;
            }
        }
    }

    // Copiar a imagem resultante de volta para a imagem original
    for (int i = 0; i < largura * altura * 3; i++)
    {
        imagem[i] = imagemTemp[i];
    }

    free(imagemTemp);
}

int main()
{
    int largura, altura, canais;
    unsigned char *imagem = stbi_load("imagem.jpg", &largura, &altura, &canais, 0);
    if (!imagem)
    {
        fprintf(stderr, "Erro ao carregar a imagem.\n");
        return 1;
    }

    if (canais != 3)
    {
        fprintf(stderr, "A imagem deve ser colorida (3 canais RGB).\n");
        stbi_image_free(imagem);
        return 1;
    }

    double start_time = omp_get_wtime();

    filtroSobel(imagem, largura, altura);

    double end_time = omp_get_wtime();
    printf("Tempo de execução: %f segundos\n", end_time - start_time);

    if (!stbi_write_jpg("imagem_sobel.jpg", largura, altura, 3, imagem, 100))
    {
        fprintf(stderr, "Erro ao salvar a imagem resultante.\n");
    }

    stbi_image_free(imagem);

    printf("Filtro Sobel aplicado com sucesso. A imagem resultante foi salva como 'imagem_sobel.jpg'.\n");

    return 0;
}
