/*
 * IOrderSubscriber.h
 *
 *  Created on: 26/10/2018
 *      Author: jamil
 */

#ifndef IORDERSUBSCRIBER_H_
#define IORDERSUBSCRIBER_H_

#include "Order.h"

class IOrderSubscriber {
public:

	//functor will execute by the publisher
	virtual void update(Order order) = 0;
	virtual ~IOrderSubscriber() {};

private:
};


#endif /* IORDERSUBSCRIBER_H_ */
