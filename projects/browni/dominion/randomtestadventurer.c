#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"


// Test adventurer
int main() {
  printf("Testing adventurer\n");

  srand(time(NULL));

  int failures = 0;
  // int testPlayer = 0;
  int testPlayer = rand() % MAX_PLAYERS;
  printf("testPlayer: %d\n", testPlayer);
  // int testHandCount = 1;
  int testHandCount = rand() % (MAX_HAND / 5 - 1) + 1;
  printf("testHandCount: %d\n", testHandCount);
  // int testDeckCount = 5;
  int testDeckCount = rand() % (MAX_DECK / 5);
  printf("testDeckCount: %d\n", testDeckCount);
  // int testPlayedCount = 0;
  int testPlayedCount = rand() % (MAX_DECK / 5);
  printf("testPlayedCount: %d\n", testPlayedCount);
  // int testDiscardCount = 0;
  int testDiscardCount = rand() % (MAX_DECK / 5);
  printf("testDiscardCount: %d\n", testDiscardCount);
  int adventurerIndex = rand() % testHandCount;
  printf("adventurerIndex: %d\n", adventurerIndex);

  struct gameState *g = malloc(sizeof(struct gameState));
  g->whoseTurn = testPlayer;
  g->handCount[testPlayer] = testHandCount;
  g->hand[testPlayer][adventurerIndex] = adventurer;
  g->deckCount[testPlayer] = testDeckCount;
  g->playedCardCount = testPlayedCount;
  g->discardCount[testPlayer] = testDiscardCount;

  // The index that should be stopped at when revealing cards from the top (end) of the deck
  int stopIndex = 0;
  int treasureCount = 0;
  for (int i = testDeckCount - 1; i >= 0; i--) {
    int card = rand() % (treasure_map + 1);
    g->deck[testPlayer][i] = card;
    if ((treasureCount < 2) && (card == copper || card == silver || card == gold)) {
      stopIndex = i;
      treasureCount++;
    }
  }

  struct gameState *pre = malloc(sizeof(struct gameState));
  memcpy(pre, g, sizeof(struct gameState));

  pre->playedCards[pre->playedCardCount - 1] = pre->hand[testPlayer][adventurerIndex];
  pre->playedCardCount++;
  pre->hand[testPlayer][adventurerIndex] = pre->hand[testPlayer][pre->handCount[testPlayer] - 1];
  pre->handCount[testPlayer]--;

  for (int i = pre->deckCount[testPlayer] - 1; i >= stopIndex; i--) {
    if (pre->deck[testPlayer][i] == copper || pre->deck[testPlayer][i] == silver || pre->deck[testPlayer][i] == gold) {
      pre->hand[testPlayer][pre->handCount[testPlayer]] = pre->deck[testPlayer][i];
      pre->handCount[testPlayer]++;

    } else {
      pre->discard[testPlayer][pre->discardCount[testPlayer]] = pre->deck[testPlayer][i];
      pre->discardCount[testPlayer]++;
    }
    pre->deckCount[testPlayer]--;
  }

  int result = cardEffect(adventurer, -1, -1, -1, g, adventurerIndex, NULL);

  assertEqual(result, 0, &failures, __LINE__);
  assertEqual(g->handCount[testPlayer], pre->handCount[testPlayer], &failures, __LINE__);
  for (int i = 0; i < g->handCount[testPlayer]; i++) {
    assertEqual(g->hand[testPlayer][i], pre->hand[testPlayer][i], &failures, __LINE__);
  }
  assertEqual(g->playedCardCount, pre->playedCardCount, &failures, __LINE__);
  assertEqual(g->playedCards[0], pre->playedCards[0], &failures, __LINE__);

  assertEqual(g->discardCount[testPlayer], pre->discardCount[testPlayer], &failures, __LINE__);
  assertEqual(g->deckCount[testPlayer], pre->deckCount[testPlayer], &failures, __LINE__);
  for (int i = 0; i < g->deckCount[testPlayer]; i++) {
    assertEqual(g->deck[testPlayer][i], pre->deck[testPlayer][i], &failures, __LINE__);
  }

  printFailures(failures, __FILE__);
}
