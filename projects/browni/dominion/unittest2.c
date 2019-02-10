#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion_helpers.h"


// test drawCard()
int main() {
  printf("Testing drawCard()\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandCount = 1;
  int testDiscardCount = 0;
  int testDeckCount = 1;
  int testHandCard = curse;
  int testDeckCard = estate;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->discardCount[testPlayer] = testDiscardCount;
  g->deckCount[testPlayer] = testDeckCount;
  g->hand[testPlayer][0] = testHandCard;
  g->deck[testPlayer][0] = testDeckCard;

  int result = drawCard(testPlayer, g);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], testHandCount + 1, &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], testDeckCount - 1, &failures, __LINE__);
  assertEqual(g->hand[testPlayer][testHandCount - 1], testHandCard, &failures, __LINE__);
  assertEqual(g->hand[testPlayer][testHandCount], testDeckCard, &failures, __LINE__);

  printFailures(failures);
}
