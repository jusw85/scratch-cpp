#include "helpers.h"

int clamp(int value, int min, int max) {
    if (value < min)
        value = min;
    else if (value > max)
        value = max;
    return value;
}
