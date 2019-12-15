#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "foodplan.txt"
#define MAX_LINE_LENGTH 100
#define MAX_LIST_LENGTH 40

struct item{
	char name_str[MAX_LINE_LENGTH];
	char type_str[MAX_LINE_LENGTH];
	int amount_int;
};
typedef struct item item;

int prompt_for_day_or_week();
void make_lowercase(char* day_str);
void flush();
int read_for_ingrediens(char* filename_str, item * list_arr, int day_int);
int read_days_for_ingrediens(FILE * file_pointer,item * list_arr);
int read_day_for_ingrediens(FILE * file_pointer,item * list_arr, int day_int);
void print_list(item* shopping_list_arr);
void remove_underscore(char* str);

int print_shopping_list() {
	item* shopping_list_arr = calloc(MAX_LIST_LENGTH,sizeof(item));
	int day_int;
	day_int = prompt_for_day_or_week();
	if(read_for_ingrediens(FILENAME, shopping_list_arr,day_int)||shopping_list_arr == NULL)
	{
		/*printf("Error can't find the foodplan\n");*/ 
		return 1; /*Error*/
	}
	print_list(shopping_list_arr);
	free(shopping_list_arr);
	return 0;
}
/*Promps for the either a day or the whole week*/
int prompt_for_day_or_week()
{
	char* day_str = malloc(sizeof(char)*MAX_LINE_LENGTH);
    int scanres = 0;
    /*Gets input from the user*/
    printf("Write a day or \"all\" for the week: ");
    do{
        scanres = scanf("%s",day_str);
    } while(scanres != 1);
    make_lowercase(day_str);
    /*Checks input*/
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
	else if(strcmp(day_str,"all") == 0)
	{
		free(day_str);
		return 0;
	}
    else
    {
        free(day_str);
        flush();
        printf("try again\n");
        return prompt_for_day_or_week();
    }
}
/*Changes uppercase letters to lowercase*/
void make_lowercase(char* day_str)
{
    int i;
    for(i = 0; day_str[i] != '\0'; i++)
    {
        if(day_str[i] >= 'A' && day_str[i] <= 'Z')
        {
            day_str[i] = tolower(day_str[i]);
        }
    }
}
/*Gets rid of the input*/
void flush(){
    char ch;
    do
    {
        scanf("%c",&ch);
    } while(ch != '\n');
}
/*Reads for ingrediens in the foodplan*/
int read_for_ingrediens(char* filename_str, item * list_arr, int day_int)
{
    FILE *file_pointer = fopen(filename_str,"r");
	char* line_str = malloc(sizeof(char)*MAX_LINE_LENGTH);
	if(
		file_pointer == NULL||line_str == NULL
	    ||fgets(line_str,MAX_LINE_LENGTH,file_pointer) == NULL /*Getting rid of the first line*/
	    ||day_int == 0? read_days_for_ingrediens(file_pointer,list_arr) 
			   		  : read_day_for_ingrediens(file_pointer,list_arr,day_int)
	) 
	{
		return 1; /*Error*/
	}
	free(line_str);
	fclose(file_pointer);
	return 0;
}
/*Reads a each day for ingrediens recursively*/
int read_days_for_ingrediens(FILE * file_pointer,item * list_arr)
{
	char* line_str = malloc(sizeof(char)*MAX_LINE_LENGTH);
	int i;
	item temp_item;
	if(line_str == NULL || file_pointer == NULL)
	{
		return 1; /*Error*/
	}
    /*Goes over difficulty and name*/
	for(i = 0; i < 2; i++)
	{
		fgets(line_str,MAX_LINE_LENGTH,file_pointer);
	}
    /*Gets the ingredienses*/
	while(fgets(line_str,MAX_LINE_LENGTH,file_pointer)!=NULL && line_str[0] != '#')
	{
			sscanf(line_str,"%[^,]" "%*c" "%[^,]" "%*c" "%d",temp_item.name_str,temp_item.type_str,&temp_item.amount_int);
            /*Checks for collisions*/
			for(i = 0;strcmp(temp_item.name_str,list_arr[i].name_str) != 0 && list_arr[i].name_str[0] != '\0';i++);
			if(strcmp(temp_item.name_str,list_arr[i].name_str) == 0 || list_arr[i].name_str[0] == '\0')
			{
				list_arr[i].amount_int += temp_item.amount_int;
			}
			if(list_arr[i].name_str[0] == '\0')
			{
				strcpy(list_arr[i].name_str,temp_item.name_str);
				strcpy(list_arr[i].type_str,temp_item.type_str);
			}
	}
    /*Goes over the rest of the recipe*/
	while(line_str[0] != '@')
	{
		if(fgets(line_str,MAX_LINE_LENGTH,file_pointer)== NULL)
		{
			return 0; /*Reached the end of the file*/
		}
	}
	free(line_str);
	return read_days_for_ingrediens(file_pointer,list_arr);
}
/*Finds and reads the ingrediens for a specefik day*/
int read_day_for_ingrediens(FILE * file_pointer,item * list_arr, int day_int)
{
	char* line_str = malloc(sizeof(char)*MAX_LINE_LENGTH);
	int i;
    if(line_str == NULL || file_pointer == NULL)
	{
		return 1; /*Error*/
	}
    /*Finds the recipe for the specefik day*/
	for(i = 0; i != day_int;)
	{
		if(fgets(line_str,MAX_LINE_LENGTH,file_pointer) ==NULL)
		{
			return 1; /*Error*/
		}
		else if(line_str[0] == '@')
		{
			i++;
		}
	}
    /*Goes over difficulty and name*/
	for(i = 0; i < 2; i++)
	{
		fgets(line_str,MAX_LINE_LENGTH,file_pointer);
	}
    /*Gets the ingredienses*/
	for(i = 0; fgets(line_str,MAX_LINE_LENGTH,file_pointer)!=NULL && line_str[0] != '#';i++)
	{
		sscanf(line_str,"%[^,]" "%*c" "%[^,]" "%*c" "%d",list_arr[i].name_str,list_arr[i].type_str,&list_arr[i].amount_int);
	}
	free(line_str);
	return 0;
}
/*Changes underscore to space*/
void remove_underscore(char* str)
{
	int i;
	for(i = 0; str[i] != '\0';i++)
	{
		if(str[i] =='_')
		{
			str[i] = ' ';
		}
	}
}
/*Prints all items that are not zero in shopping_list_arr*/
void print_list(item* shopping_list_arr){
	int i;
	for(i = 0; i < MAX_LIST_LENGTH; i++)
	{
		if(shopping_list_arr[i].name_str[0] != 0)
		{
			remove_underscore(shopping_list_arr[i].name_str);
			remove_underscore(shopping_list_arr[i].type_str);
			printf("%s %d g\n",shopping_list_arr[i].name_str,shopping_list_arr[i].amount_int);
		}
	}
}
