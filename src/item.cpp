#include "item.h"
#include "lib_json.hpp"
#include <algorithm>
#include <vector>

#define NOT_FOUND_MSG "Item not found."

Item::Item(std::string ident, std::string description, double amount, Date date)
    : ident(ident), description(description), amount(amount), date(date) {}

Item::~Item() {}

// Getters
std::string Item::getIdent() const { 
    return ident; 
    }

std::string Item::getDescription() const {
     return description; 
     }

double Item::getAmount() const {
     return amount; 
     }

Date Item::getDate() const {
     return date; 
}

std::vector<std::string> Item::getTags() const {
     return tags; 
     }  

// Setters
void Item::setDescription(const std::string &description) {
    this->description = description;
}

void Item::setDate(Date date) {
    this->date = date;
}

void Item::setAmount(double amount) {
    this->amount = amount;
}

// Tag operations
bool Item::addTag(std::string tag) {
    // Check if tag already exists
    if (std::find(tags.begin(), tags.end(), tag) != tags.end()) {
        return false;
    }
    tags.push_back(tag);
    return true;
}

bool Item::deleteTag(std::string tag) {
    auto it = std::find(tags.begin(), tags.end(), tag);
    if (it != tags.end()) {
        tags.erase(it);
        return true;
    }
    throw std::out_of_range(NOT_FOUND_MSG);
}

bool Item::containsTag(std::string tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

unsigned int Item::numTags() const {
    return tags.size();
}

void Item::mergeTags(const std::vector<std::string>& newTags) {
    for (const auto& tag : newTags) {
        if (!containsTag(tag)) {
            tags.push_back(tag);
        }
    }
}

// Comparison operators
bool Item::operator==(const Item &other) const {
    // Need to compare sorted tags since order doesn't matter semantically
    auto thisTags = tags;
    auto otherTags = other.tags;
    std::sort(thisTags.begin(), thisTags.end());
    std::sort(otherTags.begin(), otherTags.end());
    
    return ident == other.ident &&
           description == other.description &&
           amount == other.amount &&
           date == other.date &&
           thisTags == otherTags;
}

bool Item::operator!=(const Item &other) const {
    return !(*this == other);
}

std::string Item::str() const {
    nlohmann::json j;
    j["amount"] = amount;
    j["date"] = date.str(); 
    j["description"] = description;
    
    // Return tags in their stored order (vector preserves insertion order)
    j["tags"] = tags;
    
    return j.dump();
}

// this passes test 9!!