#include <array>
#include <cstddef>
#include <iostream>
#include <list>
#include <ostream>
#include <utility>

/*
Open Addressing:
 - slower when load factor closer to 1
 - have to resize
 - better for cache locality

Chaining
 - simpler
 - better when size of input is not known

 Constraitns and Assumptions
 - For simplicity, are the keys integers only? Yes
 - For collision resolution, can we use chaining? Yes
 - Do we have to worry about load factors? No
 - Can we assume inputs are valid or do we have to validate them? Assume they're valid
 - Can we assume this fits memory? Yes
*/

class HashMap
{
  private:
	static const int buckets{ 10 };
	std::array<std::list<std::pair<int, std::string>>, buckets> table;
	size_t elements;

  public:
	bool isEmpty() const;
	int hashFunction(const int key);
	void insert(const int key, const std::string value);
	void remove(const int key);
	std::string getItem(const int key);

	friend std::ostream& operator<<(std::ostream& out, const HashMap& map); // For printing table with primitive types
};

bool HashMap::isEmpty() const
{
	return elements == 0;
}

int HashMap::hashFunction(int key){
	return key % table.size();
}

void HashMap::insert(const int key, const std::string value)
{
	int hashIndex = hashFunction(key);
	auto& bucket = table[hashIndex];
	if (bucket.empty()){
		bucket.emplace_back(key, value);
	}

	for (auto it=bucket.begin(); it!=bucket.end(); it++){
		if (it->first == key){
			it->second = value;
			std::cout << "Key: " << key << " replaced.";
			return;
		}
	}
	bucket.emplace_back(key, value);
	elements++;
}

void HashMap::remove(const int key)
{
	int hashIndex = hashFunction(key);
	auto& bucket = table[hashIndex];
	if (bucket.empty()){
		std::cout << "Failed to remove " << key << " does not exist!";
		return;
	}

	for (auto it=bucket.begin(); it!=bucket.end(); it++){
		if (it->first == key){
			bucket.erase(it);
			elements--;
			std::cout << "Key: " << key << " removed.";
			return;
		}
	}
	std::cout << "Failed to remove " << key << " does not exist!";
}


std::string HashMap::getItem(const int key)
{
	int hashIndex = hashFunction(key);
	auto& bucket = table[hashIndex];
	if (bucket.empty()){
		std::cout << key << " does not exist!";
		return "";
	} 

	for (auto it=bucket.begin(); it!=bucket.end(); it++){
		if (it->first == key){
			return it->second;
		}
	}
	std::cout << key << " does not exist!";
	return "";
}

std::ostream& operator<<(std::ostream& out, const HashMap& map)
{
	for (size_t i = 0; i < HashMap::buckets; ++i)
	{
		out << "Bucket " << i << ": ";
		for (const auto& pair : map.table[i])
		{
			out << "[" << pair.first << ": " << pair.second << "] ";
		}
		out << "\n";
	}
	return out;
}

int main() {
    HashMap phoneBook;

    // Test Case 1: Insertion and Retrieval
    phoneBook.insert(123456789, "Alice Smith");
    phoneBook.insert(987654321, "Bob Johnson");
    phoneBook.insert(5551212, "Charlie Brown");

    std::cout << "Phone Book after insertions:\n" << phoneBook << std::endl;

    std::cout << "Phone number 123456789: " << phoneBook.getItem(123456789) << std::endl;
    std::cout << "Phone number 987654321: " << phoneBook.getItem(987654321) << std::endl;
    std::cout << "Phone number 5551212: " << phoneBook.getItem(5551212) << std::endl;
    std::cout << "Phone number 111111111: " << phoneBook.getItem(111111111) << std::endl; // Test non-existent key

    // Test Case 2: Removal
    phoneBook.remove(987654321);
    std::cout << "\nPhone Book after removing Bob Johnson:\n" << phoneBook << std::endl;
    std::cout << "Phone number 987654321: " << phoneBook.getItem(987654321) << std::endl; // Should return empty string

    // Test Case 3: Empty Check
    HashMap emptyBook;
    std::cout << "\nIs emptyBook empty? " << (emptyBook.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Is phoneBook empty? " << (phoneBook.isEmpty() ? "Yes" : "No") << std::endl;

    // Test Case 4: Collisions
    phoneBook.insert(223456789, "David Lee"); // Collides with Alice Smith (same hash index)
    phoneBook.insert(323456789, "Eve Wilson"); // Also collides with Alice Smith
    std::cout << "\nPhone Book after adding collisions:\n" << phoneBook << std::endl;
    std::cout << "Phone number 223456789: " << phoneBook.getItem(223456789) << std::endl;
    std::cout << "Phone number 323456789: " << phoneBook.getItem(323456789) << std::endl;

    //Test case 5: Remove non-existing key
    phoneBook.remove(111111111);
    std::cout << "\nPhone Book after removing non existing key:\n" << phoneBook << std::endl;

    return 0;
}