/* 
 * File:   main.cpp
 * Author: Ben Walcutt
 *         bewalcut@email.uark.edu
 *
 * Created on October 3, 2014, 11:00 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// function prototype
bool friend_check(string, string);

int main(int argc, char** argv)
{
    // word to be tested
    string mainword;
    // placeholder for words read in by fstream
    string dummy;
    
    // variable used to keep track of place in vector
    unsigned int counter = 0;
    // used to keep track of start of level
    unsigned int start = 0;
    
    // vector to hold all the friends
    vector<string> friend_list;
    
    // file containing the list of words
    fstream wordfile;
    // file for outputting the vector to a document
    //fstream outfile;
    
    
    cout << "Wayfarer Challenge" << endl << endl;
    
    cout << "Enter word to be analyzed: ";
    cin >> mainword;
    
    // open the file with the words
    wordfile.open("randomlist.txt", ios::in); 
    // make sure file is opened before you start doing things
    if (!wordfile) {cout << "Unable to open file."; return 1;}    
   
    // loop to bring in each word in the list
    while (wordfile >> dummy)
    {
        // can't be a friend of yourself...terrible, I know
        if (dummy == mainword) {continue;}
        
        // run through the check function, 1 if friend, 0 if not
        if (friend_check(mainword, dummy))
        {
            // found a friend, add it to the list
            friend_list.push_back(dummy);
        }
    }
    
    
    // break down the vector into levels; this is the first level
    cout << "\nFirst Level Analysis for: " << mainword << endl;    
    for (int i = 0; i < friend_list.size(); i++)
    {
        cout << friend_list.at(i) << endl;
    }

    // ----------- START OF SECOND LEVEL ANALYSIS ----------    
    
    // this shows where the end of the first level friends are
    counter = friend_list.size();
    
    // clear the eof flag
    wordfile.clear();
    // reset to the beginning of the file
    wordfile.seekg(0, ios::beg);
    
    // this checks each of the first level friends
    for (int i = 0; i < counter; i++)
    {
        // loop to bring in each word in the list
        while (wordfile >> dummy)
        {
            // run through the check function, 1 if friend, 0 if not
            if (friend_check(friend_list[i], dummy))
                // found a friend, check to see if it is already in the entire vector
                for (int j = 0; j <= friend_list.size(); j++)
                {
                    // the word that is a friend matches something in the vector
                    // note: the program kept including the mainword in the second
                    // level of friends so the OR logic removes it
                    if ((dummy == friend_list[j]) || (dummy == mainword))
                    {
                        // ignore it
                        break;
                    }
                    // if j makes it all the way through the list
                    if (j == (friend_list.size() - 1))
                    {
                        // add the friend to the vector
                        friend_list.push_back(dummy);
                    }
                }
            
        }
        // clear the eof flag
        wordfile.clear();
        // reset to the beginning of the file
        wordfile.seekg(0, ios::beg);
        
    }
    
    // breakdown the vector into levels; this is the second level
    cout << "\nSecond Level Analysis for: " << mainword << endl;
    // start at the end of first level
    for (int i = counter; i < friend_list.size(); i++)
    {
        cout << friend_list.at(i) << endl;
    }
    
    // ----------- START OF THIRD LEVEL ANALYSIS ----------
    
    // start becomes start of second level
    start = counter;
    // counter becomes end of second level
    counter = friend_list.size();
    
    // clear the eof flag
    wordfile.clear();
    // reset to the beginning of the file
    wordfile.seekg(0, ios::beg);
    
    // this checks each of the second level friends
    for (int i = start; i < counter; i++)
    {
        // loop to bring in each word in the list
        while (wordfile >> dummy)
        {
            // run through the check function, 1 if friend, 0 if not
            if (friend_check(friend_list[i], dummy))
                // found a friend, check to see if it is already in the entire vector
                for (int j = 0; j < friend_list.size(); j++)
                {
                    // the word that is a friend matches something in the vector
                    if (dummy == friend_list[j])
                    {
                        // ignore it
                        break;
                    }
                    // if j makes it all the way through the list
                    if (j == (friend_list.size() - 1))
                    {
                        // add the friend to the vector
                        friend_list.push_back(dummy);
                    }                    
                }
        }
        
        // clear the eof flag
        wordfile.clear();
        // reset to the beginning of the file
        wordfile.seekg(0, ios::beg);
        
    }
    
    // breakdown the vector into levels; this is the third level
    cout << "\nThird Level Analysis for: " << mainword << endl;
    // start at the end of the second level
    for (int i = counter; i < friend_list.size(); i++)
    {
        cout << friend_list.at(i) << endl;
    }
    
    // ----------- DISPLAY THE FULL ANALYSIS ----------
    
    // this can be substituted for an output to a file
    // the output is provided but commented out
    
//    outfile.open("output.txt", ios::out);
//    
//    outfile << "Friend Analysis for: " << mainword << endl;
//    
//    for (int i = 0; i < friend_list.size(); i++)
//    {
//        outfile << friend_list[i] << endl;
//    }
//    
//    outfile.close();
    
    cout << "\nFull Analysis for: " << mainword << endl;
    
    for (int i = 0; i < friend_list.size(); i++)
    {
        cout << friend_list.at(i) << endl;
    }
    
    // clean up
    wordfile.close();
    return 0;
}

/* Function: friend_check
 * Author: Ben Walcutt
 * Purpose: Take two strings and compare their Levenshtein friendship. If they
 *          are friends, their Levenshtein distance is 1.
 * Parameters: string, string
 *             compare string compared against master string
 * Return: bool function so 1 if they are friends, 0 if they aren't
 */

bool friend_check(string master, string compare)
{
    // flag to determine if there is a change in characters
    bool ischange = 0;
    
    // checks to find compares one less character than master
    if (compare.length() == master.length() - 1)
    {
        // loop through length of compare since it is shorter
        // all characters MUST be the same
        for (int i = 0; i < compare.length(); i++)
        {
            // found a difference
            if (compare[i] != master[i])
                // not friends
                return 0;
        }
        // no difference so the only change is the last character of master
        return 1;
    }
    
    // checks to find compares the same length of master
    if (compare.length() == master.length())
    {
        // you can't be your own friend...terrible, I know
        if (compare == master) {return 0;}
        // loop through length of master because it's master
        for (int i = 0; i < master.length(); i++)
        {
            // found a difference
            if (master[i] != compare[i])
            {
                // if the flag is already raised, this is the second difference
                if (ischange)
                    // not friends
                    return 0;
                // raise the flag
                ischange = 1;
            }
        }
        // either way, return the flag
        // 1 for friends, 0 for not
        return ischange;
    }    
    
    // checks to find compares one more character than master
    if (compare.length() == (master.length() + 1))
    {
        // loop through length of master since its shorter
        for (int i = 0; i < master.length(); i++)
        {
            // the first difference is that compare is one character longer
            // so if we find ANY other difference...
            if (compare[i] != master[i])
                // not friends
                return 0;
        }
        // otherwise they are friends
        return 1;
    }
    // compiler requires me to have a return here
    return 0;
}