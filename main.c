/*To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 * File:   main.c
 * Author: usuario
 *
 * Created on 18 de Abril de 2019, 21:06
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define BGPRETO "\033[1;40m"
#define FGBRANCO "\033[1;97m "
#define RESET "\033[0;0m "

float equacao(float b, float c);


float pop[5][5]; //População aleatória gerada pelo comando rand()
float respop[5][5]; //Recebe o valor de y para cada partícula que passa na função

float b_nbh[5] = {100000, 100000, 100000, 100000, 100000};
//Armazena os melhores valores de cada linha (melhor na vizinhança)
float vet_x[5];
//Armazena o valor de X correspondente ao melhor valor de Y

float y = 100000;
//Armazena o melhor valor global daquela iteração
float x = 0;
//Armazena o melhor valor global de x relativo a Y

int a = 20000;
//Taxa de geração aleatória inicial do Random
float b = 100;
//Divisão por 100 para geração de valores decimais na pop

int main(int argc, char** argv) {

    srand(time(NULL)); //variação da seed do gerador de valores aleatórios


    int contador = 0;

    while (contador <= 100) { //número de iterações ajustado em 100
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                pop[i][j] = a / 2 - rand() % a;
                pop[i][j] = pop[i][j] / b;
            }
        }

        /*Atribui valores aleatórios para a populaçao baseado na taxa "a" que
         * é gerada inicialmente em 20000 e depois se modifica de acordo com 
         * a função "equação()", visando uma diminuição da área de busca de
         * partículas
         */

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                respop[i][j] = pow(pop[i][j], 2) + 5 * pop[i][j] + 2;
            }
        }
        
        /*Armazena os valores de Y após a partícula X passar pela função.
         * No caso, a função é X² + 5X + 2, cujos menor valor possível é
         * (-2.5, -4.25), aferido no aplicativo Geogebra
         */

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (respop[j][i] < b_nbh[i]) {
                    b_nbh[i] = respop[j][i];
                    vet_x[i] = pop[j][i];
                }
            }
        }
        
        /*Compara os valores de cada linha e armazena o melhor valor possível
         * no vetor b_nbh(abreviação de best_neighborhood) e consequentemente
         * armazena o valor de x relativo àquele valor
         */

        for (int i = 0; i < 5; i++)
            if (y > b_nbh[i]) {
                y = b_nbh[i];
                x = vet_x[i];
            }
        // Armazena o melhor valor da vizinhança na 
        // variável Y e seu respectivo em X
        
        
        
        a = equacao(a, y);
        contador++;
    }

    printf("┌─────────────────────────────┐\n");
    printf("│O menor valor da sua função: │\n");
    printf("├──────┬───────┬───────┬──────┤\n");
    printf("│######│   x   │   y   │######│\n");
    printf("├──────┼───────┼───────┼──────┤\n");
    printf("│######│%.4f│%.4f│######│\n", x, y);
    printf("└──────┴───────┴───────┴──────┘\n");

    // Mostra na tela o valor de x e y
    return (EXIT_SUCCESS);
}
/**
 * Essa função modifica a taxa de geração do Rand()
 * baseado no melhor valor e na taxa atual
 * @return uma nova taxa "a"
 */
float equacao(float b, float c) {
    float vel = 0;
    float c1 = 0;
    float c2 = 0;
    vel = 4 + rand() % 4;
    vel = vel / 10;
    c1 = 1 + rand() % 4;
    c1 = c1 / 4;
    c2 = 1 + rand() % 4;
    c2 = c2 / 4;

    a = vel * c1 * (b - c) + c2 * b;
    return (a);
}