#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int i;

int main(int argc, string argv[])
            {
    string key;
    string text;
    
    
    // Get the key
        if (argc != 2)
            {
                printf("Please give me a valid text that I can use as a key!\n");
                return 1;
            }
        else
            {
                key = argv[1];
                for(i=0; i < strlen(key);i++)
                {
                if(isalpha(key[i]))
              {
    
              }
              else
              {
                  printf("Your key is not alphanumeric!\n");
                return 1;
              }
                }
             
            }
    
        do 
            {
                text = GetString();
            }
        while(text <= 0);
        
        
        
    int j = 0;
    int counter=0;
    
     for(i=0; i < strlen(text);i++)
     {
         if (isalpha(text[i]))
        { 
            // printf("%i",j);
  
            j = counter % strlen(key);

            int keyConvertAmount;
        
            if (isupper(key[j]))
            {
                keyConvertAmount = 65;
            }
            if (islower(key[j]))
            {
                keyConvertAmount = 97;
            }
        
            int textConvertAmount;
                                
            if (isupper(text[i]))
            {
                textConvertAmount = 65;
            }
            if (islower(text[i]))
            {
            textConvertAmount = 97;
            }

            int ascii = (((text[i]-textConvertAmount)+(key[j]-keyConvertAmount)) % 26)+textConvertAmount;
            char x = ascii;
            printf("%c",x);
            counter++;
    }
    else
    {
        printf("%c", text[i]);                                      
    }
     
}
            
  printf("\n");
    return 0;
                            
}   
    
