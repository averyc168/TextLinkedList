/*
 * Avery Chan
 *
 * Program: achanDS4.cpp
 * 
 * Purpose: This programs reads in files that the user inputs word by word. The program then
 * lowers and removes the punctuation from the word and inserts them into a linked list, in 
 * alphabetical order. The linked lists consists of BRIDGES SLelement. The SLelement includes 
 * the word that it read in, the number of times the word appears in the text, and the "next" 
 * pointer that points to either the SLelement or a null pointer. The linked list is in 
 * alphabetical order and is labeled with the word and the number of times it appears in the 
 * text.
 *
 * Input:   The user will input a filename that contains the text that will be read. They
 * will also input two integers, high and low, as a range for the frequency of words repeated
 * in the text. 
 *
 * Output:  The stats of all the words in the alphabetical order and frequency order. When it 
 * prints out the stats for alphabetical order, all the words that are only mentioned once will
 * be printed below the stats table and under "Words with frequency = 1". There will also be a 
 * link to the BRIDGES visualization of the linked list with each node labeled with its word and
 * frequency. 
 *
 * Note:    N/A
 */

#include "Bridges.h"
#include "SLelement.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace bridges;
using namespace std;

struct myNode {
    string word;                          // the word that is read from the text file
    int count;                            // the amount of times a word is repeated in the text file
};

class MeBlanc {
    SLelement <myNode> *head;             // the start of the linked list of SLelement<myNode>
    string cleanup(string);               // gets rid of the punctuation on the word
    string lowercase(string);             // lowercases all the letters in the word
    void insertToLL(myNode);              // inserts the SLelement node into the front, back, or middle of the list
public:
    MeBlanc();                            // DEFAULT CTOR of the MeBlanc class
    bool readText(string filename);       // reads in words one at a time from the user inputted file
    void displayStats();                  // displays the stats alphabetically
    void displayStats(int low, int high); // displays the stats by frequency based off the range the user inputted
    void showLinkedList(Bridges);         // visualizes the linked list in BRIDGES
};

//===========
// DEFAULT CTOR
// The method sets the start of the linked list ("head") to a nullptr, so it is empty.
// Parameter: N/A
// Return: it accomplishes the start of an empty linked list as a data member of the MeBlanc class
MeBlanc :: MeBlanc() {
    head = nullptr;     
}

//---------------------------------------------------------------------------------
// cleanup method
// The method goes through every character in the word, checks if there's a punctuation like period, comma
// explanation mark, and question mark.
// Parameter: string s: the word that is read from the file
// Return: string s without any punctuation
string MeBlanc :: cleanup(string s) {
    int length = s.length();  // finds the length of the word so the for loop knows when to stop
    for (int i = 0; i < length; i++) {
        if (s[i] == '.' || s[i] == ',' || s[i] == '!' || s[i] == '?')
            s.erase(s.begin() + i);
    }
    return s;
}

//---------------------------------------------------------------------------------
// lowercase method
// The method goes through every character in the word and lowercases it
// Parameter: string s: the word that is read from the file after cleaned up
// Return: string s that is all lowercased
string MeBlanc :: lowercase(string s) {
    int length = s.length();   // finds the length of the word so the for loop knows when to stop
    for (int i = 0; i < length; i++)
        s[i] = tolower(s[i]);
    return s;
}

//---------------------------------------------------------------------------------
// inserToLL method
// The method traverses through the linked list to see if the word is already in the linked list.
// If it is, then it increases the count data member in the SLelement node by 1. If not, it creates
// a new SLelement of myNode, that contains the word, count, and the "next" pointer. Then it is either
// inserted into the linked list in the front, back, or middle alphabetically.
// Parameter: myNode n, that contains the word and the count.
// Return: There is no return type, but the linked list should consist of SLelements<myNode> of all the
// words and sorted alphabetically with the number of times it is repeated. 
void MeBlanc :: insertToLL(myNode n) {
    SLelement<myNode> *cur;     // SLelement pointer that points to current node when traversing linked list
    SLelement<myNode> *prev;    // SLelement pointer that points to previous node when traversing linked list
    SLelement<myNode> *newitem; // SLelement pointer that creates new node to be inserted into linked list
    bool found;                 // boolean value that will identify spot to insert and break while loop
    found = false;
    cur = head;
    prev = nullptr;
    
    while (cur && !found) {
        if (n.word == cur->getValue().word) {
            cur->getValue().count += 1;
            // str is a string concatenation of all the node's word and number of times the word is repeated in text
            string str = cur->getValue().word + ", " + to_string(cur->getValue().count);
            cur->setLabel(str);
            break;     // breaks loop once it updates the count
        }
        else if (n.word < cur->getValue().word)
            found = true;       // breaks the loop to create new SLelement
        else {        // continue to traverse linked list
            prev = cur;
            cur = cur->getNext();
        }
    } //endwhile
    
    if (found || cur == nullptr) {
        newitem = new SLelement<myNode> (n);
        // str is a string concatenation of all the node's word and number of times the word is repeated in text
        string str = newitem->getValue().word + ", " + to_string(newitem->getValue().count);
        newitem->setLabel(str);

        // inserting to middle and end of linked list
        if (prev) {
            newitem->setNext(cur);
            prev->setNext(newitem);
        }
        // inserting to front of linked list
        else {
            newitem->setNext(cur);
            head = newitem;
        }
    } // if found || !cur    
}

