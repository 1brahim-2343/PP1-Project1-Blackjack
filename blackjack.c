#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int draw_card(void) {
    int result = rand() % 13 + 1;

    return result;
}

int game_status(int dealer_points, int player_points) {
    if (dealer_points > 21) {
        return 1; // dealer bust, player won
    }
    if (dealer_points > player_points) {
        return -1; // dealer won
    }
    if (player_points > dealer_points) {
        return 1; // player won
    }
    if (player_points == dealer_points) {
        return 0; //draw
    }

    return 2; //continue game
}

int card_points(int card_number) {
    if (card_number >= 11) {
        return 10;
    }
    return card_number;
}

void print_card_value(int card_number) {
    if (card_number >= 11 && card_number <= 13) {
        switch (card_number) {
            case 11:
                printf("J\n");
                break;
            case 12:
                printf("Q\n");
                break;
            case 13:
                printf("K\n");
                break;
            default:
                break;
        }
    } else if (card_number == 1) {
        printf("A\n");
    } else if (card_number >= 2 && card_number <= 10) {
        printf("%d\n", card_number);
    }
}

int read_choice(void) {
    int choice = 0;

    scanf("%d", &choice);

    while (!(choice == 1 || choice == 2)) {
        printf("Please type 1 or 2.\nChoice: ");
        scanf("%d", &choice);
    }
    return choice;
}

int dealer_turn(void) {
    printf("\n=== DEALER TURN ===\n");
    int resultant_total = 0;
    do {
        int drawn_card_number = draw_card();
        int drawn_card_point = card_points(drawn_card_number);

        resultant_total += drawn_card_point;

        printf("Dealer draws: ");
        print_card_value(drawn_card_number);
    } while (resultant_total < 17);

    printf("Dealer total: %d\n", resultant_total);

    if (resultant_total > 21) {
        printf("Dealer busts!\n");
    } else {
        printf("Dealer stands.\n");
    }

    return resultant_total;
}


int player_turn(void) {
    printf("\n=== PLAYER TURN ===\n");
    int drawn_card_number = draw_card();
    int drawn_card_point = card_points(drawn_card_number);
    int current_point = drawn_card_point;
    printf("You draw: ");
    print_card_value(drawn_card_number);


    return current_point;
}

int play_game(void) {
    int player_points = 0;
    int dealer_points = 0;

    player_points = player_turn();

    while (true) {
        printf("Your total: %d\n", player_points);
        if (player_points > 21) {
            printf("BUST! Your total is above 21\n");
            return -1;
        }
        printf("1. Hit\n");
        printf("2. Stand\n");
        printf("Choice: ");

        const int choice = read_choice();

        if (choice == 1) {
            player_points += player_turn();
        } else if (choice == 2) {
            dealer_points = dealer_turn();
            const int game_status_value = game_status(dealer_points, player_points);
            if (dealer_points > 21) {
                return game_status_value;
            }
            if (game_status_value != 2) {
                printf("Player total: %d\n", player_points);
                printf("Dealer total: %d\n", dealer_points);
                return game_status_value;
            }
        }
    }



    return 0;
}


int main(void) {
    srand(time(NULL));
    int win_count = 0;
    int draw_count = 0;
    int lose_count = 0;

    while (true) {
        const int result = play_game();

        if (result == 1) {
            printf("You win!\n");
            win_count++;
        } else if (result == -1) {
            printf("Dealer wins.\n");
            lose_count++;
        } else if (result == 0) {
            printf("Draw!\n");
            draw_count++;
        }


        printf("1. Play again\n2. Quit\nChoice: ");

        int choice = read_choice();


        if (choice == 2) {
            printf("Wins: %d, losses: %d, draws: %d\n", win_count, lose_count, draw_count);
            printf("Goodbye!\n");
            break;
        }
    }

    return 0;
}
