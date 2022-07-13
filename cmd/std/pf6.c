#include <ansi.h>
#include <skill.h>
#include <action.h>
#include <effect.h>

// 函数：命令处理
int main(object me, string arg2)
{
        object file, what;
        string id, item, family, arg;
        int busy, pf, x, y, which, count, time;
        me->set("new_heart", 1); // 新走路的标志
        if (me->is_store_open())
        {
                notify("您在摆摊，不能打架。");
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
        if (get_effect(me, EFFECT_CHAR_FAINT) || get_effect(me, EFFECT_CHAR_FAINT_2) || get_effect(me, EFFECT_SLEEP) || get_effect(me, EFFECT_MAGIC_4243) || get_effect(me, EFFECT_CHAR_FREEZE) || get_effect(me, EFFECT_CHAR_DREAM_1) || get_effect(me, EFFECT_CHAR_DREAM))
                return 1;

        count = me->get_2("go_count.count2");

        CHAR_CHAR_D->stop_loop_perform_9(me); // 中断持续效果(其它)

        if (!arg2)
        {
                return 1;
        }
        if (sscanf(arg2, "%d %s", time, arg) != 2)
        {
                return 1;
        }
        if (time > count)
        {
                count = time;
                me->set_2("go_count.count2", count);
        }
        else if (count > time)
        {
                notify("客户端时钟不对");
                return 1;
        }
        if (count > get_heart_timer(me))
        {
                notify("客户端时钟过快");
                return 1;
        }
        if (arg == "4131.@") // 控制召唤兽
        {
                PF_FILE_04131->main(me, 0, 0, 0, "@");
                return 1;
        }
        if (get_effect(me, EFFECT_CHAR_INVISIBLE))
        {
                pf = to_int(arg);
                if (pf != 3686 && pf != 3643)
                        set_effect_2(me, EFFECT_CHAR_INVISIBLE, 1, 1); // 隐身(中断)
        }
        if (get_effect(me, EFFECT_CHAR_NO_PF))
        {
                family = me->get_fam_name();
                if (family == "Côn Luân" || family == "Mao Sơn" || family == "Vân Mộng Cốc")
                {
                        notify("Ngươi bị trúng trạng thái phong ấn.");
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
        me->set_time("pf", time()); // 由 pf 成功后设置
        send_user(me, "%c%w%c%w", 0x50, 0, 0xff, 1);

        return 1;
}
