// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "date.h"

// TODO: write a default constructor that sets the member variables to today's
// date. 
// Example:
//  Date d = Date();

// TODO: write a constructor that takes a three integer argument and sets the
// appropriate member variables (year, month, day). If the date is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");

// TODO: write a constructor that takes a string argument in "YYYY-MM-DD" format
// and sets the appropriate member variables (year, month, day). If dateString
// is not valid throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");

// TODO: Write a function, str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  
// Example:
//  Date d = Date(2024,12,25);
//  std::cout << d.str() << std::endl;

// TODO:: create a function setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters.
// Example:
//  Date d = Date();
//  d.setDate(2024, 12, 25);

// TODO:: Write a function, getYear, that takes no parameters and returns year
// member variable
// Example:
//  Date d = Date();
//  auto year = d.getYear();

// TODO: Write a function, getMonth, that takes no parameters and returns month
// member variable
// Example:
//  Date d = Date();
//  auto month = d.getMonth();

// TODO: Write a function, getDay, that takes no parameters and returns day
// member variable
// Example:
//  Date d = Date();
//  auto day = d.getDay();

// TODO: Write an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date(2024, 12, 25);
//  if (d1 == d2) {
//    ...
//  }

// TODO: Write an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. 
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date();
//  Date d2 = Date(2024, 12, 31);
//   if (d1 < d2) {
//     ...
//   }
