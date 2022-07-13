#include <effect.h>
#include <npc.h>

// NPC 专用

class Health
{
        int Point;                              // 当前数值
        int MaxPoint;                           // 最大数值
}

private class Health HP = new( class Health );  // 生命点数(Health)
private class Health MP = new( class Health );  // 法力点数(Magic)

private int HP_Cent;                     // 气血比例(注意：0/50～50/50)

private int AP0, AP;                            // 物理攻击(Attack)
private int DP0, DP;                            // 物理防御(Defence)
private int CP0, CP;                            // 法术攻击(Cast)
private int PP0, PP;                            // 法术防御(Protect)
private int SP0, SP;                            // 腾挪躲闪(Speed)

private int Poison;                             // 中毒点数
private int Poison2;                            // 中毒点数(暗器)

private static int WalkSpeed = WALK_SPEED_4;    // 走路速度(秒)
private static int WalkStep = 1;                // 走路步数

private static int AttackSpeed = ATTACK_SPEED_4;// 攻击速度(秒)

private static int MaxSeek = 4;                 // 最大搜索范围

private static int SmartCaster;                 // 游击战模式

private int Die;                                // 死亡标志

// -------------------------------------------------------------

// 函数：获取当前ＨＰ
int get_hp() { return HP->Point; }

// 函数：获取当前ＭＰ
int get_mp() { return MP->Point; }

// 函数：获取最大ＨＰ
int get_max_hp() { return HP->MaxPoint; }

// 函数：获取最大ＭＰ
int get_max_mp() { return MP->MaxPoint; }

// 函数：获取气血比例
int get_hp_cent() { return HP_Cent; }

// 函数：设置当前ＨＰ
int set_hp( int point ) 
{
        object me = this_object();
        object owner;
        int old_hp_cent = HP_Cent;
        point = range_value( point, -1, HP->MaxPoint );
        HP_Cent = ( point < 1 || HP->MaxPoint < 1 ) ? 0 : point * 50 / HP->MaxPoint;
        if( old_hp_cent != HP_Cent ) send_user( get_scene_object_2(me, USER_TYPE), "%c%d%c", 0x2a, getoid(me), HP_Cent );
        owner = me->get_owner();
        if (owner) send_user(owner, "%c%c%d%c", 0x2c, 3, getoid(me), HP_Cent );
        return HP->Point = point; 
}

// 函数：设置当前ＭＰ
int set_mp( int point ) 
{ 
        point = range_value( point, -1, MP->MaxPoint );
        return MP->Point = point; 
}

// 函数：设置最大ＨＰ
int set_max_hp( int point ) 
{ 
	object me = this_object();
        point = range_value(point, 1, MAX_NUMBER);
        HP->MaxPoint = point;
        if (me->get_owner()) ;
        else set_hp(point);
        return point;
}

// 函数：设置最大ＭＰ
int set_max_mp( int point ) 
{ 
	object me = this_object();
        point = range_value(point, 1, MAX_NUMBER);
        if (!me->get_owner()) 
        	MP->Point = point;    // 设满法力
        return MP->MaxPoint = point;
}

// 函数：增添当前ＨＰ
int add_hp( int point ) { return set_hp( HP->Point + point ); }

// 函数：增添当前ＭＰ
int add_mp( int point ) { return set_mp( MP->Point + point ); }

// 函数：增添最大ＨＰ
int add_max_hp( int point ) { return set_max_hp( HP->MaxPoint + point ); }

// 函数：增添最大ＭＰ
int add_max_mp( int point ) { return set_max_mp( MP->MaxPoint + point ); }

// -------------------------------------------------------------

// 函数：获取物理攻击(基值)
int get_ap_0() { return AP; }

// 函数：获取物理防御(基值)
int get_dp_0() { return DP; }

// 函数：获取法术攻击(基值)
int get_cp_0() { return CP; }

// 函数：获取法术防御(基值)
int get_pp_0() { return PP; }

