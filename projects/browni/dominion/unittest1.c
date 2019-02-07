#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"


// Test numHandCards()
int main() {
  printf("Testing numHandCards()\n");
  int testPlayer = 0;
  int testHandSize = 1;
  struct gameState *g = malloc(sizeof(struct gameState));

  g->numPlayers = 1;
  g->whoseTurn = testPlayer;
  g->handCount[testPlayer] = testHandSize;

  int result = numHandCards(g);
  assert(result == testHandSize);
  printf("Test successful\n");
}
