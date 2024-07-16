#include "hashtable.h"
#include "hotel.h"
#include "bst.hpp"

// Constructor
HashTable::HashTable(int capacity) {
    this->buckets = new list<Entry>[capacity];
    this->size = 0;
    this->capacity = capacity;
    this->collisions = 0;
}


// Hash function to genrate hashcode
unsigned long HashTable::hashCode(string key) {
    
    unsigned long hashValue = 0;
    for (std::string::iterator it = key.begin(); it != key.end(); ++it) {
        char c = *it;
    
        hashValue = 37 * hashValue + c;
    }
    return hashValue % capacity;
}

// Insert method
void HashTable::insert(string key, Hotel* value) {
    unsigned long index = hashCode(key);//generate the hashcode
    bool found = false;//initialize the boolean as false
    
    for (list<Entry>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        Entry& entry = *it;
        if (entry.key == key) {//if the key is found
            entry.value = value; // Update existing entry
            found = true;//change the value of the boolean tot true
            break;
        }
    }

    if (!found) {//if not found
        buckets[index].push_back(Entry(key, value));//insert the entry
        size++;
        if (buckets[index].size() > 1) {
            collisions++;
        }
    }
    // Update or insert the city record into the BST
    cityRecords.insert(cityRecords.getRoot(), value->getCity(), value);
}


// Find method
Hotel* HashTable::find(string key) {
    unsigned long index = hashCode(key);
    for (list<Entry>::iterator it = buckets[index].begin(); it != buckets[index].end(); ++it) {
        Entry& entry = *it;
    
        if (entry.key == key) {//if the key is found
            return entry.value;
        }
    }
    return nullptr; // Not found
}

// FindAll method
void HashTable::findAll(string city, string stars) {
    
    list<Hotel*> hotels = cityRecords.findAll(city);//get all the hotels for the same city from the method in BST
    for (list<Hotel*>::iterator it = hotels.begin(); it != hotels.end(); ++it) {
        Hotel* hotel = *it;
        if (hotel->getStars() == stars) {
            hotel->print(); // Assuming print() is a method in the Hotel class
        }
    }
}// Erase method
void HashTable::erase(string key) {
    unsigned long index = hashCode(key);//generate the hashcode
    for (list<Entry>::iterator itr = buckets[index].begin(); itr != buckets[index].end(); ++itr) {
        Entry& entry = *itr;
    
        if (itr->key == key) {//if the key is found
            buckets[index].erase(itr);//delete the entry
            size--;//decrement the size
            return;
        }
    }
    cerr << "No such element found" << endl;
}

// getSize method
unsigned int HashTable::getSize() {
    return size;
}

// getCollisions method
unsigned int HashTable::getCollisions() {
    return collisions;
}

// Dump method
void HashTable::dump(string path) {
    ofstream file(path);
    if (!file.is_open()) {//show the error message if you cant find the file
        cerr << "Could not open file " << path << endl;
        return;
    }
    
    for (unsigned int i = 0; i < capacity; ++i) {
        for (list<Entry>::iterator itr = buckets[i].begin(); itr != buckets[i].end(); ++itr) {
            Entry& entry = *itr;

            file << entry.value->toString() << endl; //format the writing
        }
    }
    file.close();
}


// Destructor
HashTable::~HashTable() {
    for (unsigned int i = 0; i < capacity; ++i) {
        for (list<Entry>::iterator itr = buckets[i].begin(); itr != buckets[i].end(); ++itr) {
            Entry& entry = *itr;
            delete entry.value; 
        }
    }
    delete[] buckets;
}