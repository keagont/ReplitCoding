#include <iostream>
#include <string>
#include <vector> 
#include <ctime>
#include <cstdlib>
#include <math.h>
using namespace std;

class player {
private:
	int gold = 0;
	int health = 20;
	int maxHealth = 20;
	int turns = 0;
	int min = 1;
	bool hasAdvantage = false;
	bool hasMagnet = false;
	int items = 0;
	int RBCountdown = 0;
	int magnetCountdown = 0;
	int dieSize = 6;

public:
	int GetGold() {return gold;}
	int GetHealth() {return health;}
	int GetMaxHealth() {return maxHealth;}
	int GetTurns() {return turns;}
	int GetMin() {return min;}
	bool GetAdvantage() {return hasAdvantage;}
	bool GetMagnet() {return hasMagnet;}
	int GetItems() {return items;}
	int GetRBCountdown() {return RBCountdown;}
	int GetMagnetCountdown() {return magnetCountdown;}
	int GetDieSize() {return dieSize;}

	void SetGold(int givenGold) {
		gold = givenGold;
	}
	void SetHealth(int givenHealth) {
		health = givenHealth;
	}
	void SetMaxHealth(int givenMaxHealth) {
		maxHealth = givenMaxHealth;
	}
	void SetTurns(int givenTurns) {
		turns = givenTurns;
	}
	void SetMin(int givenMin) {
		min = givenMin;
	}
	void SetAdvantage(bool givenAdvantage) {
		hasAdvantage = givenAdvantage;
	}
	void SetMagnet(bool givenMagnet) {
		hasMagnet = givenMagnet;
	}
	void SetItems(int givenItems) {
		items = givenItems;
	}
	void SetRBCountdown(int givenCountdown) {
		RBCountdown = givenCountdown;
	}
	void SetMagnetCountdown(int givenCountdown) {
		magnetCountdown = givenCountdown;
	}
	void SetDieSize(int givenDieSize) {
		dieSize = givenDieSize;
	}

};

player Bob;

int displayHealth(int h) {
	if(h < 0) {
		h = 0;
	}
	return h;
}

enum itemNames {
	shieldGrower, redbull, shieldHardener, bandaid, guaze, goldMagnet, roids,
	last
};

string itemNamesToString(itemNames n) {
	switch(n) {
		case shieldGrower:
			return "Shield Grower";
			break;
		case redbull:
			return "Redbull";
			break;
		case shieldHardener:
			return "Shield Hardener";
			break;
		case bandaid:
			return "Bandaid";
			break;
		case guaze:
			return "Guaze";
			break;
		case goldMagnet:
			return "Gold Magnet";
			break;
		case roids:
			return "Roids";
			break;
		default:
			return "Fake Item";
			break;
	}
}

int itemCosts(itemNames n) {
	switch(n) {
		case shieldGrower:
			return 5;
			break;
		case redbull:
			return 7;
			break;
		case shieldHardener:
			return 8;
			break;
		case bandaid:
			return 2;
			break;
		case guaze:
			return 6;
			break;
		case goldMagnet:
			return 13;
			break;
		case roids:
			return 10;
			break;
		default:
			return 0;
			break;
	}
}

itemNames shuffleItemNames(itemNames n = last, itemNames oldName = last) {
	itemNames newName = itemNames(rand() % last);
	while(newName == n || newName == oldName) {
		newName = itemNames(rand() % last);
	}
	return newName;
}

