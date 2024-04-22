#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define max 20


int SumViews(char* nums, char* nums1) {
    int Sum = 0;
    for (int j = 0; j < 8; j++)
    {
        Sum += (nums[j] & nums1[j]);//bitwise AND operation to get the common elements
    }
    
   
    return Sum;
}
int main(){
    
    char numsStr[max];
    char nums1Str[max];
    char nums[8];
    char nums1[8];
    fgets(numsStr, max, stdin); 
    fgets(nums1Str, max, stdin); 
    char split[] = " ";
    int i = 0;
    nums[i] = atoi(strtok(numsStr,split));
    for (i = 1; i < 8; i++)
    {
        nums[i] = atoi(strtok(NULL,split));
    }
    // nums[i] = '\0';
    int k = 0;
    nums1[k] = atoi(strtok(nums1Str,split));
    for (k = 1; k < 8; k++)
    {
        nums1[k] = atoi(strtok(NULL,split));
  
    }

    // nums1[i] = '\0';
    
    int Sum = SumViews(nums, nums1);
    printf("%d", Sum);
    return 0;
}
