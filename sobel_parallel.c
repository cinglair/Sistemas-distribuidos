#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Função para aplicar o filtro Sobel a uma imagem
void filtroSobel(unsigned char *imagem, int largura, int altura)
{
    // Definir as máscaras Sobel para detecção de bordas horizontal e vertical
    int mascaraHorizontal[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int mascaraVertical[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Criar uma matriz temporária para armazenar a imagem após a aplicação do filtro
    unsigned char *imagemTemp = malloc(largura * altura * 3); // Correção na alocação de memória

// Aplicar o filtro Sobel de forma paralela nas linhas da imagem
#pragma omp parallel for
    for (int y = 1; y < altura - 1; y++)
    {
        for (int x = 1; x < largura - 1; x++)
        {
            int somaHorizontal = 0;
            int somaVertical = 0;

            // Aplicar a máscara horizontal e vertical
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int pixel = imagem[3 * ((y + i) * largura + (x + j))]; // Correção para lidar com os canais RGB
                    somaHorizontal += pixel * mascaraHorizontal[i + 1][j + 1];
                    somaVertical += pixel * mascaraVertical[i + 1][j + 1];
                }
            }

            // Calcular o valor do pixel após a aplicação do filtro
            int valor = sqrt(somaHorizontal * somaHorizontal + somaVertical * somaVertical);
            imagemTemp[3 * (y * largura + x)] = (unsigned char)valor;     // Correção para lidar com os canais RGB
            imagemTemp[3 * (y * largura + x) + 1] = (unsigned char)valor; // Canais G e B com o mesmo valor
            imagemTemp[3 * (y * largura + x) + 2] = (unsigned char)valor;
        }
    }

    // Copiar a imagem resultante de volta para a imagem original
    for (int i = 0; i < largura * altura * 3; i++) // Correção na cópia dos canais RGB
    {
        imagem[i] = imagemTemp[i];
    }

    // Liberar a memória da imagem temporária
    free(imagemTemp);
}

int main()
{
    // Carregar a imagem usando a biblioteca stb_image
    int largura, altura, canais;
    unsigned char *imagem = stbi_load("imagem.jpg", &largura, &altura, &canais, 0);
    if (!imagem)
    {
        fprintf(stderr, "Erro ao carregar a imagem.\n");
        return 1;
    }

    // Verificar se a imagem tem 3 canais (RGB)
    if (canais != 3)
    {
        fprintf(stderr, "A imagem deve ser colorida (3 canais RGB).\n");
        stbi_image_free(imagem);
        return 1;
    }

    // Iniciar o tempo de medição
    double start_time = omp_get_wtime();

    filtroSobel(imagem, largura, altura);

    // Parar o tempo de medição
    double end_time = omp_get_wtime();
    printf("Tempo de execução: %f segundos\n", end_time - start_time);

    // Salvar a imagem resultante
    if (!stbi_write_jpg("imagem_sobel.jpg", largura, altura, 3, imagem, 100))
    {
        fprintf(stderr, "Erro ao salvar a imagem resultante.\n");
    }

    // Liberar a memória da imagem
    stbi_image_free(imagem);

    printf("Filtro Sobel aplicado com sucesso. A imagem resultante foi salva como 'imagem_sobel.jpg'.\n");

    return 0;
}
