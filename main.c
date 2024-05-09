#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

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

    //création de la grille

    char **forest = (char **)malloc(length_h * sizeof(char *));
    for (int i = 0; i < length_h; i++) {
        forest[i] = (char *)malloc(length_l * sizeof(char));
    }

    // création d'un tableau d'index ou seront stocker les coordonnées des cases en feu
    // cela va nous permettre de vérifier les cases adjacents aux cases en feu au lieu de parcourir l'ensemble de la grille
    Coordinate *fire_index = (Coordinate *)malloc(length_h * length_l * sizeof(Coordinate));
    int num_fires = 0;

    for (int i = 0; i < length_h; i++) {
        for (int j = 0; j < length_l; j++) {
            forest[i][j] = '0';
        }
    }

    //pour positionner la première case en feu
    forest[initial_fire_x][initial_fire_y] = '1';
    fire_index[num_fires].x = initial_fire_x;
    fire_index[num_fires].y = initial_fire_y;
    num_fires++;

    // Affichage de la grille
    printf("\nGrille de la forêt initiale :\n");
    for (int i = 0; i < length_h; i++) {
        for (int j = 0; j < length_l; j++) {
            printf("%c ", forest[i][j]);
        }
        printf("\n");
    }
    return 0;
}