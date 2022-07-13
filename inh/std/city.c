
#include <ansi.h>

inherit DBASE_F;
inherit SAVE_F;

private int Level;                      // 等级

private int Defence;                    // 城防
private int Soldier;                    // 士兵
private int Armor;                      // 装备
private int Training;                   // 训练度

private int Cash;                       // 资金(流动资金)
private int Money;                      // 积累资金
private int Tax;                        // 税收
private int Tax2;                       // 其它收入
private int Food;                       // 粮草

private int Stability;                  // 安定
private int Disease;                    // 疾病

private int Agriculture;                // 农业
private int Fishculture;                // 渔业
private int Mining;                     // 矿业
private int Industry;                   // 工业
private int Commercial;                 // 商业

private int Arts;                       // 艺术
private int Education;                  // 教育
private int Religion;                   // 宗教

private string Master;                  // 城主
private string Master2;                 // 城主２(副城主)
private string Master3;                 // 城主３(副城主)

private string MasterName;              // 城主姓名
private string MasterName2;             // 城主２姓名
private string MasterName3;             // 城主３姓名

private int BuyTax;                     // 买入税
private int SellTax;                    // 卖出税
private int BuyTax2;                    // 买入税２
private int SellTax2;                   // 卖出税２

private int Tax2Cash;                   // 税收分红率

private int *Friend = ({ 0, 0, 0, 0, 0, 0, 0 });        // 友好度
private int *Relation = ({ 0, 0, 0, 0, 0, 0, 0 });      // 外交关系

private int Contribute;                 // 今日贡献

private int *Salary0 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, });    // 贡献/工资表(源)
private int *Salary2 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, });    // 领取工资表

// 函数：城市识别函数
int is_city() { return 1; }

// -------------------------------------------------------------

// 函数：获取等级属性
int get_level() { return Level; }

// 函数：设置等级属性
int set_level( int point ) { return Level = point; }

// 函数：增添等级属性
int add_level( int point ) { return set_level( Level + point ); }

// -------------------------------------------------------------

// 函数：获取城防属性
int get_defence() { return Defence; }

// 函数：设置城防属性
int set_defence( int point ) 
{ 
        if( point > Level * 2000 + 1000 ) point = Level * 2000 + 1000;
        return Defence = point; 
}

// 函数：增添城防属性
int add_defence( int point ) { return set_defence( Defence + point ); }

// 函数：判断士兵足够
int is_soldier_enough() { return Soldier >= Level * 50000 + 50000; }

// 函数：获取士兵属性
int get_soldier() { return Soldier; }

// 函数：设置士兵属性
int set_soldier( int point )
{ 
        if( point > Level * 50000 + 50000 ) point = Level * 50000 + 50000;
        if( point < Armor ) Armor = point;
        if( point < Training ) Training = point;
        return Soldier = point; 
}

// 函数：增添士兵属性
int add_soldier( int point ) { return set_soldier( Soldier + point ); }

// 函数：获取装备属性
int get_armor() { return Armor; }

// 函数：设置装备属性
int set_armor( int point ) 
{ 
        if( point > Soldier ) point = Soldier;
        return Armor = point; 
}

// 函数：增添装备属性
int add_armor( int point ) { return set_armor( Armor + point ); }

// 函数：获取训练度属性
int get_training() { return Training; }

// 函数：设置训练度属性
int set_training( int point ) 
{ 
        if( point > Soldier ) point = Soldier;
        return Training = point; 
}

// 函数：增添训练度属性
int add_training( int point ) { return set_training( Training + point ); }

// -------------------------------------------------------------

// 函数：获取流动资金
int get_cash() { return Cash; }

// 函数：设置流动资金
int set_cash( int gold ) 
{ 
        if( gold > MAX_NUMBER ) gold = MAX_NUMBER;
        return Cash = gold; 
}

// 函数：增添流动资金
int add_cash( int gold ) { return set_cash( Cash + gold ); }

// 函数：获取积累资金
int get_money() { return Money; }

// 函数：设置积累资金
int set_money( int gold ) 
{ 
        if( gold > MAX_NUMBER ) gold = MAX_NUMBER;
        return Money = gold; 
}

// 函数：增添积累资金
int add_money( int gold ) { return set_money( Money + gold ); }

// 函数：获取税收属性
int get_tax() { return Tax; }

