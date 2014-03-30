#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

/**We are splitting the problem in three parts, if the current char is a letter, using isalpha, if it is upper or 
lowercase. If none of the above is true, we proceed to the next one. The encryption is done by the formula, and to 
convert it back to ASCII, we are adding to 'a' if lower case, or 'A' if upper.*/

int main(int argc, string argv[])
{
    int currentLetter;
    int cypher;
    
    // Validate if correct number of arguments is inputted. 
    if(argc != 2){
        printf("You must include single integer as a command line parameter\nTry again!\n");
        return 1;
    }else{
        int key = atoi(argv[1]);
        string message = GetString();
        for(int i = 0; i < strlen(message); i++){
            if(isalpha(message[i])){
                if(isupper(message[i])){
                    currentLetter = message[i] - 'A';
                    cypher = (currentLetter + key) % 26;
                    message[i] = 'A' + cypher;
                }else if(islower(message[i])){
                    currentLetter = message[i] - 'a';
                    cypher = (currentLetter + key) % 26;
                    message[i] = 'a' + cypher;
                }
            }else{
                continue;
            }
        }
        
        printf("%s\n", message);
    }
}
