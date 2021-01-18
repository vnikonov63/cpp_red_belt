#include "test_runner.h"

#include <string>
#include <vector>
#include <list>
#include <forward_list>
#include <numeric>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    //return find_if(first, last, pred);
    
    if (first == last) {
        return last;
    }
    //ForwardIterator answer = find_if(first, last, pred);
    // for solution commented above it is necessary to delete flag == false and put flag = true right beneath
    // the statement [if(pred(*first) == true)]
    ForwardIterator answer = first;
    bool flag = false;
    while(first != last) {
        if (pred(*first) == true) {
            if (*first > *answer || flag == false) {
                answer = first;
            }
            flag = true;
        }
        ++first;
    }
    if (flag) {
        return answer;
    } else {
        return last;
    }
}

void TestUniqueMax() {
  auto IsEven = [](int x) {
    return x % 2 == 0;
  };

  const list<int> hill{2, 4, 8, 9, 6, 4, 2};
  auto max_iterator = hill.begin();
  advance(max_iterator, 2);

  vector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  Assert(
    max_element_if(numbers.begin(), numbers.end(), IsEven) == --numbers.end(),
    "Expect the last element"
  );

  Assert(
    max_element_if(hill.begin(), hill.end(), IsEven) == max_iterator,
    "Expect the maximal even number"
  );
}

void TestSeveralMax() {
  struct IsCapitalized {
    bool operator()(const string &s) {
      return !s.empty() && isupper(s.front());
    }
  };

  const forward_list<string> text{"One", "two", "Three", "One", "Two",
    "Three", "one", "Two", "three"};
  auto max_iterator = text.begin();
  advance(max_iterator, 4);


  Assert(
    max_element_if(text.begin(), text.end(), IsCapitalized()) == max_iterator,
    "Expect the first \"Two\""
  );
}

void TestNoMax() {
  const vector<int> empty;
  const string str = "Non-empty string";
  const string str1 = "l";
  vector<int> numbers(10);
  iota(numbers.begin(), numbers.end(), 1);

  auto AlwaysTrue = [](int) {
    return true;
  };
  
  auto AlwaysFalseInt = [](int) {
        return false;
    };
    
  Assert(
    max_element_if(empty.begin(), empty.end(), AlwaysTrue) == empty.end(),
    "Expect end for empty container"
  );
    
    Assert(
      max_element_if(numbers.begin(), numbers.end(), AlwaysFalseInt) == numbers.end(),
      "Expect end for empty container"
    );

  auto AlwaysFalse = [](char) {
    return false;
  };
  Assert(
    max_element_if(str.begin(), str.end(), AlwaysFalse) == str.end(),
    "Expect end for AlwaysFalse predicate"
  );
    Assert(
      max_element_if(str1.begin(), str1.end(), AlwaysFalse) == str1.end(),
      "Expect end for AlwaysFalse predicate"
    );
}

int main() {
  TestRunner tr;
  tr.RunTest(TestUniqueMax, "TestUniqueMax");
  tr.RunTest(TestSeveralMax, "TestSeveralMax");
  tr.RunTest(TestNoMax, "TestNoMax");
  return 0;
}
