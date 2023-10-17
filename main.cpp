
// Name: Sandesh Poudel
// Class: CSC319A
// Title: First C++ program
// Date: 9/17




#include <iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<vector>
#include<cctype>
#include<algorithm>
#include <bits/stdc++.h>
#include <iterator>
#include<iomanip>

using namespace std;

// function that reads the user input file fileName and displays the words without whitespace and punctuation.
vector<string> read_file(string fileName){

  string line;
  ifstream myfile ;
  string word ;

  vector <string> word_from_file;

  //opens user input file
  myfile.open(fileName);

  //checks if file is opened
  while (!myfile.is_open()){
    // if file is not opened ask user to retry until the file is opened
    cout <<"Invalid file Name. Please re-enter: ";
    getline(cin, fileName);
    myfile.open(fileName);
  }
    // while loop to loop over every line of the file.
    while (getline(myfile,line)){

    for (int i = 0; i<(line.length()+1); i++){

        //ignore whitespace and punctuation and store it in word_from_file vector in Uppercase letter.
        if (isalpha(line[i])){
            word +=toupper(line[i]);
            }
        else{
                /*if statement to avoid blank element in vector i.e if there is
                "end. Next" in the file then isalpha() will avoid "." and pushback "end" to vector
                and again next iteration " " between "." and "Next" will also be ignored by isalpha()
                and word which is equal to "" from our declaration in else statement will also be
                pushed back to vector which will create and space element in our vector i.e <"end", "", "Next">. */
            if (word !=""){
                word_from_file.push_back(word);
                }

            word="";
            }

        }
    }

    //print out content of the file without any whitespace and punctuation.
    cout<<"\nThe contents of the files are: "<<endl;
    for (auto it = word_from_file.begin(); it != word_from_file.end(); it++)
        cout << *it << " ";

    cout<<"\n"<<endl;

    //close file
    myfile.close();
    //return the vector with the word from file.
    return word_from_file;


}

// function that sorts the word from the file in alphabetical order.
vector<string> sort_vector(vector<string> vector_name){

    //simple sorting algorithm to sort vector alphabetically.
    sort(vector_name.begin(), vector_name.end());

    cout<<"\n"<<endl;
    // prints sorted vector
    for (int i =0; i<vector_name.size();i++){
        cout<< vector_name[i]<<" "<<endl;
    }
    cout<<"\n"<<endl;

    //return the input vector in sorted format.
    return vector_name;
}


// function that counts the frequency of repeated words and prints how many times the word is repeated
vector<int> count_vector(vector<string> vector_name){
    vector<string> unique_vector;
    vector<int> counter_vector;

    unique_vector = vector_name;

    //erasing the repeated value from unique vector.
    unique_vector.erase(unique(unique_vector.begin(), unique_vector.end()), unique_vector.end());

    //initializing every element to counter_vector to 0 whose size is equal to the size of unique vector without duplicates.
    for (int i=0; i<unique_vector.size(); i++){
        counter_vector.push_back(0);
    }

    /* if element from unique vector is repeated in original vector then increment by 1.
    Here even if the element is not repeated but still if unique vector[i]== original vector[i]
    we increment by 1 because we initially set every value of counter vector to 0 so incrementing by 1 says
    it is repeated 1 times. */
    for (auto& i: vector_name){
        for(int j =0; j<unique_vector.size(); j++){
            if (i == unique_vector[j]){
                counter_vector[j]+=1;
                //if equal breaks loop and go to different element from original vector and checks.
                break;
            }
        }

    }
    cout<<"\n"<<endl;
    // prints how many time element is repeated without frequency sorted.
    for (int i=0; i<unique_vector.size(); i++){
        cout<< unique_vector[i]<< " is repeated "<< counter_vector[i]<< " times. "<<endl;
    }
    cout<<"\n"<<endl;
    /*returns vector with counters. we are not returning unique vector because
    we cannot return two separate value from single function and finding unique vector is only 1 line of code*/
    return counter_vector;
}


//function that reports the content of the file with the sorted order of occurrence.
int report(vector<string> duplicate_vector, vector<int> counter_vector){
    //removes duplicates from original vector.
    duplicate_vector.erase(unique(duplicate_vector.begin(), duplicate_vector.end()), duplicate_vector.end());

    //declaring a vector of pairs with 1st value as int and 2nd as string.
    vector< pair<int, string>> report_vector;

    //making a pair in report vector with first value from counter vector and second from unique vector.
    for(int i =0; i<counter_vector.size(); i++){
        report_vector.push_back( make_pair(counter_vector[i], duplicate_vector[i]));

    }

    //sorting vector based on 1st value of the pair.
    sort(report_vector.rbegin(), report_vector.rend());

    cout<<"\nReport of the file with sorted with most frequency of repeated word is: \n"<<endl;
    cout<<"Word"<<"\t"<<"Frequency"<<endl;

    //printing the report
    for(int i =0; i<counter_vector.size(); i++){

        cout<<report_vector[i].second<<setw(10)<< report_vector[i].first<<endl;
    }
    cout<<"\n"<<endl;

    return 0;

}

//main function that calls other function based on user input.
int main () {
  string command;
  string word;
  vector<string> final;
  vector<int> counter_vect;

  //get user input.
  cout<<"Enter Command: ";
  getline(cin, command);

  // checks if the user wants to exit.
  while(command != "exit"){

  /*declared files vector inside while loop
  because for every iteration of while loop the file vector
  where we store user input will be empty and we will only get the input
  user enters at particular iteration. */

  vector<string> files ={};

  //puts the user input in vector(command seperated with space will be two elements in vector).
  for (int i = 0; i<(command.length()+1); i++){

    /*check for whitespace for only first word from command and puts in vector
    command = read file.txt, below if statement only puts read in files vector because "." in file extension
    will be ignored by isalpha()*/

    if (files.size() ==0){
        if (isalpha(command[i])){
            word +=toupper(command[i]);
        }
        else{
            //if encountered space put the word before space to vector

        files.push_back(word) ;

        word="";
    }
  }
   else{
        //put every string after space into word including "." from file extension.
      word+=command[i];
    }
  }

    /*isaplha() will ignore the "." in file extension, so if
    the vector has already one element(1st command) in it,
    we will not check for isaplha() so that we can have fileName.extension vector[1]
    which we can read and every iteration of for loop above will empty the word string.*/

    files.push_back(word);
    word="";

     if (files[0]=="READ"){
        // final is the vector with all the words in file that user wants to read.
        final =read_file(files[1]);
        }
     if (files[0] =="SORT"){
         // sorting the final vector on alphabetical order.
        final=sort_vector(final);
        }
    if (files[0] == "COUNT"){
        // counter_vect is vector with number of occurence of words in the files in sorted alphabetical order.
        counter_vect = count_vector(final);
    }
    if (files[0] == "REPORT"){
        report(final, counter_vect);
    }


  // if user wants to exit or proceed with other commands.
  cout<<"Enter Command again: ";
  getline(cin, command);
  }


  exit(0);

  return 0;
}


