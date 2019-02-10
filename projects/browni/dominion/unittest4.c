#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion_helpers.h"


// test updateCoins()
int main() {
  printf("Testing updateCoins()\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 0;
  int testCoins = 0;
  int testBonus = 0;
  int result;


  struct gameState *g = malloc(sizeof(struct gameState));

  // Test updating with no treasure cards in hand and no bonus
  g->coins = testCoins;
  g->handCount[testPlayer] = testHandCount;
  result = updateCoins(testPlayer, g, testBonus);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->coins, testCoins, &failures, __LINE__);

  // Test updating with no treasure cards in hand and 1 bonus
  testBonus++;
  testCoins++;
  result = updateCoins(testPlayer, g, testBonus);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->coins, testCoins, &failures, __LINE__);

  // Test updating with one copper in hand and no bonus
  testBonus--;
  testCoins--;
  testHandCount++;
  g->handCount[testPlayer] = testHandCount;
  testCoins += 1;
  g->hand[testPlayer][testHandCount - 1] = copper;
  result = updateCoins(testPlayer, g, testBonus);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->coins, testCoins, &failures, __LINE__);

  // Test updating with one copper in hand and one bonus
  testBonus++;
  testCoins++;
  result = updateCoins(testPlayer, g, testBonus);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->coins, testCoins, &failures, __LINE__);

  printFailures(failures, __FILE__);
}
