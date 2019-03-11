#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"


// Test smithy
int main() {
  printf("Testing smithy\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 1;
  int testDeckCount = 3;
  int testDeckCard = copper;
  int testPlayedCount = 0;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][testHandCount - 1] = smithy;
  g->deckCount[testPlayer] = testDeckCount;
  for (int i = 0; i < testDeckCount; i++) {
    g->deck[testPlayer][i] = testDeckCard;
  }
  g->playedCardCount = testPlayedCount;

  int result = cardEffect(smithy, -1, -1, -1, g, testHandCount - 1, NULL);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->playedCardCount, testPlayedCount + 1, &failures, __LINE__);
  assertEqual(g->playedCards[0], smithy, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount + 3 - 1, &failures, __LINE__);
  for (int i = 1; i <= 3; i++) {
    assertEqual(g->hand[testPlayer][testHandCount + 3 - 1 - i], testDeckCard, &failures, __LINE__);
  }
  assertEqual(g->deckCount[testPlayer], testDeckCount - 3, &failures, __LINE__);

  printFailures(failures, __FILE__);
}
