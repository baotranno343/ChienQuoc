
#include <ansi.h>
#include <city.h>

#define TIME_SEC        0
#define TIME_MIN        1
#define TIME_HOUR       2
#define TIME_MDAY       3
#define TIME_MON        4
#define TIME_YEAR       5
#define TIME_WDAY       6
#define TIME_YDAY       7
#define TIME_GMTOFF     8
#define TIME_ZONE       9

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：构造处理
void create() 
{
//        object npc = new( "/npc/task/8800" );    // 军备商人
}

// 函数：获取国家编号
int get_city_number( string name )
{
        switch( name )
        {
  case "Tề Quốc" : return 1;
  case "Hàn Quốc" : return 2;
  case "Triệu Quốc" : return 3;
  case "Ngụy Quốc" : return 4;
  case "Tần Quốc" : return 5;
  case "Sở Quốc" : return 6;
  case "Yên Quốc" : return 7;
      default : return 8;
        }
}

// 函数：获取国家名称
string get_city_name( int city )
{
        switch( city )
        {
      default : return "Tề Quốc";
       case 2 : return "Hàn Quốc";
       case 3 : return "Triệu Quốc";
       case 4 : return "Ngụy Quốc";
       case 5 : return "Tần Quốc";
       case 6 : return "Sở Quốc";
       case 7 : return "Yên Quốc";
        }
}

// 函数：获取国家对象
object get_city_object( object who )
{
        switch( who->get_city_name() )
        {
  case "Tề Quốc" : return load_object( CITY_QI );
  case "Hàn Quốc" : return load_object( CITY_HAN );
  case "Triệu Quốc" : return load_object( CITY_ZHAO );
  case "Ngụy Quốc" : return load_object( CITY_WEI );
  case "Tần Quốc" : return load_object( CITY_QIN );
  case "Sở Quốc" : return load_object( CITY_CHU );
  case "Yên Quốc" : return load_object( CITY_YAN );
      default : return load_object( CITY_ZHOU );
        }
}

// 函数：获取国家对象
object get_city_object_2( int city )
{
        switch( city )
        {
       case 1 : return load_object( CITY_QI );
       case 2 : return load_object( CITY_HAN );
       case 3 : return load_object( CITY_ZHAO );
       case 4 : return load_object( CITY_WEI );
       case 5 : return load_object( CITY_QIN );
       case 6 : return load_object( CITY_CHU );
       case 7 : return load_object( CITY_YAN );
      default : return load_object( CITY_ZHOU );
        }
}

// 函数：城市每天处理
void city_everyday( object city )
{
        mixed *time;
        string result;
        int defence, soldier, armor, training, gold, tax, food, stability;
        int agriculture, fishculture, mining, industry, commercial, arts, education, religion;
        int salary, day;

	return ;
/*
        time = localtime( time() );
        day = time[TIME_YDAY];

        if( city->get_save("day") != day )
        {
                city->set_save("day", day);

                if( city->get_disease() > 0 )    // 瘟疫继续影响
                {
                        city->add_disease(-1);

                        defence = -city->get_defence() / 20;    // 5%
                        soldier = -city->get_soldier() / 20;
                        armor = -city->get_armor() / 20;
                        training = -city->get_training() / 20;

                        gold = -city->get_cash() / 20;
                        tax = -city->get_tax() / 100 * 15;    // 15%
                        food = -city->get_food() / 20;

                        stability = -city->get_stability() / 20;

                        agriculture = -city->get_agriculture() / 20;
                        fishculture = -city->get_fishculture() / 20;
                        mining = -city->get_mining() / 20;
                        industry = -city->get_industry() / 20;
                        commercial = -city->get_commercial() / 20;
                        arts = -city->get_arts() / 20;
                        education = -city->get_education() / 20;
                        religion = -city->get_religion() / 20;

                        city->add_defence(defence);
                        city->add_soldier(soldier);
                        city->add_armor(armor);
                        city->add_training(training);

                        city->add_money(gold);
                        city->add_tax(tax);
                        city->add_food(food);

                        city->add_stability(stability);

                        city->add_agriculture(agriculture);
                        city->add_fishculture(fishculture);
                        city->add_mining(mining);
                        city->add_industry(industry);
                        city->add_commercial(commercial);

                        city->add_arts(arts);
                        city->add_education(education);
                        city->add_religion(religion);

                        result = sprintf( HIY "%s的瘟疫还在蔓延……\n"
                                HIY "　　城防 %+d, 士兵 %+d, 装备 %+d, 训练度 %+d, 资金 %+d, 税收 %+d, 粮草 %+d, 安定 %+d,\n"
                                HIY "　　农业 %+d, 渔业 %+d, 矿业 %+d, 工业 %+d, 商业 %+d, 艺术 %+d, 教育 %+d, 宗教 %+d.",
                                city->get_name(), defence, soldier, armor, training, gold, tax, food, stability,
                                agriculture, fishculture, mining, industry, commercial, arts, education, religion );
                        FAMILY_D->city_channel( city->get_name(), 0, result );
                }

                stability = city->get_stability();    // 每天自动增加
                agriculture = city->get_agriculture();
                fishculture = city->get_fishculture();
                commercial = city->get_commercial();

                gold = city->get_level() * 10000;
                tax = agriculture * stability / 10000 + fishculture * stability / 15000 + commercial * stability / 1000;
                food = agriculture * stability / 10000 + fishculture * stability / 15000 - city->get_soldier();

                city->add_cash(gold);
                city->add_tax(tax);
                city->add_food(food);

                salary = city->get_tax() * city->get_tax_2_cash() / 100 + city->get_tax_2();
                city->insert_contribute_salary( city->get_contribute(), salary );

                city->add_money( city->get_tax() * ( 100 - city->get_tax_2_cash() ) / 100 );

                city->set_tax(0);
                city->set_tax_2(0);
                city->set_contribute(0);

                result = sprintf( HIY "%s百姓每日努力工作……资金 %+d, 税收 %+d, 粮草 %+d.可分配分红：%d\n", 
                        city->get_name(), gold, tax, food, salary );
                FAMILY_D->city_channel( city->get_name(), 0, result );

                if( stability > 6000 ) city->add_stability( -stability / 10 );    // 安定自动下降
        }
*/        
}

