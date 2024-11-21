#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pet {
    char name[16];    // max 15 characters (plus room for null terminator)
    int age;
    char species[16];
};

int main() {
    size_t capacity = 1;
    size_t count = 0;
    struct Pet* pets = malloc(sizeof(struct Pet) * capacity);
    
    if (pets == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return 1;
    }

    char name[16];
    char species[16];
    int age;

    while (scanf("%15s %d %15s", name, &age, species) == 3) {
        if (count == capacity) {
            capacity *= 2;
            struct Pet* new_pets = realloc(pets, sizeof(struct Pet) * capacity);
            if (new_pets == NULL) {
                fprintf(stderr, "Error: Failed to reallocate memory\n");
                free(pets);
                return 1;
            }
            pets = new_pets;
        }

        // Copy strings to the struct fields
        strcpy(pets[count].name, name);
        pets[count].age = age;
        strcpy(pets[count].species, species);
        
        count++;
    }

    if (!feof(stdin)) {
        fprintf(stderr, "Error: Invalid input format\n");
        free(pets);
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s, %d, %s\n", pets[i].name, pets[i].age, pets[i].species);
    }

    free(pets);
    return 0;
}