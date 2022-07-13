
#include <skill.h>

private static object Enemy;            // 攻击对象(物理锁定)
private static object Enemy2;           // 攻击对象(暗器，法术，医术，施毒锁定)

private static object Enemy5;           // 反击对象(顺势推舟)    // effect/attack

private static int PerformTime;         // 特殊技准备时间(用于聚气超时扣减法力)

// -------------------------------------------------------------

// 函数：获取攻击对象
object get_enemy_2() { return Enemy2; }

// 函数：设置攻击对象
object set_enemy_2( object who ) 
{ 
        object me = this_object();

        if( objectp(Enemy2) )    // 取消锁定标记
                send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(Enemy2), 00111, 10, OVER_BODY, PF_STOP );
        if( objectp(who) )    // 显示锁定标记
                send_user( me, "%c%d%w%c%c%c", 0x6f, getoid(who), 00111, 10, OVER_BODY, PF_LOOP );

        return Enemy2 = who; 
}

// 函数：获取反击对象
object get_enemy_5() { return Enemy5; }

// 函数：设置反击对象
object set_enemy_5( object who ) { return Enemy5 = who; }

// 函数：获取特技准备时间
int get_perform_enable_time() { return PerformTime; }

// 函数：设置特技准备时间
int set_perform_enable_time( int time ) { return PerformTime = time; }

// -------------------------------------------------------------

// 函数：停止战斗
void stop_fight()
{
        object me = this_object();
        object soldier, *zombie;
        int i, size;

        if( objectp( soldier = me->get("soldier") ) )    // 停止召唤兽攻击
        {
                if( soldier->get_enemy() == Enemy ) soldier->set_enemy(0);
        }
        if( arrayp( zombie = me->get("zombie") ) )
        {
                for( i = 0, size = sizeof(zombie); i < size; i ++ ) 
                        if( zombie[i] && ( zombie[i]->get_enemy() == Enemy ) ) zombie[i]->set_enemy(0);
        }

        Enemy = 0;
}
