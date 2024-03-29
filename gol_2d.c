#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int sz;
int lim;
int el, eu, fl, fu, time_steps;
int **cells;
int **neighbours;

void print_array(int **matrix);
void primordial_soup(int **matrix);
void count_neighbours(int **matrix);
void update();
void reset_matrix(int ** matrix);

int main() {
    sz = 10; // set size of tensor in 3D
    el = 2;     // environment lower 
    eu = 3;     // environment upper
    fl = 3;     // fertility lower
    fu = 3;     // fertility upper
    time_steps = 15;
    lim = 50;

    srand(4);       // set to 4 just to be consistent
    // srand(time(NULL));      // sets the random number generator seed based on the current time, can be set to specific number.
    
    // initiate matrix with cells
    cells = (int **)calloc(sz, sizeof(int *));
    for (int i = 0; i < sz; i++) {
        cells[i] = (int *)calloc(sz, sizeof(int));
    }

    neighbours = (int **)calloc(sz, sizeof(int *));
    for (int i = 0; i < sz; i++) {
        neighbours[i] = (int *)calloc(sz, sizeof(int));
    }

    // create primordial soup
    primordial_soup(cells);
    print_array(cells);
    printf("\n");

    printf("loops begin here \n");

    for (int i = 0; i < time_steps; i++){
        count_neighbours(cells);
        update();
        reset_matrix(neighbours);
        print_array(cells);
        printf("\n");
    }

    
    // print_array(neighbours);

    return 0;
}

void print_array(int **matrix) {
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void primordial_soup(int **matrix){
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++) {
            int random_number = rand() % 101; // produces random number between 0 and 100
            printf("random number: %d \n", random_number);
            if (random_number > lim)
                matrix[i][j] = 1;
        }
}

void count_neighbours(int **matrix) {
    int sum;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            sum = 0;
            if (j-1 >= 0 && matrix[i][j-1] == 1)
                sum += 1;
            if (j+1 < sz && matrix[i][j+1] == 1)
                sum += 1;
            for (int k = j-1; k <= j+1; k++) {
                if (i-1 >= 0 && matrix[i-1][k] == 1)
                    sum += 1;
                if (i+1 < sz && matrix [i+1][k] == 1)
                    sum += 1; 
            }
            neighbours[i][j] = sum;   
        }
    }
}

void update() {
    int cell;
    int count;
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            cell = cells[i][j];
            count = neighbours[i][j];
            if ((cell == 1) && ((el > count) || (count > eu)))
                cells[i][j] = 0;
            if ((cell == 0) && ((fl <= count) && (count <= fu)))
                cells[i][j] = 1;
            }
        }   
    }

void reset_matrix(int **matrix) {
    for (int i = 0; i < sz; i++) {
        memset(matrix[i], 0, sz * sizeof(int));
    }
}

// change matrix

// https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus hashtables