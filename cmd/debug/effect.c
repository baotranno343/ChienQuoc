
#include <effect.h>

// 函数：命令处理
int main( object me, string arg )
{
        object what = me;
        string result, *effect = ({ });
        int effect1, effect2, effect3, effect4,effect5, effect6, effect7, effect8;
        int len, i, size;

        if( is_player(me) ) 
        {
                notify( "您没有足够的权限。" );
		return 1;
        }

        if( arg && !( what = find_any_object(arg) ) )
        {
                notify( "无法找到这样东西。" );
		return 1;
        }

        if( what->is_npc() )
                tell_user( me, "征状情况：%s", what->get_name() );
        else    tell_user( me, "征状情况：%s(%d)", what->get_name(), what->get_number() );

        if( effect1 = get_effect_flag(what,1) )    // 简单征状标志１(３２位)
        {
                if( effect1 & 0x0000ffff )
                {
                        if( effect1 & 0x000000ff )    // 0
                        {
                                if( effect1 & 0x00000001 ) effect += ({ sprintf( "LOGIN: %d", get_effect(what, EFFECT_USER_LOGIN) ) });
                                if( effect1 & 0x00000002 ) effect += ({ sprintf( "BUSY: %d", get_effect(what, EFFECT_CHAR_BUSY) ) });
                                if( effect1 & 0x00000004 ) effect += ({ sprintf( "FAINT: %d", get_effect(what, EFFECT_CHAR_FAINT) ) });
                                if( effect1 & 0x00000008 ) effect += ({ sprintf( "FAINT_0: %d", get_effect(what, EFFECT_CHAR_FAINT_0) ) });
                                if( effect1 & 0x00000010 ) effect += ({ sprintf( "FAINT_2: %d", get_effect(what, EFFECT_CHAR_FAINT_2) ) });
                                if( effect1 & 0x00000020 ) effect += ({ sprintf( "FAINT_3: %d", get_effect(what, EFFECT_CHAR_FAINT_3) ) });
                                if( effect1 & 0x00000040 ) effect += ({ sprintf( "FREEZE: %d", get_effect(what, EFFECT_CHAR_FREEZE) ) });
                                if( effect1 & 0x00000080 ) effect += ({ sprintf( "FREEZE_0: %d", get_effect(what, EFFECT_CHAR_FREEZE_0) ) });
                        }
                        if( effect1 & 0x0000ff00 )    // 8
                        {
                                if( effect1 & 0x00000100 ) effect += ({ sprintf( "SHUT: %d", get_effect(what, EFFECT_CHAR_SHUT) ) });
                                if( effect1 & 0x00000200 ) effect += ({ sprintf( "SHUT_0: %d", get_effect(what, EFFECT_CHAR_SHUT_0) ) });
                                if( effect1 & 0x00000400 ) effect += ({ sprintf( "NO_PF: %d", get_effect(what, EFFECT_CHAR_NO_PF) ) });
                                if( effect1 & 0x00000800 ) effect += ({ sprintf( "NO_PF_0: %d", get_effect(what, EFFECT_CHAR_NO_PF_0) ) });
                                if( effect1 & 0x00001000 ) effect += ({ sprintf( "LAZY: %d", get_effect(what, EFFECT_CHAR_LAZY) ) });
                                if( effect1 & 0x00002000 ) effect += ({ sprintf( "LAZY_0: %d", get_effect(what, EFFECT_CHAR_LAZY_0) ) });
                                if( effect1 & 0x00004000 ) effect += ({ sprintf( "SLOW: %d", get_effect(what, EFFECT_CHAR_SLOW) ) });
                                if( effect1 & 0x00008000 ) effect += ({ sprintf( "SLOW_0: %d", get_effect(what, EFFECT_CHAR_SLOW_0) ) });
                        }
                }
                if( effect1 & 0xffff0000 )
                {
                        if( effect1 & 0x00ff0000 )    // 16
                        {
                                if( effect1 & 0x00010000 ) effect += ({ sprintf( "DREAM_1: %d", get_effect(what, EFFECT_CHAR_DREAM_1) ) });
                                if( effect1 & 0x00020000 ) effect += ({ sprintf( "DREAM_0: %d", get_effect(what, EFFECT_CHAR_DREAM_0) ) });
                                if( effect1 & 0x00040000 ) effect += ({ sprintf( "CHAOS: %d", get_effect(what, EFFECT_CHAR_CHAOS) ) });
                                if( effect1 & 0x00080000 ) effect += ({ sprintf( "CHAOS_0: %d", get_effect(what, EFFECT_CHAR_CHAOS_0) ) });
                                if( effect1 & 0x00100000 ) effect += ({ sprintf( "WOUND: %d", get_effect(what, EFFECT_CHAR_WOUND) ) });
                                if( effect1 & 0x00200000 ) effect += ({ sprintf( "WOUND_0: %d", get_effect(what, EFFECT_CHAR_WOUND_0) ) });
//                              if( effect1 & 0x00400000 )
                                if( effect1 & 0x00800000 ) effect += ({ sprintf( "BLOOD_0: %d", get_effect(what, EFFECT_CHAR_BLOOD_0) ) });
                        }
                        if( effect1 & 0xff000000 )    // 24
                        {
                                if( effect1 & 0x01000000 ) effect += ({ sprintf( "BLIND: %d", get_effect(what, EFFECT_CHAR_BLIND) ) });
                                if( effect1 & 0x02000000 ) effect += ({ sprintf( "BLIND_0: %d", get_effect(what, EFFECT_CHAR_BLIND_0) ) });
//                              if( effect1 & 0x04000000 )
                                if( effect1 & 0x08000000 ) effect += ({ sprintf( "BURN_0: %d", get_effect(what, EFFECT_USER_BURN_0) ) });
                                if( effect1 & 0x10000000 ) effect += ({ sprintf( "NO_WEAPON: %d", get_effect(what, EFFECT_NO_WEAPON) ) });
                                if( effect1 & 0x20000000 ) effect += ({ sprintf( "NO_WEAPON_0: %d", get_effect(what, EFFECT_NO_WEAPON_0) ) });
//                              if( effect1 & 0x40000000 )
//                              if( effect1 & 0x80000000 )
                        }
                }
        }

        if( effect2 = get_effect_flag(what,2) )    // 简单征状标志２(３２位)
        {
                if( effect2 & 0x0000ffff )
                {
                        if( effect2 & 0x000000ff )    // 32
                        {
                                if( what->is_user() )
                                {
                                        if( effect2 & 0x00000001 ) effect += ({ sprintf( "+HP: %d", get_effect(what, EFFECT_USER_HP) ) });
                                        if( effect2 & 0x00000002 ) effect += ({ sprintf( "+MP: %d", get_effect(what, EFFECT_USER_MP) ) });
                                        if( effect2 & 0x00000004 ) effect += ({ sprintf( "+AP: %d", get_effect(what, EFFECT_USER_AP) ) });
                                        if( effect2 & 0x00000008 ) effect += ({ sprintf( "+DP: %d", get_effect(what, EFFECT_USER_DP) ) });
                                        if( effect2 & 0x00000010 ) effect += ({ sprintf( "+CP: %d", get_effect(what, EFFECT_USER_CP) ) });
                                        if( effect2 & 0x00000020 ) effect += ({ sprintf( "+PP: %d", get_effect(what, EFFECT_USER_PP) ) });
//                                      if( effect2 & 0x00000040 )
//                                      if( effect2 & 0x00000080 )
                                }
                                else
                                {
                                        if( effect2 & 0x00000001 ) effect += ({ sprintf( "0531_1: %d", get_effect(what, EFFECT_NPC_0531_1) ) });
                                        if( effect2 & 0x00000002 ) effect += ({ sprintf( "0531_2: %d", get_effect(what, EFFECT_NPC_0531_2) ) });
                                        if( effect2 & 0x00000004 ) effect += ({ sprintf( "ZOMBIE: %d", get_effect(what, EFFECT_NPC_ZOMBIE) ) });
                                        if( effect2 & 0x00000008 ) effect += ({ sprintf( "ZOMBIE_2: %d", get_effect(what, EFFECT_NPC_ZOMBIE_2) ) });
//                                      if( effect2 & 0x00000010 )
//                                      if( effect2 & 0x00000020 )
//                                      if( effect2 & 0x00000040 )
//                                      if( effect2 & 0x00000080 )
                                }
                        }
                        if( effect2 & 0x0000ff00 )    // 40
                        {
                                if( effect2 & 0x00000100 ) effect += ({ sprintf( "-50AP: %d", get_effect(what, EFFECT_CHAR_5215) ) });
                                if( effect2 & 0x00000200 ) effect += ({ sprintf( "加气血药物: %d", get_effect(what, EFFECT_USE_ITEM_1) ) });
                                if( effect2 & 0x00000400 ) effect += ({ sprintf( "加法力药物: %d", get_effect(what, EFFECT_USE_ITEM_2) ) });
//                              if( effect2 & 0x00000800 )
//                              if( effect2 & 0x00001000 )
//                              if( effect2 & 0x00002000 )
//                              if( effect2 & 0x00004000 )
                                if( effect2 & 0x00008000 ) effect += ({ sprintf( "变身术: %d", get_effect(what, EFFECT_MAGIC_4243) ) });
                        }
                }
                if( effect2 & 0xffff0000 )
                {
                        if( effect2 & 0x00ff0000 )    // 48
                        {
                                if( effect2 & 0x00010000 ) effect += ({ sprintf( "ATTACK: %d", get_effect(what, EFFECT_CHAR_ATTACK) ) });
                                if( effect2 & 0x00020000 ) effect += ({ sprintf( "MOVE: %d", get_effect(what, EFFECT_CHAR_MOVE) ) });
                                if( effect2 & 0x00040000 ) effect += ({ sprintf( "INVISIBLE: %d", get_effect(what, EFFECT_CHAR_INVISIBLE) ) });
                                if( effect2 & 0x00080000 ) effect += ({ sprintf( "CHANGE: %d", get_effect(what, EFFECT_CHAR_CHANGE) ) });
//                              if( effect2 & 0x00100000 )
//                              if( effect2 & 0x00200000 )
//                              if( effect2 & 0x00400000 )
//                              if( effect2 & 0x00800000 )
                        }
                        if( effect2 & 0xff000000 )    // 56
                        {
                                if( effect2 & 0x01000000 ) effect += ({ sprintf( "ARMORFALL: %d", get_effect(what, EFFECT_CHAR_ARMORFALL) ) });
                                if( effect2 & 0x02000000 ) effect += ({ sprintf( "ADD_DP: %d", get_effect(what, EFFECT_CHAR_ADD_DP) ) });
                                if( effect2 & 0x04000000 ) effect += ({ sprintf( "ADD_PP: %d", get_effect(what, EFFECT_CHAR_ADD_PP) ) });
                                if( effect2 & 0x08000000 ) effect += ({ sprintf( "POWERFAIL: %d", get_effect(what, EFFECT_CHAR_POWERFALL) ) });
                                if( effect2 & 0x10000000 ) effect += ({ sprintf( "POWERUP: %d", get_effect(what, EFFECT_CHAR_POWERUP) ) });
                                if( effect2 & 0x20000000 ) effect += ({ sprintf( "MISS: %d", get_effect(what, EFFECT_CHAR_MISS) ) });
                                if( effect2 & 0x40000000 ) effect += ({ sprintf( "HALFGOLD: %d", get_effect(what, EFFECT_CHAR_HALFGOD) ) });
                                if( effect2 & 0x80000000 ) effect += ({ sprintf( "IMMORTAL: %d", get_effect(what, EFFECT_CHAR_IMMORTAL) ) });
                        }
                }
        }

        if( effect3 = get_effect_flag(what,3) )    // 简单征状标志３(３２位)
        {
                if( effect3 & 0x0000ffff )
                {
                        if( effect3 & 0x000000ff )    // 64
                        {
//                              if( effect3 & 0x00000001 )
//                              if( effect3 & 0x00000002 )
//                              if( effect3 & 0x00000004 )
//                              if( effect3 & 0x00000008 )
//                              if( effect3 & 0x00000010 )
//                              if( effect3 & 0x00000020 )
                                if( effect3 & 0x00000040 ) effect += ({ sprintf( "不中毒: %d", get_effect(what, EFFECT_CHAR_9140) ) });
                                if( effect3 & 0x00000080 ) effect += ({ sprintf( "无异常: %d", get_effect(what, EFFECT_CHAR_9145) ) });
                        }
                        if( effect3 & 0x0000ff00 )    // 72
                        {
//                              if( effect3 & 0x00000100 )
                                if( effect3 & 0x00000200 ) effect += ({ sprintf( "KING: %d", get_effect(what, EFFECT_CHAR_KING) ) });
                                if( effect3 & 0x00000400 ) effect += ({ sprintf( "KING_2: %d", get_effect(what, EFFECT_CHAR_KING_2) ) });
                                if( effect3 & 0x00000800 ) effect += ({ sprintf( "CHAN: %d", get_effect(what, EFFECT_CHAR_CHAN) ) });
                                if( effect3 & 0x00001000 ) effect += ({ sprintf( "SUPPRESS: %d", get_effect(what, EFFECT_CHAR_SUPPRESS) ) });
//                              if( effect3 & 0x00002000 )
                                if( effect3 & 0x00004000 ) effect += ({ sprintf( "HERB: %d", get_effect(what, EFFECT_USER_HERB) ) });
                                if( effect3 & 0x00008000 ) effect += ({ sprintf( "HERB_OK: %d", get_effect(what, EFFECT_USER_HERB_OK) ) });
                        }
                }
                if( effect3 & 0xffff0000 )
                {
                        if( effect3 & 0x00ff0000 )    // 80
                        {
                                if( effect3 & 0x00010000 ) effect += ({ sprintf( "PK: %d", get_effect(what, EFFECT_USER_PK) ) });
                                if( effect3 & 0x00020000 ) effect += ({ sprintf( "PK_RED: %d", get_effect(what, EFFECT_USER_PK_RED) ) });
//                              if( effect3 & 0x00040000 )
                                if( effect3 & 0x00080000 ) effect += ({ sprintf( "DIE: %d", get_effect(what, EFFECT_USER_DIE) ) });
                                if( effect3 & 0x00100000 ) effect += ({ sprintf( "DIE5: %d", get_effect(what, EFFECT_USER_DIE_5) ) });
                                if( effect3 & 0x00200000 ) effect += ({ sprintf( "DIE9: %d", get_effect(what, EFFECT_USER_DIE_9) ) });
//                              if( effect3 & 0x00400000 )
//                              if( effect3 & 0x00800000 )
                        }
                        if( effect3 & 0xff000000 )    // 88
                        {
//                              if( effect3 & 0x01000000 )
//                              if( effect3 & 0x02000000 )
                                if( effect3 & 0x04000000 ) effect += ({ sprintf( "ESCAPE: %d", get_effect(what, EFFECT_USER_ESCAPE) ) });
//                              if( effect3 & 0x08000000 )
//                              if( effect3 & 0x10000000 )
//                              if( effect3 & 0x20000000 )
                                if( effect3 & 0x40000000 ) effect += ({ sprintf( "ORG: %d", get_effect(what, EFFECT_ITEM_ORG) ) });
                                if( effect3 & 0x80000000 ) effect += ({ sprintf( "CITY: %d", get_effect(what, EFFECT_ITEM_CITY) ) });
                        }
                }
        }

        if( effect7 = get_effect_flag(what, 7) )    // 复杂征状标志(３２位)
        {
                if( effect7 & 0x0000ffff )
                {
                        if( effect7 & 0x000000ff )    // 96
                        {
                                if( effect7 & 0x00000001 ) effect += ({ sprintf( "POISON: %d %d/%d", get_effect(what, EFFECT_CHAR_POISON), get_effect_count(what, EFFECT_CHAR_POISON), get_effect_interval(what, EFFECT_CHAR_POISON) ) });
                                if( effect7 & 0x00000002 ) effect += ({ sprintf( "POISON_2: %d %d/%d", get_effect(what, EFFECT_CHAR_POISON_2), get_effect_count(what, EFFECT_CHAR_POISON_2), get_effect_interval(what, EFFECT_CHAR_POISON_2) ) });
                                if( effect7 & 0x00000004 ) effect += ({ sprintf( "BLOOD: %d %d/%d", get_effect(what, EFFECT_CHAR_BLOOD), get_effect_count(what, EFFECT_CHAR_BLOOD), get_effect_interval(what, EFFECT_CHAR_BLOOD) ) });
                                if( effect7 & 0x00000008 ) effect += ({ sprintf( "BURN: %d %d/%d", get_effect(what, EFFECT_USER_BURN), get_effect_count(what, EFFECT_USER_BURN), get_effect_interval(what, EFFECT_USER_BURN) ) });
                                if( effect7 & 0x00000010 ) effect += ({ sprintf( "HURT: %d %d/%d", get_effect(what, EFFECT_USER_HURT), get_effect_count(what, EFFECT_USER_HURT), get_effect_interval(what, EFFECT_USER_HURT) ) });
                                if( effect7 & 0x00000020 ) effect += ({ sprintf( "THUNDER: %d %d/%d", get_effect(what, EFFECT_USER_THUNDER), get_effect_count(what, EFFECT_USER_THUNDER), get_effect_interval(what, EFFECT_USER_THUNDER) ) });
                                if( effect7 & 0x00000040 ) effect += ({ sprintf( "FALL: %d %d/%d", get_effect(what, EFFECT_CHAR_FALL), get_effect_count(what, EFFECT_CHAR_FALL), get_effect_interval(what, EFFECT_CHAR_FALL) ) });
//                              if( effect7 & 0x00000080 )
                        }
                        if( effect7 & 0x0000ff00 )    // 104
                        {
                                if( effect7 & 0x00000100 ) effect += ({ sprintf( "INVISIBLE: %d %d/%d", get_effect(what, EFFECT_CHAR_INVISIBLE), get_effect_count(what, EFFECT_CHAR_INVISIBLE), get_effect_interval(what, EFFECT_CHAR_INVISIBLE) ) });
                                if( effect7 & 0x00000200 ) effect += ({ sprintf( "DREAM: %d %d/%d", get_effect(what, EFFECT_CHAR_DREAM), get_effect_count(what, EFFECT_CHAR_DREAM), get_effect_interval(what, EFFECT_CHAR_DREAM) ) });
                              	if( effect7 & 0x00000400 ) effect += ({ sprintf( "USE FOOD: %d %d/%d", get_effect(what, EFFECT_CON_HP_MP), get_effect_count(what, EFFECT_CON_HP_MP), get_effect_interval(what, EFFECT_CON_HP_MP) ) });
//                              if( effect7 & 0x00000800 )
//                              if( effect7 & 0x00001000 )
//                              if( effect7 & 0x00002000 )
                                if( effect7 & 0x00004000 ) effect += ({ sprintf( "RECOVER: %d %d/%d", get_effect(what, EFFECT_USER_RECOVER), get_effect_count(what, EFFECT_USER_RECOVER), get_effect_interval(what, EFFECT_USER_RECOVER) ) });
//                              if( effect7 & 0x00008000 )
                        }
                }
                if( effect7 & 0xffff0000 )
                {
                        if( effect7 & 0x00ff0000 )    // 112
                        {
                                if( effect7 & 0x00010000 ) effect += ({ sprintf( "STUDY: %d %d/%d", get_effect(what, EFFECT_USER_STUDY), get_effect_count(what, EFFECT_USER_STUDY), get_effect_interval(what, EFFECT_USER_STUDY) ) });
                                if( effect7 & 0x00020000 ) effect += ({ sprintf( "DANCE: %d %d/%d", get_effect(what, EFFECT_CHAR_DANCE), get_effect_count(what, EFFECT_CHAR_DANCE), get_effect_interval(what, EFFECT_CHAR_DANCE) ) });
                                if( effect7 & 0x00040000 ) effect += ({ sprintf( "SING: %d %d/%d", get_effect(what, EFFECT_CHAR_SING), get_effect_count(what, EFFECT_CHAR_SING), get_effect_interval(what, EFFECT_CHAR_SING) ) });
//                              if( effect7 & 0x00080000 )
//                              if( effect7 & 0x00100000 )
//                              if( effect7 & 0x00200000 )
//                              if( effect7 & 0x00400000 )
//                              if( effect7 & 0x00800000 )
                        }
/*                      if( effect7 & 0xff000000 )    // 120
                        {
                                if( effect7 & 0x01000000 )
                                if( effect7 & 0x02000000 )
                                if( effect7 & 0x04000000 )
                                if( effect7 & 0x08000000 )
                                if( effect7 & 0x10000000 )
                                if( effect7 & 0x20000000 )
                                if( effect7 & 0x40000000 )
                                if( effect7 & 0x80000000 )
                        }       */
                }
        }

        size = sizeof(effect);  result = "";
        for( i = 0, len = 0; i < size; i ++ ) 
        {
                len += strlen( effect[i] ) + 3;
                if( len >= OUTPUT_WIDTH )
                {
                        len = strlen( effect[i] );
                        result = sprintf( "%s\n%s  ", result, effect[i] );
                }
                else    result = sprintf( "%s%s  ", result, effect[i] );
        }
        if( result != "" ) tell_user(me, "%s", result);    // 注意：字串有 % 

        return 1;
}
