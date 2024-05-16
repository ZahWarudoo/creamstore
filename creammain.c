#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void searchGame();
void browseGenre();
void displayMenu();
void clearScreen();
void viewCart();
void proceedToPayment(float totalAmount);  // Add parameter type here
void payment_method(float totalAmount);    // Add parameter type here
void printReceipt(float totalAmount, float paymentAmount);  // Add parameter types here

// Predefined selection of games by genre
typedef struct {
    char *genre;
    char *games[5];
    float prices[5]; // Prices for each game
} Genre;

Genre genres[] = {
    {"Action", {"The Legend of Zelda: Breath of the Wild", "Super Mario Odyssey", "Grand Theft Auto V", "Red Dead Redemption 2", "DOOM Eternal"},
               {59.99, 49.99, 39.99, 49.99, 59.99}},
    {"Adventure", {"Minecraft", "The Witcher 3: Wild Hunt", "Uncharted 4: A Thief's End", "Life is Strange", "Firewatch"},
                  {19.99, 39.99, 29.99, 19.99, 24.99}},
    {"RPG", {"Cyberpunk 2077", "Final Fantasy XV", "Dark Souls III", "Persona 5", "The Elder Scrolls V: Skyrim"},
            {49.99, 39.99, 29.99, 49.99, 39.99}},
    {"Shooter", {"Call of Duty: Modern Warfare", "Overwatch", "Fortnite", "Apex Legends", "Counter-Strike: Global Offensive"},
                {59.99, 39.99, 0.0, 0.0, 14.99}},
    {"Sports", {"FIFA 21", "NBA 2K21", "Madden NFL 21", "Tony Hawk's Pro Skater 1+2", "Rocket League"},
               {59.99, 59.99, 59.99, 39.99, 19.99}}
};

int totalGenres = sizeof(genres) / sizeof(genres[0]);

