
private static object Enemy4;           // 持续攻击对象
private static int AttackTime;          // 持续攻击时间

private static int FightTime;           // 宠物攻击时间：召唤兽记录攻击时间，用于 110 秒打不死就放弃的情况

private static int MaxDamage = 0;       // 受到最大伤害
private static object MainEnemy = 0;    // 最重要的敌人：NPC 优先的攻击对象

// -------------------------------------------------------------

// 函数：获取持续攻击对象
object get_enemy_4() { return Enemy4; }

// 函数：设置持续攻击对象
object set_enemy_4( object who ) { return Enemy4 = who; }

// 函数：获取持续攻击时间
int get_attack_time() { return AttackTime; }

// 函数：设置持续攻击时间
int set_attack_time( int time ) { return AttackTime = time; }

// 函数：获取宠物攻击时间
int get_fight_time() { return FightTime; }

// 函数：设置宠物攻击时间
int set_fight_time( int time ) { return FightTime = time; }

// -------------------------------------------------------------

// 函数：获取受到最大伤害
int get_max_damage() { return MaxDamage; }

// 函数：设置受到最大伤害
int set_max_damage( int point ) { return MaxDamage = point; }

// 函数：获取最重要的敌人
object get_main_enemy() { return MainEnemy; }

// 函数：设置最重要的敌人
object set_main_enemy( object who ) { return MainEnemy = who; }

// 函数：初始化敌人伤害
void init_enemy_damage( object who, int point )
{
        MainEnemy = who;  MaxDamage = point;
}
