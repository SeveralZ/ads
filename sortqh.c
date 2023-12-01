#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};


void heapify(struct Student arr[], int n, int i, int *swapCount) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no) {
        largest = left;
    }

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no) {
        largest = right;
    }

    if (largest != i) {
        
        struct Student temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        (*swapCount)++;

        
        heapify(arr, n, largest, swapCount);
    }
}


void heapSort(struct Student arr[], int n, int *swapCount) {
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, swapCount);
    }

    
    for (int i = n - 1; i > 0; i--) {
        
        struct Student temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        (*swapCount)++;

        
        heapify(arr, i, 0, swapCount);
    }
}


int partition(struct Student arr[], int low, int high, int *swapCount) {
    struct Student pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].student_roll_no < pivot.student_roll_no) {
            i++;

            
            struct Student temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            (*swapCount)++;
        }
    }

    
    struct Student temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    (*swapCount)++;

    return i + 1;
}


void quickSort(struct Student arr[], int low, int high, int *swapCount) {
    if (low < high) {
        
        int pivotIndex = partition(arr, low, high, swapCount);

       
        quickSort(arr, low, pivotIndex - 1, swapCount);
        quickSort(arr, pivotIndex + 1, high, swapCount);
    }
}


void displayStudents(struct Student arr[], int n) {
    printf("Student Details:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %-20s Roll No: %-5d Total Marks: %-5d\n",
               arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

int main() {
    int n;

    printf("Enter the number of students: ");
    scanf("%d", &n);

  
    struct Student* students = (struct Student*)malloc(n * sizeof(struct Student));

    
    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Roll No: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }

    
    struct Student* studentsHeapSort = (struct Student*)malloc(n * sizeof(struct Student));
    struct Student* studentsQuickSort = (struct Student*)malloc(n * sizeof(struct Student));

    memcpy(studentsHeapSort, students, n * sizeof(struct Student));
    memcpy(studentsQuickSort, students, n * sizeof(struct Student));

    
    int swapCountHeapSort = 0;
    heapSort(studentsHeapSort, n, &swapCountHeapSort);

    
    int swapCountQuickSort = 0;
    quickSort(studentsQuickSort, 0, n - 1, &swapCountQuickSort);

    
    printf("\nSorted Array using Heap Sort:\n");
    displayStudents(studentsHeapSort, n);
    printf("Number of swaps in Heap Sort: %d\n", swapCountHeapSort);

    printf("\nSorted Array using Quick Sort:\n");
    displayStudents(studentsQuickSort, n);
    printf("Number of swaps in Quick Sort: %d\n", swapCountQuickSort);

   
    free(students);
    free(studentsHeapSort);
    free(studentsQuickSort);

    return 0;
}
