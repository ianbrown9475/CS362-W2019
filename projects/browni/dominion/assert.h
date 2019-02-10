#ifndef _ASSERT_H
#define _ASSERT_H


void assertTrue(int statement, int *failures);
void assertEqual(int actual, int expected, int *failures, int line);
void printFailures(int failures);

#endif