// Cart to store selected games
char *cart[100];
int cartSize = 0;

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchGame();
                break;
            case 2:
                browseGenre();
                break;
            case 3:
                printf("Exiting the program.\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

void searchGame() {
    char searchQuery[100];
    int found = 0;

    clearScreen();
    printf("Search for a Game\n");
    printf("=================\n");
    printf("Enter the name of the game: ");
    getchar();  // Clear the newline character left by the previous input
    fgets(searchQuery, sizeof(searchQuery), stdin);
    searchQuery[strcspn(searchQuery, "\n")] = '\0';  // Remove trailing newline

    for (int i = 0; i < totalGenres; i++) {
        for (int j = 0; j < 5; j++) {
            if (strcasecmp(searchQuery, genres[i].games[j]) == 0) {
                printf("You have picked: %s ($%.2f)\n", genres[i].games[j], genres[i].prices[j]);
                cart[cartSize++] = genres[i].games[j];
                found = 1;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        printf("Game not found. Returning to search page.\n");
        printf("Press Enter to continue...");
        getchar();  // Wait for user input before continuing
        getchar();  // Wait for user input
        return;     // Redirect back to search page
    }

    viewCart();
}

void browseGenre() {
    int genreChoice, gameChoice;

    clearScreen();
    printf("Browse by Genre\n");
    printf("================\n");
    for (int i = 0; i < totalGenres; i++) {
        printf("%d. %s\n", i + 1, genres[i].genre);
    }
    printf("Enter the number of the genre you want to browse: ");
    scanf("%d", &genreChoice);

    if (genreChoice < 1 || genreChoice > totalGenres) {
        printf("Invalid genre choice. Returning to main menu.\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
        return;
    }

    Genre selectedGenre = genres[genreChoice - 1];
    clearScreen();
    printf("Games in %s\n", selectedGenre.genre);
    printf("=================\n");
    for (int i = 0; i < 5; i++) {
        printf("%d. %s ($%.2f)\n", i + 1, selectedGenre.games[i], selectedGenre.prices[i]);
    }
    printf("Enter the number of the game you want to choose: ");
    scanf("%d", &gameChoice);

    if (gameChoice < 1 || gameChoice > 5) {
        printf("Invalid game choice. Returning to genre selection.\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
        return;
    }

    printf("You have picked: %s ($%.2f)\n", selectedGenre.games[gameChoice - 1], selectedGenre.prices[gameChoice - 1]);
    cart[cartSize++] = selectedGenre.games[gameChoice - 1];

    viewCart();
}

void viewCart() {
    int choice;

    printf("\n1. Proceed to Payment\n");
    printf("2. Pick Another Game\n");
    printf("3. Return to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        float totalAmount = 0.0;
        for (int i = 0; i < cartSize; i++) {
            for (int j = 0; j < totalGenres; j++) {
                for (int k = 0; k < 5; k++) {
                    if (strcasecmp(cart[i], genres[j].games[k]) == 0) {
                        totalAmount += genres[j].prices[k];
                        break;
                    }
                }
            }
        }
        proceedToPayment(totalAmount);
    } else if (choice == 2) {
        displayMenu();
    } else if (choice == 3) {
        printf("Returning to main menu.\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
    } else {
        printf("Invalid choice. Returning to main menu.\n");
        printf("Press Enter to continue...");
        getchar();
        getchar();
    }
}

void proceedToPayment(float totalAmount) {
    clearScreen();
    printf("Review Your Selection\n");
    printf("=====================\n");

    if (cartSize == 0) {
        printf("Your cart is empty.\n");
    } else {
        printf("Games in Your Cart:\n");
        for (int i = 0; i < cartSize; i++) {
            for (int j = 0; j < totalGenres; j++) {
                for (int k = 0; k < 5; k++) {
                    if (strcasecmp(cart[i], genres[j].games[k]) == 0) {
                        printf("%d. %s ($%.2f)\n", i + 1, cart[i], genres[j].prices[k]);
                        break;
                    }
                }
            }
        }
        printf("Total Amount: $%.2f\n", totalAmount);
        payment_method(totalAmount); // Call payment method function
    }

    printf("Press Enter to exit...");
    getchar();
    getchar();
    exit(0);
}

void displayMenu() {
    clearScreen();
    printf("Welcome to the Video Game Store\n");
    printf("===============================\n");
    printf("1. Search for a Game\n");
    printf("2. Browse by Genre\n");
    printf("3. Exit\n");
}

void clearScreen() {
    system("clear || cls");
}

void payment_method(float totalAmount) {
    int choice;

    printf("\nPayment Methods:\n");
    printf("1. GrabPay\n");
    printf("2. MasterCard\n");
    printf("3. Touch 'n Go\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("You have chosen GrabPay.\n");
            break;
        case 2:
            printf("You have chosen MasterCard.\n");
            break;
        case 3:
            printf("You have chosen Touch 'n Go.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            payment_method(totalAmount); // Redirect to payment method selection again
            break;
    }

    printf("\nEnter the amount to pay ($%.2f): ", totalAmount);
    float paymentAmount;
    scanf("%f", &paymentAmount);

    if (paymentAmount < totalAmount) {
        printf("Insufficient amount. Please try again.\n");
        payment_method(totalAmount); // Redirect to payment method selection again
    } else {
        printf("Payment successful!\n");
        printReceipt(totalAmount, paymentAmount);
    }
}

void printReceipt(float totalAmount, float paymentAmount) {
    float change = paymentAmount - totalAmount;
    printf("\n--- Receipt ---\n");
    printf("Total Amount: $%.2f\n", totalAmount);
    printf("Payment Amount: $%.2f\n", paymentAmount);
    printf("Change: $%.2f\n", change);
    printf("Thank you for your purchase!\n");

    // Prompt user to return to the main menu
    printf("\nPress Enter to return to the main menu...");
    getchar();
    getchar();
    displayMenu(); // Return to the main menu after printing the receipt
}