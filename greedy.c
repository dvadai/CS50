#include <stdio.h>
#include <cs50.h>
#include <math.h>


float GetFloat(void);
float change;
int rounded;
float i;

const int QUARTER = 25;
const int DIME = 10;
const int NICKEL = 5;
const int PENNY = 1;
int NumberOfQuarters;
int NumberOfDimes;
int NumberOfNickels;
int NumberOfPennies;

int CoinCounter = 0;
int remainder1;

int main (void)

{
    
        do
            {
                printf("Please tell me how much is the change:\n");
                change = GetFloat();
                
            }
    
        while (change <= 0);
        rounded = roundf(change * 100.00f);
    
        

            if (rounded >= QUARTER)
     {
            
                NumberOfQuarters= rounded/QUARTER;
                CoinCounter = NumberOfQuarters;
                rounded = rounded - (NumberOfQuarters * QUARTER);
     }
    
            if (rounded >= DIME)
     {
                NumberOfDimes= rounded/DIME;
                CoinCounter = CoinCounter + NumberOfDimes;
                rounded = rounded - (NumberOfDimes * DIME);
     }
     
            if (rounded >= NICKEL)
     {
                NumberOfNickels= rounded/NICKEL;
                CoinCounter = CoinCounter + NumberOfNickels;
                rounded = rounded - (NumberOfNickels * NICKEL);
     }
    
     
            if (rounded >= PENNY)
     {
                remainder1= rounded % PENNY;
                NumberOfPennies= rounded/PENNY;
                CoinCounter = CoinCounter + NumberOfPennies;
                rounded = rounded - (NumberOfPennies * PENNY);
     }
    
    
    printf("%i\n", CoinCounter);
}
