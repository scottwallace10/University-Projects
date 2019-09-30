#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "life.h"

/* Be sure to read life.h and the other given source files to understand
 * what they provide and how they fit together.  You don't have to
 * understand all of the code, but you should understand how to call
 * parse_life() and clearterm().
 */

/* This is where your program will start.  You should make sure that it
 * is capable of accepting either one or two arguments; the first
 * argument (which is required) is a starting state in one of the Life
 * formats supported by parse_life(), and the second (which is optional)
 * is a number of generations to run before printing output and stopping.
 *
 * The autograder will always call your program with two arguments.  The
 * one-argument format (as described in the handout) is for your own
 * benefit!
 */

void next_generation_rules(int y, int x,  char grid[2][GRIDY][GRIDX]);

void compute_rules(char[2][GRIDY][GRIDX]);

void output_grid(char **cell,char grid[2][GRIDY][GRIDX]);

void print_state(char grid[2][GRIDY][GRIDX]);

void next_gen(char grid[2][GRIDY][GRIDX]);

int usleep(suseconds_t usec);

void z_axis();
int gen_number = 0;
int current_gen = 0;
int z = 0;

int main(int argc, char *argv[]){
    if(argc > 1 && argc <= 3){
        char **cell = parse_life(argv[1]);
        char grid[2][GRIDY][GRIDX];
        output_grid(cell,grid);
        if(argc == 3){
            char second_arg[strlen(argv[2])];
            for(int i = 0; i < strlen(argv[2]); i++){      //converts the second argument of the terminal into an integer so it can be used as the generation number.
                    second_arg[i] = argv[2][i];
                    if(!isdigit(second_arg[i])){
                        printf("This is not a digit");
                        return 1;
                    }
                }
            gen_number = atoi(second_arg);
            if(gen_number < 0){
                printf("%s", "Can't be a negative for the generations");
                return 1;
            }
            else if(gen_number == 0){
                print_state(grid);
            }
            else{
                next_gen(grid);
            }
    }
    }
    else if(argc > 3){
        printf("%s", "Too many args");
        return 1;
    }
    else{
        printf("Another error");
        return 1;
    }
    return 0;
}
/*
this function computes the next generation given the rules of the game of life by counting the neighbor number and the rules applied to the neighbors.
*/


void next_generation_rules(int y, int x, char grid[2][GRIDY][GRIDX]){
    int neighbor_number = 0;
 
    if(x > 0 && y > 0) {
        if(grid[z][y-1][x-1] == LIVE){
            neighbor_number++;
        }  
    }
    if(x > 0){
        if(grid[z][y][x-1] == LIVE){
            neighbor_number++;
        }
    }

    if(y > 0){
        if(grid[z][y-1][x] == LIVE){
             neighbor_number++;   
    }
        
    }
    if(x < GRIDX - 1){
        if(grid[z][y][x+1] == LIVE){
            neighbor_number++;
        }
        if(grid[z][y-1][x+1] == LIVE){
            neighbor_number++;
        }
        
    }
    if(y < GRIDY - 1){
        if(grid[z][y+1][x] == LIVE){
            neighbor_number++;
        }
        if(grid[z][y+1][x-1] == LIVE){
            neighbor_number++;
        }
    }
    if(x < GRIDX - 1 && y < GRIDY - 1){
        if(grid[z][y+1][x+1] == LIVE){
            neighbor_number++;
        }
        
    }
    if(grid[z][y][x] == LIVE && (neighbor_number == 2 || neighbor_number == 3)){
        if(z == 0){
            grid[1][y][x] = LIVE;
        }
        else if(z == 1){
            grid[0][y][x] = LIVE;
        }
    }
    else if(grid[z][y][x] == DEAD && (neighbor_number == 3)){
        if(z == 0){
            grid[1][y][x] = LIVE;
        }
        else if (z == 1){
            grid[0][y][x] = LIVE;
        }
    }
    else if(neighbor_number < 2 || neighbor_number > 3){
        if(z == 0){
            grid[1][y][x] = DEAD;
        }
        else if(z == 1){
            grid[0][y][x] = DEAD;
        }
    }
    else{
        if(z == 0){
            grid[1][y][x] = DEAD;
       }
        else if( z == 1){
            grid[0][y][x] = DEAD;
        }
    }
}
//Puts the rules from the nex_generation_rules into terms of the grid of the eventual main program.
void compute_rules(char grid[2][GRIDY][GRIDX]){
    for(int i = 0; i < GRIDY; i++){
        for(int j = 0; j < GRIDX; j++){
            next_generation_rules(i,j,grid);
            
        }
    }
    
}
//outputs the grid to the program to start the computations.
void output_grid(char **cell, char grid[2][GRIDY][GRIDX]){
    for(int i = 0; i < GRIDY; i++){
        for(int j = 0; j < GRIDX; j++)
            grid[z][i][j] = cell[i][j];
    }
}
// This function prints out a the starting state.
void print_state( char grid[2][GRIDY][GRIDX]){
    for(int i = 0; i < GRIDY; i++){
        for(int j = 0; j < GRIDX; j++){
            printf("%c", grid[z][i][j]);
    }
        printf("\n");
    
}
}

void z_axis(){
    if(z == 0){
        z = 1;
    }
    else{
        z = 0;
    }
  
}
/*
This function goes to the next function for every generation.
 */

void next_gen (char grid[2][GRIDY][GRIDX]){
    while(current_gen < gen_number){
        compute_rules(grid);
        print_state(grid);
        usleep(300000);
        clearterm();
        z_axis();
        current_gen++;
    }
    
    
    
    
    




}


        
        
        
