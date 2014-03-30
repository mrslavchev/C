#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Variables declaration.
    float change;
    int quater = 25;
    int dime = 10;
    int nickel = 5;
    int pennie = 1;
    
    // Check if user input is valid.
    do{
        printf("O hai!  How much change is owed?\n");
        change = GetFloat();
    }while(change < 0);
    
    int changeAsInt;
    changeAsInt = (int)round(change * 100);
    int coinsCount = 0;
    
    // Extract the biggest amount possible.
    while(changeAsInt != 0){
        if(changeAsInt >= quater){
            changeAsInt -= quater;
            coinsCount++;
        }else if(changeAsInt >= dime){
            changeAsInt -= dime;
            coinsCount++;
        }else if(changeAsInt >= nickel){
            changeAsInt -= nickel;
            coinsCount++;
        }else if(changeAsInt >= pennie){
            changeAsInt -= pennie;
            coinsCount++;
        }
    }
    
    printf("%d\n", coinsCount);
    
    return 0;
}