// 函数：设置税收属性
int set_tax( int gold ) 
{ 
        if( gold > MAX_NUMBER ) gold = MAX_NUMBER;
        return Tax = gold; 
}

// 函数：增添税收属性
int add_tax( int gold ) { return set_tax( Tax + gold ); }

// 函数：获取其它收入
int get_tax_2() { return Tax2; }

// 函数：设置其它收入
int set_tax_2( int gold ) 
{ 
        if( gold > MAX_NUMBER ) gold = MAX_NUMBER;
        return Tax2 = gold; 
}

// 函数：增添其它收入
int add_tax_2( int gold ) { return set_tax_2( Tax2 + gold ); }

// 函数：获取粮草属性
int get_food() { return Food; }

// 函数：设置粮草属性
int set_food( int point ) 
{ 
        if( point > MAX_NUMBER ) point = MAX_NUMBER;
        return Food = point; 
}

// 函数：增添粮草属性
int add_food( int point ) { return set_food( Food + point ); }

// -------------------------------------------------------------

// 函数：获取安定属性
int get_stability() { return Stability; }

// 函数：设置安定属性
int set_stability( int point ) 
{ 
        if( point > 11000 ) point = 11000;
        return Stability = point; 
}

// 函数：增添安定属性
int add_stability( int point ) { return set_stability( Stability + point ); }

// 函数：获取疾病属性
int get_disease() { return Disease; }

// 函数：设置疾病属性
int set_disease( int point ) { return Disease = point; }

// 函数：增添疾病属性
int add_disease( int point ) { return set_disease( Disease + point ); }

// -------------------------------------------------------------

// 函数：获取农业属性
int get_agriculture() { return Agriculture; }

// 函数：设置农业属性
int set_agriculture( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Agriculture = point; 
}

// 函数：增添农业属性
int add_agriculture( int point ) { return set_agriculture( Agriculture + point ); }

// 函数：获取渔业属性
int get_fishculture() { return Fishculture; }

// 函数：设置渔业属性
int set_fishculture( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Fishculture = point; 
}

// 函数：增添渔业属性
int add_fishculture( int point ) { return set_fishculture( Fishculture + point ); }

// 函数：获取矿业属性
int get_mining() { return Mining; }

// 函数：设置矿业属性
int set_mining( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Mining = point; 
}

// 函数：增添矿业属性
int add_mining( int point ) { return set_mining( Mining + point ); }

// 函数：获取工业属性
int get_industry() { return Industry; }

// 函数：设置工业属性
int set_industry( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Industry = point; 
}

// 函数：增添工业属性
int add_industry( int point ) { return set_industry( Industry + point ); }

// 函数：获取商业属性
int get_commercial() { return Commercial; }

// 函数：设置商业属性
int set_commercial( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Commercial = point; 
}

// 函数：增添商业属性
int add_commercial( int point ) { return set_commercial( Commercial + point ); }

// -------------------------------------------------------------

// 函数：获取艺术属性
int get_arts() { return Arts; }

// 函数：设置艺术属性
int set_arts( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Arts = point; 
}

// 函数：增添艺术属性
int add_arts( int point ) { return set_arts( Arts + point ); }

// 函数：获取教育属性
int get_education() { return Education; }

// 函数：设置教育属性
int set_education( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Education = point; 
}

// 函数：增添教育属性
int add_education( int point ) { return set_education( Education + point ); }

// 函数：获取宗教属性
int get_religion() { return Religion; }

// 函数：设置宗教属性
int set_religion( int point ) 
{ 
        if( point > (Level + 1) * 20000 + 10000 ) point = (Level + 1) * 20000 + 10000;
        return Religion = point; 
}

// 函数：增添宗教属性
int add_religion( int point ) { return set_religion( Religion + point ); }

// -------------------------------------------------------------

// 函数：获取城主ＩＤ
string get_master() { return Master ? Master : ""; }

// 函数：设置城主ＩＤ
string set_master( string id ) { return Master = id; }

// 函数：获取城主２ＩＤ
string get_master_2() { return Master2 ? Master2 : ""; }

// 函数：设置城主２ＩＤ
string set_master_2( string id ) { return Master2 = id; }

// 函数：获取城主３ＩＤ
string get_master_3() { return Master3 ? Master3 : ""; }

// 函数：设置城主３ＩＤ
string set_master_3( string id ) { return Master3 = id; }

