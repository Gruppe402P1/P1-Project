#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_MEAT 100
#define MIN_FISH 300

typedef struct opskrift
{
    int nutrition [5];
} opskrift;

enum food_type{meat, fish};


void make_random_opskrifter(opskrift opskrifter[]);
void print_opskrift_list(opskrift opskrif_list[], int amount);
void print_madplan(opskrift* opskrif_list[], int amount);
void make_madplan(opskrift opskrifter[], opskrift* out_madplan[]);
opskrift total_ingredients_of_madplan(opskrift* opskrift_list[], int list_length);
int index_of_worst_opskrift(opskrift* opskrift_list[]);
void switch_two_places_madplan(opskrift* opskrift_list[], int index_1, int index_2);
double length_to_optimal(opskrift in_opskrift);
double length_of_meat_dim(opskrift in_opskrift);
double length_of_fish_dim(opskrift in_opskrift);
double mapRange(double min, double max, double val);

int main(void)
{
    opskrift opskrifter[50];
    opskrift *madplan[7];
    srand(time(NULL));
    make_random_opskrifter(opskrifter);
    printf("---Opskrift list---\n");
    print_opskrift_list(opskrifter, 50);
    printf("---Current madplan--- \n");
    make_madplan(opskrifter, madplan);
    //print_madplan(madplan, 7);

    return 0;
}

void make_random_opskrifter(opskrift opskrifter[])
{
    int i;
    for (i = 0; i < 50; i++)
    {
        opskrifter[i].nutrition[meat] = rand() % 50;
        opskrifter[i].nutrition[fish]  = rand() % 50;
    }
}

void print_opskrift_list(opskrift opskrif_list[], int amount)
{
    int i, total_meat = 0, total_fish = 0;
    for (i = 0; i < amount; i++)
    {
        printf("Opskrift [%d] har: meat: %d og fish: %d \n", i, opskrif_list[i].nutrition[meat], opskrif_list[i].nutrition[fish]);
        total_meat += opskrif_list[i].nutrition[meat];
        total_fish += opskrif_list[i].nutrition[fish];
    }
    printf("Total Meat: %d\nTotal Fish: %d\n", total_meat, total_fish);
}

void print_madplan(opskrift* opskrif_list[], int amount)
{
    int i, total_meat = 0, total_fish = 0;

    for (i = 0; i < amount; i++)
    {
        printf("Opskrift [%d] har: meat: %d og fish: %d \n", i, opskrif_list[i]->nutrition[meat], opskrif_list[i]->nutrition[fish]);
        total_meat += opskrif_list[i]->nutrition[meat];
        total_fish += opskrif_list[i]->nutrition[fish];
    }
    printf("Total Meat: %d\nTotal Fish: %d\n", total_meat, total_fish);
}


void make_madplan(opskrift opskrifter[], opskrift* out_madplan[])
{
    int i, length_to_good = 999, index_of_worst, loop_count = 0;
    
    opskrift total_madplan_ingredients;
    /* Makes first random madplan */
    for (i = 0; i < 7; i++)
    {
        out_madplan[i] = &opskrifter[(rand() % 50)];
    }
    
    total_madplan_ingredients = total_ingredients_of_madplan(out_madplan, 7);  
    while(length_to_optimal(total_madplan_ingredients) != 0)
    {
        loop_count++;
        index_of_worst = index_of_worst_opskrift(out_madplan);
        out_madplan[index_of_worst] = &opskrifter[rand() % 50];
        total_madplan_ingredients = total_ingredients_of_madplan(out_madplan, 7);
    }
    
    printf("Done. Final madplan was found after %d loops and is:\n", loop_count);
    print_madplan(out_madplan, 7);
}

opskrift total_ingredients_of_madplan(opskrift* opskrift_list[], int list_length)
{
    int i;
    opskrift return_opskrift;

    return_opskrift.nutrition[meat] = 0;
    return_opskrift.nutrition[fish] = 0;

    for (i = 0; i < list_length; i++)
    {
        if(opskrift_list[i] != NULL)
        {
            return_opskrift.nutrition[meat] += opskrift_list[i]->nutrition[meat];
            return_opskrift.nutrition[fish] += opskrift_list[i]->nutrition[fish];
        }
    }
    return return_opskrift;
}

int index_of_worst_opskrift(opskrift* opskrift_list[])
{
    int i, index, index_of_worst = -1;
    double current_length, length_of_worst = 9999;
    opskrift total_madplan_ingredients;

    for (i = 0; i < 7; i++)
    {
        switch_two_places_madplan(opskrift_list, i, 6);
        total_madplan_ingredients = total_ingredients_of_madplan(opskrift_list, 6);
        current_length = length_to_optimal(total_madplan_ingredients);

        if(current_length < length_of_worst)
        {
            length_of_worst = current_length;
            index_of_worst = i;
        }
        switch_two_places_madplan(opskrift_list, 6, i);
    }
    return index_of_worst;
}

void switch_two_places_madplan(opskrift* opskrift_list[], int index_1, int index_2)
{
    opskrift *buffer;
    buffer = opskrift_list[index_1];
    opskrift_list[index_1] = opskrift_list[index_2];
    opskrift_list[index_2] = buffer;
}

double length_to_optimal(opskrift in_opskrift)
{
    double return_length = 0;
    return_length += pow(length_of_meat_dim(in_opskrift), 2);
    return_length += pow(length_of_fish_dim(in_opskrift), 2);
    return sqrt(return_length);
}

double length_of_meat_dim(opskrift in_opskrift)
{
    return mapRange(0, MAX_MEAT, (MAX_MEAT - in_opskrift.nutrition[meat]) > 0 ? 0 : (in_opskrift.nutrition[meat] - MAX_MEAT));
}

double length_of_fish_dim(opskrift in_opskrift)
{
    return mapRange(0, MIN_FISH, (MIN_FISH - in_opskrift.nutrition[fish]) < 0 ? 0 : (MIN_FISH - in_opskrift.nutrition[fish]));
}

/* Copyright Laurits Mumberg */ 
double mapRange(double min, double max, double val)
{
    return (val-min)/(max-min);
}