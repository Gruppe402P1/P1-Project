#include <stdio.h>

void add_recipe(){
    int choice = 0;

    printf("To add form txt file enter 1\nTo add manually enter 2\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add_from_txt();
        break;
    
    case 2:
        add_manually();
        break;

    default:
        break;
    }

    return;
}

void add_manually(){

}

void add_from_txt(){

}