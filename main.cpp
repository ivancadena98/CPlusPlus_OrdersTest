
#include <iostream>
#include "OrderCacheImplementation.h"


using namespace std;
static void printOrders(vector<Order> orders)
{
	for (Order o : orders)
	{
		cout << o.orderId() << " " << o.securityId() << " " << o.side() << " " << o.qty() << " " << o.user() << " " << o.company() << endl;
	}
}

static void AddOrder1(OrderCacheInterface *c)
{
	c->addOrder(Order("OrdId1", "SecId1", "Buy", 1000, "User1", "CompanyA"));
	c->addOrder(Order("OrdId2", "SecId2", "Sell", 3000, "User2", "CompanyB"));
	c->addOrder(Order("OrdId3", "SecId1", "Sell", 500, "User3", "CompanyA"));
	c->addOrder(Order("OrdId4", "SecId2", "Buy", 600, "User4", "CompanyC"));
	c->addOrder(Order("OrdId5", "SecId2", "Buy", 100, "User5", "CompanyB"));
	c->addOrder(Order("OrdId6", "SecId3", "Buy", 1000, "User6", "CompanyD"));
	c->addOrder(Order("OrdId7", "SecId2", "Buy", 2000, "User7", "CompanyE"));
	c->addOrder(Order("OrdId8", "SecId2", "Sell", 5000, "User8", "CompanyE"));

	int q = c->getMatchingSizeForSecurity("SecId1");
	int q2 = c->getMatchingSizeForSecurity("SecId2");
	int q3 = c->getMatchingSizeForSecurity("SecId3");
	cout << q << endl;
	cout << q2 << endl;
	cout << q3 << endl;
}
static void AddOrder2(OrderCacheInterface *c)
{
	c->addOrder(Order("OrdId1", "SecId1", "Sell", 100, "User10", "Company2"));
	c->addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User8", "Company2"));
	c->addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User13", "Company2"));
	c->addOrder(Order("OrdId4", "SecId2", "Sell", 400, "User12", "Company2"));
	c->addOrder(Order("OrdId5", "SecId3", "Sell", 500, "User7", "Company2"));
	c->addOrder(Order("OrdId6", "SecId3", "Buy", 600, "User3", "Company1"));
	c->addOrder(Order("OrdId7", "SecId1", "Sell", 700, "User10", "Company2"));
	c->addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
	c->addOrder(Order("OrdId9", "SecId2", "Buy", 900, "User6", "Company2"));
	c->addOrder(Order("OrdId10", "SecId2", "Sell", 1000, "User5", "Company1"));
	c->addOrder(Order("OrdId11", "SecId1", "Sell", 1100, "User13", "Company2"));
	c->addOrder(Order("OrdId12", "SecId2", "Buy", 1200, "User9", "Company2"));

	int q = c->getMatchingSizeForSecurity("SecId1");
	int q2 = c->getMatchingSizeForSecurity("SecId2");
	int q3 = c->getMatchingSizeForSecurity("SecId3");
	cout << q << endl;
	cout << q2 << endl;
	cout << q3 << endl;
}

static void AddOrder3(OrderCacheInterface& c)
{
	c.addOrder(Order("OrdId1", "SecId3", "Sell", 100, "User1", "Company1"));
	c.addOrder(Order("OrdId2", "SecId3", "Sell", 200, "User3", "Company2"));
	c.addOrder(Order("OrdId3", "SecId1", "Buy", 300, "User2", "Company1"));
	c.addOrder(Order("OrdId4", "SecId3", "Sell", 400, "User5", "Company2"));
	c.addOrder(Order("OrdId5", "SecId2", "Sell", 500, "User2", "Company1"));
	c.addOrder(Order("OrdId6", "SecId2", "Buy", 600, "User3", "Company2"));
	c.addOrder(Order("OrdId7", "SecId2", "Sell", 700, "User1", "Company1"));
	c.addOrder(Order("OrdId8", "SecId1", "Sell", 800, "User2", "Company1"));
	c.addOrder(Order("OrdId9", "SecId1", "Buy", 900, "User5", "Company2"));
	c.addOrder(Order("OrdId10", "SecId1", "Sell", 1000, "User1", "Company1"));
	c.addOrder(Order("OrdId11", "SecId2", "Sell", 1100, "User6", "Company2"));

	int q = c.getMatchingSizeForSecurity("SecId1");
	int q2 = c.getMatchingSizeForSecurity("SecId2");
	int q3 = c.getMatchingSizeForSecurity("SecId3");
	cout << q << endl;
	cout << q2 << endl;
	cout << q3 << endl;
}

static void cancelOrdersForUser(OrderCacheInterface* c, string user)
{
	c->cancelOrdersForUser(user);
}

static void cancelOrdersForSecIdWithMinimumQty(OrderCacheInterface* c, const std::string& securityId,unsigned int minQty)
{
	c->cancelOrdersForSecIdWithMinimumQty(securityId, minQty);
}

static void GetAllOrder(OrderCacheInterface *c)
{
	vector<Order> orderTest = c->getAllOrders();
	printOrders(orderTest);
}

static void getMatchingSizeForSecurity(OrderCacheInterface* c, string securityId)
{
	cout << "Matching size for security: " << securityId << endl;
	int q = c->getMatchingSizeForSecurity(securityId);
	cout << q << endl;
}
//mutex mtx;
//void incNum(int &num)
//{
//	lock_guard<mutex> lock(mtx);
//	for (int i = 0; i < 10000; i++)
//	{
//		num ++;
//	}
//}
//
//void DecNum(int& num)
//{
//	lock_guard<mutex> lock(mtx);
//	for (int i = 0; i < 10000; i++)
//	{
//		num--;
//	}
//}

int main()
{
    try
    {
        vector<Order> orderTest;
		OrderCacheInterface* c = new COrderCacheImplementation();
		AddOrder3(*c);
		GetAllOrder(c);


        delete c;
    }
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

	getchar();
	return 0;
}