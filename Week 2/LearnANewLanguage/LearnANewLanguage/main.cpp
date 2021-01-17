#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>

#include "profile.h"

using namespace std;

class Learner {
 private:
  vector<string> dict;
    set<string> mySet;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (mySet.find(word) == mySet.end()) {
        ++newWords;
        mySet.insert(word);
        dict.push_back(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    sort(dict.begin(), dict.end());
    dict.erase(unique(dict.begin(), dict.end()), dict.end());
    return dict;
  }
};


int main() {
    LOG_DURATION("total");
    ifstream input("input.txt");
    
    
      Learner learner;
      string line;
    {
        LOG_DURATION("read process");
        while (getline(input, line)) {
          vector<string> words;
          stringstream ss(line);
          string word;
          while (ss >> word) {
            words.push_back(word);
          }
            {   LOG_DURATION("Learn function");
                // the main problem comes from Learn function
                learner.Learn(words);
            }
        }
    }
      //cout << "=== known words ===\n";
    {
        LOG_DURATION("Known Words");
        for (auto word : learner.KnownWords()) {
          //cout << word << "\n";
        }
    }
    }
