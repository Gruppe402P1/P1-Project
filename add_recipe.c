#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct recipe 
{ 
    char name[] 
    int time 
    int difficulty 
    ingredient ingrediens[] 
    char instructions[]  
    char source[] 
};

struct ingredient 
{ 
    char name[] /* fx. røget laks */ 
    char food_type[] /* fx fisk */ 
    int amount 
};

/*Får programmet til at indlæse opskriften fra en valgt txt fil*/
void add_from_txt(struct ingredient ingrediens[], struct recipe recipe_list[]);

/*Tillader brugeren at indlæse deres opskrift manuelt*/
void add_manually(struct ingredient ingrediens[], struct recipe recipe_list[]);

void add_recipe(struct ingredient ingrediens[], struct recipe recipe_list[]){
    int choice = 0;

    printf("To add from txt file enter 1\nTo add manually enter 2\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add_from_txt(ingrediens, recipe_list);
        break;
    
    case 2:
        add_manually(ingrediens, recipe_list);
        break;

    default:
        break;
    }

    write_to_txt(ingrediens, recipe_list);

    return;
}

void add_manually(struct ingredient ingrediens[], struct recipe recipe_list[])
{
    int choice, count = 0;

    printf("Enter recipe name\n");
    scanf("%s", recipe_list[0].name);

    printf("\nEnter instructions\n");
    scanf("%s", recipe_list[0].instructions);

    do
    {   

        printf("\nEnter ingredient\n");
        scanf("%s", ingrediens[count].name);

        printf("\nEnter amount in g\n");
        scanf("%d", ingrediens[count].amount);

        printf("\nEnter foodtype\n");
        scanf("%s", ingrediens[count].food_type);

        count++;

        printf("\nEnter another ingredient, 0 = no,?\n");
        scanf("%d", &choice);
    }
    while (choice != 0);
    
    printf("\nEnter amount of time\n");
    scanf("%d", recipe_list[0].time);

    printf("\nEnter difficulty from 1 = Easy to 10 = Hard\n");
    scanf("%d", recipe_list[0].difficulty);

    return;
}

void add_from_txt(struct ingredient ingrediens[], struct recipe recipe_list[])
{
    FILE *recipetxt;
    char temp[100];
    char* instruc_temp = (char*)calloc(2000, sizeof(char));
    int n = 0, count = 0;

    if(instruc_temp == NULL){
        printf("Failed to allocate memory");
        exit(0);
    }

    int first = 0, second = 0, third = 0;
    printf("Enter name of recipe file, with file extension");
    recipetxt = fopen(scanf("%s"),"r");

    fgets(recipe_list[0].name, 256, recipetxt);
    
    while (fgets(temp[], 100, recipetxt) != NULL)
    {
        if(temp[n] >= 0 && temp[n] < 10)
        {

             = find_empty(ingrediens);
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

            strncpy(ingrediens[count].name, temp + n, strlen(temp)-n);
            ingrediens[count].amount = first + second + third;
            count++;
        }
        else
        {
            strcat(instruc_temp, temp);
        }
        
    }

    strcpy(recipe_list[0].instructions, instruc_temp);
    
    free(instruc_temp);
    fclose(recipetxt);

    return;
}

void write_to_txt(struct ingredient ingrediens[], struct recipe recipe_list)
{
    FILE *database;
    database = fopen("recipees.txt","a");

    

    fclose(database)
    return;
}