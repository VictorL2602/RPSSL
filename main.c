#include <stdbool.h> // lets us use true/false (bool)
#include <stdio.h>   // lets us use printf and scanf
#include <stdlib.h>  // lets us use rand and srand
#include <time.h>    // lets us get the current time
#include <windows.h> // lets us use sleep

#define WINNING_SCORE 3 // how many points you need to win

// all possible moves, plus a counter (MOVE_COUNT = 5)
enum Move { ROCK, PAPER, SCISSORS, LIZARD, SPOCK, MOVE_COUNT };

int main(void) {
  srand((unsigned int)time(
      NULL)); // set random seed (so computer picks differently each run)

  // names of the moves, for printing
  const char *names[] = {"Rock", "Paper", "Scissors", "Lizard", "Spock"};

  // --- Menu before starting the game ---
  for (;;) { // repeat until valid choice
    printf(R"(
==== Rock-Paper-Scissors-Lizard-Spock ====
1) Play
2) Quit
)");
    printf("Choose (1-2): ");

    int menu, c;
    if (scanf("%d", &menu) != 1) { // check if input is a number
      printf("Invalid input. Please type 1 or 2.\n");
      while ((c = getchar()) != '\n' && c != EOF) {
      } // clear wrong input
      continue; // ask again
    }
    while ((c = getchar()) != '\n' && c != EOF) {
    } // clear extra input

    if (menu == 2) { // quit option
      printf("Goodbye!\n");
      return 0;             // end program
    } else if (menu == 1) { // play option
      break;                // exit menu loop
    } else {
      printf("Please enter 1 or 2.\n");
    }
  }

  int playerScore = 0, computerScore = 0; // scores start at 0

  printf(R"(
First to %d points wins.
Choices:
0 - Rock
1 - Paper
2 - Scissors
3 - Lizard
4 - Spock
)",
         WINNING_SCORE);

  // --- Main game loop ---
  while (playerScore < WINNING_SCORE && computerScore < WINNING_SCORE) {
    int choice, c;
    printf("Enter your choice (0-4): ");

    if (scanf("%d", &choice) != 1) { // check if input is a number
      printf("Invalid input. Please enter a number 0-4.\n");
      while ((c = getchar()) != '\n' && c != EOF) {
      }
      continue;
    }
    while ((c = getchar()) != '\n' && c != EOF) {
    }

    if (choice < 0 || choice >= MOVE_COUNT) { // must be between 0–4
      printf("Out of range. Please enter 0-4.\n");
      continue;
    }

    enum Move player = (enum Move)choice; // player’s move
    enum Move computer =
        (enum Move)(rand() % MOVE_COUNT); // computer picks randomly (based on
                                          // the computers current time)
    Sleep(1000); // 1 second waiting period to simulate the computer thinking

    printf("You chose: %s\nComputer chose: %s\n", names[player],
           names[computer]);

    if (player == computer) { // same move aka draw
      printf("Result: Draw.\n");
    } else {
      // check if player wins against computer
      bool playerWins =
          (player == ROCK && (computer == SCISSORS || computer == LIZARD)) ||
          (player == PAPER && (computer == ROCK || computer == SPOCK)) ||
          (player == SCISSORS && (computer == PAPER || computer == LIZARD)) ||
          (player == LIZARD && (computer == SPOCK || computer == PAPER)) ||
          (player == SPOCK && (computer == SCISSORS || computer == ROCK));

      if (playerWins) {
        ++playerScore; // player gets a point
        printf("Result: You win this round!\n");
      } else {
        ++computerScore; // computer gets a point
        printf("Result: Computer wins this round.\n");
      }
    }

    // show updated score
    printf("Score → You %d : %d Computer\n", playerScore, computerScore);
    printf("----------------------------------------\n");
  }

  // end of game, show winner
  if (playerScore == WINNING_SCORE)
    printf("🏆 You reached %d. You win the match!\n", WINNING_SCORE);
  else
    printf("🤖 Computer reached %d. Computer wins the match.\n", WINNING_SCORE);

  // wait for user to press Enter before closing
  printf("Press Enter to exit...");
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  } // clear leftovers
  getchar(); // wait for Enter
  return 0;  // program finished
}
