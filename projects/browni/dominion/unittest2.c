#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dominion.h"


// test drawCard()
int main() {
  printf("Testing drawCard()\n");
  int testPlayer = 0;
  int testHandCount = 0;
  int testDiscardCount = 0;
  int testDeckCount = 1;
  int testHandCard = 0;
  int testDeckCard = 1;
  struct gameState *g = malloc(sizeof(struct gameState));

  g->handCount[testPlayer] = testHandCount;
  g->discardCount[testPlayer] = testDiscardCount;
  g->deckCount[testPlayer] = testDeckCount;
  g->hand[testPlayer][0] = testHandCard;
  g->deck[testPlayer][0] = testDeckCard;

  int result = drawCard(testPlayer, g);
  assert(result == 0);
  assert(g->handCount[testPlayer] == testHandCount + 1);
  assert(g->deckCount[testPlayer] == testDeckCount - 1);
  assert(g->hand[testPlayer][1] == testDeckCard);
  printf("Test successful\n");
}
