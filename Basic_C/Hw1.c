#include <stdio.h>
#include <stdlib.h>
#include "string.h"
int main(){
    
    int numSize = 0;
    char nums_str[100];
    int nums[100];
    scanf("%d ", &numSize);
    fgets(nums_str,100,stdin);   
    char split[] = " ";
    int i = 0;
    nums[i] = atoi(strtok(nums_str,split));
    for (i = 1; i < numSize; i++)
    {
        nums[i] = atoi(strtok(NULL,split));
    }
    nums[i] = '\0';
    int profit = maxSubArray(nums, numSize);
    printf("%d", profit);
    return 0;
}
int maxSubArray(int* nums, int numSize) {
    int maxSum = 0;
    int calculatingSum = 0;
    int i =0;
    while (i< numSize){
        calculatingSum += nums[i];

        if(calculatingSum > maxSum){
            maxSum = calculatingSum; 
            // i++;
        }
        else if(calculatingSum < 0){
            calculatingSum = 0;
        //     while( i < numSize && nums[i] < 0 ){
        //         i ++ ;
        //     }
        // }
        // else{
        //     i++;
        }
        i++;
    }
    return maxSum;
}