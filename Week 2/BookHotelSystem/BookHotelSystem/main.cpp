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
        currentTime = time;
    }
    int Clients(string hotelName) {
        adjust(hotelName);
        set<int> uniqueClients;
        int result = 0;
        for (const auto& el : dataBase[hotelName]) {
            if (uniqueClients.count(el.clientId_) == 0) {
                result++;
                uniqueClients.insert(el.clientId_);
            }
        }
        return result;
    }
    int Rooms(string hotelName) {
        adjust(hotelName);
        int result = 0;
        for (const auto& el : dataBase[hotelName]) {
            result += el.roomCount_;
        }
        return result;
    }
private:
    map<string, deque<Booking>> dataBase;
    int64_t currentTime;
    void adjust(string hotelName) {
        deque<Booking>& particular = dataBase[hotelName];
        while (!particular.empty() && particular.front().time_ + 86400 <= currentTime) {
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
