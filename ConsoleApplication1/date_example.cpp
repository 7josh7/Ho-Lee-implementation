//#include "date.h"
//#include <iostream>
//
//int main() {
//    // Create two date objects
//    date date1(15, 3, 2023);
//    date date2(31, 12, 2023);
//
//    // Check if date1 is valid
//    if (date1.valid()) {
//        std::cout << "Date1 is valid." << std::endl;
//    }
//    else {
//        std::cout << "Date1 is not valid." << std::endl;
//    }
//
//    // Compare two dates
//    if (date1 < date2) {
//        std::cout << "Date1 is earlier than Date2." << std::endl;
//    }
//
//    // Display the years until date2 from date1 using the 30/360 convention
//    std::cout << "Years until Date2 from Date1 (30/360): "
//        << date1.years_until(date2, DayCountConvention::Thirty360) << std::endl;
//
//    // Increment and decrement operations
//    date tomorrow = date1++;
//    std::cout << "Tomorrow's date from Date1: " << tomorrow.day() << "/" << tomorrow.month() << "/" << tomorrow.year() << std::endl;
//
//    date yesterday = --date1;
//    std::cout << "Yesterday's date from Date1: " << yesterday.day() << "/" << yesterday.month() << "/" << yesterday.year() << std::endl;
//
//    // Using next_date and previous_date functions
//    date nextDay = date::next_date(date1);
//    std::cout << "Next day from Date1 using function: " << nextDay.day() << "/" << nextDay.month() << "/" << nextDay.year() << std::endl;
//
//    date prevDay = date::previous_date(date1);
//    std::cout << "Previous day from Date1 using function: " << prevDay.day() << "/" << prevDay.month() << "/" << prevDay.year() << std::endl;
//
//    return 0;
//}
//
