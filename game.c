#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

struct card{
  string color;
  int number;
  string action;
};


void showq(queue<card> gq)
{
	queue<card> g = gq;
	while (!g.empty()) {
        card fe = g.front();
		cout << fe.color << " : " << fe.number << " : " << fe.action << endl;
		g.pop();
	}
}

void print(vector<card> v)
{
    for (card i: v) {
        std::cout << i.color << ' ' << i.number << ' ' << i.action << endl;
    }
}

int main()
{
	vector<card> deck;

    string color[4] = {"r","b","g","y"};
    string special_card[3] = {"skip","reverse","+2"};

    for(int i=0;i<4;i++){
        for(int j=1;j<=10;j++){
	        deck.push_back(card{color[i],j,""});
        }
        for(int j=0;j<3;j++){
	        deck.push_back(card{color[i],0,special_card[j]});
        }
    }
    for(int i=0;i<4;i++){
	        deck.push_back(card{"",0,"wild_card"});
    }
    for(int i=0;i<4;i++){
	        deck.push_back(card{"",0,"+4"});
    }


	cout << "DECK.SIZE() : " << deck.size() << endl;
    
	cout << "\nTHE VECTOR DECK IS : \n" << endl;
	print(deck);

    random_shuffle(deck.begin(), deck.end());

	cout << "\nTHE SHUFFLED VECTOR DECK IS : \n" << endl;
	print(deck);

    queue<card> sdeck;
    for(int i=0;i<deck.size();i++){
        sdeck.push(deck[i]);
    }

	cout << "\nTHE FINAL BOSS DECK IS : \n" << endl;
	showq(sdeck);

    vector<card> ai;
    vector<card> human;

    for(int i=0;i<7;i++){
        ai.push_back(sdeck.front());
        sdeck.pop();
    }

    for(int i=0;i<7;i++){
        human.push_back(sdeck.front());
        sdeck.pop();
    }
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    print(ai);
    cout<<endl;
    print(human);
    cout<<endl;
    showq(sdeck);
	return 0;
}
