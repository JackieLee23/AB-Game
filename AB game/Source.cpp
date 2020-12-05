#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <string>
#include <ctime>


using namespace std;
pair<int, int> eval(string& s, string& t);
int main() {
	vector<int> nums = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	string ans;
	srand(time(NULL));
	string guess;
	string compguess;

	//generatenums list
	vector<string> candidates;
	vector<bool> possible;
	int remaining = candidates.size();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 10; k++) {
				for (int l = 0; l < 10; l++) {
					if (i != j && i != k && i != l && j != k && j != l && k != l) {
						string candidate;
						candidate = to_string(i) + to_string(j) + to_string(k) + to_string(l);
						candidates.push_back(candidate);
						possible.push_back(1);
					}
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		int randnum = rand() % (10 - i);
		ans += '0' + nums[randnum];
		nums.erase(nums.begin() + randnum);
	}

	while (1) {
		while (1) {
			cout << "Make a guess: ";
			cin >> guess;
			if (guess.size() != 4) {
				cout << "4 digits please." << "\n";
				continue;
			}
			set<int> s;
			bool invalid = 0;
			for (int i = 0; i < 4; i++) {
				if (guess[i] - '0' < 0 || guess[i] - '0' > 9) {
					cout << "Only numbers please" << "\n";
					invalid = 1;
					break;
				}
				s.insert(guess[i]);
			}
			if (s.size() != 4 && !invalid) {
				cout << "No repeats please" << "\n";
				continue;
			}
			if (invalid) continue;
			else break;
		}
		
		pair<int, int> p = eval(ans, guess);
		if (p.first == 4) {
			cout << "you win";
			break;
		}
		else cout << p.first << "a" << " " << p.second << "b" << "\n";
		

		//computer guess
		for (int i = 0; i < candidates.size(); i++) {
			if (possible[i]) {
				compguess = candidates[i];
				break;
			}
		}

		cout << compguess <<"\n";
		string astring, bstring;
		while (1) {
			cin >> astring; cin >> bstring;
			if (astring.size() != 2 || astring[1] != 'a' || astring[0] - '0' < 0 || astring[0] - '0' > 4) {
				cout << "Reenter please" << "\n"; 
				continue;
			}
			if (bstring.size() != 2 || bstring[1] != 'b' || bstring[0] - '0' < 0 || bstring[0] - '0' > 4) {
				cout << "Reenter please" << "\n";
				continue;
			}
			break;
		}

		if (astring[0] == '4') {
			cout << "Computer wins";
			break;
		}

		int a = astring[0] - '0';
		int b = bstring[0] - '0';

		for (int i = 0; i < candidates.size(); i++) {
			p = eval(compguess, candidates[i]);
			if (a != p.first || b != p.second) {
				possible[i] = 0;
				remaining--;
			}
		}
		
		if (remaining == 0) {
			cout << "You screwed up somewhere, no answer possible";
			break;
		}
	}

	return 0;
}

pair<int, int> eval(string& s, string& t) {
	int a = 0, b = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (s[i] == t[j]) {
				if (i == j) a++;
				else b++;
			}
		}
	}

	return { a, b };
}
