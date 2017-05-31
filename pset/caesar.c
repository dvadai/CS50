#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

string cypher;
int i;
int main(int argc, string argv[])
{
   string text;
   
    if(argc != 2)
    {
     printf("Please run it again and use exactly one integer argument!\n");
    return 1; 
    }
    
    int k = atoi(argv[1]);
    
    do 
      {
           text = GetString();
    
      }
    while(text <= 0);
    
    for(i = 0; i< strlen(text); i++)
   {
     if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                    int letter = text[i];
                    int new = letter-65;
                    int math = (new + k) % 26; 
                     // printf("This is your new%d\n", math);
                    int converted = math+65;
                     // printf("This is converted%d\n", converted);
                    char x = converted;
                    printf("%c", x);
            }
            if (islower(text[i]))
            {
                    int letter = text[i];
                    int new = letter-97;
                    int math = (new + k) % 26; 
                    // printf("This is your new%d\n", math);
                    int converted = math+97;
                    // printf("This is converted%d\n", converted);
                    char x = converted;
                    printf("%c", x);
            }
            
        } 
            else
            {
                    printf("%c", text[i]);
                   
            }
    
   }
    printf("\n");
    return 0;
}
