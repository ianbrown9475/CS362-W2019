#include <stdio.h>

#include "assert.h"


void assertTrue(int statement, int *failures) {
  if (!statement) {
    (*failures)++;
  }
}

void assertEqual(int actual, int expected, int *failures, int line) {
  if (expected != actual) {
    printf("assertEqual failed on line %d: actual value %d does not equal expected value %d\n", line, actual, expected);
    (*failures)++;
  }
}

void printFailures(int failures, char *file) {
  if (failures) {
    printf("TEST FAILED: %d failure(s) encountered in file %s\n", failures, file);
  } else {
    printf("TEST SUCCESSFUL in file %s\n", file);
  }
}