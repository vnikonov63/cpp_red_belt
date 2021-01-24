#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>;

using namespace std;

class BookReader {
public:
    void Read(int user, int page) {
        userInfo[user] = page;
        readCount[page]++;
    }
    
    double Cheer(int user) {
        if (userInfo.count(user) == 0) {
            return 0;
        } else if (userInfo.size() == 1) {
            return 1;
        } else {
            auto it = readCount.lower_bound(userInfo[user]);
            
            int sum = 0;
            if (it == readCount.begin()) {
                return 0;
            }
            do {
                --it;
                sum += it->second;
            } while(it != readCount.begin());
            return (sum * 1.0) / userInfo.size() ;
        }
    }
    
private:
    map<int, int> userInfo;
    map<int, int> readCount;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    BookReader myBookReader;
    
    int operationCount;
    cin >> operationCount;
    
    /*
    stringstream output;
    stringstream input;
    
    for (int i = 0; i < operationCount; ++i) {
        string line;
        getline(cin, line);
        input << line;
        input << '\n';
    }*/
    stringstream output;
    
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
            output << myBookReader.Cheer(user) << '\n';
        }
    }
    cout << output.str() << endl;
    return 0;
}
