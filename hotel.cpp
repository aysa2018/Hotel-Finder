
#include <sstream>
#include<iostream>
#include<string>
#include <iomanip>
#include "hotel.h"
using namespace std;



// Constructor
Hotel::Hotel(string name, string city, string stars, string price, string country, string address): name(name), city(city), stars(stars), price(price), country(country), address(address) {}

//the getter method to get access to private member name
string Hotel::getName() {
    return name;
}
//the getter method to get access to private member city
string Hotel::getCity() {
    return city;
}
//the getter method to get access to private member star
string Hotel::getStars() {
    return stars;
}
//the getter method to get access to private member price
string Hotel::getPrice() {
    return price;
}
//the getter method to get access to private member country
string Hotel::getCountry() {
    return country;
}
//the getter method to get access to private member address
string Hotel::getAddress() {
    return address;
}



/// Converts the hotel details to a single string (CSV format)
string Hotel::toString() {
    stringstream ss;
    ss << name << "," << city << "," << stars << "," << price << "," << country << "," << address;
    return ss.str();
}

// Prints hotel details in a formatted manner
void Hotel::print() {
    cout << "Hotel Name: " << name << "\n"
         << "City: " << city << "\n"
         << "Stars: " << stars << "\n"
         << "Price: " << price << "\n"
         << "Country: " << country << "\n"
         << "Address: " << address << "\n"
         << endl;
}






