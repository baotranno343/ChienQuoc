
#include <effect.h>
#include <skill.h>

// 函数：生成二进制码
void SAVE_BINARY() { }

// 函数：NPC 征状更新
void into_effect( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) 
{
	string file, arg;
        if( effect1 )    // 简单征状标志１(３２位)
        {
                if( effect1 & 0x0000ffff )
                {
                        if( effect1 & 0x000000ff )    // 0
                        {
//                              if( effect1 & 0x00000001 )      // LOGIN
//                              if( effect1 & 0x00000002 )      // BUSY
                                if( effect1 & 0x00000004 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_FAINT_0);    // FAINT
//                              if( effect1 & 0x00000008 )      // FAINT_0
                                if( effect1 & 0x00000010 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_FAINT_3);    // FAINT_2
//                              if( effect1 & 0x00000020 )      // FAINT_3
                                if( effect1 & 0x00000040 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_FREEZE_0);    // FREEZE
//                              if( effect1 & 0x00000080 )      // FREEZE_0
                        }
                        if( effect1 & 0x0000ff00 )    // 8
                        {
                                if( effect1 & 0x00000100 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_SHUT_0);    // SHUT
//                              if( effect1 & 0x00000200 )      // SHUT_0
                                if( effect1 & 0x00000400 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_NO_PF_0);    // NO_PF
//                              if( effect1 & 0x00000800 )      // NO_PF_0
                                if( effect1 & 0x00001000 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_LAZY_0);    // LAZY
//                              if( effect1 & 0x00002000 )      // LAZY_0
                                if( effect1 & 0x00004000 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_SLOW_0);    // SLOW
//                              if( effect1 & 0x00008000 )      // SLOW_0
                        }
                }
                if( effect1 & 0xffff0000 )
                {
                        if( effect1 & 0x00ff0000 )    // 16
                        {
                                if( effect1 & 0x00010000 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_DREAM_1);    // DREAM_1
//                              if( effect1 & 0x00020000 )      // DREAM_0
                                if( effect1 & 0x00040000 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_CHAOS_0);    // CHAOS
//                              if( effect1 & 0x00080000 )      // CHAOS_0
                                if( effect1 & 0x00100000 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_WOUND_0);    // WOUND
//                              if( effect1 & 0x00200000 )      // WOUND_0
//                              if( effect1 & 0x00400000 )
//                              if( effect1 & 0x00800000 )      // BLOOD_0
                        }
                        if( effect1 & 0xff000000 )    // 24
                        {
                                if( effect1 & 0x01000000 ) "/effect/protect"->into_effect(me, EFFECT_CHAR_BLIND_0);    // BLIND
//                              if( effect1 & 0x02000000 )      // BLIND_0
//                              if( effect1 & 0x04000000 )
//                              if( effect1 & 0x08000000 )      // BURN_0
                                if( effect1 & 0x10000000 ) "/skill/02/02114"->into_effect(me);
//                              if( effect1 & 0x20000000 )
//                              if( effect1 & 0x40000000 )
//                              if( effect1 & 0x80000000 )
                        }
                }
        }

        if( effect2 )    // 简单征状标志２(３２位)
        {
                if( effect2 & 0x0000ffff )
                {
                        if( effect2 & 0x000000ff )    // 32
                        {
                                if( effect2 & 0x00000001 ) "/effect/0531-1"->into_effect_2(me);     // 0531_1  // HP
                                if( effect2 & 0x00000002 ) "/effect/0531-2"->into_effect_2(me);     // 0531_2  // MP
                                if( effect2 & 0x00000004 ) { "/effect/zombie"->into_effect(me);  if( !me ) return; }   // ZOMBIE  // AP
                                if( effect2 & 0x00000008 ) "/skill/03/03291"->effect_done(me);
//                              if( effect2 & 0x00000010 )      // CP
                                if( effect2 & 0x00000020 ) "/skill/03/03291"->effect_done2(me);
//                              if( effect2 & 0x00000040 )
//                              if( effect2 & 0x00000080 )
                        }
                        if( effect2 & 0x0000ff00 )    // 40
                        {
                                if( effect2 & 0x00000100 ) me->add_ap(50);      // 5215
//                              if( effect2 & 0x00000200 )
//                              if( effect2 & 0x00000400 )
                                if( effect2 & 0x00000800 ) "/skill/02/02123"->effect_done(me);
//                              if( effect2 & 0x00001000 )
//                              if( effect2 & 0x00002000 )
                                if( effect2 & 0x00004000 ) "/skill/03/03173"->effect_done(me);
                                if( effect2 & 0x00008000 ) "/skill/04/04211"->into_effect(me);
                        }
                }
                if( effect2 & 0xffff0000 )
                {
                        if( effect2 & 0x00ff0000 )    // 48
                        {
                                if( effect2 & 0x00010000 ) { CHAR_CHAR_D->effect_attack_done(me);  if( !me ) return; }
                                if( effect2 & 0x00020000 ) { CHAR_CHAR_D->effect_move_done(me);  if( !me ) return; }
                                if( effect2 & 0x00040000 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_NO_MOVE);    // FAINT_2
                                if( effect2 & 0x00080000 ) { CHAR_CHAR_D->effect_change_done(me);  if( !me ) return; }
                                if( effect2 & 0x00100000 ) "/effect/protect"->into_effect_2(me, EFFECT_SLEEP);    // SLEEP
//                              if( effect2 & 0x00200000 )
//                              if( effect2 & 0x00400000 )
//                              if( effect2 & 0x00800000 )
                        }
                        if( effect2 & 0xff000000 )    // 56
                        {
                                if( effect2 & 0x01000000 ) CHAR_CHAR_D->effect_armorfall_done(me);
                                if( effect2 & 0x02000000 ) CHAR_CHAR_D->effect_add_dp_done(me);
                                if( effect2 & 0x04000000 ) CHAR_CHAR_D->effect_add_pp_done(me);
                                if( effect2 & 0x08000000 ) CHAR_CHAR_D->effect_powerfall_done(me);
                                if( effect2 & 0x10000000 ) CHAR_CHAR_D->effect_powerup_done(me);
                                if( effect2 & 0x20000000 ) CHAR_CHAR_D->effect_miss_done(me);
                                if( effect2 & 0x40000000 ) CHAR_CHAR_D->effect_halfgod_done(me);
                                if( effect2 & 0x80000000 ) CHAR_CHAR_D->effect_immortal_done(me);
                        }
                }
        }

        if( effect3 )    // 简单征状标志３(３２位)
        {
                if( effect3 & 0x0000ffff )
                {
                        if( effect3 & 0x000000ff )    // 64
                        {
                                if( effect3 & 0x00000001 ) CHAR_CHAR_D->effect_powerup2_done(me);
                                if( effect3 & 0x00000002 ) CHAR_CHAR_D->effect_powerup3_done(me);
                                if( effect3 & 0x00000004 ) CHAR_CHAR_D->effect_miss2_done(me);
                                if( effect3 & 0x00000008 ) "/skill/02/02614"->into_effect(me);
//                              if( effect3 & 0x00000008 )
                                if( effect3 & 0x00000010 )
                                {
                                	file = me->get_progress_file();
                                	arg = me->get_progress_arg();
                                	if (file)
                                		file->into_effect(me, arg);
                                }
/*                                                                
                                if( effect3 & 0x00000020 )
                                if( effect3 & 0x00000040 )      // 9140
                                if( effect3 & 0x00000080 )      // 9145
*/                        }       
                        if( effect3 & 0x0000ff00 )    // 72
                        {
//                              if( effect3 & 0x00000100 )
//                              if( effect3 & 0x00000200 )      // KING
//                              if( effect3 & 0x00000400 )      // KING_2
//                              if( effect3 & 0x00000800 )      // CHAN
//                              if( effect3 & 0x00001000 )      // SUPPRESS
//                              if( effect3 & 0x00002000 )
//                              if( effect3 & 0x00004000 )      // HERB
//                              if( effect3 & 0x00008000 )      // HERB_OK
                        }
                }
                if( effect3 & 0xffff0000 )
                {
			if( effect3 & 0x00ff0000 )    // 80
                        {
//                                if( effect3 & 0x00010000 )      // PK
//                                if( effect3 & 0x00020000 )      // PK_RED
//                                if( effect3 & 0x00040000 )
				  if( effect3 & 0x00080000 )      NPC_PET_D->revive(me);// DIE
//                                if( effect3 & 0x00100000 )      // DIE_5
//                                if( effect3 & 0x00200000 )      // DIE_9
//                                if( effect3 & 0x00400000 )
//                                if( effect3 & 0x00800000 )
                        }       
/*                      if( effect3 & 0xff000000 )    // 88
                        {
                                if( effect3 & 0x01000000 )
                                if( effect3 & 0x02000000 )
                                if( effect3 & 0x04000000 )      // ESCAPE
                                if( effect3 & 0x08000000 )
                                if( effect3 & 0x10000000 )
                                if( effect3 & 0x20000000 )
                                if( effect3 & 0x40000000 )      // ORG
                                if( effect3 & 0x80000000 )      // CITY
                        }       */
                }
        }
        if( effect4 )    // 简单征状标志４(３２位)
        {
                if( effect4 & 0x0000ffff )
                {
                      if( effect4 & 0x000000ff )    // 96
                        {
                                if( effect4 & 0x00000001 ) "/skill/02/02516"->into_effect(me);
//                                if( effect4 & 0x00000002 ) CHAR_CHAR_D->effect_powerup3_done(me);
//                                if( effect4 & 0x00000004 ) CHAR_CHAR_D->effect_miss2_done(me);
//                                if( effect4 & 0x00000008 ) "/skill/02/02614"->into_effect(me);
//                                if( effect4 & 0x00000010 )
//                                if( effect4 & 0x00000020 ) "/skill/03/03642"->into_effect(me);
/*                                if( effect4 & 0x00000040 )      // 9140
                                if( effect4 & 0x00000080 )      // 9145
*/                                
                	}  
                }
	}         

        if( effect7 )    // 复杂征状标志(３２位)
        {
                if( effect7 & 0x0000ffff )
                {
                        if( effect7 & 0x000000ff )    // 192
                        {
                                if( effect7 & 0x00000001 ) { "/effect/poison"->into_effect(me);  if( !me ) return; }    // POISON
                                if( effect7 & 0x00000002 ) { "/effect/poison"->into_effect_2(me);  if( !me ) return; }    // POISON_2
                                if( effect7 & 0x00000004 ) { "/effect/protect"->into_effect(me, EFFECT_CHAR_BLOOD_0);  if( !me ) return; }    // BLOOD
                                if( effect7 & 0x00000008 ) "/effect/protect"->into_effect(me, EFFECT_USER_BURN_0);    // BURN
                                if( effect7 & 0x00000010 ) { PF_FILE_03632->effect_hurt_done(me);  if( !me ) return; }
                                if( effect7 & 0x00000020 ) "/skill/02/02616"->into_effect(me);
                                if( effect7 & 0x00000040 ) { CHAR_CHAR_D->effect_fall_done(me);  if( !me ) return; }
                                if( effect7 & 0x00000080 ) CHAR_CHAR_D->effect_fmp_done(me);
                        }
                        if( effect7 & 0x0000ff00 )    // 200
                        {
                                if( effect7 & 0x00000100 ) { CHAR_CHAR_D->effect_invisible_done(me);  if( !me ) return; }
                                if( effect7 & 0x00000200 ) "/effect/protect"->into_effect_2(me, EFFECT_CHAR_DREAM_0);    // DREAM
                              	if( effect7 & 0x00000400 ) "/sys/item/food"->into_effect(me);
                                if( effect7 & 0x00000800 ) 
                                {
                                	file = me->get_progress_file();
                                	arg = me->get_progress_arg();
                                	if (file)
                                		file->into_effect(me, arg);
                                }                                
                                if( effect7 & 0x00001000 ) "/effect/protect"->into_effect_2(me, EFFECT_CON_RECOVER);
                              	if( effect7 & 0x00002000 ) "/sys/item/food"->into_effect2(me);
//                              if( effect7 & 0x00004000 )      // RECOVER
                                if( effect7 & 0x00008000 ) { PF_FILE_04236->effect_thunder_done(me);  if( !me ) return; }
                        }
                }
                if( effect7 & 0xffff0000 )
                {
                        if( effect7 & 0x00ff0000 )    // 208
                        {
//                              if( effect7 & 0x00010000 )      // STUDY
                                if( effect7 & 0x00020000 ) "/effect/sing"->into_dance_effect(me);   // DANCE
                                if( effect7 & 0x00040000 ) "/effect/sing"->into_sing_effect(me);   // SING
//                              if( effect7 & 0x00080000 )
//                              if( effect7 & 0x00100000 )
//                              if( effect7 & 0x00200000 )
				if( effect7 & 0x00400000 ) "sys/sys/magic_card"->into_npc_effect(me);
				if( effect7 & 0x00800000 ) "/effect/protect"->into_effect(me,EFFECT_CHAR_IGNORE);
                        }
                        if( effect7 & 0xff000000 )    // 216
                        {
                              	if( effect7 & 0x01000000 ) "/effect/protect"->into_effect(me,EFFECT_CHAR_GOOD_BAD);
                              	if( effect7 & 0x02000000 ) "/effect/protect"->into_effect(me,EFFECT_CHAR_SOUL_LOCK);
//                              if( effect7 & 0x04000000 )
//                              if( effect7 & 0x08000000 )
//                              if( effect7 & 0x10000000 )
//                              if( effect7 & 0x20000000 )
//                              if( effect7 & 0x40000000 )
//                              if( effect7 & 0x80000000 )
                        }
                }
        }
        CHAR_CHAR_D->init_loop_perform(me);
}
