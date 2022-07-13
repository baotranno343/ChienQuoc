
#include <skill.h>
class SkillLevel
{
        int Level;  // 等级
        int Degree; // 火候
}

private mapping Skills = ([]); // 技能等级

// -------------------------------------------------------------

// 函数：获取技能数据
mapping get_skill_dbase()
{

        return copy(Skills);
}

// 函数：初始技能数据
void init_skill_dbase()
{

        Skills = ([]);
}

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
        string name = sprintf("%04d", skill);

        level = range_value(level, 0, NPC->get_max_skill_level());
        if (undefinedp(Skills[name]))
                Skills[name] = new (class SkillLevel);
        ((class SkillLevel)Skills[name])->Level = level;

        return ((class SkillLevel)Skills[name])->Level;
}

// 函数：设置技能火候
int set_skill_degree(int skill, int degree)
{
        string name = sprintf("%04d", skill);
        degree = range_value(degree, 0, MAX_NUMBER);

        if (undefinedp(Skills[name]))
                Skills[name] = new (class SkillLevel);
        ((class SkillLevel)Skills[name])->Degree = degree;

        return ((class SkillLevel)Skills[name])->Degree;
}

// 函数：删除技能等级
void delete_skill(int skill)
{
        string name = sprintf("%04d", skill);

        if (undefinedp(Skills[name]))
                return;
        map_delete(Skills, name);
}

// -------------------------------------------------------------

// 函数：获取出招公式值(用于 /skill)
int get_pf_value(int skill, int square, int a, int b)
{
        int level, square2;

        level = get_skill(skill);
        square2 = level * (level + 1);
        return a + (square2 - square) / b;
}

// 函数：获取出招公式值(用于 /skill)
int get_pf_value_2(int skill, int square, int a, int b)
{
        int level, square2;

        level = get_skill(skill);
        square2 = level * (level + 1);
        return a + (square2 - square) / b;
}

/* -------------------------------------------------------------

private mapping Skills = ([ ]);         // 技能等级

// -------------------------------------------------------------

// 函数：获取技能数据集合
mapping get_skill_dbase() { return copy(Skills); }

// 函数：获取技能等级
int get_skill( int skill )
{
        string name = sprintf( "%04d", skill );
	if( undefinedp( Skills[name] ) ) return 0;
        return Skills[name];
}

// 函数：设置技能等级
int set_skill( int skill, int level )
{
        string name = sprintf( "%04d", skill );
	return Skills[name] = range_value(level, 0, MAX_NUMBER);
}

// 函数：删除技能等级
void delete_skill( int skill ) 
{
        string name = sprintf( "%04d", skill );
	if( undefinedp( Skills[name] ) ) return;
        map_delete(Skills, name);
}

------------------------------------------------------------- */
