/*
 * MyADTTestDriver.cpp - Assignment 1
 * 
 * Class Description: A test driver for the MyADT class and all of its methods.
 *
 * Author: Brendan Shen
 * Last modified on: Sept. 2023
 */


#include <iostream>
#include "MyADT.h"
#include "Profile.h"

using std::cout;
using std::endl;

int main() {
    //initialize variable that counts how many of the tests were passed
    unsigned int testsPassed = 0;
    unsigned int numberOfTests = 9;
    
    //create a heap allocated instance of MyADT using the default constructor
    MyADT* myADT1 = new MyADT();
    if(myADT1 != nullptr){
        cout << "Default constructor initialization for myADT1 test passed!" << endl;
        cout << "myADT1 is located at address: " << &myADT1 << "\n" << endl;
        testsPassed++;
    }
    else{
        cout << "Default constructor initialization for myADT1 failed!\n" << endl;
    }

    //maximum capacity from MyADT
    constexpr unsigned int MAX_CAPACITY = 5;

    //create some Profile instances for testing
    Profile profile1("user1", "Brendan Shen", "bqs1@sfu.ca", "February 2 2004");
    Profile profile2("user2", "Keyaan Vegdani", "kvd1@gmail.com", "May 8 2004");
    Profile profile3("user3", "Tiger Tong", "tgt3@langara.edu", "September 21 2004");

    //insert profiles into MyADT
    myADT1->insert(profile1);
    myADT1->insert(profile2);
    myADT1->insert(profile3);

    //test insertion of a duplicate profile
    Profile duplicateProfile("user2", "Duplicate User", "duplicate@sfu.ca", "April 7 2001");
    bool duplicateInserted = myADT1->insert(duplicateProfile); // Should return false for duplicate insertion
    if (duplicateInserted == false) {
        cout << "Duplicate profile insertion test passed!\n" << endl;
        testsPassed++;
    }
    else {
        cout << "Duplicate profile insertion test failed!\n" << endl;
    }

    //test insertion beyond the maximum capacity
    Profile overflowProfile("user4", "Overflow User", "overflow@yahoo.com", "June 4 2006");
    for (int i = 0; i < MAX_CAPACITY; i++) {
        myADT1->insert(overflowProfile);
    }
    bool capacityExceeded = myADT1->insert(overflowProfile); // Should return false for exceeding capacity
    if (capacityExceeded == false) {
        cout << "Insertion past maximum capacity test passed!\n" << endl;
        testsPassed++;
    }
    else {
        cout << "Insertion past maximum capacity test failed!\n" << endl;
    }

    //get the total element count
    unsigned int currentElementCount = myADT1->getElementCount(); // Should be 4
    if (currentElementCount == 4) {
        cout << "Total element count method test passed!\n" << endl;
        testsPassed++;
    }
    else {
        cout << "Total element count method test failed!\n" << endl;
    }

    //search for a profile
    Profile searchProfile("user2");
    Profile* foundProfile = myADT1->search(searchProfile);
    if (foundProfile != nullptr) {
        if (foundProfile->getUserName() == "user2") {
            cout << "Profile search test passed!\n" << endl;
        }
        else {
            cout << "Profile search test failed! foundProfile's username is not user2!\n" << endl;
        }
    }
    else {
        cout << "Profile search test failed! foundProfile is a nullptr!\n" << endl;
    }

    //remove a profile
    Profile removeProfile("user1");
    bool removed = myADT1->remove(removeProfile); //should return true since we are giving it a valid user to remove
    if (removed == true) {
        cout << "Profile removal method test passed!\n" << endl;
        testsPassed++;
    }
    else {
        cout << "Profile removal method test failed!\n" << endl;
    }

    //test removing nonexistent profile
    Profile nonExistentProfile("user5");
    bool notRemoved = myADT1->remove(nonExistentProfile); //should return false as we have given the method a nonexistent profile
    if (notRemoved == false) {
        cout << "Removal of non-existent profile test passed!\n" << endl;
        testsPassed++;
    }
    else {
        cout << "Removal of non-existent profile test failed!\n" << endl;
    }

    //print all profiles by calling print method
    cout << "All profiles after tests:" << endl;
    myADT1->print();

    //create a second instance of MyADT using the copy constructor to make a deep copy of myADT1
    cout << "\nCreating a copy of myADT1 called myADT2:" << endl;
    MyADT* myADT2 = new MyADT(*myADT1);
    if(myADT2 != nullptr){
        cout << "Copy constructor initialization test passed!\n" << endl;
        cout << "myADT2 is located at address: " << &myADT2 << endl;
        testsPassed++;
    }
    else{
        cout << "Copy constructor initialization test failed!\n" << endl;
    }

    //remove all profiles
    myADT1->removeAll();
    //at this point, all profiles should be gone, therefore the total element count should be zero
    unsigned int finalElementCount = myADT1->getElementCount();

    if (finalElementCount == 0) {
        cout << "\nFinal element count test passed!\n" << endl;
        testsPassed++;
    }
    else {
        cout << "\nFinal element count test failed!\n" << endl;
    }

    //delete the heap-allocated myADT1
    delete myADT1;
    myADT1 = nullptr;
    cout << "Original instance of MyADT (myADT1) freed from heap memory!\n" << endl;

    //test second instance for deep copy
    if((myADT2->search(profile2) != nullptr) && (myADT2->search(profile3) != nullptr) && (myADT2->search(overflowProfile) != nullptr)){
        cout << "Second instance copied properly! Printing second instance:" << endl;
        myADT2->print();
        testsPassed++;
    }

    //delete the heap-allocated myADT2
    delete myADT2;
    myADT2 = nullptr;
    cout << "\nCopied instance of MyADT (myADT2) freed from heap memory!\n" << endl;


    //check the amount of tests passed to see if all tests passed
    if (testsPassed == numberOfTests) {
        cout << "All tests passed!" << endl;
    }
    else {
        cout << "Not all tests passed! Only " << testsPassed << " out of " << numberOfTests << " tests passed!" << endl;
    }

    return 0;
}