//#include "test_runner.h"

#include <iostream>
#include <vector>
#include <exception>

using namespace std;

template <typename T> class  Deque {
public:
    Deque() : sizeDeque(0){};
    
    int Size() const {
        return sizeDeque;
    }
    
    bool Empty() const {
        return sizeDeque == 0;
    }
    
    T& operator[](size_t index) {
        if (index >= pushFrontVector.size()) {
            return pushBackVector[static_cast<int>(index) - pushFrontVector.size()];
        } else {
            return pushFrontVector[pushFrontVector.size() - 1 - index];
        }
    }
    
    const T& operator[](size_t index) const {
        if (index >= pushFrontVector.size()) {
            return pushBackVector[static_cast<int>(index) - pushFrontVector.size()];
        } else {
            return pushFrontVector[pushFrontVector.size() - 1 - index];
        }
    }
    
    T& At(size_t index) {
        if (index >= static_cast<size_t>(sizeDeque)) {
            throw out_of_range("error");
        } else {
            if (index >= pushFrontVector.size()) {
                return pushBackVector[static_cast<int>(index) - pushFrontVector.size()];
            } else {
                return pushFrontVector[pushFrontVector.size() - 1 - index];
            }
        }
    }
    
    const T& At(size_t index) const {
        if (index >= static_cast<size_t>(sizeDeque)) {
            throw out_of_range("error");
        } else {
            if (index >= pushFrontVector.size()) {
                return pushBackVector[static_cast<int>(index) - pushFrontVector.size()];
            } else {
                return pushFrontVector[pushFrontVector.size() - 1 - index];
            }
        }
    }
    
    
    T& Front() {
        if (pushFrontVector.size() == 0) {
            return pushBackVector[0];
        }
        return pushFrontVector[pushFrontVector.size() - 1];
    }
    
    const T& Front() const {
        if (pushFrontVector.size() == 0) {
            return pushBackVector[0];
        }
        return pushFrontVector[pushFrontVector.size() - 1];
    }
    
    T& Back() {
        if (pushBackVector.size() == 0) {
            return pushFrontVector[0];
        }
        return pushBackVector[pushBackVector.size() - 1];
    }
    
    const T& Back() const {
        if (pushBackVector.size() == 0) {
            return pushFrontVector[0];
        }
        return pushBackVector[pushBackVector.size() - 1];
    }
    
    void PushBack(const T& additionElement) {
        sizeDeque++;
        pushBackVector.push_back(additionElement);
    }
    
    void PushFront(const T& additionElement) {
        sizeDeque++;
        pushFrontVector.push_back(additionElement);
    }
    
private:
    vector<T> pushFrontVector;
    vector<T> pushBackVector;
    int sizeDeque;
};

/*
void TestTable() {
    Deque<int> my;
    my.PushFront(3);
    my.PushBack(4);
    my.PushBack(9);
    my.PushFront(11);
    ASSERT_EQUAL(my.Front(), 11);
    ASSERT_EQUAL(my.Back(), 9);
}
*/
int main() {
    /*TestRunner tr;
    RUN_TEST(tr, TestTable); */
    return 0;
}
