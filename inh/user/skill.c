
#include <skill.h>

class SkillLevel
{
        int Level;  // 等级
        int Degree; // 火候
}

private mapping Skills = ([]); // 技能等级

private
mapping Skills_0 = ([]); // 技能等级(转生前)  // 转生时，记录门派技能
private
mapping Skills_1 = ([]); // 技能等级(一转)
private
mapping Skills_2 = ([]); // 技能等级(二转)

// -------------------------------------------------------------

// 函数：获取技能数据
mapping get_skill_dbase() { return copy(Skills); }

// 函数：获取技能数据(转生前)
mapping get_skill_0_dbase() { return copy(Skills_0); }
mapping get_skill_1_dbase() { return copy(Skills_1); }
mapping get_skill_2_dbase() { return copy(Skills_2); }

// 函数：初始技能数据
void init_skill_dbase() { Skills = ([]); }

// 函数：初始技能数据(转生前)
void init_skill_0_dbase() { Skills_0 = ([]); }
void init_skill_1_dbase() { Skills_1 = ([]); }
void init_skill_2_dbase() { Skills_2 = ([]); }

// -------------------------------------------------------------

// 函数：获取技能等级
int get_skill(int skill)
{
        string name = sprintf("%04d", skill);
        if (undefinedp(Skills[name]))
                return 0;
        return ((class SkillLevel)Skills[name])->Level;
}

// 函数：获取技能火候
int get_skill_degree(int skill)
{
        string name = sprintf("%04d", skill);
        if (undefinedp(Skills[name]))
                return 0;
        return ((class SkillLevel)Skills[name])->Degree;
}

// 函数：设置技能等级
int set_skill(int skill, int level)
{
        object file, me;
        string name = sprintf("%04d", skill);

        level = range_value(level, 0, NPC->get_max_skill_level());

        if (undefinedp(Skills[name]))
                Skills[name] = new (class SkillLevel);

        if (((class SkillLevel)Skills[name])->Level != level && (file = load_object(SKILL->get_skill_file(skill))))
        {
                me = this_object();
                if (((class SkillLevel)Skills[name])->Level > level)
                        file->remove_perform(me);

                if (file->is_vita_skill())
                        send_user(me, "%c%c%w%w%d%s", 0x60, 1, skill, level, me->get_skill_degree(skill), file->get_name());
                else if (file->is_basic_skill())
                        send_user(me, "%c%w%w%d%s", 0x55, skill, level, 0, file->get_name());
                else
                        send_user(me, "%c%w%w%d%s", 0x53, skill, level, 0, file->get_name());
                send_user(me, "%c%w%c", 0x35, skill, 0); // 清空技能、特殊技描述！

                ((class SkillLevel)Skills[name])->Level = level;

                file->can_perform(me);
                file->recount_char(me);
                if (skill <= 600)
                        "/quest/help"->send_help_tips(me, 11);
                else
                {
                        "/quest/help"->send_help_tips(me, 28);
                        "/quest/help"->send_help_tips(me, 46);
                }
        }

        return level;
}

// 函数：设置技能火候
int set_skill_degree(int skill, int degree)
{
        object file;
        object me = this_object();
        string name = sprintf("%04d", skill);

        degree = range_value(degree, 0, MAX_NUMBER);

        if (undefinedp(Skills[name]))
                Skills[name] = new (class SkillLevel);

        if (((class SkillLevel)Skills[name])->Degree != degree && (file = load_object(SKILL->get_skill_file(skill))))
        {
                if (file->is_vita_skill())
                {
                        // 生活技能的熟练度有上限
                        //        		if ( degree> ( (class SkillLevel) Skills[name] ) ->Level + 10 ) degree = ( (class SkillLevel) Skills[name] ) ->Level + 10;
                        send_user(me, "%c%c%w%w%d%s", 0x60, 1, skill, ((class SkillLevel)Skills[name])->Level, degree, file->get_name());
                }
                else if (file->is_basic_skill())
                        send_user(this_object(), "%c%w%w%d%s", 0x55, skill, ((class SkillLevel)Skills[name])->Level, degree, file->get_name());
                else
                        send_user(this_object(), "%c%w%w%d%s", 0x53, skill, ((class SkillLevel)Skills[name])->Level, degree, file->get_name());
        }

        return ((class SkillLevel)Skills[name])->Degree = degree;
}

