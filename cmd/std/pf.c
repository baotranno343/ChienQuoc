#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg)
{
        object file, what;
        string id, item, family;
        int busy, pf, x, y, which, count;

        if (me->is_store_open())
        {
                notify("Mở hàng rong không thể sử dụng.");
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
        if (gone_time(me->get_time("pf")) < 1) // 时间限制
        {
                //              me->set_time( "pf", time() );
                return 1;
        }

        if (get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_CHAR_NO_PF) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_MAGIC_4243) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_DREAM_1) || get_effect(me, EFFECT_CHAR_DREAM))
                return 1;

        count = get_heart_count_2(me);
        if (count > 0)
        {
                if (get_heart_state(me) == MAGIC_STAT)
                {
                        return 1;
                }
                set_heart_count_2(me, 0);
        }
        /*	
        if( get_heart_count_2(me) > 0 )
        {        	
                me->set_force_command("pf " + arg);    // 暂存特殊技命令
                return 1;
        }
*/
        CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)

        if (get_effect(me, EFFECT_CHAR_INVISIBLE))
        {
                pf = to_int(arg);
                if (pf != 3686 && pf != 3643)
                        set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1); // 隐身(中断)
        }

        if (!arg)
        {
                if (count > 0)
                        set_heart_count_2(me, count);
                return 1;
        }
        if (arg == "4131.@") // 控制召唤兽
        {
                PF_FILE_04131->main(me, 0, 0, 0, "@");
                if (count > 0)
                        set_heart_count_2(me, count);
                return 1;
        }

        if (me->get_char_action() != DEFAULT_ACT)
                me->set_char_action(DEFAULT_ACT); // 恢复站立状态(中止小动作)

        if (get_effect(me, EFFECT_CHAR_NO_PF))
        {
                family = me->get_fam_name();
                if (family == "Côn Luân" || family == "Mao Sơn" || family == "Vân Mộng Cốc")
                {
                        notify("Ngươi bị trúng trạng thái phong ấn.");
                        if (count > 0)
                                set_heart_count_2(me, count);
                        return 1; // 封魔诀：禁止法术、出招
                }
        }

        if (sscanf(arg, "%d %d,%d", pf, x, y) == 3)
        {
                if ((file = load_object(SKILL->get_perform_file(pf))) && file->get_perform_type() != ON_ME)
                        file->main(me, 0, x, y, "");
        }
        else if (sscanf(arg, "%d (%d)", pf, which) == 2)
        {
                if ((file = load_object(SKILL->get_perform_file(pf))) && file->get_perform_type() == ON_ITEM && (what = number_present(me, which, 1, MAX_CARRY)))
                        file->main(me, what, 0, 0, "");
        }
        else if (sscanf(arg, "%d %s %d", pf, id, which) == 3)
        {
                if ((file = load_object(SKILL->get_perform_file(pf))) && file->get_perform_type() == ON_ITEM_2 && (what = find_char(id)) && number_present(what, which, 1, MAX_CARRY))
                        file->main(me, what, 0, 0, sprintf("%d", which));
        }
        else if (sscanf(arg, "%d %s", pf, arg) == 2)
        {
                if ((file = load_object(SKILL->get_perform_file(pf))) && file->get_perform_type() == ON_CHAR && (what = find_char(arg)))
                {
                        if (what != me)
                        {
                                // 不能锁定隐身的人
                                if (get_effect(what, EFFECT_CHAR_INVISIBLE))
                                        return 1;
                        }
                        file->main(me, what, 0, 0, "");
                }
        }
        else if (sscanf(arg, "%d.%s", pf, arg) == 2)
        {
                if ((file = load_object(SKILL->get_perform_file(pf))) && file->get_perform_type() == ON_ME)
                        file->main(me, 0, 0, 0, arg);
        }
        else if (pf = to_int(arg))
        {
                if ((file = load_object(SKILL->get_perform_file(pf))) && file->get_perform_type() == ON_ME)
                        file->main(me, 0, 0, 0, "");
        }
        if (count > 0)
                set_heart_count_2(me, get_heart_count_2(me) + count);
        me->set_time("pf", time()); // 由 pf 成功后设置
        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 1);

        /*    if (me->get_attack_mode()==0)
        {
        	if (what && what->is_user() && what->get_attack_mode()==0)
        	{
        		set_effect(me, EFFECT_USER_PK, 600);
        	//	return 1;
        	}
        }*/

        return 1;
}
