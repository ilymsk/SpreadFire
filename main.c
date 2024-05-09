#include <stdio.h>


int main (){

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

    return 0;
}