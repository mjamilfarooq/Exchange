/*
 * Order.h
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <string>
#include <ostream>
#include <exception>
#include <chrono>

#include "../errors/messages.h"
#include "../utils/utility_functions.h"

using namespace std;

class Order
{
public:
	Order():
		id(""),
		instrument(""),
		quantity(0),
		limit_price(0.0)
	{
	}

	Order(string id,
			string instrument,
			int32_t quantity,
			double limit_price):
				id(id),
				instrument(instrument),
				quantity(quantity),
				limit_price(limit_price)
	{

	}

	//initializer when quantity and limit price is string
	Order(string id,
			string instrument,
			string quantity,
			string limit_price):
				id(id),
				instrument(instrument),
				quantity(stoi(quantity.c_str())),
				limit_price(stod(limit_price.c_str()))
	{

	}

	bool isValid()
	{
		return (id!=""&&instrument!=""&&quantity!=0&&limit_price>0.0);
	}

	string to_string()
	{
		return id+":"+instrument+":"+std::to_string(quantity)+":"+std::to_string(limit_price);
	}

	friend ostream& operator<<(ostream& os, const Order& order)
	{
		os<<order.id<<":"<<order.instrument<<":"<<order.quantity<<":"<<order.limit_price<<endl;
		return os;
	}

	friend istream& operator>>(istream& is, Order &order)
	{
		string line;
		is>>line;

		auto split = split_str(line, ':');

		if (split.size()!=4)
		{
			throw runtime_error(INVALID_ORDER_FORMAT);
		}

		order.id = split[0];
		order.instrument = split[1];
		order.quantity = stoi(split[2].c_str());
		order.limit_price = stod(split[3].c_str());

		return is;
	}

	bool operator == (const Order &order2) const
	{
		return id == order2.id &&
				instrument == order2.instrument &&
				quantity == order2.quantity &&
				limit_price == order2.limit_price;
	}

	bool operator != (const Order &order2) const
	{
		return !(*this == order2);
	}

	bool operator < (const Order &order2) const
	{

		if  (fabs(this->limit_price - order2.limit_price)<0.00001)
		{
			return this->time > order2.time;
		}
		return this->limit_price < order2.limit_price;
	}

	bool operator > (const Order &order2) const
	{
		if  (fabs(this->limit_price - order2.limit_price)<0.00001)
		{
			return this->time > order2.time;
		}
		return this->limit_price > order2.limit_price;
	}

	bool operator <= (const Order &order2) const
	{
		return this->limit_price <= order2.limit_price;
	}

	bool operator >= (const Order &order2) const
	{
		return this->limit_price >= order2.limit_price;
	}


	//setters
	void setQuantity(int quantity) const
	{
		this->quantity = quantity;
	}

	//getters

	string getID() const { return id; }
	string getInstrument() const { return instrument; }
	int getQuantity() const { return quantity; }
	double getLimitPrice() const { return limit_price; }


	void timestamp() {
		time = chrono::system_clock::now();
	}

private:
	string id;
	string instrument;
	mutable int quantity;
	double limit_price;

	//Time stamped
	chrono::system_clock::time_point time;


};




#endif /* ORDER_H_ */
