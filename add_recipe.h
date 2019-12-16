#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ingredient 
{ 
    char name[20]; /* fx. røget laks */ 
    char food_type[10]; /* fx fisk */ 
    int amount; 
};

struct recipe 
{ 
    char name[20];
    int time; 
    int difficulty; 
    struct ingredient ingrediens[20];
    char instructions[200];
};

void flush(void){
  char trash;
  
  do{
    scanf("%c", &trash);
  }
  while(trash != '\n');

  return;
}

/*Får programmet til at indlæse opskriften fra en valgt txt fil*/
int add_from_txt(struct ingredient ingrediens[], struct recipe *recipe_list);

/*Tillader brugeren at indlæse deres opskrift manuelt*/
int add_manually(struct ingredient ingrediens[], struct recipe *recipe_list);

/*Bruges til at skrive opskrifterne ind i databasen*/
void write_to_txt(struct ingredient ingrediens[], struct recipe *recipe_list, int ingredient_count);

int main(){
    int choice = 0, ingredient_count;

    struct ingredient ingrediens[20] = {0};
    struct recipe recipe_list;

    printf("To add from txt file enter 1\nTo add manually enter 2\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        ingredient_count = add_from_txt(ingrediens, &recipe_list);
        write_to_txt(ingrediens, &recipe_list, ingredient_count);
        break;
    
    case 2:
        ingredient_count = add_manually(ingrediens, &recipe_list);
        write_to_txt(ingrediens, &recipe_list, ingredient_count);
        break;

    default:
        break;
    }

    return 0;
}

int add_manually(struct ingredient ingrediens[], struct recipe *recipe_list)
{
    int choice, ingredient_count = 0;
    flush();
    printf("Enter recipe name: ");
    scanf("%[^\n]", recipe_list->name);
    
    flush();
    printf("\nEnter instructions\n");
    scanf("%[^\n]", recipe_list->instructions);

    do
    {   

        flush();
        printf("\nEnter ingredient\n");
        scanf("%[^\n]", ingrediens[ingredient_count].name);

        flush();
        printf("\nEnter amount in g\n");
        scanf("%d", &ingrediens[ingredient_count].amount);

        flush();
        printf("\nEnter foodtype\n");
        scanf("%s", ingrediens[ingredient_count].food_type);

        ingredient_count++;

        flush();
        printf("\nEnter another ingredient, 0 = no,?\n");
        scanf("%d", &choice);
    }
    while (choice != 0);
    
    flush();
    printf("\nEnter amount of time\n");
    scanf("%d", &recipe_list->time);

    flush();
    printf("\nEnter difficulty from 1 = Easy to 10 = Hard\n");
    scanf("%d", &recipe_list->difficulty);

    flush();
    return ingredient_count;
}

int add_from_txt(struct ingredient ingrediens[], struct recipe *recipe_list)
{
    FILE *recipetxt;
    char temp[100];
    char* instruc_temp = (char*)calloc(2000, sizeof(char));
    int n = 0, ingredient_count = 0, first = 0, second = 0, third = 0, number = 0;

    if(instruc_temp == NULL){
        printf("Failed to allocate memory");
        return 1;
    }

    flush();
    printf("Enter name of recipe file, with file extension");
    scanf("%[^\n]", temp);
    flush();

    recipetxt = fopen(temp,"r");

    fgets(recipe_list->name, 200, recipetxt);
    
    while (fgets(temp, 100, recipetxt) != NULL)
    {
        if(temp[n] >= 0 && temp[n] < 10)
        {
            while(temp[n] >= 0 && temp[n] < 10)
            {
                if(n > 0)
                {
                    number *= 10;
                }                    
                number += temp[n];
                n++;
            }
                n++;
            }

            strncpy(ingrediens[ingredient_count].name, temp + n, strlen(temp)-n);
            ingrediens[ingredient_count].amount = number;
            ingredient_count++;
        }
        else
        {
            strcat(instruc_temp, temp);
        }
        
    }

    strcpy(recipe_list->instructions, instruc_temp);
    
    free(instruc_temp);
    fclose(recipetxt);

    return ingredient_count;
}

void write_to_txt(struct ingredient ingrediens[], struct recipe *recipe_list, int ingredient_count)
{
    FILE *database;
    int count;
    database = fopen("recipes.txt","a");

    printf("%s", recipe_list->name);
    printf("%s", recipe_list->instructions);

    fprintf(database, "%s\n\n%s\n\n", recipe_list->name, recipe_list->instructions);

    for (count = 0; count < ingredient_count; count++)
    {
        fprintf(database, "%dg %s\n", ingrediens[count].amount, ingrediens[count].name);
    }
    
    fclose(database);
    return;
}