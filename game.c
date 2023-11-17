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
        if(i.color != ""){
            cout << i.color;
        }
        if(i.number != 0){
            cout<<i.number;
        }
        if(i.action != ""){
            cout<<i.action;
        }
        cout << " | ";
    }
    cout<<endl;
}

void pr(card c){
    if(c.color != ""){
        cout << c.color;
    }
    if(c.number != 0){
        cout << c.number;
    }
    if(c.action != ""){
        cout << c.action;
    }
    cout<<endl;
}

void displayGameState(vector<card> ai , vector<card> human){
    cout<<"AI hand ---"<<endl;
    print(ai);
    cout<<"HUMAN hand ---"<<endl;
    print(human);
}

int main()
{
	vector<card> deck;

    string color[4] = {"R","B","G","Y"};
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
    
	// cout << "\nTHE VECTOR DECK IS : \n" << endl;
	// print(deck);

    random_shuffle(deck.begin(), deck.end());

	// cout << "\nTHE SHUFFLED VECTOR DECK IS : \n" << endl;
	// print(deck);

    queue<card> sdeck;
    for(int i=0;i<deck.size();i++){
        sdeck.push(deck[i]);
    }

	// cout << "\nTHE FINAL BOSS DECK IS : \n" << endl;
	// showq(sdeck);

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
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << endl;
    // print(ai);
    // cout << endl;
    // print(human);
    // cout << endl;
    // showq(sdeck);

    card topCard = sdeck.front();
    sdeck.pop();
    bool isAi = true;
    int input;
    vector<card> playedCards;
    while(true){
        if(human.size() == 0){
            cout << "HUMAN WINS" << endl;
            break;
        }
        else if(ai.size() == 0){
            cout << "A.I. WINS" << endl;
            break;
        }
        cout << "\nCurrent Game state ----" << endl;
        displayGameState(ai,human);
        cout << "topCard --" << endl;
        pr(topCard);
        if(sdeck.size() == 0){
            random_shuffle(playedCards.begin(), playedCards.end());
            for(int i=0;i<playedCards.size();i++){
                sdeck.push(playedCards[i]);
            }
            playedCards.clear();
        }
        if(isAi){
            cout << "A.I. Enter the card number 1-" << ai.size() << endl;
            cin >> input;
            cout << "Card Seleted" << endl ;
            pr(ai[input-1]);
            ai.erase(ai.begin()+(input-1));
            isAi = false;
        }
        else{
            cout << "Human Enter the card number 1-" << human.size() << endl;
            cout << "Enter 0 for draw card" << endl;
            cin >> input;
            if(input == 0){
                cout << "drawing card" << endl;
                human.push_back(sdeck.front());
                sdeck.pop();
                isAi = true;
                continue;
            }
            else if(input < 0 && input > human.size()){
                cout << "--- Invalid Move PLAY VALID MOVE again ---" << endl;
                continue;
            }
            else{
                cout << "Card Seleted" << endl ;
                pr(human[input-1]);

                playedCards.push_back(topCard);
                topCard = human[input-1];
                human.erase(human.begin()+(input-1));
                isAi = true;
                
                break;
            }
        }
    }

	return 0;
}
