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
  int testHandCount = rand() % (MAX_HAND / 4 - 2) + 2;
  printf("testHandCount: %d\n", testHandCount);
  int testTrashCard = rand() % (treasure_map + 1);
  printf("testTrashCard: %d\n", testTrashCard);
  int testGainCard = rand() % (treasure_map + 1);
  printf("testGainCard: %d\n", testGainCard);
  int testDeckCount = rand() % (MAX_DECK / 4);
  printf("testDeckCount: %d\n", testDeckCount);
  int testPlayedCount = rand() % (MAX_DECK / 4);
  printf("testPlayedCount: %d\n", testPlayedCount);
  int testSupplyCount = rand() % (MAX_DECK / 4);
  printf("testSupplyCount: %d\n", testSupplyCount);
  int mineIndex = rand() % testHandCount;
  printf("mineIndex: %d\n", mineIndex);
  int trashCardIndex;
  do {
    trashCardIndex = rand() % testHandCount;
  } while (trashCardIndex == mineIndex);
  printf("trashCardIndex: %d\n", trashCardIndex);

  struct gameState *g = malloc(sizeof(struct gameState));
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][mineIndex] = mine;
  g->hand[testPlayer][trashCardIndex] = testTrashCard;
  g->deckCount[testPlayer] = testDeckCount;
  g->playedCardCount = testPlayedCount;
  g->supplyCount[testGainCard] = testSupplyCount;
  g->whoseTurn = testPlayer;

  int expectedResult;
  int trashCardNotTreasure = (testTrashCard < copper || testTrashCard > gold);
  int gainCardNotTreasure = (testGainCard < copper || testGainCard > gold);
  int gainCardTooExpensive = (getCost(testGainCard) > (getCost(testTrashCard) + 3));
  if (trashCardNotTreasure || gainCardNotTreasure || gainCardTooExpensive || testSupplyCount < 1) {
    expectedResult = -1;
  } else {
    expectedResult = 0;
  }

  struct gameState *pre = malloc(sizeof(struct gameState));
  memcpy(pre, g, sizeof(struct gameState));

  pre->handCount[testPlayer]--;
  pre->playedCardCount++;
  pre->hand[testPlayer][pre->handCount[testPlayer] - 1] = testGainCard;

  int result = cardEffect(mine, trashCardIndex, testGainCard, -1, g, mineIndex, NULL);
  assertEqual(result, expectedResult, &failures, __LINE__);
  if (result == -1 && expectedResult == -1) {
    return;
  }
  assertEqual(g->handCount[testPlayer], pre->handCount[testPlayer], &failures, __LINE__);
  int lastIndex = g->handCount[testPlayer] - 1;
  assertEqual(g->hand[testPlayer][lastIndex], pre->hand[testPlayer][lastIndex], &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], pre->deckCount[testPlayer], &failures, __LINE__);
  assertEqual(g->playedCardCount, g->playedCardCount, &failures, __LINE__);
  assertEqual(g->playedCards[g->playedCardCount - 1], mine, &failures, __LINE__);

  printFailures(failures, __FILE__);
  if (failures > 0) {
    exit(1);
  }
}

// Test mine
int main() {
  printf("Testing mine\n");

  int numIterations = 100000;
  printf("Iterating %d times", numIterations);

  srand(time(NULL));

  for (int i = 0; i < numIterations; i++) {
    printf("Iteration %d\n", i + 1);
    test();
    printf("\n");
  }
}
