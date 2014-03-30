#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Variables definition.
    int n;
    bool isNotValid;
    
    // Reading user inpit and check if it's valid.
    do{
        printf("Heigth:");
        n = GetInt(); 
        if(n < 0 || n > 23){
            isNotValid = true;
        }else{
            isNotValid = false;
        }
      
    }while(isNotValid);
    
    int counter;
    counter = 0;
    
    // Print the pyramid.
    for(int row = 0; row < n; row++){
        for(int col = 0; col <= n; col++){
            if(col >= (n - 1 - counter)){
                printf("#");
            }else{
                printf(" ");
            }
        }
        
        counter++;
        printf("\n");
    }
    return 0;
}
