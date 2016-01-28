//André Gardner 9/23/15 adgardner1@dmacc.edu
//This program lets you play baccarat against the computer. Although I don't know what changed
//within the last build and this one, it's giving me an unresolved external error but I can't
//find the cause.

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Card.h"
using namespace std;

//User interface function prototypes
void display (string);
void message(string,string,int, string);

//function prototypes
void declareWinner(short int,short int,short int);
short int checkWin(short int,short int,short int);
bool bankDraw(short int,short int);

const int LINE_LENGTH=30;
const char LINE_SYMBOL='*';

int main()
{
	//Fill a vector with card objects
	vector<Card> deck;
	for(short int x=0;x<4;x++)
	{
		string suit;
		switch(x)
		{
		case 1:
			suit="Hearts";
			break;
		case 2:
			suit="Diamonds";
			break;
		case 3:
			suit="Spades";
			break;
		case 4:
			suit="Clubs";
			break;
		}
		
		for(short int index=1;index<14;)
		{
			Card temp = Card(index,suit);
			deck.push_back(temp);
		}
		
		
	}
	
	//shuffle the deck of cards
	std::random_shuffle(deck.begin(), deck.end()); 
	
	//First two cards for each player get dealt and displayed
	Hand player(deck.at(52));
		message("Player's first draw", "Player", player.card1.getFace(), player.card1.getSuit());
	
	Hand bank(deck.at(51));
		message("Banker's first draw", "Banker", bank.card1.getFace(), bank.card1.getSuit());
	
	player.addCard(deck.at(50));
		message("Player's second draw", "Player", player.card2.getFace(), player.card2.getSuit());
	
	bank.addCard(deck.at(49));
		message("Banker's second draw", "Banker", bank.card2.getFace(), bank.card2.getSuit());
	
		
	short int winner=0; //win conditions will be 1=player, 2=bank, 3=tie;
	winner=checkWin(player.value(), bank.value(),1);

	if(winner==0)
	{
		player.addCard(deck.at(48));
		if(bankDraw(player.card3.value(),bank.value()))
		{
			bank.addCard(deck.at(47));
		}
		winner=checkWin(player.value(),bank.value(),2);
	}

	declareWinner(winner,player.value(),bank.value());

	return 0;
}

/********************
* Declares a winner *
********************/
void declareWinner(short int winner, short int player, short int bank)
{
	display("AND THE WINNER IS...");
	
	switch (winner)
	{
		case 1:
			cout<<"Player WINS with a hand of "<<player<<" over the Banker's hand of "<<bank<<endl;
			break;
		case 2:
			cout<<"Banker WINS with a hand of "<<bank<<" over the Players's hand of "<<player<<endl;
			break;
		case 3:
			cout<<"Player and Banker TIE with hands of "<<player<<endl;
			break;
	}
}
/*********************************************
* Checks to see if we have a winner or a tie *
*********************************************/
short int checkWin(short int player, short int bank, short int round)
{
	if(round==1)
	{
		if(player>7 && bank<=7)
		{
			return 1;
		}
		else if(bank>7 && player<=7)
		{
			return 2;
		}
		else if(bank>7 && player>7)
		{
			return 3;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if(player>bank)
		{
			return 1;
		}
		else if(bank>player)
		{
			return 2;
		}
		else
		{
			return 3;
		}
	}
}

/*********************************************************************************************
* Checks wether the banker should draw or not based on the punto blanco casino drawing rules *
*********************************************************************************************/
bool bankDraw(short int player,short int banker)
{
	//set rounding toward zero
	int originalRounding = _controlfp_s(0,0,0);
	_controlfp_s(_RC_CHOP,_MCW_RC,0);

	if(player==8)
	{
		player=-2;
	}
	if(player==9)
	{
		player=-1;
	}

	if((player/2)+3>=banker)
	{
		return true;
	}
	else
	{
		return false;
	}

	//reset original rounding
	_controlfp(originalRounding,_MCW_RC);
}		

/*******************************
* Sets the title of the screen *
*******************************/
void display(string title)
{
	string line;

	system("CLS");	
	
	//Set the title
	cout<<setw(20)<<right<<title<<endl;
	
	//display the seperator line belowe the screen title
	cout<<line.assign(LINE_LENGTH,LINE_SYMBOL)<<"\n"<<endl;
}

/********************************************
* Simple notice for user. Refreshes screen. *
********************************************/
void message(string title, string player,short int face, string suit)
{
	
	display(title);

	cout<<setw(30)<<left<<player<<" draws a "<<face<<" of "<<suit<<endl;
	cout<<"\n"<<endl;

	system("pause");
}