#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

void get_pointer_to_recipe_n(int recipe_number, FILE* out_file_pointer);
void print_single_recipe(FILE* file);
void remove_last_char(char *returnString);
void underscore_to_spaces(char outString[]);
void print_ingredints(FILE *file);
void print_instructions(FILE *file);

int main(void)
{
    FILE *file;
    file = fopen("recipe.txt","r");
    get_pointer_to_recipe_n(2, file);
    print_single_recipe(file);
    return 0;
}

void get_pointer_to_recipe_n(int recipe_number, FILE* out_file_pointer)
{
    int current_recipe_number = 0;
    char input_line[2];

    while(current_recipe_number < recipe_number)
    {
        fgets(input_line,sizeof(input_line), out_file_pointer);
        if(input_line[0] == '@')
        {
            current_recipe_number++;
        }
    }
}




/* Code for printing a single recipe */ 
void print_single_recipe(FILE* file)
{
    char inputLine[100];
    
    fgets(inputLine,sizeof(inputLine),file);
    
    /* Prints dish name */
    fgets(inputLine,sizeof(inputLine),file);
    remove_last_char(inputLine);
    printf("----- %s -----\n", inputLine);
    
    /* Prints dish difficulty */
    fgets(inputLine,sizeof(inputLine),file);
    printf("Dificulty level: %s", inputLine);

    /* Prints dish time */
    fgets(inputLine,sizeof(inputLine),file);
    printf("Time to make: %s", inputLine);

    /**/
    print_ingredints(file);
    print_instructions(file);
}

void remove_last_char(char *returnString)
{
    returnString[strlen(returnString) - 1] = '\0';
}

void underscore_to_spaces(char outString[])
{
    int i;
    for (i = 0; i < strlen(outString); i++)
    {
        if(outString[i] == '_')
        {
            outString[i] = ' ';
        }
    }
}

void print_ingredints(FILE *file)
{
    char inputLine[100];
    char ingredient[20];
    char type[20];
    int amount;
    
    while (fgets(inputLine,sizeof(inputLine),file) && inputLine[0] != '#')
    {
        sscanf(inputLine, "%s %s %d", &ingredient, &type, &amount);
        underscore_to_spaces(ingredient);
        printf("%s ", ingredient);
        printf("%d g.\n", amount);
    }
}

void print_instructions(FILE *file)
{
    char inputLine[100];
    
    while (fgets(inputLine,sizeof(inputLine),file) && inputLine[0] != '@')
    {
        printf("%s", inputLine);
    }    
}