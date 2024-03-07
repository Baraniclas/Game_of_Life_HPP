#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void print_array(int **matrix);
void primordial_soup(int **matrix);
void count_neighbours(int **matrix);
void update();
void reset_matrix(int ** matrix);
void renderGrid(SDL_Renderer *renderer);

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define CELL_SIZE 25
#define GRID_WIDTH 1000
#define GRID_HEIGHT 1000

int sz;
int lim;
int el, eu, fl, fu, time_steps;
int **cells;
int **neighbours;
int grid[GRID_WIDTH][GRID_HEIGHT] = {0}; // Initialize grid

int main() {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);


    sz = 1000; // set size of tensor in 3D
    el = 2;     // environment lower 
    eu = 3;     // environment upper
    fl = 3;     // fertility lower
    fu = 3;     // fertility upper
    time_steps = 100;
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
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_Quit();
                return 0;
            }
        }
        count_neighbours(cells);
        update();
        reset_matrix(neighbours);
        // print_array(cells);
        // printf("\n");

        renderGrid(renderer);

        SDL_Delay(100); // Adjust speed of simulation
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

void renderGrid(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    // Render each cell
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (cells[x][y] == 1) {
                SDL_Rect cellRect = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black cell
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}


// https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus hashtables