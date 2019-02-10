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

void printFailures(int failures) {
  if (failures) {
    printf("TEST FAILED: %d failures encountered\n", failures);
  } else {
    printf("TEST SUCCESSFUL\n");
  }
}
