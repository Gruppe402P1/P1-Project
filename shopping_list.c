#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "foodplan.txt"
#define MAX_LINE_LENGTH 100
#define MAX_LIST_LENGTH 40

struct item{
	char name_str[MAX_LINE_LENGTH];
	char type_str[MAX_LINE_LENGTH];
	int amount_int;
};
typedef struct item item;

int read_for_ingrediens(char* filename_str, item * list_arr);
int read_day_for_ingrediens(FILE * file_pointer,item * list_arr,int index);
void remove_underscore(char* str);

int main() {
	item* shopping_list_arr = calloc(sizeof(item),sizeof(item));
	int i;
	if(read_for_ingrediens(FILENAME, shopping_list_arr)||shopping_list_arr == NULL)
	{
		printf("fejl");
		return 1;
	}
	for(i = 0; i <= MAX_LIST_LENGTH; i++)
	{
		if(shopping_list_arr[i].name_str[0] != 0)
		{
			remove_underscore(shopping_list_arr[i].name_str);
			remove_underscore(shopping_list_arr[i].type_str);
			printf("%s %d g\n",shopping_list_arr[i].name_str,shopping_list_arr[i].amount_int);
		}
	}
	return 0;
}
/*Reads for ingrediens by reading it day for day*/
int read_for_ingrediens(char* filename_str, item * list_arr)
{
	FILE *file_pointer = fopen(filename_str,"r");
	if(file_pointer == NULL)
	{
		return 1; /*Error*/
	}
	char* line_str = malloc(sizeof(char)*MAX_LINE_LENGTH);
	if(line_str == NULL)
	{
		return 1; /*Error*/
	}
	fgets(line_str,MAX_LINE_LENGTH,file_pointer); /*getting rid of the first line*/
	free(line_str);
	if((read_day_for_ingrediens(file_pointer,list_arr,0)))
	{
		return 1; /*Error*/
	}
	fclose(file_pointer);
	return 0;
}
/*reads a day for ingredienses*/
int read_day_for_ingrediens(FILE * file_pointer,item * list_arr,int index)
{
	char* line_str = malloc(sizeof(char)*MAX_LINE_LENGTH);
	int i;
	item temp_item;
	if(line_str == NULL)
	{
		return 1; /*Error*/
	}
	for(i = 0; i < 2; i++)
	{
		fgets(line_str,MAX_LINE_LENGTH,file_pointer);
	}
	while(line_str[0] != '#')
	{
		if(fgets(line_str,MAX_LINE_LENGTH,file_pointer)!=NULL)
		{
			if(line_str[0] != '#')
			{
				sscanf(line_str,"%[^,]" "%*c" "%[^,]" "%*c" "%d",temp_item.name_str,temp_item.type_str,&temp_item.amount_int);
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
		}
	}
	while(line_str[0] != '@')
	{
		if(fgets(line_str,MAX_LINE_LENGTH,file_pointer)== NULL)
		{
			return 0;
		}
	}
	free(line_str);
	read_day_for_ingrediens(file_pointer,list_arr,index);
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