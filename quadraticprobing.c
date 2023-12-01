#include <stdio.h>

#define MAX_TABLE_SIZE 100

int quadraticProbing(int hashTable[], int key, int tableSize, int *collisionCount) {
    int index = key % tableSize;
    int i = 1;

    while (hashTable[index] != -1) {
        index = (index + i * i) % tableSize;
        i++;
        (*collisionCount)++;
    }

    hashTable[index] = key;
    return index;
}

int main() {
    int tableSize, numKeys, collisionCount = 0;

    printf("Enter the size of the hash table: ");
    scanf("%d", &tableSize);

    int hashTable[MAX_TABLE_SIZE];
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = -1;
    }

    printf("Enter the number of keys to insert: ");
    scanf("%d", &numKeys);

    printf("Enter the keys to insert:\n");
    for (int i = 0; i < numKeys; i++) {
        int key;
        scanf("%d", &key);
        int index = quadraticProbing(hashTable, key, tableSize, &collisionCount);
        printf("Inserted %d at index %d\n", key, index);
    }

    printf("Total collisions: %d\n", collisionCount);

    return 0;
}
