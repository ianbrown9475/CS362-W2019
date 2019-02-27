#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"


// Test mine
int main() {
  printf("Testing mine\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 2;
  int testTrashCard = copper;
  int testGainCard = silver;
  int testDeckCount = 0;
  int testPlayedCount = 0;
  int testSupplyCount = 1;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][testHandCount - 2] = mine;
  g->hand[testPlayer][testHandCount - 1] = testTrashCard;
  g->deckCount[testPlayer] = testDeckCount;
  g->playedCardCount = testPlayedCount;
  g->supplyCount[testGainCard] = testSupplyCount;

  int result = cardEffect(mine, testHandCount - 1, testGainCard, -1, g, testHandCount - 2, NULL);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount - 1, &failures, __LINE__);
  assertEqual(g->hand[testPlayer][testHandCount - 2], testGainCard, &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], testDeckCount, &failures, __LINE__);
  assertEqual(g->playedCardCount, testPlayedCount + 1, &failures, __LINE__);
  assertEqual(g->playedCards[g->playedCardCount - 1], mine, &failures, __LINE__);

  printFailures(failures, __FILE__);
}
