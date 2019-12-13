#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ingredient 
{ 
    char name[256]; /* fx. røget laks */ 
    char food_type[256]; /* fx fisk */ 
    int amount; 
};

struct recipe 
{ 
    char name[256];
    int time; 
    int difficulty; 
    struct ingredient ingrediens[256];
    char instructions[256];
    char source[256];
};

/*Får programmet til at indlæse opskriften fra en valgt txt fil*/
int add_from_txt(struct ingredient ingrediens[], struct recipe recipe_list[]);

/*Tillader brugeren at indlæse deres opskrift manuelt*/
int add_manually(struct ingredient ingrediens[], struct recipe recipe_list[]);

/*Bruges til at skrive opskrifterne ind i databasen*/
void write_to_txt(struct ingredient ingrediens[], struct recipe recipe_list[], int ingredient_count);

int main(){
    int choice = 0, ingredient_count;

    struct ingredient ingrediens[256] = {0};
    struct recipe recipe_list[256] = {0};

    printf("To add from txt file enter 1\nTo add manually enter 2\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        ingredient_count = add_from_txt(ingrediens, recipe_list);
        write_to_txt(ingrediens, recipe_list, ingredient_count);
        break;
    
    case 2:
        ingredient_count = add_manually(ingrediens, recipe_list);
        write_to_txt(ingrediens, recipe_list, ingredient_count);
        break;

    default:
        break;
    }

    return 0;
}

int add_manually(struct ingredient ingrediens[], struct recipe recipe_list[])
{
    int choice, ingredient_count = 0;

    printf("Enter recipe name\n");
    scanf("%s", recipe_list[0].name);

    printf("\nEnter instructions\n");
    scanf("%s", recipe_list[0].instructions);

    do
    {   

        printf("\nEnter ingredient\n");
        scanf("%s", ingrediens[ingredient_count].name);

        printf("\nEnter amount in g\n");
        scanf("%d", &ingrediens[ingredient_count].amount);

        printf("\nEnter foodtype\n");
        scanf("%s", ingrediens[ingredient_count].food_type);

        ingredient_count++;

        printf("\nEnter another ingredient, 0 = no,?\n");
        scanf("%d", &choice);
    }
    while (choice != 0);
    
    printf("\nEnter amount of time\n");
    scanf("%d", &recipe_list[0].time);

    printf("\nEnter difficulty from 1 = Easy to 10 = Hard\n");
    scanf("%d", &recipe_list[0].difficulty);

    return ingredient_count;
}

int add_from_txt(struct ingredient ingrediens[], struct recipe recipe_list[])
{
    FILE *recipetxt;
    char temp[100];
    char* instruc_temp = (char*)calloc(2000, sizeof(char));
    int n = 0, ingredient_count = 0, first = 0, second = 0, third = 0;

    if(instruc_temp == NULL){
        printf("Failed to allocate memory");
        return 1;
    }

    printf("Enter name of recipe file, with file extension");
    scanf("%s", temp);

    recipetxt = fopen(temp,"r");

    fgets(recipe_list[0].name, 256, recipetxt);
    
    while (fgets(temp, 100, recipetxt) != NULL)
    {
        if(temp[n] >= 0 && temp[n] < 10)
        {

            first = temp[0];
            n++;

            if(temp[n] >= 0 && temp[n] < 10)
            {
                first *= 10;
                second = temp[1];
                n++;

                if(temp[n] >= 0 && temp[n] < 10)
                {
                    first *= 10;
                    second *= 10;
                    third = temp[2];
                    n++;
                } 
            }

            strncpy(ingrediens[ingredient_count].name, temp + n, strlen(temp)-n);
            ingrediens[ingredient_count].amount = first + second + third;
            ingredient_count++;
        }
        else
        {
            strcat(instruc_temp, temp);
        }
        
    }

    strcpy(recipe_list[0].instructions, instruc_temp);
    
    free(instruc_temp);
    fclose(recipetxt);

    return ingredient_count;
}

void write_to_txt(struct ingredient ingrediens[], struct recipe recipe_list[], int ingredient_count)
{
    FILE *database;
    int count;
    database = fopen("recipes.txt","a");

    fprintf(database, "%s\n\n%s\n\n", recipe_list[0].name, recipe_list[0].instructions);

    for (count = 0; count < ingredient_count; count++)
    {
        fprintf(database, "%d %s\n", ingrediens[count].amount, ingrediens[count].name);
    }
    

    fclose(database);
    return;
}