#include "OrderCacheImplementation.h"
#include <stdexcept>
#include <iterator>
#include <algorithm>

// Functions to handle the orders using the OrderCacheInterface class with unordered map.
// Same implementation can be done using a Vector with lambda expressions, but I was not sure if
// I was allowed to modify the OrderCache.h file to overload the == operator.
// I used a unordered map to store the orders, the key is the order id and the value is the order itself.
// I tried to use a mutex to lock when adding or removing orders, but it failed with my local tests when using threads.


void COrderCacheImplementation::addOrder(Order order)
{
	std::lock_guard<std::mutex> lock(mOrderMutex);
	if (order.orderId().empty() || order.securityId().empty() || order.side().empty() || order.user().empty() || order.company().empty())
		throw std::runtime_error("Invalid order");
	else if (order.side() != "Buy" && order.side() != "Sell") {
		throw std::runtime_error("Side must be Buy or Sell");
	}
	auto it = mOrder.emplace(order.orderId(), order);
	if (!it.second)
	{
		throw std::runtime_error("Order already exists");
	}
}

void COrderCacheImplementation::cancelOrder(const std::string &orderId)
{
	std::lock_guard<std::mutex> lock(mOrderMutex);
	mOrder.erase(orderId);
}

void COrderCacheImplementation::cancelOrdersForUser(const std::string &user)
{
	std::lock_guard<std::mutex> lock(mOrderMutex);
	for (auto i = mOrder.begin(); i != mOrder.end();)
	{
		if (i->second.user() == user)
			i = mOrder.erase(i);
		else
			++i;
	}

}

void COrderCacheImplementation::cancelOrdersForSecIdWithMinimumQty(const std::string &securityId, unsigned int minQty)
{
	std::lock_guard<std::mutex> lock(mOrderMutex);
	for (auto i = mOrder.begin(); i != mOrder.end();)
	{
		if (i->second.securityId() == securityId && i->second.qty() >= minQty)
			i = mOrder.erase(i);
		else
			++i;
	}
}

unsigned int COrderCacheImplementation::getMatchingSizeForSecurity(const std::string &securityId)
{
	int qty = 0;
	int dif = 0;
	std::unordered_map<std::string, unsigned int> mOrderBuy;
	std::unordered_map<std::string, unsigned int> mOrderSell;

	std::lock_guard<std::mutex> lock(mOrderMutex);
	for (auto i = mOrder.begin(); i != mOrder.end(); ++i)
	{
		if (i->second.securityId() == securityId)
		{
			if (i->second.side() == "Buy")
				mOrderBuy[i->second.company()] += i->second.qty();
			else
				mOrderSell[i->second.company()] += i->second.qty();
		}
	}

	for (auto i = mOrderBuy.begin(); i != mOrderBuy.end(); ++i)
	{
		for (auto j = mOrderSell.begin(); j != mOrderSell.end(); ++j)
		{
			if (i->first != j->first)
			{
				dif = std::min(i->second, j->second);
				qty += dif;
				i->second -= dif;
				j->second -= dif;
			}
		}
	}
	return qty;
}

std::vector<Order> COrderCacheImplementation::getAllOrders() const
{
	std::lock_guard<std::mutex> lock(mOrderMutex);

	std::vector<Order> localOrder;
	for (auto i = mOrder.begin(); i != mOrder.end(); ++i)
	{
		localOrder.push_back(i->second);
	}
	return localOrder;
}
