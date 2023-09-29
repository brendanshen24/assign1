/*
 * MyADT.h
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
 
 
#ifndef MyADT_H
#define MyADT_H

/*
 * You can add more #include statements.
 */
 
#include <string>
#include "Profile.h"


class MyADT {

private:

/* 
 * You can add more attributes to this class, 
 * but you cannot remove/change the attributes below.
 */
 
    constexpr static unsigned int MAX_ALPHA = 26;   // 26 letters in the alphabet 
    constexpr static unsigned int MAX_ELEMENTS = 5; // Small capacity so can test when data collection becomes full 
                                                    // Feel free to change this MAX_ELEMENTS value.
    Profile * elements[MAX_ALPHA];                  // MAX_ALPHA arrays of elements 
    unsigned int elementCount[MAX_ALPHA];           // Current element count in each of the MAX_ALPHA arrays of elements

    //added attribute totalElementCount to keep track of how many elements in total are in an instance of MyADT 
    unsigned int totalElementCount;

/* 
 * You can add private methods to this class.
 */
 
    // Utility methods

      
public:

/* 
 * You cannot remove/change the public methods below.
 * Bottom line: you cannot change the ***public interface*** of this class. 
 */
    // Default constructor
    MyADT();

    // Copy constructor - Covered in Lab 3
    MyADT(const MyADT& rhs);

    // Should overload the = operator.
    // Overloaded Operators - More on this topic in Lab 4.
    // operator=(const MyADT& rhs);
    
    // Destructor
    // Description: Destruct this object, releasing heap-allocated memory.
    ~MyADT();

    // Description: Returns the total element count currently stored in MyADT object.
    unsigned int getElementCount() const;

    // Description: Inserts an element.
    // Precondition: newElement must not already be in data collection.  
    // Postcondition: newElement inserted and the appropriate elementCount has been incremented.
    //                Returns "true" when the insertion is successfull,
    //                otherwise "false".
    bool insert(const Profile& newElement);

    // Description: Remove an element. 
    // Postcondition: toBeRemoved (if found) is removed and the appropriate elementCount is decremented.
    //                Returns "true" when the removal is successfull,
    //                otherwise "false".    
    bool remove(const Profile& toBeRemoved);
    
    // Description: Remove all elements.
    void removeAll();
   
    // Description: Search for target element.
    //              Returns a pointer to the element if found,
    //              otherwise, returns nullptr.
    Profile* search(const Profile& target);
    
    // Description: Prints all elements stored in MyADT by ascending order of search key.
    // ***For Testing Purposes - Conceptualy, it is not part of this class.***
    void print();
   

}; // end MyADT
#endif
