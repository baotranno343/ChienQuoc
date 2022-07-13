
#include <item.h>

inherit ITEM;

private int BuyIn;                      // 买入价格
private static int SellOut;             // 卖出价格
private static int BuyPrice;            // 买入基价
private static int BuyRange;            // 买入差价
private static int SellPrice;           // 卖出基价
private static int SellRange;           // 卖出差价

// -------------------------------------------------------------

// 函数：特产商品
// int is_good() { return 1; }

// 函数：特产商品
int get_item_type() { return ITEM_TYPE_GOOD; }

// 函数：特产商品
int get_item_type_2() { return ITEM_TYPE_2_GOOD; }

// 函数：获取买入价格
int get_buyin() { return BuyIn; }

// 函数：设置买入价格
int set_buyin( int gold ) { return BuyIn = gold; }

// 函数：获取卖出价格
int get_sellout() { return SellOut; }

// 函数：设置卖出价格
int set_sellout( int gold ) { return SellOut = gold; }

// 函数：获取买入基价
int get_buy_price() { return BuyPrice; }

// 函数：设置买入基价
int set_buy_price( int value ) { return BuyPrice = value; }

// 函数：获取买入差价
int get_buy_range() { return BuyRange; }

// 函数：设置买入差价
int set_buy_range( int value ) { return BuyRange = value; }

// 函数：获取卖出基价
int get_sell_price() { return SellPrice; }

// 函数：设置卖出基价
int set_sell_price( int value ) { return SellPrice = value; }

// 函数：获取卖出差价
int get_sell_range() { return SellRange; }

// 函数：设置卖出差价
int set_sell_range( int value ) { return SellRange = value; }
