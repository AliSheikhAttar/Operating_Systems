#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <stdbool.h>
#define max 32
void reverseString(char* str) {
    int length = strlen(str);
    int i, j;
    char temp;

    // Swap characters from beginning and end
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
bool isEqual(char* neck0, char* neck1,int len){
    int len1 = strlen(neck0);
    int len2 = strlen(neck1);

    // Check if lengths are different
    if (len1 != len2)
        return 0;

    // Concatenate necklace1 with itself
    char temp[16];
    strcpy(temp, neck0);
    strcat(temp, neck0);
    temp[2 * len1] = '\0';
    // Check if necklace2 is a substring of concatenated necklace1
    if (strstr(temp, neck1) != NULL)
        return 1;
    reverseString(neck1);
    if(strstr(temp, neck1) != NULL)
        return 1;
    return 0;

//     int indexOuter = 0;
//     char state = '0';
//     for(int i = 0; i < len;i++){
//         if (state== '1'){ return true; }
//         indexOuter = i; state = '1';
//         for(int j = 0; j < len; j++){
//             if(indexOuter == len){
//                 indexOuter = 0;
//             }
//             if (neck0[indexOuter] != neck1[j]){
//                 state = '0';
//                 break;
//             }
//             indexOuter ++;
//         }
//    } 
//     for(int i = 0; i < len;i++){
//         if (state == '1'){ return true; }
//         indexOuter = i; state = '1';
//         for(int j = len -1 ; j >= 0; j--){
//             if(indexOuter == len){
//                 indexOuter = 0;
//             }
//             if (neck0[indexOuter] != neck1[j]){
//                 state = '0';
//                 break;
//             }
//             indexOuter ++;
//         }
//    } 
//    return false;
}
int main(){
    int n = 0;
    int counter;
    int counter1;
    char necklaces[32];
    char necklace0[32];
    char necklace1[32];
    char results[21844];
    int len;
    scanf("%d", &n);
    while (getchar() != '\n'); // Clear input buffer // Consume the newline character 
    for (int i = 0; i<n; i++){
        fgets(necklaces, max, stdin); 
        counter = 0 ;

        while(necklaces[counter] != ' '){
            necklace0[counter] = necklaces[counter];
            counter ++;
        }
        necklace0[counter] = '\0';
        counter ++;
        counter1 = counter;
        counter = 0;
        while(necklaces[counter1]!= '\0' && necklaces[counter1] != '\n'){
            necklace1[counter] = necklaces[counter1];
            counter++;
            counter1++;
        }
        necklace1[counter] = '\0';
        if (strlen(necklace0) != strlen(necklace1))
        {
            results[i] = '0';
            continue;
        }
        len = strlen(necklace0);
        if (isEqual(necklace0,necklace1,len) == 1){ results[i]= '1';}
        else{ results[i] = '0';}
    }

    for(int r = 0;r < n; r++){
        switch (results[r])
        {
            case '1':
                printf("YES\n");
                break;
            case '0':
                printf("NO\n");
            default:
                break;
        }
    }

    return 0;

    
}
