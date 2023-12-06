// ====================================================
// Your name: Jeremiah Shue
// Complier:  g++
// File type: htable.cpp implementation file
//=====================================================
#include <fstream>
#include "htable.h"

/**
 * @brief Constructor to create an empty hash table
 * @param size The number of buckets in the hash table
 */
HashTable::HashTable(int size)
{
	table_size = size;
	table.resize(size);
}

/**
 * @brief Destructor
 */
HashTable::~HashTable() {}
/**
 * @brief  Get the hash key of the order
 * @return int The hashed index of the order ID
 */
int HashTable::hash(int id)
{
	return id % table_size;
}

/**
 * @brief Find an order by its ID
 * @param id: the order ID
 * @param order: the reference to stored found order (if found)
 * @return true if found, false otherwise
 */
bool HashTable::findOrder(int id, Order &order)
{
	int orderHash = hash(id);
	int pos = table.at(orderHash).search(order);
	if (pos != -1)
	{
		order = table.at(orderHash).getNode(pos)->val;
		return true;
	}
	return false;
}

/**
 * @brief Insert an order into the hash table. The order ID is used as the key.
 * A order is inserted only if its ID isn't in the table
 * @return true if inserted, false otherwise
 */
bool HashTable::insertOrder(const Order &order)
{
	int orderHash = hash(order.id);
	int pos = table[orderHash].search(order);
	if (pos == -1)
	{
		table[orderHash].addRear(order);
		return true;
	}
	return false;
}

/**
 * @brief Load orders from a file
 *
 * @param file_name The name of the file to load
 */
void HashTable::fillTable(string file_name)
{
	// Open the file to read
	ifstream fin;
	fin.open(file_name.c_str());
	if (!fin)
	{
		cout << "Error opening file " << file_name << endl;
		return;
	}
	int id;
	string name;
	float amount;

	while (fin >> id >> name >> amount)
	{
		insertOrder(Order{id, name, amount});
	}
	fin.close();
}

//
/**
 * @brief Remove an order from the hash table. The order ID is used as the key.
 *        A order is removed only if its ID is in the table
 *
 * @param id
 * @return true if the order is removed, false otherwise
 */
bool HashTable::removeOrder(int id)
{
	int orderHash = hash(id);
	// variant on internal LinkedList search logic
	// to search by id in particular.
	Node *ptr = table[orderHash].getFront();
	int pos = 0;
	while (ptr != nullptr)
	{
		if (ptr->val.id == id)
		{
			// LinkedList wants a reference to return deleted data
			// we don't care about deleted data though.
			auto garbage = Order{0, "", 0};
			return table[orderHash].deleteAt(pos, garbage);
		};
		ptr = ptr->next;
		pos++;
	}
	return false;
}

// Display the hash table
void HashTable::printTable()
{
	for (int i = 0; i < table_size; i++)
	{
		cout << "Bucket " << i << ": ";
		table[i].displayAll();
	}
}

/**
 * @brief Get the total number of orders in the hash table
 *
 * @return int The number of orders in the hash table
 */
int HashTable::numOrders() const
{
	int orderCount = 0;
	for (auto it = table.cbegin(); it != table.cend(); it++)
	{
		orderCount += it->length();
	}
	return orderCount;
}

// Update the order in the hash table
/**
 * @brief Update a order in the hash table. The order ID is used as the key.
 * 		  A order is updated only if its ID is in the table
 * @param order the new order that is used to update the old order
 * @return true if the order is updated, false otherwise
 */
bool HashTable::updateOrder(const Order &order)
{
	int orderHash = hash(order.id);
	// find the position of the order in its bucket list
	int pos = table.at(orderHash).search(order);
	if (pos != -1)
	{
		Node *node = table.at(orderHash).getNode(pos);
		node->val.amount = order.amount;
		node->val.name = order.name;
		return true;
	}
	return false;
}

/**
 * @brief Rehash the hash table to a new size. The orders are rehashed to the new table
 *
 * @param new_size The new number of buckets in the hash table
 */
void HashTable::rehash(int new_size)
{

	if (new_size == table_size)
	{
		return;
	}
	vector<LinkedList> newTable;
	newTable.resize(new_size);
	for (auto it = table.cbegin(); it != table.cend(); it++)
	{
		for (int i = 0; i < it->length(); i++)
		{

			Node *node = it->getNode(i);
			int orderHash = node->val.id % new_size;
			int pos = newTable.at(orderHash).search(node->val);
			if (pos == -1)
			{
				newTable.at(orderHash).addRear(node->val);
			}
		}
	}
	table_size = new_size;
	table = newTable;
}
