#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

string name;
int i;
int main(void)

{
     do
   {
          name = GetString();
   }
    while (name == NULL);
            
        printf("%c", toupper(name[0]));
          
        
     for(i =0; i < strlen(name); i++)
     {
         if(name[i-1] == ' ' && name[i] != ' ')
         {
             printf("%c", toupper(name[i]));
    
         }
     }
        
    printf("\n");
}
