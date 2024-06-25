#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hierarchy(char hierarchy[][500], int num_employees) {
    for (int i = 0; i < num_employees; i++) {
        printf("%s ", hierarchy[i]);
    }
    printf("\n");
}

// Function to apply changes
void apply_changes(char hierarchy[][500] , int* num_employees, char changes[][3][500], int num_changes) {
    for (int i = 0; i < num_changes; i++) {
        char *change_type = changes[i][0];
        if (strcmp(change_type, "add") == 0) {
            char *name = changes[i][1];
            int position = atoi(changes[i][2]);
            if (position >= (*num_employees))
                position = (*num_employees);
            // hierarchy[*num_employees] = (char*)malloc(500);
            for (int j = *num_employees; j > position; j--) {
                strcpy(hierarchy[j], hierarchy[j - 1]);
            }
            strcpy(hierarchy[position], name);
            (*num_employees)++;
        }
        else if (strcmp(change_type, "delete") == 0) {
            char *name = changes[i][1];
            for (int j = 0; j < *num_employees; j++) {
                if (strcmp(hierarchy[j], name) == 0) {
                    for (int k = j; k < *num_employees - 1; k++) {
                        strcpy(hierarchy[k], hierarchy[k + 1]);
                    }
                    (*num_employees)--;
                    break;
                }
            }
        }
        else if (strcmp(change_type, "swap") == 0) {
            char *name1 = changes[i][1];
            char *name2 = changes[i][2];
            int index1 = -1, index2 = -1;
            for (int j = 0; j < *num_employees; j++) {
                if (strcmp(hierarchy[j], name1) == 0) {
                    index1 = j;
                }
                else if (strcmp(hierarchy[j], name2) == 0) {
                    index2 = j;
                }
            }
            if (index1 != -1 && index2 != -1) {
                char temp[500];
                strcpy(temp, hierarchy[index1]);
                strcpy(hierarchy[index1], hierarchy[index2]);
                strcpy(hierarchy[index2], temp);
            }
        }
    }
}

int main() {
    int num_employees, num_changes;
    scanf("%d", &num_employees);

    // char** employees = (char**)malloc(num_employees);
    // for(int s = 0;s<num_employees;s++){
    //     employees[s] = (char*)malloc(500);
    // }
    char employees[num_employees][500];
    if (num_employees != 0){
        for (int i = 0; i < num_employees; i++) {
            scanf("%s", employees[i]);
        }
    }

    scanf("%d", &num_changes);
    // while (getchar() != '\n');
    
    char changes[num_changes][3][500];
    // char employees[2000][500];
    for (int i = 0; i < num_changes; i++) {
        scanf("%s", changes[i][0]);
        if (strcmp(changes[i][0], "delete") == 0)
        {
            scanf("%s", changes[i][1]);
        }
        else{
            for (int j = 1; j < 3; j++) {
                scanf("%s", changes[i][j]);
            }
        }
    }
    // Apply changes
    apply_changes(employees, &num_employees, changes, num_changes);

    // Print the hierarchy
    print_hierarchy(employees, num_employees);
    // printf("\n");

    // free(employees); // Free allocated memory
    return 0;
}
