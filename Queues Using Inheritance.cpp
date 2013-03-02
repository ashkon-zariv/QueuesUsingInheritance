#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Card
{
public:
   enum State {deleted, active};
   enum Suit {clubs, diamonds, hearts, spades};

private:
   char value;
   Suit suit;
   State state;
   bool errorFlag;

public:
   Card(char value = 'A', Suit suit = spades);
   string toString();
   bool set(char value = 'A', Suit suit = spades);
   bool SetState(State state);
   State GetState() {return this->state;}
   Suit GetSuit() {return suit;}
   char GetValue() {return value;}
   bool GetErrorFlag() {return this->errorFlag;}
   bool equals(Card card);
};

class Node
{
public:
   Node *next;
   Node();
   virtual ~Node();
   virtual void toString();   
};

class Queue
{
private:
   Node *head, *tail;
public:
   Queue();
   virtual ~Queue();
   void add(Node *newNode);
   Node *remove();
   virtual void toString();

   class QueueEmptyException { };
};

class CardNode : public Node
{
private:
   Card data;
public:
   CardNode(Card cNode);
   void toString();
   Card getData() {return this->data;}
};

class CardQueue : public Queue
{
public:
   ~CardQueue();
   void add(Card cardIn);
   Card remove();
};

int main()
{
   CardQueue crdq;
   Card card1('A', Card::hearts), card2('2', Card::hearts),
      card3('3', Card::hearts) , card4('4', Card::hearts),
      rCard;

   crdq.add(card1);
   crdq.add(card2);
   crdq.add(card3);
   crdq.add(card4);

   cout << "Card Queue toString() method" << endl;
   crdq.toString();
   cout << endl << endl << "Card Queue removing and printing 5 elements"
      << endl;
   
   for (int k = 0; k < 5; k++)
   {
      try
      {
         cout << crdq.remove().toString() << ", ";
      }
      catch(Queue::QueueEmptyException)
      {
         cout << "(empty stack) ";
      }
   }
   cout << endl;
   return 0;
}

Node::Node()
{
   next = NULL;
}

Node::~Node()
{
}

void Node::toString()
{
   cout << "(generic node) ";
}

Queue::Queue()
{
   head = new Node();
   tail = head;
}

void Queue::add(Node *newNode)
{
   if (newNode == NULL)
      return;
   tail->next = newNode;
   tail = tail->next;
}

Node *Queue::remove()
{
   Node *temp = head->next;

   if(temp != NULL)
      head->next = temp->next;
   if(tail == head)
      tail = NULL;
   return temp;
}

Queue::~Queue()
{
   delete head;
}

void Queue::toString()
{
   Node *p;
   for(p = head; p = p->next;)
      p->toString();
}  

CardNode::CardNode(Card cNode)
{
   data.set(cNode.GetValue(), cNode.GetSuit());
}

void CardNode::toString()
{
   cout << data.toString() << ", ";
}

void CardQueue::add(Card cardIn)
{
   CardNode *cn = new CardNode(cardIn);
   Queue::add(cn);
}

Card CardQueue::remove()
{
   Card cardOut;
   CardNode *cn = (CardNode *)Queue::remove();
   if (cn == NULL)
      throw Queue::QueueEmptyException();
   
   cardOut = cn->getData();
   delete cn;
   return cardOut;
}

CardQueue::~CardQueue()
{
   Node *dl;
   while (dl = Queue::remove())
      delete dl;
}

Card::Card(char value, Suit suit)
{
   set(value, suit);
   SetState(active);
}

bool Card::set(char value, Suit suit)
{
   char UpCase;
   UpCase = toupper((int)value);
   
   if(UpCase == 'A' || UpCase == 'K' || UpCase == 'Q' || UpCase == 'J' ||
      UpCase == 'X' || UpCase == 'T' || (UpCase >= '2' && UpCase <= '9'))
   {
      state = active;
      this->suit = suit;
      this->value = UpCase;
      errorFlag = false;
      return true;
   }
   else
   {
      errorFlag = true;
      return false;
   }
}

bool Card::SetState(State state)
{
   if(state == active)
   {
      this->state = state;
      return true;
   }
   else if (state == deleted)
   {
      this->state = state;
      return false;
   }
}

bool Card::equals(Card card)
{
   if(this->value == card.value && 
      this->suit == card.suit && 
      this->errorFlag == card.errorFlag
      && this->state == card.state)
      return true;
   else
      return false;
}

string Card::toString()
{
   string deletedout = "[deleted]";
   string invalidout = "[invalid]";
   string validout;
   
   if(state == deleted)
   {
      return deletedout;
   }
   else if(value == 'X')
   {
      if (suit == spades)
         validout += "Joker # 1";
      else if (suit == diamonds)
         validout += "Joker # 2";
      else if (suit == hearts)
         validout += "Joker # 3";
      else if (suit == clubs)
         validout += "Joker # 4";
      return validout;
   }
   else if(value == 'A' || value == 'K' || value == 'Q' || value == 'J' ||
      value == 'T' || (value >= '2' && value <= '9'))
   {
      char validVal[2];
      validVal[0] = value;
      validVal[1] = '\0';
      validout = string(validVal);

      if (suit == spades)
         validout += " of Spades";
      else if (suit == hearts)
         validout += " of Hearts";
      else if (suit == diamonds)
         validout += " of Diamonds";
      else if (suit == clubs)
         validout += " of Clubs";
      return validout;
   }
   else if(errorFlag == true)
   {
      return invalidout;
   }
}