#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <string.h>
#include <random>
#include <chrono> 

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
            cout << i.color << " ";
        }
        if(i.number != 0){
            cout<<i.number << " ";
        }
        if(i.action != ""){
            cout<<i.action << " ";
        }
        cout << " | ";
    }
    cout<<endl;
}

void pr(card c){
    if(c.color != ""){
        cout << c.color << " ";
    }
    if(c.number != 0){
        cout << c.number << " ";
    }
    if(c.action != ""){
        cout << c.action << " ";
    }
    cout<<endl;
}

void displayGameState(vector<card> ai , vector<card> human){
    //cout<<"AI has cards : "<<ai.size()<<" left."<<endl;
    cout<<"A.I. hand ---"<<endl;
    print(ai);
    cout<<"HUMAN hand ---"<<endl;
    print(human);
}

int main()
{
    vector<card> deck;

    string color[4] = {"Red","Blue","Green","Yellow"};
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
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle (deck.begin(), deck.end(), default_random_engine(seed));

    queue<card> sdeck;
    for(int i=0;i<deck.size();i++){
        sdeck.push(deck[i]);
    }

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
    
    // initializing top card
    
    card topCard = sdeck.front();
    sdeck.pop();
    
    bool isAi = true;
    int input;
    vector<card> playedCards;
    bool skip = false;
    int draw = 0;
    string changeColor = "";
    
    while(true){
        if(human.size() == 0){
            cout << "HUMAN WINS" << endl;
            break;
        }
        else if(ai.size() == 0){
            cout << "A.I. WINS" << endl;
            break;
        }
        cout << "\n====================================================" <<endl;
        cout << "\nCurrent Game state ----" << endl;
        displayGameState(ai,human);
        cout << "\ntopCard --" << endl;
        pr(topCard);
        
        if(sdeck.size() == 0){
            shuffle (playedCards.begin(), playedCards.end(), default_random_engine(seed));
            for(;playedCards.size()!=0;){
                sdeck.push(playedCards.front());
                playedCards.erase(playedCards.begin());
            }
        }

        //A.I.

        if(isAi){
        
            if(skip){
                cout << "A.I. SKIPPED" << endl;
                skip = false;
                for(;draw>0;draw--){
                        ai.push_back(sdeck.front());
                        sdeck.pop();
                }
                isAi = false;
                continue;
            }
            else{
                cout << "\nnot skipping" << endl;
            }
            
            cout << "\n ---- A.I.'s move ---- " << endl;
            string color = topCard.color;
            int number = topCard.number;
            string action = topCard.action;

            card selectedCard;
            int selectedCardNumber = 0;
            
            
            if(topCard.number == -1){
                for(int i=0;i<ai.size();i++){
                        if((ai[i].color.compare(color) == 0) && (color != "")){
                                cout << "color found" <<endl;
                            selectedCard = ai[i];
                            selectedCardNumber = i+1;
                            break;
                        }
                        else if ((ai[i].action.compare(action) == 0) && (action != "")){
                                cout << "action found\n" <<endl;
                            selectedCard = ai[i];
                            selectedCardNumber = i+1;
                            break;
                        }
                }
            }
            else{
                    for(int i=0;i<ai.size();i++){
                        if((ai[i].color.compare(color) == 0) && (color != "")){
                                cout << "color found" <<endl;
                            selectedCard = ai[i];
                            selectedCardNumber = i+1;
                            break;
                        }
                        else if (ai[i].number == number && number != 0){
                                cout << "number found" <<endl;
                            selectedCard = ai[i];
                            selectedCardNumber = i+1;
                            break;
                        }
                        else if ((ai[i].action.compare(action) == 0) && (action != "")){
                                cout << "action found\n" <<endl;
                            selectedCard = ai[i];
                            selectedCardNumber = i+1;
                            break;
                        }
                    }
            }
            
            if(selectedCardNumber == 0){
                for(int i=0;i<ai.size();i++){
                        if(ai[i].action.compare("")!=0 &&ai[i].color.compare("") == 0 && ai[i].number == 0){
                                selectedCard = ai[i];
                                selectedCardNumber = i+1;
                                break;
                        }
                }
                if(selectedCardNumber == 0){
                        cout << "A.I. drawing card" << endl;
                        ai.push_back(sdeck.front());
                        sdeck.pop();
                        isAi = false;
                        continue;
                }
            }
            
            
            cout << "Card Seleted : ";
            pr(selectedCard);
            cout << "Card Number is : " << selectedCardNumber <<endl;
            playedCards.push_back(topCard);
            ai.erase(ai.begin()+(selectedCardNumber-1));
            
            if(selectedCard.color.compare("") == 0 && selectedCard.number == 0 && selectedCard.action.compare("") != 0){
		        if(selectedCard.action.compare("+4") == 0){
		                changeColor = ai[0].color;
		                skip = true;
		                draw = 4;
		                selectedCard.color = changeColor;
		                selectedCard.number = -1;
		        }
		        else{
		                changeColor = ai[0].color;
		                skip = false;
		                draw =0;
		                selectedCard.color = changeColor;
		                selectedCard.number = -1;
		        }
		     }
            else if(selectedCard.action.compare("") != 0){
                        if(selectedCard.action.compare("skip") == 0){
		                skip = true;
		                draw = 0;
		                changeColor = "";
		        }
		        else if(selectedCard.action.compare("reverse") == 0){
		                skip = true;
		                draw = 0;
		                changeColor = "";
		        }
		        else{
		                changeColor = "";
		                skip = true;
		                draw = 2;
		        }
            }
            topCard = selectedCard;
            isAi = false;
        }

        //HUMAN

        else{
            
            if(skip){
                cout << "HUMAN SKIPPED" << endl;
                skip = false;
                for(;draw>0;draw--){
                        human.push_back(sdeck.front());
                        sdeck.pop();
                }
                isAi = true;
                continue;
            }
            
            cout << "\nHuman Enter the card number 1-" << human.size() << endl;
            cout << "Enter 0 for draw card" << endl;
            cin >> input;
            if(input == 0){
                cout << "drawing card" << endl;
                human.push_back(sdeck.front());
                sdeck.pop();
                isAi = true;
                continue;
            }
            else if(input < 0 || input > human.size()){
                cout << "--- Invalid Move PLAY VALID MOVE again ---" << endl;
                continue;
            }
            else{
            	string color = topCard.color;
            	int number = topCard.number;
            	string action = topCard.action;
            	bool valid = false;
            	if
            	(
                    	(
                            	(human[input-1].color.compare(color) == 0 || human[input-1].number == number)
                            	 && 
                            	(human[input-1].color.compare(color) == 0 || human[input-1].action.compare(action) == 0)
                    	)
                    	 || 
            	        (human[input-1].color.compare("") == 0 && human[input-1].number == 0 && human[input-1].action.compare("") != 0)
            	)
            	{
            	        valid = true;
            	}
            	if(valid){
            	     
		     cout << "Card Seleted" << endl;
		     pr(human[input-1]);
		     playedCards.push_back(topCard);
		     topCard = human[input-1];
		     
		     if(human[input-1].color.compare("") == 0 && human[input-1].number == 0 && human[input-1].action.compare("") != 0){
		        if(human[input-1].action.compare("+4") == 0){
		                cout << "enter the color : \nRed\nBlue\nGreen\nYellow" <<endl;
		                cin >> changeColor;
		                skip = true;
		                draw = 4;
		                topCard.color = changeColor;
		                topCard.number = -1;
		        }
		        else{
		                cout << "enter the color : \nRed\nBlue\nGreen\nYellow" <<endl;
		                cin >> changeColor;
		                skip = false;
		                draw =0;
		                topCard.color = changeColor;
		                topCard.number = -1;
		        }
		     }
		     
		     else if(human[input-1].action.compare("") != 0){
		        cout << "executing ifelseif for action card" << endl;
		        if(human[input-1].action.compare("skip") == 0){
		                changeColor = "";
		                skip = true;
		                draw = 0;
		        }
		        else if(human[input-1].action.compare("reverse") == 0){
		                changeColor = "";
		                skip = true;
		                draw = 0;
		        }
		        else{
		                changeColor = "";
		                skip = true;
		                draw = 2;
		        }
		     }
		     
		     human.erase(human.begin()+(input-1));
		     
		     isAi = true;
            	}
                else{
                     cout << "Invalid card selected play a valid card" << endl;
                }
            }
        }
    }

	return 0;
}
