/*
 * MyADT.cpp
 *
 * Class Description: A linear data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - This is a value-oriented data collection: the elements are kept in
 *                     ascending sort order of search key.
 *                   - Its data structure is not expandable, i.e., resizable.
 *
 * Author: AL & Brendan Shen
 * Last modified on: Sept. 2023
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"  // Header file
#include "Profile.h"

using std::cout;
using std::endl;

// Default constructor.
MyADT::MyADT() {
    //sets each "letter" array in elements to a null pointer and also sets the element count for each letter array to zero
    for (unsigned int i = 0; i < MAX_ALPHA; i++) {
        elements[i] = nullptr;
        elementCount[i] = 0;
    }
    //sets total element count to 0
    totalElementCount = 0;
}  // end default constructor


// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
    //reuse default constructor's code

    //sets each "letter" array in elements to a null pointer and also sets the element count in each letter array to zero
    for (unsigned int i = 0; i < MAX_ALPHA; i++) {
        elements[i] = nullptr;
        elementCount[i] = 0;
    }
    //sets total element count to 0
    totalElementCount = 0;

    //now to copy over all the data from rhs
    for (unsigned int i = 0; i < MAX_ALPHA; i++) {//going through all 26 "letters positions" in elements
        if (rhs.elementCount[i] > 0){//if the letter array at index i has profiles in it
            elements[i] = new Profile[MAX_ELEMENTS]; //allocate on the heap an array of profile elements at elements[i] with size MAX_ELEMENTS
            for (unsigned int j = 0; j < rhs.elementCount[i]; j++) { // copy each profile in that letter array from rhs
                elements[i][j] = rhs.elements[i][j];
            }
            elementCount[i] = rhs.elementCount[i];//make the elementCount for that letter array at index i equal to the elementCount of the letter array at index i of rhs
        }
    }
    totalElementCount = rhs.totalElementCount; //copy over the totalElementCount

}  // end copy constructor


// Destructor
// Description: Destruct this object, releasing heap-allocated memory.
MyADT::~MyADT() {
/*     for (unsigned int i = 0; i < MAX_ALPHA; i++)
    {//iterates through all letter arrays in elements
        if(elementCount[i] > 0){//if there are elements in that letter array
            delete[] elements[i]; //free that letter array from the heap
        }

    } */
    removeAll();//the removeAll method already does essentially all the work that the destructor needs to do, clear all the heap memory that MyADT created

} // end destructor

// Description: Returns the total element count of elements currently stored in MyADT.
unsigned int MyADT::getElementCount() const {
    //okay, I technically could just do a for loop through elementCount, but whats the fun in that? having it this way make it O(1)
    return totalElementCount;//returns the totalElementCount value

}  // end getElementCount


// Description: Inserts an element.
// Precondition: newElement must not already be in data collection.
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull,
//                otherwise "false".

bool MyADT::insert(const Profile& newElement) {
    char firstLetter = newElement.getFirstLetter();
    int position = firstLetter - 'A'; //assuming uppercase letters
    int currentAmountOfElements = elementCount[position];


    if (currentAmountOfElements == MAX_ELEMENTS) {
        return false; //capacity already reached, insertion failed
    }

    //check if letter has not been encountered before
    if (currentAmountOfElements == 0) {
        //allocate memory on the heap for this letter's profiles
        elements[position] = new Profile[MAX_ELEMENTS];
    }

    //check if the new username already exists in the array
    for (int i = 0; i < currentAmountOfElements; i++) {
        if (newElement.getUserName() == elements[position][i].getUserName()) {
            return false; //username already exists, insertion failed
        }
    }

    //insert the new profile
    elements[position][currentAmountOfElements] = newElement;
    //increment totalElementCount and elementCount at index position by 1
    totalElementCount++;
    elementCount[position]++;
    return true; //insertion successful
}


// Description: Search for target element.
//              Returns a pointer to the element if found,
//              otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {//this is a linear search
    char firstLetter = target.getFirstLetter(); //use the getfirstLetter method in the Profile class to get the uppercase first letter of target's username
    int position = firstLetter - 'A'; //turn firstLetter into a postion index in elements
    int currentAmountOfElements = elementCount[position];//just a variable that simplifies things, its the amount of elements in elements[position]

    for (int i = 0; i < currentAmountOfElements; i++) {//iterate over the letter array of elements[position]
        if (target.getUserName() == elements[position][i].getUserName()) {//if the username matches
            return &elements[position][i];//return the address of the found profile
        }
    }
    return nullptr;//if it doesnt find it then it will return nullptr

}  // end of search

// Description: Remove an element.
// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.
//                Returns "true" when the removal is successfull,
//                otherwise "false".

bool MyADT::remove(const Profile& toBeRemoved) {
    //recycle code from search
    char firstLetter = toBeRemoved.getFirstLetter();
    int position = firstLetter - 'A';
    int currentAmountOfElements = elementCount[position];

    for (int i = 0; i < currentAmountOfElements; i++) {
        if (toBeRemoved.getUserName() == elements[position][i].getUserName()) {//if an element matching the username in toBeRemoved matches
            //if the element is found, and it is the only member of the array at that index, we must delete that array from heap memory
            if(elementCount[position] == 1){
                delete[] elements[position];
            }

            else{//if the element is found and also it is not the only member of its letter array
                //shift elements to fill the gap
                for (int j = i; j < currentAmountOfElements - 1; j++) {
                    elements[position][j] = elements[position][j + 1];
                }
            }
            //decrement totalElementCount and elementCount at index position by 1
            totalElementCount--;
            elementCount[position]--;
            //return true for success
            return true;
        }
    }
    return false;
}

// Description: Remove all elements.
void MyADT::removeAll() {
    for (unsigned int i = 0; i < MAX_ALPHA; i++){//iterate through all letter arrays in elements
        if(elementCount[i] > 0){//if that letter array has profile elements inside of it (ie. been allocatted on the heap)
            delete[] elements[i];//delete from the heap
            elementCount[i] = 0;//set elementCount at that letter to 0
        }
    }
    totalElementCount = 0;//zero out totalElementCount at the end

}  // end removeAll


void MyADT::print() {
    for (unsigned int i = 0; i < MAX_ALPHA; i++) {//iterate through all letter arrays in elements
        if (elementCount[i] > 0){//if that letter array has profile elements inside of it
            for (unsigned int j = 0; j < elementCount[i]; j++) {//go through all profile elements and print out the profile's username, name, email and birthday
                cout << elements[i][j].getUserName() << ", "
                << elements[i][j].getName() << ", "
                << elements[i][j].getEmail() << ", "
                << elements[i][j].getBirthday() << endl;
            }
        }
    }

} // end of print

//  End of implementation file