// 函数：获取物理攻击
int get_ap() 
{ 
	object me = this_object();
	if (get_effect(me, EFFECT_CHAR_WOUND)) return AP * 8 /10;
	return AP; 
}

// 函数：获取物理防御
int get_dp() 
{
	int rate; 
	object me = this_object();
	rate = 0;
	if (get_effect(me, EFFECT_CHAR_WOUND)) rate += 20;
	if (get_effect(me, EFFECT_2123_ARMORFALL)) rate += 10;
	return DP*(100-rate)/100; 
}

// 函数：获取法术攻击
int get_cp() { return CP; }

// 函数：获取法术防御
int get_pp() { return PP; }

// 函数：获取腾挪躲闪
int get_sp() { return SP; }

// 函数：获取中毒点数
int get_poison() { return Poison; }

// 函数：获取中毒点数(暗器)
int get_poison_2() { return Poison2; }

// 函数：设置物理攻击
int set_ap( int point ) { return AP = range_value(point, 1, MAX_NUMBER); }

// 函数：设置物理防御
int set_dp( int point ) { return DP = range_value(point, 1, MAX_NUMBER); }

// 函数：设置法术攻击
int set_cp( int point ) { return CP = range_value(point, 1, MAX_NUMBER); }

// 函数：设置法术防御
int set_pp( int point ) { return PP = range_value(point, 1, MAX_NUMBER); }

// 函数：设置腾挪躲闪
int set_sp( int point ) { return SP = range_value(point, 1, MAX_NUMBER); }

// 函数：设置中毒点数
int set_poison( int point ) { return Poison = range_value(point, 1, MAX_NUMBER); }

// 函数：设置中毒点数(暗器)
int set_poison_2( int point ) { return Poison2 = range_value(point, 1, MAX_NUMBER); }

// 函数：增添物理攻击
int add_ap( int point ) { return set_ap( AP + point ); }

// 函数：增添物理防御
int add_dp( int point ) { return set_dp( DP + point ); }

// 函数：增添法术攻击
int add_cp( int point ) { return set_cp( CP + point ); }

// 函数：增添法术防御
int add_pp( int point ) { return set_pp( PP + point ); }

// 函数：增添腾挪躲闪
int add_sp( int point ) { return set_sp( SP + point ); }

// 函数：增添中毒点数
int add_poison( int point ) { return set_poison( Poison + point ); }

// 函数：增添中毒点数(暗器)
int add_poison_2( int point ) { return set_poison_2( Poison2 + point ); }

// -------------------------------------------------------------

// 函数：获取走路步数
int get_walk_step() { return WalkStep; }

// 函数：设置走路步数
int set_walk_step( int point ) { return WalkStep = point; }

// 函数：获取走路速度(秒)
int get_walk_speed() { return range_value(WalkSpeed, 2, MAX_NUMBER); }

// 函数：设置走路速度(秒)
int set_walk_speed( int point ) 
{ 
        object me = this_object();
        send_user( get_scene_object_2(me, USER_TYPE), "%c%c%d%c", 0x3d, 245, getoid(me), point );
        return WalkSpeed = point; 
}

// 函数：获取攻击速度(秒)
int get_attack_speed() { return range_value(AttackSpeed, ATTACK_SPEED_1, MAX_NUMBER); }

// 函数：设置攻击速度(秒)
int set_attack_speed( int point ) { return AttackSpeed = point; }

// 函数：获取最大搜索范围
int get_max_seek() { return MaxSeek; }

// 函数：设置最大搜索范围
int set_max_seek( int point ) { return MaxSeek = point; }

// 函数：获取游击战模式
int is_smart_caster() { return SmartCaster; }

// 函数：设置游击战模式
int be_smart_caster( int flag ) { return SmartCaster = flag; }

// 函数：获取死亡标志
int is_die() { return Die; }

// 函数：设置死亡标志
// 参数：0 复活；1 死亡；2 有人解救；3 复活；9 战场死亡
int set_die( int flag )
{
        return Die = flag;
}