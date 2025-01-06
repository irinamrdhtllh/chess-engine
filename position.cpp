#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

#define INITIAL_CAPACITY 8

void position_print(Position position) {
    printf("%c%c", position.file, position.rank);
}

PositionArray *position_array_new() {
    PositionArray *position_array = malloc(sizeof(PositionArray));
    position_array->capacity = INITIAL_CAPACITY;
    position_array->length = 0;
    position_array->array = calloc(position_array->capacity, sizeof(Position));

    return position_array;
}

void position_array_free(PositionArray *position_array) {
    free(position_array->array);
    free(position_array);
}

void position_array_append(PositionArray *position_array, Position position) {
    if (position_array->length >= position_array->capacity) {
        position_array->capacity = 2 * position_array->capacity;
        position_array->array = reallocarray(
            position_array->array, position_array->capacity, sizeof(Position));
    }

    position_array->array[position_array->length] = position;
    position_array->length++;
}