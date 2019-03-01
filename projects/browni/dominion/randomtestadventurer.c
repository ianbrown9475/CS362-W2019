#include <math.h>
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
  int testHandCount = rand() % (MAX_HAND / 5 - 1) + 1;
  printf("testHandCount: %d\n", testHandCount);
  int testDeckCount = rand() % (MAX_DECK / 5);
  printf("testDeckCount: %d\n", testDeckCount);
  int testPlayedCount = rand() % (MAX_DECK / 5);
  printf("testPlayedCount: %d\n", testPlayedCount);
  int testDiscardCount = rand() % (MAX_DECK / 5);
  printf("testDiscardCount: %d\n", testDiscardCount);
  int adventurerIndex = rand() % testHandCount;
  printf("adventurerIndex: %d\n", adventurerIndex);

  struct gameState *g = malloc(sizeof(struct gameState));
  g->whoseTurn = testPlayer;
  g->handCount[testPlayer] = testHandCount;
  g->deckCount[testPlayer] = testDeckCount;
  g->playedCardCount = testPlayedCount;
  g->discardCount[testPlayer] = testDiscardCount;

  int maxDrawTreasure = 0;
  for (int i = 0; i < testDeckCount; i++) {
    int card = rand() % (treasure_map + 1);
    g->deck[testPlayer][i] = card;
    if ((maxDrawTreasure < 2) && (card == copper || card == silver || card == gold)) {
      maxDrawTreasure++;
    }
  }

  for (int i = 0; i < testDiscardCount; i++) {
    int card = rand() % (treasure_map + 1);
    g->discard[testPlayer][i] = card;
    if ((maxDrawTreasure < 2) && (card == copper || card == silver || card == gold)) {
      maxDrawTreasure++;
    }
  }

  int treasureCount = 0;
  for (int i = 0; i < testHandCount; i++) {
    if (i == adventurerIndex) {
      g->hand[testPlayer][i] = adventurer;
      continue;
    }
    int card = rand() % (treasure_map + 1);
    g->hand[testPlayer][i] = card;
    if (card == copper || card == silver || card == gold) {
      treasureCount++;
    }
  }

  struct gameState *pre = malloc(sizeof(struct gameState));
  memcpy(pre, g, sizeof(struct gameState));

  pre->playedCards[pre->playedCardCount] = pre->hand[testPlayer][adventurerIndex];
  pre->playedCardCount++;
  pre->hand[testPlayer][adventurerIndex] = pre->hand[testPlayer][pre->handCount[testPlayer] - 1];
  pre->handCount[testPlayer]--;
  pre->handCount[testPlayer] += maxDrawTreasure;

  int result = cardEffect(adventurer, -1, -1, -1, g, adventurerIndex, NULL);

  assertEqual(result, 0, &failures, __LINE__);
  int newTreasureCount = 0;
  int numLoops = g->handCount[testPlayer];
  for (int i = 0; i < numLoops; i++) {
    int card = g->hand[testPlayer][i];
    if (card == copper || card == silver || card == gold) {
      newTreasureCount++;
    }
  }
  assertEqual(newTreasureCount, treasureCount + maxDrawTreasure, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], pre->handCount[testPlayer], &failures, __LINE__);
  assertEqual(g->playedCardCount, pre->playedCardCount, &failures, __LINE__);
  assertEqual(g->playedCards[g->playedCardCount - 1], pre->playedCards[pre->playedCardCount - 1], &failures, __LINE__);

  printFailures(failures, __FILE__);
  if (failures > 0) {
    exit(1);
  }
}

// Test adventurer
int main() {
  printf("Testing adventurer\n");

  int numIterations = 100000;
  printf("Iterating %d times\n", numIterations);

  srand(time(NULL));

  for (int i = 0; i < numIterations; i++) {
    test();
  }
}
