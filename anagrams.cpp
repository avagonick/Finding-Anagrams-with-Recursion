#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
using namespace std;
const int MAXRESULTS = 20; // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


//clears array of all possible values so that it is empty

void clearArray(string array[], const int& maxsize){
    if(maxsize == 0){
        return;
    }
    array[maxsize - 1] = "";
    clearArray(array, maxsize - 1);
}

//currently doesn't work for empty files or files that are too big
int addWords(istream &dictfile, string dict[], const int& pos){
    string s;
    if(!getline(dictfile, s)) {//this checks if the file is empty if it is it return if no it sets s to the value
        
        return pos;
    }
    
    //if MAXDICTWORDS items leave
    if(pos == MAXDICTWORDS -1)
        return MAXDICTWORDS;
    dict[pos] = s;
    
    
    //recursive call
    return addWords(dictfile, dict, pos + 1 );
    
    
}

int vocabularyCreator(istream &dictfile, string dict[]){
    //when reach base case means after will start filling dict so clear it
   clearArray(dict, MAXDICTWORDS);
    

    //this adds words into the dictionary and returns how many words have been added
    return addWords(dictfile, dict, 0);
    
}


//this function deletes a character
string deletechar(string suffix, const int& index){
    
    //the beginning of the new string is everything before the index + the end of the new string is everything after the index
    return suffix.substr(0, index) += suffix.substr(index + 1, suffix.length() - 1 - index);
}


//this function tells you if a word is a repeat of a word in results
bool isrepeat(const string& word, string results[], const int& resultsize){
    //means go to the end without having a repeat
    if(resultsize == 0)
        return false;
    
    //if a match return true
    if(word == results[resultsize - 1])
        return true;
    
    
    return isrepeat(word, results, resultsize - 1);
}


//this checks if a word is in dict and adds matches to results
void checkword(const string& word, const string dict[], const int& size, string results[], int& resultsize){
    
    
    //if this word is already in result return
    if(isrepeat(word, results, resultsize))
        return;
    //if gone through everything return 0
    if(size == 0)
        return;
    
    //if something matches in dict
    if(word == dict[size - 1]){
        //add it to result
        results[resultsize] = word;
        //increase the size of result
        resultsize++;
        //return
        return;
    }
    //recursively call to check everything
    checkword(word, dict, size - 1, results, resultsize);
}


//this gets all possible anagrams, then calls checkword to see if they should be added into results
void getanagrams(string prefix, string suffix, const int& counter, const string dict[], const int& size, string results[], int& resultsize){
    
    //if empty string just return
    if(suffix.length()== 0 && prefix.length() == 0){
        return;
    }
    
    //if suffix is empty then everything is in prefix and return
   if(suffix.length() == 0){
       //if the results array is not full check if can add it into the results array
       if(resultsize < MAXRESULTS){
           checkword(prefix, dict, size, results, resultsize);
       }
        return;
    }
    
    //if resultsize if full stop going through the loop
    if(resultsize == MAXRESULTS){
        return;
    }
    
   // if looped through everything in the suffix return, this is for the calls not changing suffix length because they want to try every value for prefix
   if(counter == suffix.length() )
        return;
    
    //go through with old prefix so every combinition of characters for this posiiton can be checked
    getanagrams(prefix, suffix, counter + 1, dict, size, results, resultsize);
    
    //go through with the newprefix which moves the function to start adding all possible values to the next index
    getanagrams(prefix += suffix [counter], deletechar(suffix, counter), 0, dict, size, results, resultsize);
    
}

//now need to check for repeats, this should also be in the check resuts function but have it be another function called check repeats done before try to add anything in if it is a repeat just reutrn


int potentialSequences(string word, const string dict[], int size, string results[]){
    
    //clear the results array because could be given one with values in it
   clearArray(results, MAXRESULTS);
    string prefix;
    int resultsize = 0;
    getanagrams(prefix, word, 0, dict, size, results, resultsize);
    return resultsize;
}

//displays size number of strings from results
void outcomeDisclosure(const string results[], int size){
    if(size == 0)
        return;
    cout << "Matching word " << results[size - 1] << endl;
    outcomeDisclosure(results, size - 1);
}



