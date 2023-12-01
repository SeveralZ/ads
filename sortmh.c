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


void merge(struct Student arr[], int left, int mid, int right, int *swapCount) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    
    struct Student* L = (struct Student*)malloc(n1 * sizeof(struct Student));
    struct Student* R = (struct Student*)malloc(n2 * sizeof(struct Student));

    
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
        if (L[i].student_roll_no <= R[j].student_roll_no) {
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


void mergeSort(struct Student arr[], int left, int right, int *swapCount) {
    if (left < right) {
       
        int mid = left + (right - left) / 2;

        
        mergeSort(arr, left, mid, swapCount);
        mergeSort(arr, mid + 1, right, swapCount);

        
        merge(arr, left, mid, right, swapCount);
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
    struct Student* studentsMergeSort = (struct Student*)malloc(n * sizeof(struct Student));

    memcpy(studentsHeapSort, students, n * sizeof(struct Student));
    memcpy(studentsMergeSort, students, n * sizeof(struct Student));

    
    int swapCountHeapSort = 0;
    heapSort(studentsHeapSort, n, &swapCountHeapSort);

    
    int swapCountMergeSort = 0;
    mergeSort(studentsMergeSort, 0, n - 1, &swapCountMergeSort);

    
    printf("\nSorted Array using Heap Sort:\n");
    displayStudents(studentsHeapSort, n);
    printf("Number of swaps in Heap Sort: %d\n", swapCountHeapSort);

    printf("\nSorted Array using Merge Sort:\n");
    displayStudents(studentsMergeSort, n);
    printf("Number of swaps in Merge Sort: %d\n", swapCountMergeSort);

    
    free(students);
    free(studentsHeapSort);
    free(studentsMergeSort);

    return 0;
}
