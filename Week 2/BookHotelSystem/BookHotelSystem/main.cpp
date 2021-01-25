#include <iostream>
#include <cstdint>
#include <string>
#include <deque>
#include <map>
#include <set>

using namespace std;

struct Booking {
    Booking(int64_t time, int clientId, int roomCount) : time_(time),
                                                        clientId_(clientId),
                                                        roomCount_(roomCount){};
    int64_t time_;
    int clientId_;
    int roomCount_;
};

class BookingSystem {
public:
    void Book(int64_t time, string hotelName, int clientId, int roomCount) {
        dataBase[hotelName].push_back({time, clientId, roomCount});
        if (fastResults.count(hotelName) == 0) {
            fastResults[hotelName] = roomCount;
            fastResultsClients[hotelName][clientId] += 1;
        } else {
            fastResults[hotelName] += roomCount;
            fastResultsClients[hotelName][clientId] += 1;
        }
        currentTime = time;
    }
    int Clients(string hotelName) {
        adjust(hotelName);
        /*
        set<int> uniqueClients;
        for (const auto& el : dataBase[hotelName]) {
            uniqueClients.insert(el.clientId_);
        }*/
        return fastResultsClients[hotelName].size();
    }
    int Rooms(string hotelName) {
        adjust(hotelName);
        return fastResults[hotelName];
    }
private:
    map<string, deque<Booking>> dataBase;
    map<string, int> fastResults;
    map<string, map<int, int>> fastResultsClients;
    int64_t currentTime;
    void adjust(string hotelName) {
        auto& particular = dataBase[hotelName];
        auto& call = fastResults[hotelName];
            while (!particular.empty() && particular.front().time_ + 86400 <= currentTime) {
                call -= particular.front().roomCount_;
                fastResultsClients[hotelName][particular.front().clientId_]--;
                if (fastResultsClients[hotelName][particular.front().clientId_] == 0) {
                    fastResultsClients[hotelName].erase(particular.front().clientId_);
                }
                particular.pop_front();
            }
    }
};

int main() {
    int numberCommands;
    cin >> numberCommands;
    
    BookingSystem myBookingSystem;
    
    for (int i = 0; i < numberCommands; ++i) {
        string commandName;
        cin >> commandName;
        
        if (commandName == "BOOK") {
            int64_t time;
            string hotelName;
            int clientId, roomCount;
            cin >> time >> hotelName >> clientId >> roomCount;
            myBookingSystem.Book(time, hotelName, clientId, roomCount);
        }
        
        if (commandName == "CLIENTS") {
            string hotelName;
            cin >> hotelName;
            cout << myBookingSystem.Clients(hotelName) << endl;
        }
        
        if (commandName == "ROOMS") {
            string hotelName;
            cin >> hotelName;
            cout << myBookingSystem.Rooms(hotelName) << endl;
        }
    }
    return 0;
}
