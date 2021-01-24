#include <iostream>
#include <map>
#include <set>

using namespace std;

class RouteHandler {
public:
    void Add(int one, int two) {
        routesInfo[one].insert(two);
        routesInfo[two].insert(one);
    }
    
    int Go(int firstStop, int secondStop) {
        int result = abs(firstStop - secondStop);
         if (routesInfo[firstStop].count(secondStop) == 1) {
            return 0;
        } else {
            auto it = routesInfo[firstStop].lower_bound(secondStop);
            if (it != routesInfo[firstStop].end()) {
                result = min(result, abs(secondStop -  *it));
            }
            if (it != routesInfo[firstStop].begin()) {
                result = min(result, abs(secondStop -  *prev(it)));
            }
            return result;
        }
        
        return 1;
    }
private:
    map<int, set<int>> routesInfo;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int numberOfCommands;
    cin >> numberOfCommands;
    
    RouteHandler myRouteHandler;
    
    for(int i = 0; i < numberOfCommands; ++i) {
        string command;
        int first, second;
        cin >> command;
        if (command == "ADD") {
            cin >> first >> second;
            myRouteHandler.Add(first, second);
        }
        if (command == "GO") {
            cin >> first >> second;
            cout << myRouteHandler.Go(first, second) << endl;
        }
    }
    return 0;
}
