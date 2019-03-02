#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"


void test() {
  int failures = 0;
  int testPlayer = rand() % MAX_PLAYERS;
  printf("testPlayer: %d\n", testPlayer);
  int testHandCount = rand() % (MAX_HAND / 3 - 1) + 1;
  printf("testHandCount: %d\n", testHandCount);
  int testDeckCount = rand() % (MAX_DECK / 3);
  printf("testDeckCount: %d\n", testDeckCount);
  int testPlayedCount = rand() % (MAX_DECK / 3);
  printf("testPlayedCount: %d\n", testPlayedCount);
  int testActions = rand() % 100;
  printf("testActions: %d\n", testActions);
  int villageIndex = rand() % testHandCount;
  printf("villageIndex: %d\n", villageIndex);

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][villageIndex] = village;
  for (int i = 0; i < testHandCount; i++) {
    g->hand[testPlayer][i] = rand() % (treasure_map + 1);
  }
  g->deckCount[testPlayer] = testDeckCount;
  for (int i = 0; i < testDeckCount; i++) {
    g->deck[testPlayer][i] = rand() % (treasure_map + 1);
  }
  g->playedCardCount = testPlayedCount;
  g->numActions = testActions;
  g->whoseTurn = testPlayer;

  struct gameState *pre = malloc(sizeof(struct gameState));
  memcpy(pre, g, sizeof(struct gameState));

  discardCard(villageIndex, testPlayer, pre, 0);
  pre->numActions += 2;
  drawCard(testPlayer, pre);

  int result = cardEffect(village, -1, -1, -1, g, villageIndex, NULL);
  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->playedCardCount, pre->playedCardCount, &failures, __LINE__);
  for (int i = 0; i < g->playedCardCount; i++) {
    assertEqual(g->playedCards[i], pre->playedCards[i], &failures, __LINE__);
  }
  assertEqual(g->handCount[testPlayer], pre->handCount[testPlayer], &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], pre->deckCount[testPlayer], &failures, __LINE__);
  assertEqual(g->numActions, pre->numActions, &failures, __LINE__);

  printFailures(failures, __FILE__);
  if (failures > 0) {
    exit(1);
  }
}

// Test village
int main() {
  printf("Testing village\n");

  int numIterations = 100000;
  printf("Iterating %d times\n", numIterations);

  srand(time(NULL));

  for (int i = 0; i < numIterations; i++) {
    printf("Iteration %d\n", i + 1);
    test();
    printf("\n");
  }
}
