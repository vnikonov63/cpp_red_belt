#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class BookReader {
public:
    
    BookReader() : userInfoVector(100000), numberPeople(0), pageCount(1001) {}
    void Read(int user, int page) {
        if (userInfoVector[user] != 0) {
            int temp = userInfoVector[user];
            auto it = next(pageCount.begin(), temp + 1);
            auto it1 = next(pageCount.begin(), page + 1);
            transform(it, it1, it, [](int a){
                return a - 1;
            });
        } else {
            numberPeople++;
            auto it = next(pageCount.begin(), page + 1);
            transform(it, pageCount.end(), it, [](int a){
                return a + 1;
            });
        }
        userInfoVector[user] = page;
    }
    
    double Cheer(int user) {
        if (userInfoVector[user] == 0) {
            return 0;
        } else if (numberPeople == 1) {
            return 1;
        } else {
            int userPageCount = userInfoVector[user];
            return (pageCount[userPageCount] * 1.0) / (numberPeople - 1);
        }
    }
    
private:
    vector<int> userInfoVector;
    map<int, int> readCount;
    vector<int> pageCount;
    int numberPeople;
};

ostream& operator << (ostream& os, vector<int> v) {
    for (const auto& el : v) {
        os << el << " ";
    }
    return os;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BookReader myBookReader;
    
    int operationCount;
    cin >> operationCount;
    
    for (int i = 0; i < operationCount; ++i) {
        string command;
        cin >> command;
        if (command == "READ") {
            int user, page;
            cin >> user >> page;
            myBookReader.Read(user, page);
        }
        if (command == "CHEER") {
            int user;
            cin >> user;
            cout << myBookReader.Cheer(user) << '\n';
        }
    }

    return 0;
}
