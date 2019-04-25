/*
 * To change this license header, choose License Headers in Project Properties.
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

int equacao();

float pop[5][5];
float respop[5][5];

float b_nbh[5] = {100000, 100000, 100000, 100000, 100000};
float vet_x[5];

float y = 100000;
float x = 0;

int a = 20000;
float b = 100;

int main(int argc, char** argv) {

    srand(time(NULL)); //variação da seed do gerador de valores aleatórios


    int contador = 0;

    while (contador <= 100) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                pop[i][j] = a/2 - rand() % a;
                pop[i][j] = pop[i][j] / b;
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                respop[i][j] = pow(pop[i][j], 2) + 5 * pop[i][j] + 2;
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (respop[j][i] < b_nbh[i]) {
                    b_nbh[i] = respop[j][i];
                    vet_x[i] = pop[j][i];
                }
            }
        }

        for (int i = 0; i < 5; i++)
            if (y > b_nbh[i]) {
                y = b_nbh[i];
                x = vet_x[i];
            }
        equacao();
        contador++;
    }

    printf("(%.3f,%.3f)", x, y);

    return (EXIT_SUCCESS);
}

int equacao() {
    float vel = 0;
    float c1 = 0;
    float c2 = 0;
    vel = 4 + rand() % 4;
    vel = vel / 10;
    c1 = 1 + rand() % 4;
    c1 = c1 / 4;
    c2 = 1 + rand() % 4;
    c2 = c2 / 4;

    a = vel * c1 * (a - y) + c2 * a;
    return(a);
}