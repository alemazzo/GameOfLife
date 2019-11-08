/*
Autori : {
    Mazzoli Alessandro,
    Andruccioli Manuel,
    Ponteggi Luca,
    Ciccioli Simone
}
Data : Data di scadenza
Esercizio : Settimana  - Esercizio 
Consegna : testo dell'esercizio
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
//Includere qui altre librerie

#define RANDOM(min, max) (int)(min + (rand() + time(NULL)) % (max - min + 1))
#define COPY_MATRIX(destination, source, rows, columns) for(int i = 0; i < rows; i++) for(int j = 0; j < columns; j++) destination[i][j] = source[i][j];
#define CLEAR_STDIN() while(getchar() != '\n');

#define DIMENSIONE 30

#define VIVA 1
#define MORTA 0

void printMatrix(int rows, int columns, int campo[rows][columns]){
    
    system("cls");

    int total_char = (rows * ((2 * columns) + 2)) + 1;
    char output[total_char];
    int index = 0;
    for(int row = 0; row < rows; row++){ 
        for (int column = 0; column < columns; column++){
            output[index++] = '|';
            if(campo[row][column] == VIVA)
                output[index++] = 'o';
            else
                output[index++] = ' ';
        }      
        output[index++] = '|';  
        output[index++] = '\n';       
    }
    output[index++] = '\0';
    fputs(output, stdout);
    //puts(output);
}

int main(int argc, char const *argv[]) {
    
    printf("Press enter to start");
    getchar();
    //Inizializzazione
    int campo[DIMENSIONE][DIMENSIONE];

    for(int indice = 0; indice < (DIMENSIONE * DIMENSIONE); indice++)
        *(*campo + indice) = RANDOM(0, 1);

    while(1){
        //Stampa
        printMatrix(DIMENSIONE, DIMENSIONE, campo);

        //Campo successivo
        int newCampo[DIMENSIONE][DIMENSIONE];

        for(int riga = 0; riga < DIMENSIONE; riga++){
            for (int colonna = 0; colonna < DIMENSIONE; colonna++)
            {
                int up = riga > 0 && campo[riga - 1][colonna] == 1 ? 1 : false;
                int dw = riga < (DIMENSIONE - 1) && campo[riga + 1][colonna] == 1 ? 1 : 0;
                int sx = colonna > 0 && campo[riga][colonna - 1] == 1 ? 1 : 0;
                int dx = colonna < (DIMENSIONE - 1) && campo[riga][colonna + 1] == 1 ? 1 : 0;

                int upsx = colonna > 0 && riga > 0 && campo[riga - 1][colonna - 1] == 1 ? 1 : 0;
                int updx = colonna < (DIMENSIONE - 1) && riga > 0 && campo[riga - 1][colonna + 1] == 1 ? 1 : 0;
                int dwsx = colonna > 0 && riga < (DIMENSIONE - 1) && campo[riga + 1][colonna - 1] == 1 ? 1 : 0;
                int dwdx = colonna < (DIMENSIONE - 1) && riga < (DIMENSIONE - 1) && campo[riga + 1][colonna + 1] == 1 ? 1 : 0;

                int celluleVicine = up + dw + sx + dx + upsx + updx + dwsx + dwdx;
                if(campo[riga][colonna] == VIVA){
                    
                    switch (celluleVicine)
                    {
                    case 2 ... 3:
                        newCampo[riga][colonna] = VIVA;
                        break;                    
                    default:
                        newCampo[riga][colonna] = MORTA;
                        break;
                    }

                }else{

                    switch (celluleVicine)
                    {
                    case 3:
                        newCampo[riga][colonna] = VIVA;
                        break;                    
                    default:
                        newCampo[riga][colonna] = MORTA;
                        break;
                    }
                }
                
            }            
        }

        COPY_MATRIX(campo, newCampo, DIMENSIONE, DIMENSIONE);
        
    }

    //End of the program.
    printf("Press any key to exit...");
    CLEAR_STDIN();
    getchar();
    return 0;
}