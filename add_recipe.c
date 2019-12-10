#include <stdio.h>
#include <string.h>

struct recipy 
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

void add_recipe(struct ingredient ingrediens[], struct recipy recipe_list[]){
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

    return;
}

void add_manually(struct ingredient ingrediens[], struct recipy recipe_list[])
{
    int choice;
    
    printf("Enter recipe name\n");
    scanf("%s", recipe_list[].name);

    printf("\nEnter instructions\n");
    scanf("%s", recipe_list[].instructions);

    do
    {
        printf("\nEnter ingredient\n");
        scanf("%s", ingrediens[].name);

        printf("\nEnter amount in g\n");
        scanf("%d", ingrediens[].amount);

        printf("\nEnter foodtype\n");
        scanf("%s", ingrediens[].food_type);

        printf("\nEnter another ingredient, 0 = no,?\n");
        scanf("%d", &choice);
    }
    while (choice != 0);
    
    printf("\nEnter amount of time\n");
    scanf("%d", recipe_list[].time);

    printf("\nEnter difficulty from 1 = Easy to 10 = Hard\n");
    scanf("%d", recipe_list[].difficulty);

    return;
}

void add_from_txt(struct ingredient ingrediens[], struct recipy recipe_list[])
{

    return;
}