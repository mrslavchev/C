#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define LOWER 'a'
#define UPPER 'A'

// Function declarations. 
static bool stringIsAlpha(string s);
static string ignoreCase(string s);
static string encryptMessage(string msg, string key);

int main (int argc, string argv[])
{
    string key;
    string message;
    string encrypted;
    
    if(argc != 2){
        printf("Invalid key count. Must use single key as command line argument.\nPlease try again.\n");
        return 1;
    }else if(!stringIsAlpha(argv[1])){
        printf("Incorrect key! Key must be single word with characters a-z and A-Z.\nPlease try again.");
        return 1;
    }else{
        key = ignoreCase(argv[1]);
        message = GetString();
        encrypted = encryptMessage(message, key);
        printf("%s\n", encrypted);
    }
}

/**Reverts string to lowercase ignoring uppercase letters*/
static string ignoreCase(string s)
{
    for(int i = 0; i < strlen(s); i++){
        s[i] = tolower(s[i]);
    }
    
    return s;
}

/**Takes two strings and encrypts the first one, using the second one as a key.
Uses cuctom logic for key, shorter than the message.Preserves case of the original
message.*/
static string encryptMessage(string msg, string key)
{
    int msgLen = strlen(msg);
    int keyLen = strlen(key);
    int msgLetter;
    int keyLetter;
    int result;
    int index = 0;
    
    if(msgLen >= keyLen){
        for(int i = 0; i < msgLen; i++){
            if(isalpha(msg[i])){
                keyLetter = key[index % keyLen] - LOWER;
                if(isupper(msg[i])){
                    msgLetter = msg[i] - UPPER;                    
                    result = (msgLetter + keyLetter) % 26;
                    msg[i] = result + UPPER;               
                }else{
                    msgLetter = msg[i] - LOWER;
                    result = (msgLetter + keyLetter) % 26;
                    msg[i] = result + LOWER;
                }
                
                index++;
            }else{
                continue;
            }
        }
    }else{
        for(int i = 0; i < msgLen; i++){
            if(isalpha(msg[i])){
                keyLetter = key[i] - LOWER;
                if(isupper(msg[i])){
                    msgLetter = msg[i] - UPPER;                    
                    result = (msgLetter + keyLetter) % 26;
                    msg[i] = result + UPPER;
                }else{
                    msgLetter = msg[i] - LOWER;
                    result = (msgLetter + keyLetter) % 26;
                    msg[i] = result + LOWER;
                }
            }else{
                continue;
            }
        }
    }
    
    return msg;
}

/**Takes string as single argument, returns false if non-alphabetic symbols are contained and true in
the opposite case.*/
static bool stringIsAlpha(string s){
    for(int i = 0; i < strlen(s); s++){
        if(isalpha(s[i])){
            continue;
        }else{
            return false;
        }
    }
    
    return true;
}
