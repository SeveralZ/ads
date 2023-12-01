#include <stdio.h>

void findSwappedPair(int arr[], int n) {
    int firstIndex = -1, secondIndex = -1;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (firstIndex == -1) {
                
                firstIndex = i;
            } else {
                
                secondIndex = i + 1;
                break;  
            }
        }
    }

    if (firstIndex != -1 && secondIndex != -1) {
        printf("Swapped elements are %d and %d\n", arr[firstIndex], arr[secondIndex]);
        printf("Their positions are %d and %d\n", firstIndex + 1, secondIndex + 1);
    } else {
        printf("No swapped pair found.\n");
    }
}

int main() {
    int n;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    findSwappedPair(arr, n);

    return 0;
}
