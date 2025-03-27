// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// The root object that holds all data for 371expenses. This
// class contains Categories, which in turn hold Expense Items,
// which have a description, amount, and date
// -----------------------------------------------------


#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include <unordered_set>

#include "category.h"


class ExpenseTracker {
    private:
    std::unordered_set<Category> categories;

    public:
        ExpenseTracker() = default;
        ~ExpenseTracker() = default;

        unsigned int size();

        Category &newCategory(const std::string &ident);
        bool addCategory(Category cat);
        Category &getCategory(const std::string &ident);
        bool deleteCategory(std::string ident);

        double getSum() const;

        void load(const std::string& jsonString);
        void save(const std::string &filePath) const;

        std::string str() const;
        std::unordered_set<Category> getCategories();
};

#endif // EXPENSETRACKER_H
