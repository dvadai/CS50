#include <stdio.h>
#include <cs50.h>


int GetInt(void);
int main (void)

{
   int height;
    do
    {
    printf ("Please give me a positive number that is no greater than 23 to build a half-pyramid\n");  
    height = GetInt();
    }
    while (height > 23 || height < 0);
    
    
     int spaces;
     int hash;
     int lines;
     int i;
    
     for (i = 0;  i< height; i++)
     {
    
         lines = i+1;

            for (spaces = (height-lines); spaces > 0; spaces--)
      
                 {
                   printf(" "); 
                 }
        
            for (hash = (lines +1); hash > 0 ; hash--)
                 {
                   printf("#");  
                 }
    
         printf("\n");
     }
}
       
          