//---------------------------------------------------------------------------------
// readText method
// The method takes the filename and reads in the words of the file one at a time. Those words are
// then sent to be cleaned and lowered, and then sent to either update or insert into the linked list
// Parameter: The user inputted filename
// Return: it returns a bool value if a filename is found or not. 
bool MeBlanc :: readText(string filename) {
    string word;                // the word from the file
    ifstream infile;            // name to open and close the file
    infile.open(filename);

    if (infile) {
        infile >> word;
        while (word != "DONE") {
            word = cleanup(word);
            word = lowercase(word);
            myNode node;       // creating a new node of the word and the number of times it is in text
            node.word = word;
            node.count = 1;            
            insertToLL(node);
            infile >> word;
        } // endwhile
        infile.close();
        return true;
    } // endif

    else {
        cerr << endl << "ERROR: No input file found." << endl;
        return false;
     } //else
}

//---------------------------------------------------------------------------------
// displayStats method (alphabetically)
// displays the stats of the words and their frequencies alphabetically and formats a nice
// readable table
// Parameter: N/A
// Return: no return value but there should be a nicely formatted table with words that are
// mentioned more than once are in a table alphabetically while the others are on the bottom
// alphabetically
void MeBlanc :: displayStats() {
    SLelement<myNode> *cur;    // a current pointer that traverses through the linked list
    cur = head;
    cout << endl << "Words in alphabetical order: " << endl;
    cout << "Word" << setw(16) << "Frequency" << endl;
    cout << "====================" << endl;
    while (cur) {
        if (cur->getValue().count > 1)
            cout << cur->getValue().word << setw(16 - cur->getValue().word.length() + 4) << cur->getValue().count << endl;
        cur = cur->getNext();
        }
    cout << endl << "Words with frequency = 1" << endl;
    cout << "====================" << endl;
    cur = head;
    while (cur) {
        if (cur->getValue().count == 1)
            cout << cur->getValue().word << " ";
        cur = cur->getNext();
    }
    cout << endl << endl << endl;
}


//---------------------------------------------------------------------------------
// displayStats method (frequency)
// The method shows all the words in a nice formatted table that are within the range of
// frequencies that the user inputted
// Parameter: two ints (high and low) that set the range of frequencies
// Return: no return value, but the range of frequencies decides which words will be outputted
void MeBlanc :: displayStats(int low, int high) {
    SLelement<myNode> *cur;        // a current pointer that traverses through the linked list 
    cout << endl << "Words in frequency order: " << endl;
    cout << "Word" << setw(16) << "Frequency" << endl;
    cout << "====================" << endl; 
    while (high >= low) {
        cur = head;
        while (cur) {
            if (cur->getValue().count == high)
                cout << cur->getValue().word << setw(16 - cur->getValue().word.length() + 4) << cur->getValue().count << endl;
            cur = cur->getNext(); 
        }
        high--;
    }
    cout << endl;
}

//---------------------------------------------------------------------------------
// showLinkedList method
// The method displays the BRIDGES visualization of the linked list 
// Parameters: BRIDGES object for visual
// Return: no return value, but there should be a link outputted that shows the BRIDGES visual
void MeBlanc :: showLinkedList(Bridges bridges) {
    bridges.setDataStructure(head);
    bridges.visualize();
}

//=================================================================================

int main () {
   Bridges bridges (4, "ac168", "451369086567"); // your credentials here
   MeBlanc myList;   
   string fileName;
   int low, high;

   cout << "Enter file name: ";
   cin >> fileName;


   if (myList.readText (fileName)) {
      myList.displayStats();
      cout << "Enter low frequency : ";
      cin >> low;
      cout << "Enter high frequency: ";
      cin >> high;
      myList.displayStats(low, high);
      myList.showLinkedList (bridges);
   } else
      cout << "Error - problem reading file." << endl;

   return 0;
}