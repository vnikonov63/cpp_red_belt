#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

class BookReader {
public:
    
    BookReader() : userInfoVector(100000), numberPeople(0) {}
    void Read(int user, int page) {
        if (userInfoVector[user] != 0) {
            int temp = userInfoVector[user];
            readCount[temp]--;
        } else {
            numberPeople++;
        }
        userInfoVector[user] = page;
        readCount[page]++;
    }
    
    double Cheer(int user) {
        if (userInfoVector[user] == 0) {
            return 0;
        } else if (numberPeople == 1) {
            return 1;
        } else {
            auto it = readCount.lower_bound(userInfoVector[user]);
            int sum = 0;
            if (it == readCount.begin()) {
                return 0;
            }
            do {
                --it;
                sum += it->second;
            } while(it != readCount.begin());
            return (sum * 1.0) / (numberPeople - 1) ;
        }
    }
    
private:
    vector<int> userInfoVector;
    map<int, int> readCount;
    int numberPeople;
};

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
