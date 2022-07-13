
private static int BuyRate;             // 买入指数
private static int SellRate;            // 卖出指数

// 函数：商人识别
int is_trader() { return 1; }

// 函数：获取买入指数
int get_buy_rate() { return BuyRate; }

// 函数：设置买入指数
int set_buy_rate( int rate ) 
{ 
        if( rate < 0 ) rate = 0;
        else if( rate > 1000 ) rate = 1000;
        return BuyRate = rate; 
}

// 函数：增加买入指数
int add_buy_rate( int rate ) { return BuyRate += rate; }

// 函数：获取卖出指数
int get_sell_rate() { return SellRate; }

// 函数：设置卖出指数
int set_sell_rate( int rate ) 
{ 
        if( rate < 0 ) rate = 0;
        else if( rate > 1000 ) rate = 1000;
        return SellRate = rate; 
}

// 函数：增加卖出指数
int add_sell_rate( int rate ) { return SellRate += rate; }
