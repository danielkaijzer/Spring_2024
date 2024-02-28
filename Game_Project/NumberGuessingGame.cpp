#include <iostream>
#include <cstdlib>

using namespace std;

// guess the number game
int main(){
    srand(time(0)); // seed random num generator


    int secretNum = rand() % 10 + 1; // generate ran num btwen 1 and 10
    int guess;
    bool isCorrect = false;

    cout << "Welcome to guessing game!\n";

    // game loop
    while(!isCorrect){
        cout << "Enter your guess: ";

        cin >> guess;

        if (guess == secretNum){
            isCorrect = true;
            cout << "Congratulations! You guessed right!\n";
        }
        else if (guess > secretNum){
            cout << "Your guess is too high.\n";
        }
        else{
            cout << "Your guess is too low.\n";
        }
    }
    return 0;
}


