#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"


// Test adventurer
int main() {
  printf("Testing adventurer\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 1;
  int testDeckCount = 5;
  int testPlayedCount = 0;
  int testDiscardCount = 0;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][testHandCount - 1] = adventurer;
  g->deckCount[testPlayer] = testDeckCount;
  g->playedCardCount = testPlayedCount;
  g->discardCount[testPlayer] = testDiscardCount;

  // deck order: curse | copper | curse | copper | curse
  for (int i = 0; i < testDeckCount; i++) {
    if (i == 1 || i == 3) {
      g->deck[testPlayer][i] = copper;
    } else {
      g->deck[testPlayer][i] = curse;
    }
  }

  int result = cardEffect(adventurer, -1, -1, -1, g, testHandCount - 1, NULL);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount + 2 - 1, &failures, __LINE__);
  for (int i = 0; i < g->handCount[testPlayer]; i++) {
    assertEqual(g->hand[testPlayer][i], copper, &failures, __LINE__);
  }
  assertEqual(g->playedCardCount, testPlayedCount + 1, &failures, __LINE__);
  assertEqual(g->playedCards[testPlayedCount], adventurer, &failures, __LINE__);

  assertEqual(g->discardCount[testPlayer], testDiscardCount + 2, &failures, __LINE__);
  for (int i = 0; i < g->discardCount[testPlayer]; i++) {
    assertEqual(g->discard[testPlayer][i], curse, &failures, __LINE__);
  }
  assertEqual(g->deckCount[testPlayer], testDeckCount - 4, &failures, __LINE__);
  assertEqual(g->deck[testPlayer][testDeckCount - 4 - 1], curse, &failures, __LINE__);

  printFailures(failures, __FILE__);
}
