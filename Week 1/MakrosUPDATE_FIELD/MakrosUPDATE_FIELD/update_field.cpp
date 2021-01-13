#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values)  try {      \
        istringstream is(values.at(#field));            \
        is >> ticket.field;                             \
        } catch(exception& ex) {}       

bool operator == (const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

void operator >> (istringstream& is, Date& date) {
    string temp1, temp2, temp3;
    
    getline(is, temp1, '-');
    getline(is, temp2, '-');
    getline(is, temp3, '-');
    
    date.year = stoi(temp1);
    date.month = stoi(temp2);
    date.day = stoi(temp3);
}

void operator >> (istringstream& is, Time& time) {
    string temp1, temp2;
    
    getline(is, temp1, ':');
    getline(is, temp2, ':');
    
    time.hours = stoi(temp1);
    time.minutes = stoi(temp2);

}

ostream& operator << (ostream& os, const Date& date) {
    os << date.year << " " << date.month << " " << date.day;
    return os;
}

ostream& operator << (ostream& os, const Time& time) {
    os << time.hours << ":" << time.minutes;
    return os;
}


void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 Ð½Ðµ ÑÐ¾Ð´ÐµÑ€Ð¶Ð¸Ñ‚ ÐºÐ»ÑŽÑ‡ÐµÐ¹ "departure_date" Ð¸ "departure_time", Ð¿Ð¾ÑÑ‚Ð¾Ð¼Ñƒ
  // Ð·Ð½Ð°Ñ‡ÐµÐ½Ð¸Ñ ÑÑ‚Ð¸Ñ… Ð¿Ð¾Ð»ÐµÐ¹ Ð½Ðµ Ð´Ð¾Ð»Ð¶Ð½Ñ‹ Ð¸Ð·Ð¼ÐµÐ½Ð¸Ñ‚ÑŒÑÑ
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
