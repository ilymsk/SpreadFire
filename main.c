#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOIS '0'
#define FEU '1'
#define CENDRE '2'

typedef struct {
    int x;
    int y;
} Coordinate;


void spreadFire(char **forest, int x, int y, int length_h, int length_l, float probability_fire) {
    // coordonnées des cellules voisines
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    // Pour chaque cellule voisine
    for (int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];

        // on vérifie si la cellule voisine est à l'intérieur de la grille
        if (new_x >= 0 && new_x < length_h && new_y >= 0 && new_y < length_l) {
            // Si la cellule voisine est du bois, la mettre en feu avec la probabilité de mise en feu
            if (forest[new_x][new_y] == BOIS && (float)rand() / RAND_MAX < probability_fire) {
                forest[new_x][new_y] = FEU;
            }
        }
    }
}


int main (){
    srand(time(NULL));
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


// Affichage de la grille initiale
    printf("\nGrille de la forêt initiale :\n");
    for (int i = 0; i < length_h; i++) {
        for (int j = 0; j < length_l; j++) {
            printf("%c ", forest[i][j]);
        }
        printf("\n");
    }

// Première propagation limitée du feu au début de la simulation
    for (int i = 0; i < num_fires; i++) {
        Coordinate current_fire = fire_index[i];
        spreadFire(forest, current_fire.x, current_fire.y, length_h, length_l, probability_fire);
    }


// Affichage de la grille après la première propagation du feu
    printf("\nGrille de la forêt après la première propagation du feu :\n");
    for (int i = 0; i < length_h; i++) {
        for (int j = 0; j < length_l; j++) {
            printf("%c ", forest[i][j]);
        }
        printf("\n");
    }


    char input; // initialisation de la variable d'entrée user

    while (num_fires > 0) {
        // pour chaque cellule en feu
        for (int i = 0; i < length_h; i++) {
            for (int j = 0; j < length_l; j++) {
                if (forest[i][j] == FEU) {
                    // eteindre le feu dans la cellule actuelle
                    forest[i][j] = CENDRE;
                    num_fires--;

                    // Propager le feu aux cellules voisines avec une certaine probabilité
                    spreadFire(forest, i, j, length_h, length_l, probability_fire);
                }
            }
        }

        printf("\nGrille de la forêt après cette étape de propagation du feu :\n");
        for (int i = 0; i < length_h; i++) {
            for (int j = 0; j < length_l; j++) {
                printf("%c ", forest[i][j]);
            }
            printf("\n");
        }

        // demande à l'utilisateur de taper une touche pour continuer ou 'x' pour quitter
        printf("Tapez 'x' pour quitter ou une autre touche pour continuer : ");
        scanf(" %c", &input);
    }

    return 0;
}