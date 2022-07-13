
#include <city.h>

private string Occupation;              // 职业
private string Title;                   // 头衔

private int GiftRA;                     // 仁爱
private int GiftZY;                     // 正义
private int GiftZS;                     // 忠实
private int GiftCX;                     // 诚信
private int GiftYG;                     // 勇敢
private int GiftZM;                     // 智谋

private int Repute;                     // 声望
private int Contribute;                 // 贡献

private int Strength;                   // 体力

class OccupationData
{
        int Level;                      // 职业等级
        int Exp;                        // 职业经验
}

private mapping Jobs = ([ ]);           // 职业等级

int get_login_flag();

// -------------------------------------------------------------

// 函数：艺人识别
int is_actor() { return Occupation == JOB_ACTOR; }

// 函数：农夫识别
int is_farmer() { return Occupation == JOB_FARMER; }

// 函数：士兵识别
int is_soldier() { return Occupation == JOB_SOLDIER; }

// 函数：书生识别
int is_scholar() { return Occupation == JOB_SCHOLAR; }

// 函数：商人识别
int is_businessman() { return Occupation == JOB_TRADER; }

// 函数：获取城市职业
string get_occupation() { return Occupation ? Occupation : ""; }

// 函数：设置城市职业
string set_occupation( string name ) 
{ 
        if( !name || name == "" )
                send_user( this_object(), "%c%c%c", 0x3d, 51, 0 );
        else    send_user( this_object(), "%c%c%s", 0x3d, 51, name );
        return Occupation = name;
}

// 函数：获取头衔称号
string get_title() { return Title ? Title : ""; }

// 函数：设置头衔称号
string set_title( string name ) 
{ 
        if( !name || name == "" )
                send_user( this_object(), "%c%c%c", 0x3d, 52, 0 );
        else    send_user( this_object(), "%c%c%s", 0x3d, 52, name );
        return Title = name;
}

// -------------------------------------------------------------

// 函数：获取仁爱属性
int get_gift_ra() { return GiftRA; }

// 函数：设置仁爱属性
int set_gift_ra( int gift ) 
{ 
        object me = this_object();
        if( GiftRA != gift && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 60, gift);
        return GiftRA = gift; 
}

// 函数：增加仁爱属性
int add_gift_ra( int gift ) { return set_gift_ra( GiftRA + gift ); }

// 函数：获取正义属性
int get_gift_zy() { return GiftZY; }

// 函数：设置正义属性
int set_gift_zy( int gift ) 
{ 
        object me = this_object();
        if( GiftZY != gift && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 61, gift);
        return GiftZY = gift; 
}

// 函数：增加正义属性
int add_gift_zy( int gift ) { return set_gift_zy( GiftZY + gift ); }

// 函数：获取忠实属性
int get_gift_zs() { return GiftZS; }

// 函数：设置忠实属性
int set_gift_zs( int gift ) 
{ 
        object me = this_object();
        if( GiftZS != gift && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 62, gift);
        return GiftZS = gift; 
}

// 函数：增加忠实属性
int add_gift_zs( int gift ) { return set_gift_zs( GiftZS + gift ); }

// 函数：获取诚信属性
int get_gift_cx() { return GiftCX; }

// 函数：设置诚信属性
int set_gift_cx( int gift ) 
{ 
        object me = this_object();
        if( GiftCX != gift && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 63, gift);
        return GiftCX = gift; 
}

// 函数：增加诚信属性
int add_gift_cx( int gift ) { return set_gift_cx( GiftCX + gift ); }

// 函数：获取勇敢属性
int get_gift_yg() { return GiftYG; }

// 函数：设置勇敢属性
int set_gift_yg( int gift ) 
{ 
        object me = this_object();
        if( GiftYG != gift && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 64, gift);
        return GiftYG = gift; 
}

// 函数：增加勇敢属性
int add_gift_yg( int gift ) { return set_gift_yg( GiftYG + gift ); }

// 函数：获取智谋属性
int get_gift_zm() { return GiftZM; }

// 函数：设置智谋属性
int set_gift_zm( int gift ) 
{ 
        object me = this_object();
        if( GiftZM != gift && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 65, gift);
        return GiftZM = gift; 
}

// 函数：增加智谋属性
int add_gift_zm( int gift ) { return set_gift_zm( GiftZM + gift ); }

// 函数：获取声望点数
int get_repute() { return Repute; }

// 函数：设置声望点数
int set_repute( int point ) 
{ 
        object me = this_object();
        if( Repute != point && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 66, point);
        return Repute = point; 
}

// 函数：增加声望点数
int add_repute( int point ) { return set_repute( Repute + point ); }

// 函数：获取贡献点数
int get_contribute() { return Contribute; }

