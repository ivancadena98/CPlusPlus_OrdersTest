# CPlusPlus_OrdersTest
+Read Me:
 - Task is to implement an in-memory cache of order objects that supports adding new orders, removing existing orders and matching buy and sell orders. 
- On "order" is a request to buy or sell a financial security (eg. bond, stock, commodity, etc.)
- Each order is uniquely identified by an order id
- Each security has a different security id 
- Order matching occurs for orders with the same security id, different side (buy or sell), and different company (company of person who requested the order)
 - Provide an implementation for the OrderCacheInterface class in OrderCache.h 
 - An Order class is provided for you:
 - This class holds basic order info
 - Do not remove the provided member variables and methods in the Order class
 - You may add additional members if you like
 - For your implementation of OrderCacheInterface:
 - Write a class that derives OrderCacheInterface
 - Choose appropriate data structure(s) to hold Order objects and any additional data you'd like 
 - Implement the following methods (do not change their signatures)
 - addOrder()
 - cancelOrder()
- cancelOrdersForUser()
- cancelOrdersForSecIdWithMinimumQty()
 - getMatchingSizeForSecurity()
 - getAllOrders()
 - Add any additional methods and variables you'd like to your class
 
 # Order matching rules for getMatchingSizeForSecurity()
 - Your implementation of getMatchingSizeForSecurity() should give the total qty that can match for a security id
 - Can only match orders with the same security id
 - Can only match a Buy order with a Sell order
 - Buy order can match against multiple Sell orders (and vice versa)
 - eg a security id "ABCD" has 
    Buy order with qty 10000
    Sell order with qty 2000
   Sell order with qty 1000 
 - security id "ABCD" has a total match of 3000. The Buy order's qty is big enough to match against both Sell orders and still has 7000 remaining
 - Any order quantity already allocated to a match cannot be reused as a match against a differnt order (eg the qty 3000 matched above for security id "ABCD" example)
 - Some orders may not match entirely or at all 
 - Users in the same company cannot match against each other

