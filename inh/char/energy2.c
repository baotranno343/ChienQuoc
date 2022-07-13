
private static int AbsorbHP;                    // 吸取气血("hp*")
private static int AbsorbMP;                    // 吸取法力("mp*")

private static int HitRate;                     // 命中率("!%")
private static int HitRate2;                    // 法术命中率("c!%")
private static int HitRate3;                    // 暗器命中率("t!%")

private static int DodgeRate;                   // 闪避率("?%")
private static int DodgeRate2;                  // 法术闪避率("c?%")

private static int AntiHurt;                    // 免伤害("-*")
private static int AntiHurt2;                   // 免法术伤害("-c*")
private static int AntiHurtRate;                // 免伤害率("-*%")
private static int AntiHurtRate2;               // 免法术伤害率("-c*%")

private static int ChangeHurt;                  // 转化伤害率(MP)

private static int Hurt;                        // 反弹伤害
private static int Hurt2;                       // 反法术伤害
private static int HurtRate;                    // 反伤害率
private static int HurtRate2;                   // 反法术伤害率
private static int HurtRand;                    // 反伤害发生
private static int HurtRand2;                   // 反法术伤害发生

private static int DoubleRate;			// 物理暴击率
private static int DoubleRate2;			// 法术暴击率

private static int PoisonRate;                  // 毒性增强("@", "@%")
private static int AntiPoison;                  // 抗毒几率
private static int LostPoison;                  // 抗毒性("-@%")
private static int Immunity;                    // 免异常效果("/%")(BUSY药)

private static int HealingRate;                 // 康复率(恢复类药物)

private static int Lucky;                       // 运气率("??%")

private static int LessProp;                    // 免装备条件("#%")

private static int AntiNoPF;                    // 抗封魔率
// -------------------------------------------------------------

// 函数：获取吸取气血
int get_absorb_hp() { return AbsorbHP; }

// 函数：设置吸取气血
int set_absorb_hp( int point ) { return AbsorbHP = point; }

// 函数：获取吸取法力
int get_absorb_mp() { return AbsorbMP; }

// 函数：设置吸取法力
int set_absorb_mp( int point ) { return AbsorbMP = point; }

// 函数：获取命中率
int get_hit_rate() { return HitRate; }

// 函数：设置命中率
int set_hit_rate( int point ) { return HitRate = point; }

// 函数：获取法术命中率
int get_hit_rate_2() { return HitRate2; }

// 函数：设置法术命中率
int set_hit_rate_2( int point ) { return HitRate2 = point; }

// 函数：获取暗器命中率
int get_hit_rate_3() { return HitRate3; }

// 函数：设置暗器命中率
int set_hit_rate_3( int point ) { return HitRate3 = point; }

// 函数：获取闪避率
int get_dodge_rate() { return DodgeRate; }

// 函数：设置闪避率
int set_dodge_rate( int point ) { return DodgeRate = point; }

// 函数：获取法术闪避率
int get_dodge_rate_2() { return DodgeRate2; }

// 函数：设置法术闪避率
int set_dodge_rate_2( int point ) { return DodgeRate2 = point; }

// 函数：获取免伤害
int get_anti_hurt() { return AntiHurt; }

// 函数：设置免伤害
int set_anti_hurt( int point ) { return AntiHurt = point; }

// 函数：获取免法术伤害
int get_anti_hurt_2() { return AntiHurt2; }

// 函数：设置免法术伤害
int set_anti_hurt_2( int point ) { return AntiHurt2 = point; }

// 函数：获取免伤害率
int get_anti_hurt_rate() { return AntiHurtRate; }

// 函数：设置免伤害率
int set_anti_hurt_rate( int point ) { return AntiHurtRate = point; }

// 函数：获取免法术伤害率
int get_anti_hurt_rate_2() { return AntiHurtRate2; }

// 函数：设置免法术伤害率
int set_anti_hurt_rate_2( int point ) { return AntiHurtRate2 = point; }

// 函数：获取转化伤害率
int get_change_hurt() { return ChangeHurt; }

// 函数：设置转化伤害率
int set_change_hurt( int point ) { return ChangeHurt = point; }

// 函数：获取反弹伤害
int get_hurt() { return Hurt; }

// 函数：设置反弹伤害
int set_hurt( int point ) { return Hurt = point; }

// 函数：获取反法术伤害
int get_hurt_2() { return Hurt2; }

// 函数：设置反法术伤害
int set_hurt_2( int point ) { return Hurt2 = point; }

// 函数：获取反伤害率
int get_hurt_rate() { return HurtRate; }

// 函数：设置反伤害率
int set_hurt_rate( int point ) { return HurtRate = point; }

// 函数：获取反法术伤害率
int get_hurt_rate_2() { return HurtRate2; }

// 函数：设置反法术伤害率
int set_hurt_rate_2( int point ) { return HurtRate2 = point; }

// 函数：获取反伤害发生
int get_hurt_rand() { return HurtRand; }

// 函数：设置反伤害发生
int set_hurt_rand( int point ) { return HurtRand = point; }

// 函数：获取反法术伤害发生
int get_hurt_rand_2() { return HurtRand2; }

// 函数：设置反法术伤害发生
int set_hurt_rand_2( int point ) { return HurtRand2 = point; }

// 函数：获取物理暴击率
int get_double_rate() { return DoubleRate; }

// 函数：设置物理暴击率
int set_double_rate( int point ) { return DoubleRate = point; }

// 函数：获取物理暴击率
int get_double_rate_2() { return DoubleRate2; }

// 函数：设置物理暴击率
int set_double_rate_2( int point ) { return DoubleRate2 = point; }

// -------------------------------------------------------------

// 函数：获取毒性增强
int get_poison_rate() { return PoisonRate; }

// 函数：设置毒性增强
int set_poison_rate( int point ) { return PoisonRate = point; }

// 函数：获取抗毒率
int get_anti_poison() { return AntiPoison; }

// 函数：设置抗毒率
int set_anti_poison( int point ) { return AntiPoison = range_value(point,0,100); }

// 函数：获取御毒率
int get_lost_poison() { return LostPoison; }

// 函数：设置御毒率
int set_lost_poison( int point ) { return LostPoison = point; }

// 函数：获取免异常效果
int get_immunity() { return Immunity; }

// 函数：设置免异常效果
int set_immunity( int point ) { return Immunity = point; }

// 函数：获取康复率
int get_healing_rate() { return HealingRate; }

// 函数：设置康复率
int set_healing_rate( int point ) { return HealingRate = point; }

// 函数：获取运气率
int get_lucky() { return Lucky; }

// 函数：设置运气率
int set_lucky( int point ) 
{
        object me = this_object();
        point = range_value(point, 0, 100);
//        if( Lucky != point && me->get_login_flag() > 1 ) send_user(me, "%c%c%c", 0x3d, 29, point);
        return Lucky = point; 
}

// 函数：获取免装备条件
int get_less_prop() { return LessProp; }

// 函数：设置免装备条件
int set_less_prop( int point ) { return LessProp = point; }
// 函数：获取抗封魔率
int get_anti_NoPF() { return AntiNoPF; }

// 函数：设置抗封魔率
int set_anti_NoPF( int point ) { return AntiNoPF = range_value(point,0,100); }
