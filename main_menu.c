#include <stdio.h>

int main() 
{ 
  int done = 0, select_done = 0, function_selection = 0; 
 
  do 
  { 
    do 
    { 
      /* menu description */ 
      printf("\n1: set preferences
              \n2: generate foodplan
              \n3: print shoppinglist
              \n4: show current foodplan
              \n5: show foodplan history
              \n6: add or remove recipees
              \n7: quit program
              \nSelect function: "); 
 
      /* select function */ 
      select_done = 0; 
      scanf("%d", &function_selection); 
      switch(function_selection) 
      { 
        case 1: 
          set_preferences(); break; 
        case 2: 
          generate_foodplan(); break; 
        case 3: 
          print_shoppinglist(); break; 
        case 4: 
          show_foodplan(); break; 
        case 5: 
          show_history(); break; 
        case 6: 
          add_recipes(); break; 
        case 7: 
          done = 1; select_done = 1; break; 
        default:;           
      } 
    } while (!select_done); 
  } while (!done); 
  return 0; 
} 