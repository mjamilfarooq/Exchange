/*
 * IOrderPublisher.h
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */

#ifndef IORDERPUBLISHER_H_
#define IORDERPUBLISHER_H_

#include <list>
#include <algorithm>

#include "IOrderSubscriber.h"
#include "Order.h"

using namespace std;

class AbstractOrderPublisher {
public:

	AbstractOrderPublisher():
		notifyEnable(false)
	{}

	void disableNotify()
	{
		notifyEnable = false;
	}

	void enableNotify()
	{
		notifyEnable = true;
	}

	bool isNotifyEnable()
	{
		return notifyEnable;
	}

	// register subscriber
	virtual void subscribe(IOrderSubscriber *subscriber)
	{
		subscribers.push_back(subscriber);
	}

	virtual void unsubscribe(IOrderSubscriber *subscriber)
	{
		subscribers.remove(subscriber);
	}

	//publish order to all subscriber
	virtual void publish(Order order)
	{
		if (notifyEnable)
		{
			for_each(subscribers.begin(),
					subscribers.end(),
					[&order](IOrderSubscriber *subscriber){
				if (subscriber!=nullptr)
					subscriber->update(order);
			});
		}
	};

	virtual ~AbstractOrderPublisher(){}

	//pure virtual method to be implement run loop
	virtual void run() = 0;
private:
	list<IOrderSubscriber*> subscribers;
	bool notifyEnable;
};


#endif /* IORDERPUBLISHER_H_ */
