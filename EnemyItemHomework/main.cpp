#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;
// HOMEWORK create BASIC adventure functionality using the enemy 
// class for each encounter. each enemy must use a weapon. 
// each enemy has health. player has option of using weapon or 
// consumable. at least one encounter, to the death. i am grading 
// based on the enemy class, does it have the functionality that 
// it needs to interact with the player 

enum itemType {
	weapon, consumable
};

class item {
private:
	itemType type;
	int damage;
	string itemName;
	int healing;
	vector<string> weaponNames = {"Excalibre", "Master Sword", "Stormbreaker", "Frostbite Dagger", "Radiant Saber", "Arcane Axe", "Wild Mace"};
	vector<string> consumNames = {"Health Potion", "Bottle of Water", "Bandaid"};

public:
	item(int randNumber) {
		switch(randNumber) {
			case 0:
			case 1:
			case 2:
				// coding stuff
				type = weapon;
				random_shuffle(weaponNames.begin(), weaponNames.end());
				itemName = weaponNames[0];
				damage = rand() % 5 + 2;
				healing = 0;
				break;
			case 3:
				// more coding stuff
				type = consumable;
				random_shuffle(consumNames.begin(), consumNames.end());
				itemName = consumNames[0];
				healing = rand() % 9 + 8;
				damage = -healing;
				break;
			default:
				cout << "Invalid Item Choice.";
				break;
		}
	}

	string GetItemName() {
		return itemName;
	}
	int GetItemDamage() {
		return damage;
	}
	itemType GetItemType() {
		return type;
	}
};

class enemy {
private:
	int health;
	int attack;
	item heldItem;

public:
	enemy(int givenHealth, int givenAttack) : heldItem(2) {
		health = givenHealth;
		attack = givenAttack;
	}

	int GetHealth() {
		return health;
	}
	int GetAttack() {
		return attack;
	}
	string GetHeldItemName() {
		return heldItem.GetItemName();
	}
	int GetHeldItemDamage() {
		return heldItem.GetItemDamage();
	}
	void SetHealth(int givenHealth) {
		health = givenHealth;
	}
	void SetAttack(int givenAttack) {
		attack = givenAttack;
	}


};

class player {
private: 
	int health = 30;
	int attack = 2;
	item heldItem;

public:
	player(int givenHealth, int givenAttack) : heldItem((rand() % 4)) {
		health = givenHealth;
		attack = givenAttack;
	}

	int GetHealth() {
		return health;
	} 
	int GetAttack() {
		return attack;
	}
	string GetHeldItemName() {
		return heldItem.GetItemName();
	}
	int GetHeldItemDamage() {
		return heldItem.GetItemDamage();
	}
	itemType GetHeldItemType() {
		return heldItem.GetItemType();
	}

	void SetHealth(int givenHealth) {
		health = givenHealth;
	}
	
};

int main() {
	srand(time(0));
	while(true) {
		string response;
		cout << "Would you like to go on an adventure?\n";
		cin >> response;

		if(response == "yes" || response == "y") {
			// adventure coding goes here
			player Bob(20, 2);
			enemy Monster(rand() % 10 + 11, rand() % 3 + 2);
			cout << "A monster jumps out and attacks you!\n";
			while(Bob.GetHealth() > 0 && Monster.GetHealth() > 0) {
				cout << "\nWhat would you like to do?\n";
				cout << "1. Attack with Item (" << Bob.GetHeldItemName() << ").\n";
				cout << "2. Attack without Item.\n";
					if (Bob.GetHeldItemType() == consumable) {
						cout << "3. Use consumable (" << Bob.GetHeldItemName() << ") on self.\n";
					}
				cin >> response;
				if (response == "1") {
					Monster.SetHealth(Monster.GetHealth() - (Bob.GetAttack() + Bob.GetHeldItemDamage()));
					cout << "\nYou attack the monster, doing " << Bob.GetAttack() + Bob.GetHeldItemDamage() << " damage.\n";
					cout << "The monster now has " << Monster.GetHealth() << " health left\n";
				}
				else if (response == "2") {
					Monster.SetHealth(Monster.GetHealth() - (Bob.GetAttack()));
					cout << "\nYou attack the monster, doing " << Bob.GetAttack() << " damage.\n";
					cout << "The monster now has " << Monster.GetHealth() << " health left\n";
				}
				else if (response == "3") {
					Bob.SetHealth(Bob.GetHealth() - Bob.GetHeldItemDamage());
					cout << "\nYou heal " << -Bob.GetHeldItemDamage() << " health.\n";
				}
				else {
					cout << "Invalid answer.\n";
				}
				if (Monster.GetHealth() > 0 && (response == "1" || response == "2" || response == "3")) {
					Bob.SetHealth(Bob.GetHealth() - (Monster.GetAttack() + Monster.GetHeldItemDamage()));
					cout << "The monster attacks with " << Monster.GetHeldItemName() << ", doing " << Monster.GetAttack() + Monster.GetHeldItemDamage() << " damage.\n";
				}
			}
			if(Bob.GetHealth() > 0 ) {
				cout << "\nYou have defeated the monster!\n";
			}
			else {
				cout << "\nThe monster has killed you.";
				break;
			}
		}
		else if(response == "no" || response == "n") {
			// ask to quit the game
		}
		else {
			cout << "Invalid response.\n";
		}
	}
}