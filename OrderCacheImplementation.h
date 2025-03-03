#include "OrderCacheInterface.h"
#include <unordered_map>
#include <mutex>


class COrderCacheImplementation : public OrderCacheInterface
{
public:

COrderCacheImplementation() = default;
~COrderCacheImplementation() = default;
 // add order to the cache
 void addOrder(Order order);

 // remove order with this unique order id from the cache
 void cancelOrder(const std::string& orderId); 

 // remove all orders in the cache for this user
 void cancelOrdersForUser(const std::string& user); 

 // remove all orders in the cache for this security with qty >= minQty
 void cancelOrdersForSecIdWithMinimumQty(const std::string& securityId, unsigned int minQty); 

 // return the total qty that can match for the security id
unsigned int getMatchingSizeForSecurity(const std::string& securityId); 

 // return all orders in cache in a vector
std::vector<Order> getAllOrders() const;

private :


std::unordered_map<std::string, Order> mOrder;
mutable std::mutex mOrderMutex; // Thread mutex for multiple threads.
};