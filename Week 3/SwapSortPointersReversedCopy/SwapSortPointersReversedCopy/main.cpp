#include "test_runner.h"

#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
void Swap(T* first, T* second) {
    T temp = *first;
    *first = *second;
    *second = temp;
}

template <typename T>
void SortPointers(vector<T*>& pointers) {
    for (int i = 0; i < pointers.size() - 1; ++i) {
        for (int j = 0; j < pointers.size() - i - 1; ++j) {
            if (*pointers[j] > *pointers[j+ 1]) {
                Swap(pointers[j], pointers[j + 1]);
            }
        }
    }
}

template <typename T>
void ReversedCopy(T* source, size_t count, T* destination) {
  auto source_begin = source;
  auto source_end = source + count;
  auto dest_begin = destination;

  for (size_t i = 0; i < count; i++) {
    T* source_curr = source_end - i - 1;
    T* dest_curr = dest_begin + i;

    if (dest_curr < source_begin || dest_curr >= source_end) {
      *dest_curr = *source_curr;
    } else if (dest_curr < source_curr) {
      Swap(source_curr, dest_curr);
    }
  }
}

void TestSwap() {
  int a = 1;
  int b = 2;
  Swap(&a, &b);
  ASSERT_EQUAL(a, 2);
  ASSERT_EQUAL(b, 1);

  string h = "world";
  string w = "hello";
  Swap(&h, &w);
  ASSERT_EQUAL(h, "hello");
  ASSERT_EQUAL(w, "world");
}

void TestSortPointers() {
  int one = 1;
  int two = 2;
  int three = 3;

  vector<int*> pointers;
  pointers.push_back(&two);
  pointers.push_back(&three);
  pointers.push_back(&one);

  SortPointers(pointers);

  ASSERT_EQUAL(pointers.size(), 3u);
  ASSERT_EQUAL(*pointers[0], 1);
  ASSERT_EQUAL(*pointers[1], 2);
  ASSERT_EQUAL(*pointers[2], 3);
}

void TestReverseCopy() {
  const size_t count = 7;

  int* source = new int[count];
  int* dest = new int[count];

  for (size_t i = 0; i < count; ++i) {
    source[i] = i + 1;
  }
  ReversedCopy(source, count, dest);
  const vector<int> expected1 = {7, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(dest, dest + count), expected1);

  // ÐžÐ±Ð»Ð°ÑÑ‚Ð¸ Ð¿Ð°Ð¼ÑÑ‚Ð¸ Ð¼Ð¾Ð³ÑƒÑ‚ Ð¿ÐµÑ€ÐµÐºÑ€Ñ‹Ð²Ð°Ñ‚ÑŒÑÑ
  ReversedCopy(source, count - 1, source + 1);
  const vector<int> expected2 = {1, 6, 5, 4, 3, 2, 1};
  ASSERT_EQUAL(vector<int>(source, source + count), expected2);

  delete[] dest;
  delete[] source;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSwap);
  RUN_TEST(tr, TestSortPointers);
  RUN_TEST(tr, TestReverseCopy);
  return 0;
}
