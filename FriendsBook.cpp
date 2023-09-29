/*
 * FriendsBook.cpp - Assignment 1
 * 
 * Class Description: Social network application (completed implementation).
 *
 * In this version, we use our MyADT.
 * A linear data collection ADT.
 * Author: AL & Brendan Shen
 * Modified on: Sept. 30, 2023
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "MyADT.h"

using std::cout;
using std::ws;
using std::cin;
using std::endl;

void join(MyADT &theMembers) {
    string user_name;
    string name;
    string birthday;
    string email;

    cout << "Please enter your username (only lower/upper letters and underscore allowed, max 12 char):" << endl;
    cin >> user_name;

    //in case you want to convert name to lowercase character by character, but i'm sure you TAs will play nice and follow those rules
/*     int length = user_name.length();
    for (int i = 0; i < length; ++i) {
        user_name[i] = tolower(user_name[i]);
    } */

    cout << "Please enter your name (First and Last):" << endl;
    cin.ignore();
    getline(cin,name);//need to do this in order to get a space separated string since cin sometimes exibits strange behaviour when dealing with space characters

    cout << "Please enter your email (no spaces, ie: example@example.com):" << endl;
    cin >> email;//we can assume the email will not have a space in it

    cout << "Please enter your birthday:" << endl;
    cin.ignore();
    getline(cin,birthday);

    //create a Profile object using the second parameterized constructor and the information we just gathered from the user
    Profile newProfile(user_name,name,email,birthday);

    //we insert newProfile into the members and save the resulting boolean value into a variable
    bool success = theMembers.insert(newProfile);

    //tell the user whether or not the insert returned true or false
    if(success == true){
        cout << "User added successfully!" <<endl;
    }
    else{
        cout << "User could not join!" << endl;
    }
}

void leave(MyADT & theMembers) {
    string user_name;
    cout << "What is your username?" << endl;
    cin >> user_name;

    //making a profile using the first parameterized constructor
    Profile leavingProfile(user_name);

    //call the .search method of MyADT to get a pointer to the searched for profile / a nullptr
    Profile* searchedProfile= theMembers.search(leavingProfile);
    if (searchedProfile != nullptr){//if the searchedProfile is not a nullpointer, and thus is a profile in theMembers
        cout << "\nProfile found!\n" << endl;//tell user the profile is found

        bool success = theMembers.remove(leavingProfile);//call the .remove method and save boolean result in success

        if (success == true){//alert user that user has been removed / not removed
            cout << "User removed successfully!" <<endl;
        }
        else{
            cout << "User could not leave!" <<endl;
        }
    }
    else{//alert user that a profile with the username entered does not exist 
        cout << "\nProfile not found!\n" << endl;
    }
}

void search(MyADT & theMembers) {
    string user_name;
    cout << "What is the username of the friend you are looking for?" << endl;
    cin >> user_name;

    //making a profile using the first parameterized constructor
    Profile searchingProfile(user_name);

    //call the .search method of MyADT to get a pointer to the searched for profile / a nullptr
    Profile* searchedProfile= theMembers.search(searchingProfile);
    if (searchedProfile != nullptr){//if the searchedProfile is not a nullpointer, and thus is a profile in theMembers
        cout << "\nProfile found!\n" << endl;//tell user the profile is found
        //cout all the getter methods in Profile (username,name,email,birthday)
        cout << searchedProfile->getUserName() << ", " 
        << searchedProfile->getName() << ", " 
        << searchedProfile->getEmail() << ", " 
        << searchedProfile->getBirthday() << endl;
    }
    else{//alert user that a profile with the username entered does not exist 
        cout << "\nProfile not found!\n" << endl;
    }
}

void modify(MyADT & theMembers) {
    //get user to put in their username
    string user_name;
    cout << "What is your username? " << endl;
    cin >> user_name;

    //do essentially the same thing as the search function
    Profile searchingProfile(user_name);
    Profile* searchedProfile= theMembers.search(searchingProfile);
    if (searchedProfile != nullptr){//if the searchedProfile is not a nullpointer, and thus is a profile in theMembers
        cout << "\nProfile found!\n" << endl;//tell user the profile is found

        //get user to input a choice of changing their profile's name, email, or birthday
        char choice;
        cout << "What would you like to change?\n1. Change name:\n2. Change email:\n3. Change birthday:" << endl;
        cin >> choice;

        //the three options all are about the same
        if(choice == '1'){
            //gets that the user wants to thange their profile's name to
            string newName;
            cout << "What would you like to change your name to?" <<endl;
            cin.ignore();
            getline(cin,newName);
            searchedProfile->setName(newName);//use the name setter method in Profile
            if (newName == searchedProfile->getName()){//checks if the new name was actually set properly by using the getter mehod in Profile and comparing it to newName
                cout << "Name changed successfully!" <<endl;
            }
            else{
                cout << "Something went wrong!" <<endl;
            }
        }
        else if (choice == '2'){
            string newEmail;
            cout << "What would you like to change your email to?" <<endl;
            cin.ignore();
            getline(cin,newEmail);
            searchedProfile->setEmail(newEmail);
            if (newEmail == searchedProfile->getEmail()){
                cout << "Email changed successfully!" <<endl;
            }
            else{
                cout << "Something went wrong!" <<endl;
            }
        }
        else if (choice == '3'){
            string newBirthday;
            cout << "What would you like to change your birthday to?" <<endl;
            cin.ignore();
            getline(cin,newBirthday);
            searchedProfile->setBirthday(newBirthday);
            if (newBirthday == searchedProfile->getBirthday()){
                cout << "Birthday changed successfully!" <<endl;
            }
            else{
                cout << "Something went wrong!" <<endl;
            }
        }
        else{
            cout << "You did not enter a valid option." <<endl;
        }    }
    else{
        cout << "\nProfile not found!\n" << endl;
    }
}

void print(MyADT & theMembers) {
    theMembers.print();//just calls the print method of MyADT
}

int main() {

    // Variables declaration
    MyADT members = MyADT();  // Object MyADT on the stack, its arrays on the heap
    bool done = false;
    char input = 0;
        
    // Keep going until the user exits
    while (not done) {
        // Print menu to stdout
        cout << "\n----Welcome to FriendsBook!" << endl << endl;
        cout << endl << "Enter ..." << endl;
        cout << "j -> to join FriendsBook by creating a profile." << endl;
        cout << "l -> to leave FriendsBook." << endl;
        cout << "s -> to search for a friend on FriendsBook." << endl;
        cout << "m -> to modify your profile on FriendsBook." << endl;
        cout << "p -> to print all members on FriendsBook." << endl;
        cout << "x -> to exit FriendsBook." << endl << endl;


        cout << "Your choice: ";
        cin >> input;
        cout << endl;
        input = tolower(input);
        switch(input) {
            case 'j': join(members); break;
            case 'l': leave(members); break;
            case 's': search(members); break;
            case 'm': modify(members); break;
            case 'p': print(members); break;
            case 'x': cout << "\n----Bye!\n" << endl; 
                      done = true; break;
            default: cout << "Not sure what you mean! Please, try again!" << endl;
        }
    }

    return 0;
}
