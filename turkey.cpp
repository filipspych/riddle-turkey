#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

#define NUMBER_OF_DAYS 7
#define NUMBER_OF_BOXES 5
#define DISABLE_HEAVY_OUTPUT true
#define OUTPUT_STREAM out

using namespace std;

class CatchStrategy {
public:
	int boxes[NUMBER_OF_DAYS];

	CatchStrategy(int box[]) {
		for (int i = 0; i < NUMBER_OF_DAYS; i++)
			boxes[i] = box[i];
	}
};

class EscapeStrategy : public CatchStrategy {
public:
	using CatchStrategy::CatchStrategy;

	bool isLegal() {
		for (size_t i = 1; i < NUMBER_OF_DAYS; i++) {
			if (abs(boxes[i - 1] - boxes[i]) != 1) {
				return false;
			}
		}
		return true;
	}
};

vector<EscapeStrategy> escapeStrategies;
vector<CatchStrategy> catchStrategies;

void generateStrategies() {
	for (int i = 0; i < NUMBER_OF_BOXES; i++)
	for (int j = 0; j < NUMBER_OF_BOXES; j++)
	for (int k = 0; k < NUMBER_OF_BOXES; k++)
	for (int l = 0; l < NUMBER_OF_BOXES; l++)
	for (int m = 0; m < NUMBER_OF_BOXES; m++) 
	for (int n = 0; n < NUMBER_OF_BOXES; n++) 
	for (int o = 0;	o < NUMBER_OF_BOXES; o++)
	{
		int boxes[NUMBER_OF_DAYS] = { i, j, k, l, m, n, o};
		catchStrategies.push_back(CatchStrategy(boxes));
		EscapeStrategy es = EscapeStrategy(boxes);
		if (es.isLegal())
			escapeStrategies.push_back(es);
	}
}

///true if the catcher wins; false otherwise
bool confrontStrategies(CatchStrategy catchStrat, EscapeStrategy escapeStrat) {
	for (int i = 0; i < NUMBER_OF_DAYS; i++)
		if (catchStrat.boxes[i] == escapeStrat.boxes[i])
			return true;
	return false;
}

string strategyToString(CatchStrategy strategy) {
	string ret = "";
	for (int box : strategy.boxes) {
		char buffer[2] = {};
		_itoa_s(box, buffer, 10);
		ret += buffer;
		ret += ' ';
	}
	return ret + '\n';
}


ofstream out("output_turkey.txt");
void printStrategies(CatchStrategy cs, EscapeStrategy es, string winner) {
	static int counter = 0;
	counter++;
	if (counter % 100 != 0 || DISABLE_HEAVY_OUTPUT) return;
	
	cout << winner << " ";
	for (size_t i = 0; i < NUMBER_OF_DAYS; i++) {
		cout << cs.boxes[i] << " " << es.boxes[i] << '\t';
	} 
	cout << endl;
}

void cleanup() {
	out.close();
}

int catchStratCounter = 0;
void fight() {
	bool catcherAlwaysWins2 = true;
	for (auto cs : catchStrategies) {
		if(!DISABLE_HEAVY_OUTPUT) printf("---------CATCH STRATEGY %d---------\n", catchStratCounter);
		int catcherLostCount = 0;
		++catchStratCounter;
		for (auto es : escapeStrategies) {
			//if (catchStratCounter % 1000000 == 0) printf("catchStratCounter=%d\n", catchStratCounter);
			if (confrontStrategies(cs, es)) {
				//Catcher won
				printStrategies(cs, es, "C");
			}
			else {
				//Escaper won
				catcherLostCount++;
				printStrategies(cs, es, "E");
				if (catcherLostCount == 3) break;
			}
		}
		if (catcherLostCount <= 0) {
			printf("%d %d\n", catcherLostCount, catchStratCounter);
		}
		else {
			catcherAlwaysWins2 = false;
		}
	}
	if (catcherAlwaysWins2)
		printf("catcher_really_always_wins");
}

int main()
{
	generateStrategies();

	fight();

	cleanup();
}
