/*
 * Trade.h
 *
 *  Created on: 29/10/2018
 *      Author: jamil
 */

#ifndef TRADE_TRADE_H_
#define TRADE_TRADE_H_

#include <string>

#include "../utils/utility_functions.h"

class Trade {
public:

	Trade():
		matchedQuantity(0),
		matchedPrice(0.0) {
	}

	Trade(std::string buyer,
			std::string seller,
			std::string instrument,
			uint32_t matchedQuantity,
			double matchedPrice):
				buyerid(buyer),
				sellerid(seller),
				instrument(instrument),
				matchedQuantity(matchedQuantity),
				matchedPrice(matchedPrice) {
	}

	std::string to_string() const {
		return buyerid + ":" + sellerid + ":" + instrument + ":"
				+ std::to_string(matchedQuantity) + ":" + std::to_string(matchedPrice);
	}

	friend std::ostream& operator<<(std::ostream& os, const Trade& trade) {
		os<<trade.to_string();
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Trade &trade)
		{
		std::string line;
			is>>line;

			auto split = split_str(line, ':');

			if (split.size()!=5)
			{
				throw std::runtime_error("Invalid order format");
			}

			trade.buyerid = split[0];
			trade.sellerid = split[1];
			trade.instrument = split[2];
			trade.matchedQuantity = std::stoi(split[3].c_str());
			trade.matchedPrice = std::stod(split[4].c_str());

			return is;
		}

	bool operator == (const Trade& trade)
			{
				return (
						buyerid == trade.buyerid &&
						sellerid == trade.sellerid &&
						instrument == trade.instrument &&
						matchedQuantity == trade.matchedQuantity &&
						matchedPrice == trade.matchedPrice
				);
			}

	bool operator != (const Trade& trade)
		{
			return ! (*this == trade);
		}

private:
	std::string buyerid;
	std::string sellerid;
	std::string instrument;
	uint32_t matchedQuantity;
	double matchedPrice;
};


#endif /* TRADE_TRADE_H_ */
