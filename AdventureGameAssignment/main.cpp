#include <iostream>
#include <string>
#include <vector> 
#include <ctime>
#include <cstdlib>
using namespace std;

int rollDiePlayer(int sides = 6) {
	return (rand() % (sides) + 1);
}
// rolls the block number for the player

int rollDieOrc(int sides = 6) {
	return (rand() % (sides) + 1);
}
// rolls the attack number for the orc 
// the two functions are separate in case of future implementations
string askYesNo(string question) {
	string answer;
	cout << "\n" << question;
	cin >> answer;
	return answer;
}
// asks a yes or no answer to the player and returns the string

string playerState(int health = 0) {
	if(health <= 0) {
		return "\nYou have died from the evil orcs on your adventure.\n";
	}
	else if(health <= 5) {
		return "\nYou made it back from your adventure. However, you may want to visit a hospital.\n";
	}
	else {
		return "\nYou made it back from your adventure as healthy as ever!\n";
	}
}
// uses the current player health to decide which "ending" they get
int winGold(int min, int max) {
	int goldWon = (rand() % (max - min)) + min;
	cout << "You successfully blocked the orcs attack and only took 1 damage!\n";
	cout << "On the ground, you find " << goldWon << " gold!!\n";
	return goldWon;
}
// calculates the amount of gold won during attack
void endResults(int health, int gold, int turns) {
	cout << "============================================================\n";
	cout << playerState(health);
	cout << "You lasted " << turns << " turns this run!\n";
	if(health <= 0) {
		cout << "Next to your lifeless body was a pile of " << gold << " gold.\n";
	}
	else {
		cout << "During your adventure, you accumulated " << gold << " pieces of gold!\n";
	}
}
// declares the end results of player state, gold, and turns
int main() {
	int gold = 0;
	int health = 10;
	int turns = 0;
	srand(time(0));
	
	while(true) {
		string input = askYesNo("\nWould you like to adventure?\n");
		// asks the player if they would like to play
		if(input == "yes") {
			turns += 1; // adds one turn to the counter at the start of each loop
			cout << "\n============================================================\n";
			cout << "You forge ahead into a small clearing in the woods.\n";
			cout <<	"While standing there, an orc jumps out from the bushes and attacks you!\n"; // text about orc attacking and player blocking
			cout << "You pull out your shield to block the attack.\n"; 
			int block = rollDiePlayer();
			int attack = rollDieOrc();
			// rolls for attack and block
			if(block >= attack) {
				// if the block is greater than or equal to the attack
				cout << "============================================================\n";
				cout << "You put up your shield just in time and block the attack!\n";
				gold += winGold(turns, turns + 3); // adds gold 
				health -= 1;
			}
			else {
				cout << "============================================================\n"; 
				cout << "You couldn't react in time and the orc strikes you!\n";
				health -= attack;
				cout << "The orc does " << attack << " damage! You run off, ignoring the gold on the ground.\n";
			}
			if (health <= 0) {
				cout << "You fall to the ground and drop all your gold.\n";
				break;
			}
		}
		else if(input == "no") {
			break;
		}
		
	}
	endResults(health, gold, turns);
	// calculates end numbers and results
}
