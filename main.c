#include <stdio.h>
#include <stdlib.h>

int main (){

    //Récupération des paramètres du fichier externe et vérification de ceux-ci
    FILE* params = NULL;

    params = fopen("params.txt", "r");

    if (params == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    int length_l, length_h;
    float probability_fire;
    int initial_fire_x, initial_fire_y;

    fscanf(params, "length_l = %d\n", &length_l);
    fscanf(params, "length_h = %d\n", &length_h);
    fscanf(params, "probability_fire = %f\n", &probability_fire);
    fscanf(params, "initial_fire_x = %d\n", &initial_fire_x);
    fscanf(params, "initial_fire_y = %d\n", &initial_fire_y);

    fclose(params);

    printf("length_l = %d\n", length_l);
    printf("length_h = %d\n", length_h);
    printf("probability_fire = %f\n", probability_fire);
    printf("initial_fire_x = %d\n", initial_fire_x);
    printf("initial_fire_y = %d\n", initial_fire_y);

    //création de la grille qu'on remplit avec des 0 dans un premier temps

    char **forest = (char **)malloc(length_h * sizeof(char *));
    for (int i = 0; i < length_h; i++) {
        forest[i] = (char *)malloc(length_l * sizeof(char));
    }

    for (int i = 0; i < length_h; i++) {
        for (int j = 0; j < length_l; j++) {
            forest[i][j] = '0';
        }
    }


    printf("\nGrille de la forêt initiale :\n");
    for (int i = 0; i < length_h; i++) {
        for (int j = 0; j < length_l; j++) {
            printf("%c ", forest[i][j]);
        }
        printf("\n");
    }
    return 0;
}