// 函数：设置贡献点数
int set_contribute( int point ) 
{ 
        object me = this_object();
        if( Contribute != point && get_login_flag() > 1 ) send_user(me, "%c%c%d", 0x3d, 67, point);
        return Contribute = point; 
}

// 函数：增加贡献点数
int add_contribute( int point ) 
{ 
        object city;
        if( city = CITY_D->get_city_object( this_object() ) ) city->add_contribute(point);
        return set_contribute( Contribute + point ); 
}

#define MAX_STRENGTH    200             // 最大体力

// 函数：获取体力点数
int get_strength() { return Strength; }

// 函数：设置体力点数
int set_strength( int point ) 
{ 
        object me = this_object();
//      point = range_value(point, 0, MAX_STRENGTH);    // 容易出 BUG
        if( point > MAX_STRENGTH ) point = MAX_STRENGTH;
        if( Strength != point && get_login_flag() > 1 ) send_user(me, "%c%c%c", 0x3d, 68, point);
        return Strength = point;
}

// 函数：增加体力点数
int add_strength( int point ) { return set_strength( Strength + point); }

// -------------------------------------------------------------

// 函数：获取职业数据
mapping get_job_dbase() { return copy(Jobs); }

// 函数：初始职业数据
void init_job_dbase() { Jobs = ([ ]); }

// 函数：获取职业等级
varargs int get_occupation_level( string occupation ) 
{ 
        class OccupationData job;
        string name;

        if( !occupation || occupation == "" ) occupation = Occupation;
        if( !occupation || occupation == "" ) return 0;

        switch( occupation )
        {
       case JOB_ACTOR : name = "actor";  break;
      case JOB_FARMER : name = "farmer";  break;
     case JOB_SOLDIER : name = "soldier";  break;
     case JOB_SCHOLAR : name = "scholar";  break;
      case JOB_TRADER : name = "trader";  break;
        }

        if( undefinedp( job = Jobs[name] ) ) return 0;

        return job->Level;
}

// 函数：设置职业等级
int set_occupation_level( int level ) 
{ 
        class OccupationData job;
        string name;

        if( !Occupation || Occupation == "" ) return 0;

        if( level < 0 ) level = 0;

        switch( Occupation )
        {
       case JOB_ACTOR : name = "actor";  break;
      case JOB_FARMER : name = "farmer";  break;
     case JOB_SOLDIER : name = "soldier";  break;
     case JOB_SCHOLAR : name = "scholar";  break;
      case JOB_TRADER : name = "trader";  break;
        }

        if( undefinedp( Jobs[name] ) ) job = new( class OccupationData );
        else job = Jobs[name];

        send_user( this_object(), "%c%c%w", 0x3d, 53, level );

        job->Level = level;
        Jobs[name] = job;

        return level;
}

// 函数：增加职业等级
int add_occupation_level( int level ) { return set_occupation_level( get_occupation_level() + level ); }

// 函数：获取职业经验
varargs int get_occupation_exp( string occupation ) 
{ 
        class OccupationData job;
        string name;

        if( !occupation || occupation == "" ) occupation = Occupation;
        if( !occupation || occupation == "" ) return 0;

        switch( occupation )
        {
       case JOB_ACTOR : name = "actor";  break;
      case JOB_FARMER : name = "farmer";  break;
     case JOB_SOLDIER : name = "soldier";  break;
     case JOB_SCHOLAR : name = "scholar";  break;
      case JOB_TRADER : name = "trader";  break;
        }

        if( undefinedp( job = Jobs[name] ) ) return 0;

        return job->Exp;
}

// 函数：设置职业经验
int set_occupation_exp( int exp ) 
{ 
        class OccupationData job;
        string name;

        if( !Occupation || Occupation == "" ) return 0;

        if( exp < 0 ) exp = 0;

        switch( Occupation )
        {
       case JOB_ACTOR : name = "actor";  break;
      case JOB_FARMER : name = "farmer";  break;
     case JOB_SOLDIER : name = "soldier";  break;
     case JOB_SCHOLAR : name = "scholar";  break;
      case JOB_TRADER : name = "trader";  break;
        }

        if( undefinedp( Jobs[name] ) ) job = new( class OccupationData );
        else job = Jobs[name];

        send_user( this_object(), "%c%c%d", 0x3d, 54, exp );

        job->Exp = exp;
        Jobs[name] = job;

        return exp;
}

// 函数：增加职业经验
int add_occupation_exp( int exp ) { return set_occupation_exp( get_occupation_exp() + exp ); }

// -------------------------------------------------------------

// 函数：职业升级所需经验
int get_job_exp( int level )
{
        level ++;  return level * level * level / 5;
}