int rollDiePlayer(int sides = 6, int additional = 1, bool advantage = false) {
	if(advantage) {
		int roll1 = (rand() % (sides + 1 - additional) + additional);
		int roll2 = (rand() % (sides + 1 - additional) + additional);
		cout << "Roll 1: " << roll1 << ". Roll 2: " << roll2 << ".\n";
		if(roll1 > roll2) {
			return roll1;
		}
		return roll2;
	}
	return (rand() % (sides + 1 - additional) + additional);
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
	else if((Bob.GetHealth() / Bob.GetMaxHealth()) < .4 ) {
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
	if(Bob.GetMagnet()) {		// multiplies the gold collected by 3 if player has magnet
		goldWon *= 2;
	}
	cout << "On the ground, you find " << goldWon << " gold!!\n";
	return goldWon;
}
// calculates the amount of gold won during attack

void itemEffects(itemNames itemBought, int cost) {
	
	switch(itemBought) {
		case shieldGrower: {
			cout << "You pick up the bottle and pour it on the shield.\n";
			cout << "The shield is now easier to block with!\n";
			Bob.SetDieSize(Bob.GetDieSize() + 1);
			Bob.SetGold(Bob.GetGold() - cost);
			Bob.SetItems(Bob.GetItems() + 1);
			break;
		}
		case redbull: {
			cout << "You pick up the can and drink it in one fell swoop.\n";
			cout << "Your reaction time is higher now!\n";
			Bob.SetAdvantage(true);
			Bob.SetGold(Bob.GetGold() - cost);
			Bob.SetRBCountdown(3);
			Bob.SetItems(Bob.GetItems() + 1);
			break;
		}
		case shieldHardener: {
			cout << "You pick up the bottle and pour it on the shield.\n";
			cout << "You feel the shield get sturdier!\n";
			Bob.SetMin(Bob.GetMin() + 2);
			Bob.SetGold(Bob.GetGold() - cost);
			Bob.SetItems(Bob.GetItems() + 1);
			break;
		}
		case bandaid: {
			cout << "You apply the bandaid to your wounds.\n";
			cout << "You gain " << Bob.GetItems() + 2 << " health!\n";
			Bob.SetHealth(Bob.GetHealth() + Bob.GetItems() + 2);
			Bob.SetGold(Bob.GetGold() - cost);
			break;
		}
		case guaze:{
			int healAmount = ceil(Bob.GetTurns() / 2) + 4;
			cout << "You wrap the guaze around your wounds.\n";
			cout << "You gain " << healAmount << " health!\n";
			Bob.SetHealth(Bob.GetHealth() + healAmount);
			Bob.SetGold(Bob.GetGold() - cost);
			break;
		}
		case goldMagnet: {
			cout << "You grab the strange magnet.\n";
			cout << "You now gain 2 times the gold!\n";
			Bob.SetMagnet(true);
			Bob.SetMagnetCountdown(5);
			Bob.SetGold(Bob.GetGold() - cost);
			Bob.SetItems(Bob.GetItems() + 1);
			break;
		}
		case roids: {
			cout << "You pick up the needle.\n";
			cout << "You gain +10 to your max health!\n";
			Bob.SetMaxHealth(Bob.GetMaxHealth() + 10);
			Bob.SetHealth(Bob.GetHealth() + 5);
			Bob.SetGold(Bob.GetGold() - cost);
			Bob.SetItems(Bob.GetItems() + 1);
			break;
		}
		default:
			cout << "You leave the man and his trinkets.\n";
			break;
	}
}

void openShop(int gold = 0, int items = 0) {
	vector<string> Items = {"Shield Grower", "Redbull", "Shield Hardener", "Bandaid", "Guaze", "Gold Magnet", "Roids"};
	vector<int> Costs = {5, 7, 8, 2, 6, 13, 11};
	itemNames itemOne = shuffleItemNames();
	itemNames itemTwo = shuffleItemNames(itemOne);
	itemNames itemThree = shuffleItemNames(itemOne, itemTwo);
	int costOne = itemCosts(itemOne) + ceil((itemCosts(itemOne) / 2) * items);
	int costTwo = itemCosts(itemTwo) + ceil((itemCosts(itemTwo) / 2) * items);
	int costThree = itemCosts(itemThree) + ceil((itemCosts(itemThree) / 2) * items);
	string response;
	while(true) {
		cout << "\n============================================================\n";
		cout << "On your journey, you find a man selling goods.\n";
		cout << "You see three items in front of him.\n";
		cout << "You currently have " << gold << " gold.\n";
		cout << "1. " << itemNamesToString(itemOne) << ", " << costOne << " gold.\n";
		cout << "2. " << itemNamesToString(itemTwo) << ", " << costTwo << " gold.\n";
		cout << "3. " << itemNamesToString(itemThree) << ", " << costThree << " gold.\n";
		cout << "4. Don't buy anything.\n";
		cin >> response;
		if(response == "1") {
			if(gold >= costOne) {
				itemEffects(itemOne, costOne);
				break;
			}
			else {
				cout << "You're too broke.\n";
			}
		}
		else if(response == "2") {
			if(gold >= costTwo) {
				itemEffects(itemTwo, costTwo);
				break;
			}
			else {
				cout << "You're too broke.\n";
			}
		}
		else if(response == "3") {
			if(gold >= costThree) {
				itemEffects(itemThree, costThree);
				break;
			}
			else {
				cout << "You're too broke.\n";
			}
		}
		else if(response == "4" ||response == "leave" ||response == "n") {
			cout << "You leave the man and his trinkets.\n";
			break;
		}
		else {
			cout << "I'm afraid thats not an option.\n";
		}
		
	}
	
}

void showStats() {
	cout << "------------------------------";
	cout << "\nThe next turn will be turn " << Bob.GetTurns() + 1 << "\n";
	cout << "You currently have:\n"; 
	cout << displayHealth(Bob.GetHealth()) << "/" << Bob.GetMaxHealth() << " health\n";
	cout << Bob.GetGold() << " gold\n";
	cout << Bob.GetItems() << " items\n";
	cout << "------------------------------\n";
}

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
	int orcDieSize = 6;
	
	
	srand(time(0));

	while(true) {
		string input = askYesNo("Would you like to adventure?\n");
		// asks the player if they would like to play
		if(input == "yes" ||input == "y") {
			Bob.SetTurns(Bob.GetTurns() + 1); // adds one turn to the counter at the start of each loop
			cout << "\n============================================================\n";
			cout << "Turn " << Bob.GetTurns() << ".\n";
			cout << "You forge ahead into a small clearing in the woods.\n";
			cout <<	"While standing there, an orc jumps out from the bushes and attacks you!\n"; // text about orc attacking and player blocking
			cout << "You pull out your shield to block the attack.\n"; 
			int block = rollDiePlayer(Bob.GetDieSize(), Bob.GetMin(), Bob.GetAdvantage());
			cout << "you roll " << block << ".\n";
			int attack = rollDieOrc(orcDieSize);
			// rolls for attack and block
			if(block >= attack) {
				// if the block is greater than or equal to the attack
				cout << "============================================================\n";
				cout << "You put up your shield just in time and block the attack!\n";
				Bob.SetGold(Bob.GetGold() + (winGold(Bob.GetTurns(), Bob.GetTurns() + 3)));
				Bob.SetHealth(Bob.GetHealth() - 1);
			}
			else {
				cout << "============================================================\n"; 
				cout << "You couldn't react in time and the orc strikes you!\n";
				Bob.SetHealth(Bob.GetHealth() - (attack - block));
				if(Bob.GetMagnet()) {		// multiplies the gold collected by 3 if player has magnet
					cout << "The orc does " << attack - block << " damage! You run off, only gaining 2 gold.\n";
					Bob.SetGold(Bob.GetGold() + 3);
				}
				else {
					cout << "The orc does " << attack - block << " damage! You run off, only gaining 1 gold.\n";
					Bob.SetGold(Bob.GetGold() + 1);
				}
				cout << "You now have " << displayHealth(Bob.GetHealth()) << "/" << Bob.GetMaxHealth() << " health.\n";
			}
			if (Bob.GetHealth() <= 0) {
				cout << "You fall to the ground and drop all your gold.\n";
				break;
			}
			else if(Bob.GetTurns() % 2 == 0) { // chance to open shop to get new items
				openShop(Bob.GetGold(), Bob.GetItems());
			}
			if(Bob.GetTurns() % 4 == 0) {
				orcDieSize += 2;
				cout << "The orcs have gotten stronger!\n";
				Bob.SetHealth(Bob.GetHealth() + 3);
				cout << "...But, you also healed.\n";
			}
			if(Bob.GetRBCountdown() > 0) {
				Bob.SetRBCountdown(Bob.GetRBCountdown() - 1);
				cout << "Redbull turns left: " << Bob.GetRBCountdown() + 1<< " turns.\n";
			}
			else if(Bob.GetAdvantage()) {
				cout << "The redbull has worn off.\n";
				Bob.SetAdvantage(false);
			}
			if(Bob.GetMagnetCountdown() > 0) {
				Bob.SetMagnetCountdown(Bob.GetMagnetCountdown() - 1);
				cout << "Magnet turns left: " << Bob.GetMagnetCountdown() + 1 << " turns.\n";
			}
			else if(Bob.GetMagnet()) {
				cout << "The magnet has shattered.\n";
				Bob.SetMagnet(false);
			}
			if(Bob.GetHealth() > Bob.GetMaxHealth()) {
				Bob.SetHealth(Bob.GetMaxHealth());
			}
		}
		else if(input == "no" ||input == "n") {
			input = askYesNo("Are you sure you want to quit?\n");
			if(input == "yes" ||input == "y") {
				break;
			}
		}
		else if(input == "display" ||input == "stats" ||input == "stat" ||input == "s" ||input == "d" ||input == "ds") {
			showStats();
		}
		else {
			cout << "I'm afraid thats not an option.\n";
		}
		
	}
	endResults(Bob.GetHealth(), Bob.GetGold(), Bob.GetTurns());
	// calculates end numbers and results
}
