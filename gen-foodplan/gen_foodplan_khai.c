#include<stdio.h> 
#include<stdlib.h>
#include<time.h>

typedef struct recipe
{
    int fish;
    int meat;
    int dairy;
    int salt;
}recipe;

int sum(int arr[], int arr_n)
{
    int i, sum = 0;
    for(i = 0; i < arr_n; i++)
        sum += arr[i];
    return sum;
}

int valueinarray(int val, int arr[], int arr_n)
{
    int i;
    for(i = 0; i < arr_n; i++)
    {
        if(arr[i] == val)
            return 1; /* is in */
    }
    return 0; /* is not in */
}

int max_diff(int arr[], int arr_n, int target)
{
    int i, temp_diff, max_diff_i;
    unsigned int  max_diff = 0;

    for(i = 0; i < arr_n; i++)
    {
        temp_diff = (target - arr[i]);

        if(  temp_diff > max_diff )
        {
            max_diff = temp_diff;
            max_diff_i = i;
        }
    }
    printf("\nmax diff = %d - %d =  %d \n", target, arr[max_diff_i], max_diff);
    return max_diff_i;
}

void find_recipe_match(int arr[], int arr_n, int source[], int max_n, int target) // last item might be best match when it is 0, no need for rand if recipe is sorted by dist 
{
    int curr_sum, rand_i;
        /*
        do{
            rand_i = rand() % max_n;
        }while(valueinarray(rand_i, arr, max_n));
        */

        int new_target = target - sum(arr, arr_n);
        int closest = findClosest(source, max_n, new_target);

        printf("target = %d closest = %d \n", new_target, closest);

        arr[arr_n - 1] = closest ;

        curr_sum = sum(arr, arr_n);

}


void rand_foodplan(int foodplan_list[], int recipe_list[], int n, int recipe_n)
{
    int i, rand_i;
    for(i = 0; i < n; i++)
    {
        do{
            rand_i = rand() % recipe_n;
        }while(valueinarray(rand_i, foodplan_list, recipe_n));

        foodplan_list[i] = recipe_list[rand_i];
        printf("%d \n", foodplan_list[i]);
    }
}


///binary search///////////////////////////////////////////////


int getClosest(int, int, int); 
  
// Returns element closest to target in arr[] 
int findClosest(int arr[], int n, int target) 
{ 
    // Corner cases 
    if (target <= arr[0]) 
        return arr[0]; 
    if (target >= arr[n - 1]) 
        return arr[n - 1]; 
  
    // Doing binary search 
    int i = 0, j = n, mid = 0; 
    while (i < j) { 
        mid = (i + j) / 2; 
  
        if (arr[mid] == target) 
            return arr[mid]; 
  
        /* If target is less than array element, 
            then search in left */
        if (target < arr[mid]) { 
  
            // If target is greater than previous 
            // to mid, return closest of two 
            if (mid > 0 && target > arr[mid - 1]) 
                return getClosest(arr[mid - 1], 
                                  arr[mid], target); 
  
            /* Repeat for left half */
            j = mid; 
        } 
  
        // If target is greater than mid 
        else { 
            if (mid < n - 1 && target < arr[mid + 1]) 
                return getClosest(arr[mid], 
                                  arr[mid + 1], target); 
            // update i 
            i = mid + 1;  
        } 
    } 
  
    // Only single element left after search 
    return arr[mid]; 
} 
  
// Method to compare which one is the more close. 
int getClosest(int val1, int val2, 
               int target) 
{ 
    if (target - val1 >= val2 - target) 
        return val2; 
    else
        return val1; 
}

int main() 
{ 
    srand ( time( 0 ) );

    int black_list[] = {2, 5, 8};
    int white_list[] = { 1, 2, 10};

    int recipe_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

    int foodplan_n = 7; 
    int recipe_n = sizeof(recipe_list)/sizeof(recipe_list[0]); 
    int sum_target = 420;

    int *foodplan_list = calloc(foodplan_n, sizeof(int));
    int rand_i;
    int i;

    rand_foodplan(foodplan_list, recipe_list, foodplan_n - 1, recipe_n);

    find_recipe_match(foodplan_list, foodplan_n, recipe_list, recipe_n, sum_target);

    int foodplan_sum = sum(foodplan_list, foodplan_n);

    printf("sum = %d ", foodplan_sum);
    //printf("max diff index = %d", max_diff(foodplan_list, foodplan_n, sum_target));

    //printCombination(arr, arr_n, comb_n, sum_target); 
    return 0; 
}
