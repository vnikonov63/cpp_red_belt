#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values)  // Ð ÐµÐ°Ð»Ð¸Ð·ÑƒÐ¹Ñ‚Ðµ ÑÑ‚Ð¾Ñ‚ Ð¼Ð°ÐºÑ€Ð¾Ñ, Ð° Ñ‚Ð°ÐºÐ¶Ðµ Ð½ÐµÐ¾Ð±Ñ…Ð¾Ð´Ð¸Ð¼Ñ‹Ðµ Ð¾Ð¿ÐµÑ€Ð°Ñ‚Ð¾Ñ€Ñ‹ Ð´Ð»Ñ ÐºÐ»Ð°ÑÑÐ¾Ð² Date Ð¸ Time

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
