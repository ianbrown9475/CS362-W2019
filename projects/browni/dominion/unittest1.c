#include <stdio.h>
#include <stdlib.h>

#include "assert.h"
#include "dominion.h"


// Test numHandCards()
int main() {
  printf("Testing numHandCards()\n");

  int failures = 0;
  int testPlayer = 0;
  int testHandSize = 1;

  struct gameState *g = malloc(sizeof(struct gameState));
  g->numPlayers = 1;
  g->whoseTurn = testPlayer;
  g->handCount[testPlayer] = testHandSize;

  int result = numHandCards(g);
  assertEqual(result, testHandSize, &failures, __LINE__);

  printFailures(failures);
}
