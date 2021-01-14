#include "test_runner.h"

#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Table {
public:
    Table(size_t nRowsValue, size_t nColsValue) :
                            nRows(nRowsValue),
                            nCols(nColsValue),
                            table(nRowsValue, vector<T>(nColsValue, T())){}

    void Resize(size_t newRowsValue, size_t newColumnValue) {
        table.resize(static_cast<int>(newRowsValue), vector<T>(nCols));
        nRows = newRowsValue;
        for (auto& row : table) {
            row.resize(static_cast<int>(newColumnValue));
        }
        nCols = newColumnValue;
    }
    
    pair<size_t, size_t> Size() const {
        if (nRows == 0 || nCols == 0) {
            return {0, 0};
        }
        return {nRows, nCols};
    }
    
    vector<T>& operator[](size_t interestValue) {
        return table[interestValue];
    }
    
    const vector<T>& operator[] (size_t interestValue) const {
        return table[interestValue];
    }
    
    
private:
    size_t nRows;
    size_t nCols;
    vector<vector<T>> table;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