// 函数：获取城主姓名
string get_master_name() { return MasterName ? MasterName : "－－"; }

// 函数：设置城主姓名
string set_master_name( string name ) { return MasterName = name; }

// 函数：获取城主２姓名
string get_master_name_2() { return MasterName2 ? MasterName2 : "－－"; }

// 函数：设置城主２姓名
string set_master_name_2( string name ) { return MasterName2 = name; }

// 函数：获取城主３姓名
string get_master_name_3() { return MasterName3 ? MasterName3 : "－－"; }

// 函数：设置城主３姓名
string set_master_name_3( string name ) { return MasterName3 = name; }

// -------------------------------------------------------------

// 函数：获取买入税
int get_buy_tax() { return BuyTax; }

// 函数：设置买入税
int set_buy_tax( int tax ) { return BuyTax = range_value(tax, 1, 20); }

// 函数：获取卖出税
int get_sell_tax() { return SellTax; }

// 函数：设置卖出税
int set_sell_tax( int tax ) { return SellTax = range_value(tax, 1, 20); }

// 函数：获取买入税２
int get_buy_tax_2() { return BuyTax2; }

// 函数：设置买入税２
int set_buy_tax_2( int tax ) { return BuyTax2 = range_value(tax, 1, 20); }

// 函数：获取卖出税２
int get_sell_tax_2() { return SellTax2; }

// 函数：设置卖出税２
int set_sell_tax_2( int tax ) { return SellTax2 = range_value(tax, 1, 20); }

// 函数：获取税收分红率
int get_tax_2_cash() { return Tax2Cash; }

// 函数：设置税收分红率
int set_tax_2_cash( int tax ) { return Tax2Cash = range_value(tax, 40, 80); }

// -------------------------------------------------------------

// 函数：获取友好数组
int *get_friend_dbase() { return copy(Friend); }

// 函数：初始友好数组
int *init_friend_dbase() { return Friend = ({ 0, 0, 0, 0, 0, 0, 0 }); }

// 函数：获取外交数组
int *get_relation_dbase() { return copy(Relation); }

// 函数：初始外交数组
int *init_relation_dbase() { return Relation = ({ 0, 0, 0, 0, 0, 0, 0 }); }

// 函数：获取友好度
int get_friend( int city ) 
{  
        if( city < 1 || city > 7 ) return 0;
        return Friend[city - 1];
}

// 函数：设置友好度
int set_friend( int city, int point ) 
{  
        if( city < 1 || city > 7 ) return 0;
        return Friend[city - 1] = range_value(point, -500, 500);
}

// 函数：增添友好度
int add_friend( int city, int point ) { return set_friend( city, get_friend(city) + point ); }

// 函数：获取外交关系
int get_relation( int city ) 
{  
        if( city < 1 || city > 7 ) return 0;
        return Relation[city - 1];
}

// 函数：获取外交关系
string get_relation_name( int city ) 
{  
        if( city < 1 || city > 7 ) return "－－";

        switch( Relation[city - 1] )
        {
       case 2 : return "Đồng Minh";
       case 1 : return "Hảo Hữu";
      default : return "－－";
      case -1 : return "Kẻ Thù";
      case -2 : return "Chiến Tranh";
        }
}

// 函数：设置外交关系
int set_relation( int city, int flag ) 
{  
        if( city < 1 || city > 7 ) return 0;
        return Relation[city - 1] = flag;
}

// -------------------------------------------------------------

// 函数：获取工资表数组(源)
int *get_salary_dbase_0() { return copy(Salary0); }

// 函数：初始工资表数组(源)
int *init_salary_dbase_0() 
{ 
        return Salary0 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }); 
}

// 函数：获取工资表数组
int *get_salary_dbase_2() { return copy(Salary2); }

// 函数：初始工资表数组
int *init_salary_dbase_2()
{ 
        return Salary2 = ({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }); 
}

// 函数：获取某日贡献(源)
int get_contribute_0( int day ) 
{  
        if( day < 1 || day > 30 ) return 0;
        return Salary0[ (day - 1) * 2 ];
}

// 函数：设置某日贡献(源)
int set_contribute_0( int day, int point ) 
{  
        if( day < 1 || day > 30 ) return 0;
        return Salary0[ (day - 1) * 2 ] = point;
}

// 函数：获取某日工资(源)
int get_salary_0( int day ) 
{  
        if( day < 1 || day > 30 ) return 0;
        return Salary0[ (day - 1) * 2 + 1 ];
}

