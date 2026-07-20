#pragma once
#include "node.h"

typedef int (*compare_function)(const void *, const void *);
int compareByWeight(const void *a, const void *b);
