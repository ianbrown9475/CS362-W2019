#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"


// Test village
int main() {
  printf("Testing village\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 1;
  int testDeckCount = 1;
  int testDeckCard = copper;
  int testPlayedCount = 0;
  int testActions = 0;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][testHandCount - 1] = village;
  g->deckCount[testPlayer] = testDeckCount;
  g->deck[testPlayer][testDeckCount - 1] = testDeckCard;
  g->playedCardCount = testPlayedCount;
  g->numActions = testActions;

  int result = cardEffect(village, -1, -1, -1, g, testHandCount - 1, NULL);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->playedCardCount, testPlayedCount + 1, &failures, __LINE__);
  assertEqual(g->playedCards[0], village, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount + 1 - 1, &failures, __LINE__);
  assertEqual(g->hand[testPlayer][g->handCount[testPlayer] - 1], testDeckCard, &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], testDeckCount - 1, &failures, __LINE__);
  assertEqual(g->numActions, testActions + 2, &failures, __LINE__);

  printFailures(failures, __FILE__);
}
