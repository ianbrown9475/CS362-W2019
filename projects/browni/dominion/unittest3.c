#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion_helpers.h"


// test gainCard()
int main() {
  printf("Testing gainCard()\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 0;
  int testDiscardCount = 0;
  int testDeckCount = 0;
  int testgainCard = curse;
  int testSupplyCount = 3;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->discardCount[testPlayer] = testDiscardCount;
  g->deckCount[testPlayer] = testDeckCount;
  g->supplyCount[testgainCard] = testSupplyCount;

  // add to discard
  int result = gainCard(testgainCard, g, 0, testPlayer);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount, &failures, __LINE__);
  assertEqual(g->discardCount[testPlayer], testDiscardCount + 1, &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], testDeckCount, &failures, __LINE__);
  assertEqual(g->supplyCount[testgainCard], testSupplyCount - 1, &failures, __LINE__);

  // add to deck
  result = gainCard(testgainCard, g, 1, testPlayer);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount, &failures, __LINE__);
  assertEqual(g->discardCount[testPlayer], testDiscardCount + 1, &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], testDeckCount + 1, &failures, __LINE__);
  assertEqual(g->supplyCount[testgainCard], testSupplyCount - 2, &failures, __LINE__);

  // add to hand
  result = gainCard(testgainCard, g, 2, testPlayer);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount + 1, &failures, __LINE__);
  assertEqual(g->discardCount[testPlayer], testDiscardCount + 1, &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], testDeckCount + 1, &failures, __LINE__);
  assertEqual(g->supplyCount[testgainCard], testSupplyCount - 3, &failures, __LINE__);

  printFailures(failures, __FILE__);
}
