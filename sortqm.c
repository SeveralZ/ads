#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Employee {
    char employee_name[50];
    int emp_no;
    float emp_salary;
};


int partition(struct Employee arr[], int low, int high, int *swapCount) {
    struct Employee pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].emp_no < pivot.emp_no) {
            i++;

            
            struct Employee temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            (*swapCount)++;
        }
    }

    
    struct Employee temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    (*swapCount)++;

    return i + 1;
}


void quickSort(struct Employee arr[], int low, int high, int *swapCount) {
    if (low < high) {
        
        int pivotIndex = partition(arr, low, high, swapCount);

        
        quickSort(arr, low, pivotIndex - 1, swapCount);
        quickSort(arr, pivotIndex + 1, high, swapCount);
    }
}


void merge(struct Employee arr[], int left, int mid, int right, int *swapCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    
    struct Employee* L = (struct Employee*)malloc(n1 * sizeof(struct Employee));
    struct Employee* R = (struct Employee*)malloc(n2 * sizeof(struct Employee));

    
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i].emp_no <= R[j].emp_no) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];

            (*swapCount) += (mid - i + 1); 
        }
    }

    
    while (i < n1) {
        arr[k++] = L[i++];
    }

    
    while (j < n2) {
        arr[k++] = R[j++];
    }

  
    free(L);
    free(R);
}


void mergeSort(struct Employee arr[], int left, int right, int *swapCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, swapCount);
        mergeSort(arr, mid + 1, right, swapCount);

        merge(arr, left, mid, right, swapCount);
    }
}


void displayEmployees(struct Employee arr[], int n) {
    printf("Employee Details:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %-20s Emp No: %-5d Salary: %-8.2f\n",
               arr[i].employee_name, arr[i].emp_no, arr[i].emp_salary);
    }
}

int main() {
    int n;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    
    struct Employee* employees = (struct Employee*)malloc(n * sizeof(struct Employee));

    
    for (int i = 0; i < n; i++) {
        printf("Enter details for employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", employees[i].employee_name);
        printf("Emp No: ");
        scanf("%d", &employees[i].emp_no);
        printf("Salary: ");
        scanf("%f", &employees[i].emp_salary);
    }

    
    struct Employee* employeesQuickSort = (struct Employee*)malloc(n * sizeof(struct Employee));
    struct Employee* employeesMergeSort = (struct Employee*)malloc(n * sizeof(struct Employee));

    memcpy(employeesQuickSort, employees, n * sizeof(struct Employee));
    memcpy(employeesMergeSort, employees, n * sizeof(struct Employee));

    
    int swapCountQuickSort = 0;
    quickSort(employeesQuickSort, 0, n - 1, &swapCountQuickSort);

   
    int swapCountMergeSort = 0;
    mergeSort(employeesMergeSort, 0, n - 1, &swapCountMergeSort);

   
    printf("\nSorted Array using Quick Sort:\n");
    displayEmployees(employeesQuickSort, n);
    printf("Number of swaps in Quick Sort: %d\n", swapCountQuickSort);

    printf("\nSorted Array using Merge Sort:\n");
    displayEmployees(employeesMergeSort, n);
    printf("Number of swaps in Merge Sort: %d\n", swapCountMergeSort);

    free(employees);
    free(employeesQuickSort);
    free(employeesMergeSort);

    return 0;
}
