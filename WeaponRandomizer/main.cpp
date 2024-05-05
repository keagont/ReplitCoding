#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class enemy {
private:
	int health;
	int attack;
	int gold;

public:
	int GetHealth() {
		return health;
	}
	int GetAttack() {
		return attack;
	}
	int GetGold() {
		return gold;
	}

void SetHealth(int givenHealth) {
	health = givenHealth;
}
void SetAttack(int givenAttack) {
	attack = givenAttack;
}
void SetGold(int givenGold) {
	gold = givenGold;
}

};

enum itemType {
	weapon, tool, consumable
};

enum elementalType {
	basic, fire, ice, candy, slime
};

class item {
public:
	itemType type;
	int damage;
	string name;
	elementalType element;
	int remainingUses;
	int healingAmount;

	item(string givenName, itemType givenType) {
		name = givenName;
		type = givenType;

		if(type == weapon) {
			damage = rand() % 5 + 3;
			element = (elementalType)(rand() % 4);
			remainingUses = 9999;
			healingAmount = 0;
		}
		else if(type == tool) {
			damage = 1;
			element = basic;
			remainingUses = rand() % 5 + 1;
		}
		else if(type == consumable) {
			healingAmount = rand() % 5 + 1;
			damage = -healingAmount;
			element = basic;
			remainingUses = 1;
		}
	}

	void Inspect() {
		cout << name << " does " << damage << " damage, " << "it is a(n) " << elementToString(element) << " elemental,\n";
		cout << "it can be used " << remainingUses << " more times, heals " << healingAmount << " health,\n";
		cout << "and is a " << typeToString(type) << ".\n\n";
	}

	string typeToString(itemType type) {
		switch(type) {
			case weapon:
				return "weapon";
				break;
			case tool:
				return "tool";
				break;
			case consumable:
				return "consumable";
				break;
			default: 
				return "unknown";
				break;
			
		}
	}

	string elementToString(elementalType element) {
		switch(element) {
			case basic:
				return "basic";
				break;
			case fire:
				return "fire";
				break;
			case ice:
				return "ice";
				break;
			case candy:
				return "candy";
				break;
			case slime:
				return "slime";
				break;
			default: 
				return "unknown";
				break;

		}
	}
};



int main() {
	srand(time(0));
  	cout << "Hello World!\n";
	enemy Enemy1;
	Enemy1.SetHealth(rand() % 20 + 1);
	Enemy1.SetAttack(rand() % 5 + 1);
	Enemy1.SetGold(rand() % 3 + 2);
	cout << "I am Enemy1, I have " << Enemy1.GetHealth() << " health, " << Enemy1.GetAttack() << " attack power, and " << Enemy1.GetGold() << " gold.\n"; 
	item sting("Sting", weapon);
	sting.Inspect();
}