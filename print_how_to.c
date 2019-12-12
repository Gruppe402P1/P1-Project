#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "foodplan.txt"
#define MAX_STR_LENGTH 2000
#define MADPLAN_LENGTH 7

int prompt_for_day();
void flush();
int read_for_how_to(char* filename, char* how_to, int day_int);
void make_lowercase(char* day_str);

int main(){
    char* how_to = malloc(sizeof(char)*MAX_STR_LENGTH);
    int day_int = 0;
    if(how_to == NULL)
    {
        return 1;
    }
    day_int = prompt_for_day();
    if(read_for_how_to(FILENAME,how_to,day_int))
    {
        printf("Error");
        return 1;
    }
    printf("%s",how_to);
    free(how_to);
    return 0; 
}
/*Prompts the user for the day and converts to a number from 1-7*/
int prompt_for_day()
{
    char* day_str = malloc(sizeof(char)*MAX_STR_LENGTH);
    int scanres = 0;
    printf("Write a day: ");
    do{
        scanres = scanf("%s",day_str);
    } while(scanres != 1);
    make_lowercase(day_str);
    
    if(strcmp(day_str,"monday") == 0)
    {
        free(day_str);
        return 1;
    }
    else if(strcmp(day_str,"tuesday") == 0)
    {
        free(day_str);
        return 2;
    }
    else if(strcmp(day_str,"wednesday") == 0)
    {
        free(day_str);
        return 3;
    }
    else if(strcmp(day_str,"thursday") == 0)
    {
        free(day_str);
        return 4;
    }
    else if(strcmp(day_str,"friday") == 0)
    {
        free(day_str);
        return 5;
    }
    else if(strcmp(day_str,"saturday") == 0)
    {
        free(day_str);
        return 6;
    }
    else if(strcmp(day_str,"sunday") == 0)
    {
        free(day_str);
        return 7;
    }
    else
    {
        free(day_str);
        flush();
        printf("try again\n");
        return prompt_for_day();
    }
}

void make_lowercase(char* day_str)
{
    int i;
    for(i = 0; day_str[i] != '\0'; i++)
    {
        if(day_str[i] > 'A' && day_str[i] < 'Z')
        {
            day_str[i] = tolower(day_str[i]);
        }
    }
}

void flush(){
    char ch;
    do
    {
        scanf("%c",&ch);
    } while(ch != '\n');
}

int read_for_how_to(char* filename, char* how_to, int day_int)
{
    FILE *file_pointer = fopen(filename,"r");
    int i;
    char* line_str = malloc(sizeof(char)*MAX_STR_LENGTH);
    if(file_pointer == NULL || line_str == NULL)
    {
        return 1;
    }
    for(i = 0; i != day_int;)
    {
        if(fgets(line_str,MAX_STR_LENGTH,file_pointer)== NULL)
        {
            return 1;
        }
        if(line_str[0] == '#')
        {
            i++;
        }
    }
    free(line_str);
    fscanf(file_pointer,"%[^@]",how_to);
    return 0;
}