// 函数：设置某日工资(源)
int set_salary_0( int day, int point ) 
{  
        if( day < 1 || day > 30 ) return 0;
        return Salary0[ (day - 1) * 2 + 1 ] = point;
}

// 函数：获取某日领取工资
int get_salary_2( int day ) 
{  
        if( day < 1 || day > 30 ) return 0;
        return Salary2[ day - 1 ];
}

// 函数：设置某日领取工资
int set_salary_2( int day, int point ) 
{  
        if( day < 1 || day > 30 ) return 0;
        return Salary2[ day - 1 ] = point;
}

// 函数：增添某日领取工资
int add_salary_2( int day, int point ) { return set_salary_2( day, get_salary_2(day) + point ); }

// 函数：插入新的贡献／工资
void insert_contribute_salary( int contribute, int salary )
{
        int i;

        for( i = 28; i >= 0; i -- )
        {
                Salary0[ i * 2 + 2 ] = Salary0[ i * 2 ];
                Salary0[ i * 2 + 3 ] = Salary0[ i * 2 + 1 ];
                Salary2[ i + 1 ] = Salary2[ i ];
        }
        Salary0[0] = contribute;  Salary0[1] = salary;  Salary2[0] = salary;
}

// -------------------------------------------------------------

// 函数：获取今日贡献
int get_contribute() { return Contribute; }

// 函数：设置今日贡献
int set_contribute( int point ) { return Contribute = point; }

// 函数：增加今日贡献
int add_contribute( int point ) { return set_contribute( Contribute + point ); }

// 函数：根据贡献分红(login.c 调用)
void pay_salary_baseon_contribute( object who )
{
        string name;
        int day, contribute, salary, salary2, point;
	return ;
/*	
        name = this_object()->get_name();

        if( name != who->get_city_name() ) return;
        if( !( day = get_save("day") - who->get_save("salary") ) ) return;

        point = who->get_contribute();

        who->set_save( "salary", get_save("day") );    // 标记今天
        who->set_contribute(0);    // 清空贡献

        if( day < 1 || day > 30 ) return 0;

        contribute = Salary0[ (day - 1) * 2 ];
        salary = Salary0[ (day - 1) * 2 + 1 ];
        salary2 = Salary2[ day - 1 ];

        if( salary < 1 )
        {
                write_user( who, ECHO "前 %d 天%s分红为 %d，您分到 %d 金。", day, name, salary, 0 );
        }
        else if( salary2 < 1 )
        {
                write_user( who, ECHO "前 %d 天%s分红为 %d，您来得太晚了，分到 %d 金。", day, name, salary, 0 );
        }
        else if( contribute < 1 )
        {
                write_user( who, ECHO "前 %d 天%s分红为 %d，您没做出贡献，分到 %d 金。", day, name, salary, 0 );
        }
        else if( contribute > point )
        {
                if( salary > 10000 ) point = salary / 100 * point / contribute * 100;
                else if( point > 1000 ) point = point / 10 * salary / contribute * 10;
                else point = salary * point / contribute;

                if( point > salary2 ) point = salary2;

                who->add_cash(point);  who->add_gold_log("task", point);
                who->log_money("分红", point);
                "/sys/sys/count"->add_income("city", point);
                Salary2[ day - 1 ] -= point;

                write_user( who, ECHO "前 %d 天%s分红为 %d，您分到 %d 金。", day, name, salary, point );
        }
        else
        {
                who->add_cash(salary2);  who->add_gold_log("task", salary2);
                who->log_money("分红", salary2);
                "/sys/sys/count"->add_income("city", salary2);
                Salary2[ day - 1 ] = 0;

                write_user( who, ECHO "前 %d 天%s分红为 %d，您分到 %d 金。", day, name, salary, salary2 );
        }
*/        
}

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() { }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１分处理
{
        ITEM_EFFECT_D->into_effect(me, effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8);    // 征状处理
}

// -------------------------------------------------------------

// 函数：消除之前处理
void before_destruct()
{
        object *reset;
        int i, size;

        if( arrayp( reset = this_object()->get("manager") ) )
        {
                size = sizeof(reset);
                for( i = 0; i < size; i ++ ) if( reset[i] )
                {
                        reset[i]->remove_from_scene();
                        destruct( reset[i] );
                }
        }
}
