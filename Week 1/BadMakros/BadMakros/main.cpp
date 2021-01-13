#include "test_runner.h"

#include <ostream>
using namespace std;

#define PRINT_VALUES(out, x, y)            \
out << (x) << endl << (y) << endl          \


int main() {
    /*
    if (true) PRINT_VALUES(cout, "yes", "yes");
    else PRINT_VALUES(cout, "no", "no");
    */
    int a=2,b=3;
        if(false)PRINT_VALUES(std::cout,a,b);
    
    if (true)
                PRINT_VALUES(cout, 5, "red belt");
            else
                PRINT_VALUES(cout, 5, "no red belt");
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");
}
