// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
#include "expensetracker.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

// TODO: Write a ExpenseTracker constructor that takes no parameters and constructs an
//  an ExpenseTracker object
//
// Example:
//  ExpenseTracker etObj{};

// TODO: Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories the ExpenseTracker contains.
//
// Example:
//  ExpenseTracker etObj{};
//  auto size = etObj.size();

// TODO: Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");

// TODO: Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged (see also Category::addItem) and then returns false. Throw a
//  std::runtime_error if the Category object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj{"categoryIdent"};
//  etObj.addCategory(cObj);

// TODO: Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category with that identifier. If no Category
//  exists, throw an appropriate exception.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  auto cObj = etObj.getCategory("categoryIdent");

// TODO: Write a function, deleteCategory, that takes one parameter, a Category
//  identifier, and deletes that catagory from the container, and returns true
//  if the Category was deleted. If no Category exists, throw an appropriate
//  exception.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  etObj.deleteCategory("categoryIdent");

// TODO: Write a function, getSum, that returns the sum of all Category expense
// sums. This consists of the sum of all individual item amounts across all categories.
// If no categories or no items exists return 0.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj = etObj.newCategory("categoryIdent");
//  Category cObj2 = etObj.newCategory("categoryIdent2");
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  cObj2.newItem("newItemName3", "Description", "3.0", Date(2024,12,25));
//  cObj2.newItem("newItemName4", "Description", "4.0", Date(2024,12,25));
//  auto sum = ejObj.getSum() // 10.0

// TODO: Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this ExpenseTracker. If the file does not open throw
//  an appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same identifier, or two expense items with the same
//  identifier within the same category, you may choose whichever category/item is parsed
//  by the nlohmann json library. The json spec on duplicate keys is undefined, so
//  you can default to the behaviour of the nlohmann json library.
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
// {
//   "Studies": {
//     "1": {
//       "amount": 999.99,
//       "date": "2024-12-25",
//       "description": "Laptop",
//       "tags": [
//         "computer",
//         "programming",
//         "uni"
//       ]
//     },
//     ...
//   },
//   "Travel": {
//     "3": {
//       "amount": 164.0,
//       "date": "2024-12-30",
//       "description": "Bus Pass",
//       "tags": [
//         "bus",
//         "uni"
//       ]
//     }
//   },
//   ...
// }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");

// TODO: Write a function, save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the ExpenseTracker object
//  as JSON.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");
//  ...
//  etObj.save("database.json");

// TODO: Write an == operator overload for the ExpenseTracker class, such that two
//  ExpenseTracker objects are equal only if they have the exact same data.
//
// Example:
//  ExpenseTracker etObj1{};
//  ExpenseTracker etObj2{};
//  if(etObj1 == etObj2) {
//    ...
//  }

// TODO: Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the ExpenseTracker.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  ExpenseTracker etObj{};
//  std::string s = etObj.str();
