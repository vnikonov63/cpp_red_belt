#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (!deallocated.empty()) {
            auto temp = deallocated.front();
            allocated.insert(temp);
            deallocated.pop();
            return temp;
        } else {
            T* newest = new T();
            allocated.insert(newest);
            return newest;
        }
    }
    T* TryAllocate() {
        if (!deallocated.empty()) {
            auto temp = deallocated.front();
            allocated.insert(temp);
            deallocated.pop();
            return temp;
        } else {
            return nullptr;
        }
    }

    void Deallocate(T* object) {
        if (allocated.count(object) == 1) {
            allocated.erase(object);
            deallocated.push(object);
        } else {
            throw invalid_argument("error");
        }
    }

    ~ObjectPool() {
        for (auto el : allocated) {
            delete el;
        }
        while (!deallocated.empty()) {
            auto temp = deallocated.front();
            delete temp;
            deallocated.pop();
        }
    }

private:
    set<T*> allocated;
    queue<T*> deallocated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