// 函数：城市选举
void city_vote( object city )
{
        mixed *time;
        string id, result;
        int day, i, size;

        time = localtime( time() );
        day = time[TIME_YDAY] - time[TIME_WDAY] + 1;

        if( day > 0 && city->get_save_2("elect.day") != day )
        {
                city->set_master("");
                city->set_master_2("");
                city->set_master_3("");
                city->set_master_name("－－");
                city->set_master_name_2("－－");
                city->set_master_name_3("－－");

                if(     city->get_save_2("elect.day")
                &&      sizeof( city->get_save_2( "elect.vote" ) )
                &&    ( id = city->get_save_2("elect.first") ) )
                {
                        result = sprintf( "%s(%s)", city->get_save_2("elect.name." + id), id );
                        city->set_master( city->get_save_2("elect.id." + id) );
                        city->set_master_name(result);

                        result = sprintf( HIY "%s lấy %d phiếu thắng cử, trở thành %s thành chủ!", 
                                result, city->get_save_2("elect.vote." + id), city->get_name() );
                        FAMILY_D->city_channel( city->get_name(), 0, result );
                }

                city->delete_save_2("elect");
                city->set_save_2("elect.day", day);
                city->save();

                result = sprintf( HIY "%s bắt đầu tranh cử, mọi người hãy tham gia bỏ phiếu!", city->get_name() );
                FAMILY_D->city_channel( city->get_name(), 0, result );
        }
}

// 函数：城市政令(24小时过期)
void city_policy( object city )
{
        object city2;
        string result;
        int i, flag;

        if(   ( flag = city->get_save_2("policy.flag") )
        &&      gone_time( city->get_save_2("policy.time") ) > 86400 )
        {
                switch( flag )
                {
               case 1 : result = sprintf( HIY "Kỳ hạn 24 giờ đã đến, %s Lệnh chiêu hiền tài tự động huỷ bỏ!", city->get_name() );
                        FAMILY_D->city_channel( city->get_name(), 0, result );
                        break;
              case -1 : result = sprintf( HIY "Kỳ hạn 24 giờ đã đến, %s lệnh đuổi khách tự động huỷ bỏ!", city->get_name() );
                        FAMILY_D->city_channel( city->get_name(), 0, result );
                        break;
                }
                city->delete_save_2("policy");
        }

        flag = get_city_number( city->get_name() );    // 本城号码

        for( i = 1; i <= 7; i ++ )
                if(     i != flag                       // 不同城市
                &&      city->get_relation(i) != -2     // 并非战争
                &&    ( city2 = get_city_object_2(i) ) )
        {
                if( city->get_relation(i) == 2 )    // 同盟关系
                {
                        if( city->get_friend(i) >= 300 ) continue;    // 仍然同盟

                        result = sprintf( HIY "Bởi vì độ hảo hữu quá thấp, %scùng %s tự động giải trừ đồng minh.", city->get_name(), city2->get_name() );
                        FAMILY_D->city_channel( city->get_name(), 0, result );
                        result = sprintf( HIY "Bởi vì độ hảo hữu quá thấp, %scùng %s tự động giải trừ đồng minh.", city2->get_name(), city->get_name() );
                        FAMILY_D->city_channel( city2->get_name(), 0, result );
                }

                if( city->get_friend(i) < -100 )    // 敌对
                {
                        city->set_relation(i, -1);  city2->set_relation(flag, -1);
                }
                else if( city->get_friend(i) < 100 )    // 普通
                {
                        city->set_relation(i, 0);  city2->set_relation(flag, 0);
                }
                else    // 友好
                {
                        city->set_relation(i, 1);  city2->set_relation(flag, 1);
                }
        }
}
