//This class sets up the Card and Hand objects for a game of baccarat
#include <string>
using namespace std;

class Card
{
	private:
		short int cardValue;
		string suit;
		short int face;

	public:
		//constructors
		Card();
		Card(short int, string);

		//member functions
		short int value();
		short int getFace();
		string getSuit();
};

// DEFAULT CONSTRUCTOR, SETS TO NO VALUE
Card::Card()
{
	cardValue=0;
	suit='0';
	face=0;
}

//CONSTRUCTOR SETS CARD NUMBER & SUIT BY VALUE GIVEN
Card::Card(short int number, string cardSuit)
{
	face=number;
	suit=cardSuit;
	cardValue=(number>9) ?  0 : number;
}

//RETURNS POINT VALUE OF THE CARD
short int Card::value()
{
	return cardValue;
}

//RETURNS CARD FACE
short int Card::getFace()
{
	return face;
}

//RETURNS CARD SUIT
string Card::getSuit()
{
	return suit;
}


//SETS UP THE CLASS FOR HAND WHICH WILL HOLD 3 CARD OBJECTS AND TALLY THEIR TOTALS
class Hand
{
	private:
		
	public:
		//Card objects
		Card card1, card2, card3;
		
		//constructors
		Hand();
		Hand(Card);

		//member functions
		short int value();
		void addCard(Card);
};

//CREATES A HAND WITH 3 CARD SLOTS, ALL VOID
Hand::Hand()
{
	Card card1 = Card();
	Card card2 = Card();
	Card card3 = Card();
}

//CREATES A HAND WITH THE CARD GIVEN ASSIGNED TO 1ST CARD SLOT, REST VOID
Hand::Hand(Card card)
{
	Card card1=card;
}

//SETS WHICHEVER CARD SLOT IS OPEN TO CARD GIVEN
void Hand::addCard(Card card)
{
	if(card1.getFace()==0)
	{
		card1=card;
	}
	else if(card2.getFace()==0)
	{
		card2=card;
	}
	else if(card3.getFace()==0)
	{
		card3=card;
	}
}

//GETS VALUES FOR CARDS IN HAND AND DETERMINES THE TOTAL VALUE OF THE HAND
short int Hand::value()
{
	int handVal=0;
	
	handVal=card1.value()+card2.value()+card3.value();

	while(handVal>10)
	{
		handVal-=10;
	}
	
	return handVal;
}