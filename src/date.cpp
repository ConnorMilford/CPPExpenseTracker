// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
#include <chrono>
#include <string>
#include <sstream>
#include <regex>
#include <string>
#include <iomanip>

#include "date.h"

#define ARGUMENT_ERROR_MSG "Invalid argument from "


// Destructor
Date::~Date(){
    // :-)
}

// A default constructor that sets the member variables to today's
// date. 
// Example:
//  Date d = Date();
Date::Date() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm* tmStruct = std::localtime(&now_t);

    this->year = tmStruct->tm_year + 1900;
    this->month = tmStruct->tm_mon + 1;
    this->day = tmStruct->tm_mday;
}




// A constructor that takes a three integer argument and sets the
// appropriate member variables (year, month, day). If the date is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");

Date::Date (unsigned int year, unsigned int month, unsigned int day) : year(year), month(month), day(day) { 
    // :-)
}


//  A constructor that takes a string argument in "YYYY-MM-DD" format
// and sets the appropriate member variables (year, month, day). If dateString
// is not valid throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");


// TODO: this constructor passes all tests, but does not consider:
// Leap years, Num days in month. e.g. 2025-02-31 is valid. 

Date::Date(std::string date) {
    std::stringstream dateStream(date);
    std::string temp;

    char delimiter = '-';

    //regex to detect format YYYY-MM-DD & 10 chars
    if (!std::regex_match(date, std::regex(R"(\d{4}-\d{2}-\d{2})"))){
        throw std::invalid_argument("Invalid format should be DDDD-MM-YY");
    } 

    if (getline(dateStream, temp, delimiter)){
        this->year = std::stoi(temp);
    } else {
        throw std::invalid_argument(std::string(ARGUMENT_ERROR_MSG) + "year: " + std::to_string(year));
    }

    if (getline(dateStream, temp, delimiter)){
        this->month = std::stoi(temp);
    } else {
        throw std::invalid_argument(std::string(ARGUMENT_ERROR_MSG) + "month: " + std::to_string(month));
    }

    if (getline(dateStream, temp, delimiter)){
        this->day = std::stoi(temp);
    } else {
        throw std::invalid_argument(std::string(ARGUMENT_ERROR_MSG) + "day: " + std::to_string(day));
    }

    if (month < 1 || month > 12) {
        throw std::invalid_argument(std::string(ARGUMENT_ERROR_MSG) + "Invalid month." + std::to_string(month));
    }
    
    
    

}

// function str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  
// Example:
//  Date d = Date(2024,12,25);
//  std::cout << d.str() << std::endl;


std::string Date::str() const {
        std::ostringstream oss;
        oss << year << "-" 
        << std::setfill('0') << std::setw(2) << month << "-" 
        << std::setfill('0') << std::setw(2) << day;
        return oss.str();
    }
    

// function setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters.
// Example:
//  Date d = Date();
//  d.setDate(2024, 12, 25);

// TODO: again this function  similarly to the constructor
// does not check for leap years, valid days in month
void Date::setDate(unsigned int year, unsigned int month, unsigned int day) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument(std::string(ARGUMENT_ERROR_MSG) + "Invalid month.");
    }
    this->year = year;
    this->month = month;
    this->day = day;
}

    


// Write a function, getYear, that takes no parameters and returns year
// member variable
// Example:
//  Date d = Date();
//  auto year = d.getYear();

unsigned int Date::getYear() const {
    return this->year;
}

// a function, getMonth, that takes no parameters and returns month
// member variable
// Example:
//  Date d = Date();
//  auto month = d.getMonth();

unsigned int Date::getMonth() const {
    return this->month;
}

// a function, getDay, that takes no parameters and returns day
// member variable
// Example:
//  Date d = Date();
//  auto day = d.getDay();

unsigned int Date::getDay() const {
    return this->day;
}

// an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date(2024, 12, 25);
//  if (d1 == d2) {
//    ...
//  }

bool operator== (const Date &lhs, const Date &rhs) {
    if (lhs.getYear() == rhs.getYear() &&
        lhs.getMonth() == rhs.getMonth() &&
        lhs.getDay() == rhs.getDay()) {
            return true;
        }
        return false;
}

// an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. 
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date();
//  Date d2 = Date(2024, 12, 31);
//   if (d1 < d2) {
//     ...
//   }

// checking if lhs before rhs
bool operator<(const Date &lhs, const Date &rhs) {

    if (lhs.getYear() < rhs.getYear()) {
        return true;
    } else if (lhs.getYear() > rhs.getYear()) {
        return false;
    }

    if (lhs.getMonth() < rhs.getMonth()) {
        return true;
    } else if (lhs.getMonth() > rhs.getMonth()) {
        return false;
    }

    return lhs.getDay() < rhs.getDay();
}

bool Date::operator!=(const Date& other) const {
        return this->day != other.day || this->month != other.month || this->year != other.year;
    }