// 函数：删除技能等级
void delete_skill(int skill)
{
        object file, me;
        string name = sprintf("%04d", skill);

        if (undefinedp(Skills[name]))
                return;

        map_delete(Skills, name);

        if (file = load_object(SKILL->get_skill_file(skill)))
        {
                me = this_object();
                file->recount_char(me);
                if (file->is_vita_skill())
                        send_user(me, "%c%c%w", 0x60, 0, skill);
                else
                        send_user(me, "%c%w%w", 0x53, 0xffff, skill);
        }
}

// -------------------------------------------------------------

// 函数：获取技能等级(转生前)
int get_skill_0(int skill)
{
        string name = sprintf("%04d", skill);
        if (Skills_0 == 0)
                Skills_0 = ([]);
        if (undefinedp(Skills_0[name]))
                return 0;
        return Skills_0[name];
}

int get_skill_1(int skill)
{
        string name = sprintf("%04d", skill);
        if (Skills_1 == 0)
                Skills_1 = ([]);
        if (undefinedp(Skills_1[name]))
                return 0;
        return Skills_1[name];
}

int get_skill_2(int skill)
{
        string name = sprintf("%04d", skill);
        if (Skills_2 == 0)
                Skills_2 = ([]);
        if (undefinedp(Skills_2[name]))
                return 0;
        return Skills_2[name];
}

int get_skill_1_2(int skill) // get_skill_1 + get_skill_2
{
        int level = 0;
        string name = sprintf("%04d", skill);
        if (Skills_1 == 0)
                Skills_1 = ([]);
        if (Skills_2 == 0)
                Skills_2 = ([]);
        if (!undefinedp(Skills_1[name]))
                level += Skills_1[name];
        if (!undefinedp(Skills_2[name]))
                level += Skills_2[name];
        return level;
}

// 函数：设置技能等级(转生前)
int set_skill_0(int skill, int level)
{
        string name = sprintf("%04d", skill);
        if (Skills_0 == 0)
                Skills_0 = ([]);
        return Skills_0[name] = range_value(level, 0, MAX_NUMBER);
}

int set_skill_1(int skill, int level)
{
        string name = sprintf("%04d", skill);
        if (Skills_1 == 0)
                Skills_1 = ([]);
        return Skills_1[name] = range_value(level, 0, MAX_NUMBER);
}

int set_skill_2(int skill, int level)
{
        string name = sprintf("%04d", skill);
        if (Skills_2 == 0)
                Skills_2 = ([]);
        return Skills_2[name] = range_value(level, 0, MAX_NUMBER);
}

// 函数：删除技能等级(转生前)
void delete_skill_0(int skill)
{
        string name = sprintf("%04d", skill);
        if (Skills_0 == 0)
                Skills_0 = ([]);
        if (undefinedp(Skills_0[name]))
                return;
        map_delete(Skills_0, name);
}

void delete_skill_1(int skill)
{
        string name = sprintf("%04d", skill);
        if (Skills_1 == 0)
                Skills_1 = ([]);
        if (undefinedp(Skills_1[name]))
                return;
        map_delete(Skills_1, name);
}

void delete_skill_2(int skill)
{
        string name = sprintf("%04d", skill);
        if (Skills_2 == 0)
                Skills_2 = ([]);
        if (undefinedp(Skills_2[name]))
                return;
        map_delete(Skills_2, name);
}

// -------------------------------------------------------------

// 函数：增加技能火候
void improve_skill(int skill, int degree) { return USER_SKILL_D->improve_skill(this_object(), skill, degree); }

// 函数：减少技能火候
void decrease_skill(int skill, int degree) { return USER_SKILL_D->decrease_skill(this_object(), skill, degree); }
