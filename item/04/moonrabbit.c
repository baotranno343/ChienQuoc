inherit ITEM;
inherit COMBINED;   

int is_zhongqiu() { return 1; }
// 函数：构造处理
void create()
{
        set_name("小月兔");
        set_picid_1(3569);
        set_picid_2(3569);
        set_unit("只");
        set_value(100);
        set_amount(1);      
        set_no_give(0);//
        set_no_drop(0);//可丢弃。
        set_no_sell(0);//可交易，可存当铺，可摆摊。
          
}

// 函数：获取描述
string get_desc() 
{
	return "这是你成功捕获的月兔，很有可能会是玉兔所伪装的哟。";    	
}