int main()
{
 return 0;
    /*
   string arr[MAXDICTWORDS];
    clearArray(arr, MAXDICTWORDS);
    
    
    //Users/avagonick/Desktop/
    
    //opens dict the usual dictionary
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile; // file containing the list of words
    int nwords; // number of words read from dictionary
    string word;
    dictfile.open("/Users/avagonick/Desktop/words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    nwords = vocabularyCreator(dictfile, dict);
    cout << "this is dictfile size" << nwords << endl;
    
    
     //open words 2 the longer dictionary
     string dict2[MAXDICTWORDS];
     ifstream extradict;
     int extraword;
     extradict.open("words2.txt");
     if (!extradict) {
     cout << "File not found!" << endl;
     return (1);
     }
     extraword=vocabularyCreator(extradict, dict);
     
     cout << "this is extradict size" << extraword << endl;
     
     //opens the empty text
     ifstream emptfile;
     int emptwords;
     string emptstring[MAXDICTWORDS];
     emptfile.open("empty.txt");
     if (!emptfile) {
     cout << "File not found!" << endl;
     return (1);
     }
     emptwords = vocabularyCreator(emptfile, emptstring);
     cout << "empty words is empty if this is 0" << emptwords<< endl;
     
    
    //open txt larger the MAXDICTWORDS
    
     
     ifstream largefile;
     int largenum;
     string largestring[MAXDICTWORDS];
     largefile.open("wordsext.txt");
     if(!largefile){
     cout << "file not found!" << endl;
     return (1);
     }
     largenum = vocabularyCreator(largefile, largestring);
     cout << "this should be 30000 " << largenum << endl;
    
    
     
     ifstream paint;
     int paintnum;
     paint.open("justpaint.txt");
     if(!paint){
     cout << "file not found!" << endl;
     return (1);
     }
     
     string paintstring[MAXDICTWORDS];
     
     //puts values into paintstring to make sure they get wiped
     for(int i = 0; i < MAXDICTWORDS; i ++){
     paintstring[i] = "whoop";
     }
     paintnum = vocabularyCreator(paint, paintstring);
     cout << paintnum;
     
     
     int numMat = potentialSequences("paint", paintstring, paintnum, results);
     cout << "this hsould be twenty because max of array" << numMat << endl;
     
     cout << "this should have the 120 permutations of paint" << endl;
     for(int i = 0; i < MAXDICTWORDS; i ++){
     cout << paintstring[i] << endl;
     }
     cout << "this should be twnety of paints anagrams"<< endl;
     outcomeDisclosure(results, numMat);
     if (!numMat) {
     cout << "No matches found" << endl;
     }
     
     
     string check[0];
     string check2[19] ={"first", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "last"};
     string check3[10] = {"first", "word", "word", "word", "word", "word", "word", "word", "word", "last"};
     outcomeDisclosure(check, 0);
     cout << endl;
     outcomeDisclosure(check2, 2);
     cout << endl;
     outcomeDisclosure(check3, 10);
     
     
     
    string wordm;
    string answ[MAXRESULTS];
    
    cout << "Please enter a string for an anagram: this is for the normal dict" << endl;
    cin >> wordm;
    int numMatchy = potentialSequences(wordm, dict, nwords, answ);
    cout << "num of matches is " << numMatchy << endl;
    
    outcomeDisclosure(answ, numMatchy);
    if (!numMatchy) {
        cout << "No matches found" << endl;
        
    }
    
    
    //tests with new dict and a full array
    string answers[MAXRESULTS] = {"hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi", "hi"};
    string words;
    cout << "Please enter a string for an anagram: with dict 2 this part also tests an already full results string this is normal dict " << endl;
    cin >> words;
    int numMatch = potentialSequences(words, dict, nwords, answers);
    cout << "num of matches is " << numMatch << endl;
    
    outcomeDisclosure(answers, numMatch);
    if (!numMatch) {
        cout << "No matches found" << endl;
    }
}
    
     
     //test with dict that is completely full
    string answers[MAXRESULTS];
     string wordy;
     cout << "Please enter a string for anagram: this is from wordsext that is very long and tests against a full 30000 dictionary this has a weird number of values to check against " << endl;
     cin >> wordy;
     int numy = potentialSequences(wordy, largestring, largenum, answers);
     cout << "num of matches is" << numy << endl;;
     outcomeDisclosure(answers, numy); */
     }
    
