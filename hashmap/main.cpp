#include <array>
#include <list>
#include <ostream>
#include <utility>

template <typename K, typename V> class HashMap
{
  private:
	static const int buckets{ 10 };
	std::array<std::list<std::pair<K, V>>, buckets> table;

  public:
	bool isEmpty() const;
	int hashFunction();
	void insert(const K key, const V value);
	void remove(const K key);
	V& getItem(const K key);

	friend std::ostream& operator<<(std::ostream& out,
									const HashMap& map); // For printing table with primitive types
};

int main() { return 0; }
