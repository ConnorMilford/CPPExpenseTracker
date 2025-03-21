// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <2214497 - Connor Milford>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// -----------------------------------------------------

#ifndef DATE_H

#define DATE_H

class Date {
    private:
        unsigned int year;
        unsigned int month;
        unsigned int day;
    public:
        Date(unsigned int year, unsigned int month, unsigned int day);
        Date(std::string date);
        Date();
        ~Date();    

        unsigned int getYear() const;
        unsigned int getMonth() const;
        unsigned int getDay() const;

        //friend std::ostream &operator<<(std::ostream &os, const Date& date);

        friend bool operator==(const Date &lhs, const Date &rhs);

        friend bool operator<(const Date &lhs, const Date &rhs);


    };



#endif // DATE_H
