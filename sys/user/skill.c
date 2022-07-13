
#include <ansi.h>
#include <task.h>
#include <skill.h>

// 函数：生成二进制码
void SAVE_BINARY() {}

// 函数：获取升级所需火候
int get_upgrade_degree(int level)
{
        level++;
        return level * level * 5;
}

// 函数：获取升级所需潜能
int get_upgrade_potential(object me, int skill)
{
        int level = me->get_skill(skill);
        return (get_upgrade_degree(level) - me->get_skill_degree(skill)) / 5 + 1;
}

// 函数：增加技能火候
void improve_skill(object me, int skill, int degree)
{
        object file, perform;
        string result;
        int level;
        int i, size, pf;

        level = me->get_skill(skill);
        file = load_object(SKILL->get_skill_file(skill));
        if (file && (file->is_vita_skill() || level < me->get_max_skill_level_3())) // 限制：等级、最高
        {
                degree = me->get_skill_degree(skill) + abs(degree);
                me->set_skill_degree(skill, degree);
                result = (file) ? file->get_name() : "Kỹ năng vô danh";
                //                write_user( me, ECHO "您的\"%s\"熟练度升至 %d.", result, degree );

                if (!level || degree > get_upgrade_degree(level)) // 直接升 1 级
                {
                        level++;
                        me->set_skill_degree(skill, 0);
                        me->set_skill(skill, level);
                        //if (file->is_vita_skill()==1)
                        if (skill == 670 || skill == 680)
                        {
                                // 设置初始熟练度
                                me->set_skill_degree(skill, 1);
                                // 自动学习可以使用的技能
                                for (i = 0; i < 500; i++)
                                {
                                        pf = skill * 100 + i;
                                        if ("/sys/item/product"->check_vita_skill(me, pf))
                                                continue;
                                        perform = load_object(SKILL->get_perform_file(pf));
                                        if (perform)
                                        {
                                                if (perform->get_skill_color())
                                                        break;
                                                if (perform->get_skill_level() <= level)
                                                {
                                                        /*
							if (skill==640)
							{
								if (perform->get_skill_type()>0 && me->get_save_2("vita.type")!=perform->get_skill_type()) continue;
							}
*/
                                                        "/sys/item/product"->add_vita_skill(me, pf);
                                                        perform->can_perform(me);
                                                }
                                                else
                                                        break;
                                        }
                                        if (i > 40 && !perform)
                                                break;
                                }
                        }
                        if (file->is_vita_skill() == 1)
                                log_file("lifeskill.txt", sprintf("%s %s %d %d %d\n", short_time(), me->get_id(), me->get_number(), skill, level));
                        result = sprintf(HIC "\" %s \" của ngươi tăng đến cấp %d !", result, level);
                        send_user(me, "%c%s", '!', result);
                        write_user(me, result);
                }
        }
        else
        {
                result = (file = load_object(SKILL->get_skill_file(skill))) ? file->get_name() : "Kỹ năng vô danh";
                send_user(me, "%c%s", '!', "Kinh nghiệm của bạn không đủ để tăng " + result + "!");
        }
}

// 函数：增加技能火候(无经验限制)
void improve_skill_2(object me, int skill, int degree)
{
        object file;
        string result;
        int level;

        level = me->get_skill(skill);

        if (level < me->get_max_skill_level())
        {
                degree = me->set_skill_degree(skill, me->get_skill_degree(skill) + abs(degree));
                result = (file = load_object(SKILL->get_skill_file(skill))) ? file->get_name() : "Kỹ năng vô danh";
                write_user(me, ECHO "\"%s\" độ thuần thục tăng tới %d.", result, degree);

                if (!level || degree > get_upgrade_degree(level)) // 直接升 1 级
                {
                        level++;
                        me->set_skill(skill, level);
                        me->set_skill_degree(skill, 0);
                        result = sprintf(HIC "\" %s \" của ngươi tăng đến cấp %d !", result, level);
                        send_user(me, "%c%s", '!', result);
                        write_user(me, result);
                }
        }
}

// 函数：增加技能火候
void improve_skill_0095(object me, int skill, int degree)
{
        object file;
        string name, result;
        int level;
        level = me->get_skill(skill);

        if (level < me->get_max_skill_level())
        {
                degree = me->set_skill_degree(skill, me->get_skill_degree(skill) + abs(degree));

                if (!level || degree > get_upgrade_degree(level)) // 直接升 1 级
                {
                        level++;
                        me->set_skill(skill, level);
                        me->set_skill_degree(skill, 0);
                        name = me->get_org_name();
                        if (!name || name == "")
                                name = "Bang Phái Vô Danh";
                        result = (file = load_object(SKILL->get_skill_file(skill))) ? file->get_name() : "Kỹ năng vô danh";
                        result = sprintf(HIC "%s \"%s\" thăng tới cấp %d !", name, result, level);
                        FAMILY_D->org_channel(name, 0, result);
                }
        }
}

// 函数：减少技能火候
void decrease_skill(object me, int skill, int degree)
{
        object file;
        string result;
        int level, old_degree, upgrade_degree;

        degree = abs(degree);
        old_degree = me->get_skill_degree(skill);

        if (old_degree >= degree)
                me->set_skill_degree(skill, old_degree - degree);
        else
        {
                result = (file = load_object(SKILL->get_skill_file(skill))) ? file->get_name() : "Kỹ năng vô danh";

                if ((level = me->get_skill(skill) - 1) < 0) // 删除技能
                {
                        me->delete_skill(skill);
                        result = sprintf(HIR "\"%s\" huỷ bỏ giảm cấp !", result);
                }
                else
                {
                        me->set_skill(skill, level);
                        upgrade_degree = get_upgrade_degree(level);
                        degree -= old_degree;
                        me->set_skill_degree(skill, upgrade_degree > degree ? upgrade_degree - degree : 0);
                        result = sprintf(HIR "\"%s\" tới cấp %d !", result, level);
                }

                send_user(me, "%c%s", '!', result);
                write_user(me, result);
        }
}

// 函数：取消准备好的特殊技
void cancel_enabled_perform(object me, string perform)
{
        string file;
        int mp;

        if (stringp(file = me->get_perform_file()) // 准备好特殊技
            && load_object(file)                   // 特殊技存在
            && file != perform                     // 不同特殊技
            && (mp = file->get_sub_mp(me)))        // 会扣减法力
        {
                me->add_mp(-mp);
        }
}
