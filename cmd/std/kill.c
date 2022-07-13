#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg)
{
        object who, owner, map;
        int busy;
        if (is_gm(me))
                return 1;
        //	if (me->get_ride()) return 1;
        if (me->is_store_open())
        {
                notify("Đang bày hàng, không thể tấn công.");
                return 1;
        }
        if (me->get_save("passhanhtrang") && me->get_save("ndmkhtk") < 1)
        {
                send_user(me, "%c%c%d%s", 0x43, 10, 0, HIR "Hành trang của bạn đang trong trạng thái Khoá !");
                return 1;
        }
        if (busy = get_effect(me, EFFECT_CHAR_BUSY))
        {
                notify("Bạn còn phải bận %d giây", busy);
                return 1;
        }
        if (get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_DREAM_1) || get_effect(me, EFFECT_CHAR_DREAM))
                return 1;

        CHAR_CHAR_D->stop_loop_perform_8(me); // 中断持续效果(其它)
        if (!arg)
                return 1;

        if (!objectp(who = find_char(arg)))
        {
                //              notify( "您无法找到这个人." );
                return 1;
        }
        if (who == me->get("soldier"))
        {
                notify("Không thể đánh triệu hồi thú của chính mình!");
                return 1;
        }
        if (me == who)
        {
                notify("Bạn muốn tấn công chính mình?");
                return 1;
        }
        if (who->is_user() && who->get_login_flag() < 3)
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        if (who->is_die())
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }

        if (!inside_screen_2(me, who))
        {
                notify("Bạn cách %s quá xa rồi.", who->get_name());
                return 1;
        }
        owner = who;
        if (who->get_ower())
                owner = who->get_owner();
        /*
        if (owner->is_user())
        {
                map = get_map_object(get_z(me));
                if (!map) notify( "Bạn đang đứng ở đâu?" );
                else
                if (map->get_no_fight()) notify( "Bản đồ này không thể PK" );
                else
                if (map->is_virtual_scene())
                {
                        if (map->get_forbbit() ) notify( "Bản đồ này không thể PK" );
                        else
                        if ( me->get("no_fight")||owner->get("no_fight")) notify( "Hai người đều đã cấm chiến đấu" );
                }
                else
                if (map->get_client_id()==885) ;
                else
                if( MAP_D->is_inside_battle( get_z(me) ) )
                {
                        if( me->get_manager() == owner->get_manager() ) notify( "Cùng phe không thể PK nhau" );
                }
                else
                if (owner->get_attack_mode()!=0) notify( "%s chưa bật PK Tự Do.", owner->get_name() );
                else
                if (abs(owner->get_level()-me->get_level())>20) notify( "%s和您的等级相差超过20级.", owner->get_name() );
                else
                if (me->get_attack_mode()==1) notify( "Bạn đang ở chế độ : Hoà Bình" );
                else
                if (me->get_leader() && me->get_leader()==owner->get_leader() ) notify( "不能攻击队友" );
                else
                if (me->get_city_name() && me->get_city_name()!="" && me->get_city_name()==owner->get_city_name() ) notify( "不能攻击同国的人" );
                else
                if (me->get_no_fight())  notify( "您处于安全区域" );
                else
                if (owner->get_no_fight())  notify( "%s处于安全区域", owner->get_name() );

        }
*/
        if (who->is_user())
                send_user(me, "%c%c%d%c", 0xA2, 6, who->get_number(), who->get_save_2("online_rank.level")); //修为等级

        if (!who->can_be_fighted(me) || !me->can_fight(who))
        {
                send_user(me, "%c", 0x01); // 取消跟随攻击
                return 1;
        }
        if (me->get_char_action() != DEFAULT_ACT)
                me->set_char_action(DEFAULT_ACT); // 恢复站立状态(中止小动作)

        if (get_effect(me, EFFECT_CHAR_INVISIBLE))
                set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1); // 隐身(中断)
        me->set_enemy(0);
        me->start_fight(who);
        if (who->is_npc())
                who->start_fight(me); // 玩家需主动还击
        me->to_front_xy(get_x(who), get_y(who));
        if (!who->is_npc())
                me->set_clean_pk_time(0); //重新累计

        return 1;
}
