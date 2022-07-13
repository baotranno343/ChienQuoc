#include <time.h>
#include <npc.h>
#include <ansi.h>
#include <skill.h>
#include <effect.h>
#include <equip.h>
#include <task.h>

private
int Reincarnation; // 转生次数

private
int UpgradeExp; // 升级经验
private
int BillionExp; // 总经验(十亿标志)
private
int Experience; // 总经验
private
int Potential; // 潜能
private
int Total_bonus; //总功德点
private
int Bonus; // 功德 10点算1点
private
int GiftPoint; // 属性点
private
int MaxLevel; // 最高等级(用于属性点)
private
int Level; // 等级
private
mapping HotKey = ([]);
private
int Cash; // 现金
private
int CashKhoa; // 现金
private
int KnbKhoa;
private
int Savings; // 存款
private
string Marry; // 配偶
private
int Divorced; // 离婚次数
private
int PK; // PK 标志
private
int clean_pk_time; //清楚PK标志时间点
private
int max_pawn; // 最大当铺数

private
static int TaskXY; // 任务坐标
private
static mapping mpTaskXY; // 综合任务坐标

int get_login_flag();

int set_level(int level);

// -------------------------------------------------------------
//获取清除PK标志时间
int get_clean_pk_time() { return clean_pk_time; }
//设置清除PK标志时间
int set_clean_pk_time(int time) { return clean_pk_time = time; }
//增加清除PK标志时间
int add_clean_pk_time(int time) { return set_clean_pk_time(clean_pk_time + time); }
// 函数：获取转生次数
int get_reincarnation() { return Reincarnation; }

// 函数：设置转生次数
int set_reincarnation(int life) { return Reincarnation = range_value(life, 0, 2); }

// 函数：获取最高人物等级
int get_max_char_level()
{
        return 60;
}

// 函数：获取最高人物等级
int get_max_char_level_2()
{
        return 60;
}
// 函数：获取最高技能等级
int get_max_skill_level()
{
        return 70;
}

// 函数：获取最高技能等级
int get_max_skill_level_2() { return 70; }

// 函数：获取最高技能等级
int get_max_skill_level_3()
{
        return 70;
}

// 函数：获取最高技能等级(基本)
int get_max_basic_skill_level_2() { return 70; }

// 函数：获取最高技能等级(基本)
int get_max_basic_skill_level_3()
{
        return 70;
}

int get_skill(int skill);
int get_skill_1(int skill);
int get_skill_1_2(int skill);

// 函数：获取出招公式值(用于 /skill)
int get_pf_value(int skill, int square, int a, int b)
{
        int level = get_skill(skill);
        int square2 = level * (level + 1);
        return a + (square2 - square) / b;
}

// 函数：获取出招公式值(用于 /skill)
int get_pf_value_2(int skill, int square, int a, int b) // 同转生相关
{
        int level = get_skill(skill);
        int square2 = level * (level + 1);

        switch (Reincarnation)
        {
        default:
                return a + (square2 - square) / b;
        case 1:
                return a * (120 + get_skill_1(skill)) / 100 + (square2 - square) / b * 100 / 80;
        case 2:
                return a * (140 + get_skill_1_2(skill)) / 100 + (square2 - square) / b * 100 / 60;
        }
}

// 函数：获取属性点倍数
int get_gift_point_times()
{
        switch (Reincarnation)
        {
        default:
                return 4;
        case 1:
                return 6;
        case 2:
                return 8;
        }
}

// 函数：获取最高功德点数
int get_max_bonus()
{
        switch (Reincarnation)
        {
        default:
                return 20000;
        case 1:
                return 40000;
        case 2:
                return 80000;
        }
}

// 函数：获取当铺数量基数
int get_max_pawn_size()
{
        if (!max_pawn)
        {
                switch (Reincarnation)
                {
                default:
                        return max_pawn = Level / 10 + 1;
                case 1:
                        return max_pawn = Level / 10 + 14; // +13
                case 2:
                        return max_pawn = Level / 10 + 28; // +13 +14
                }
        }

        return max_pawn;
}

// 函数：设置当铺数量基数
int set_max_pawn_size(int i)
{
        return max_pawn = range_value(i, 1, 100);
}

// 函数：获取减少装备等级
int get_equip_less_level()
{
        switch (Reincarnation)
        {
        default:
                return 0;
        case 1:
                return 10;
        case 2:
                return 20;
        }
}

// -------------------------------------------------------------

// 函数：获取升级经验
int get_upgrade_exp() { return UpgradeExp; }

// 函数：设置升级经验
int set_upgrade_exp(int exp)
{
        int max;
        object me = this_object();
        max = USER_EXP_D->get_upgrade_exp_limit(me); //获取经验上限
        if (exp > max)
        {
                send_user(me, "%c%s", '!', "Kinh nghiệm đã đạt hạn mức cao nhất");
                exp = max;
        }
        return UpgradeExp = range_value(exp, -MAX_NUMBER, MAX_NUMBER);
}

// 函数：增添升级经验
int add_upgrade_exp(int exp) { return set_upgrade_exp(UpgradeExp + exp); }

// 函数：获取经验标志(十亿)
int get_billion_exp() { return BillionExp; }

// 函数：设置经验标志(十亿)
int set_billion_exp(int exp) { return BillionExp = range_value(exp, 0, 1000); } // 上限：万亿

// 函数：增添经验标志(十亿)
int add_billion_exp(int exp) { set_billion_exp(BillionExp + exp); }

// 函数：获取经验属性
int get_exp() { return Experience; }

// 函数：设置经验属性
varargs int set_exp(int exp, int bil_exp)
{
        object me;
        string result;
        int status;

        if (bil_exp != 0) // exp, bil_exp 必须同号
        {
                if (bil_exp > 0 && exp < 0)
                        bil_exp = 0;
                if (bil_exp < 0 && exp > 0)
                        bil_exp = 0;
        }

        BillionExp = bil_exp + exp / BILLION_NUMBER;
        Experience = exp % BILLION_NUMBER;

        if (Level < 10 && UpgradeExp >= USER_EXP_D->get_level_exp(Reincarnation, Level))
        {
                me = this_object();

                USER_EXP_D->recount_user_level(me);
                USER_ENERGY_D->count_all_prop(me);

                me->set_hp(me->get_max_hp()); // 升级加满气血
                me->set_mp(me->get_max_mp());

                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          9043, 1, OVER_BODY, 9044, 1, OVER_BODY, PF_ONCE);

                result = sprintf(HIC "Bạn tăng lên cấp %d !", Level);
                send_user(me, "%c%s", '!', result);
                write_user(me, result);
                TEACHER_D->add_shifu_exp(me, 1); //奖励师傅经验
                "sys/user/huynhde"->add_phanthuong(me, 1);
                if (me->get_org_name() != "")
                        "/sys/sys/manager"->upgrade(me);
                "/quest/zg_dict"->player_can_be_gala(me, 1); //	给予玩家战国宝典以及摇奖机会
        }
        else if (Level < 11 && UpgradeExp >= USER_EXP_D->get_level_exp(Reincarnation, Level))
        {
                me = this_object();
                status = me->get_save("tips_status");
                if ((status & 32) == 0) // 第一次升级
                {
                        notify("Thăng cấp bằng cách nhấn vào nút thăng cấp trong giao diện thuộc tính.");
                        status |= 32;
                        me->set_save("tips_status", status);
                }
                "/quest/help"->send_help_tips(me, 19);
        }
        if (get_login_flag() >= 3)
                send_user(this_object(), "%c%c%w%d%d", 0x3d, 40, BillionExp, Experience, UpgradeExp);

        return Experience;
}

// 函数：手动升级
int Upgrade()
{
        object me;
        string result;
        //   mixed *mxTime;
        int status;
        int sub_exp;
        sub_exp = USER_EXP_D->get_level_exp(Reincarnation, Level);
        if (Level < get_max_char_level() && UpgradeExp >= sub_exp)
        {
                me = this_object();
                me->set_upgrade_exp(UpgradeExp - sub_exp);
                set_level(Level + 1);
                me->count_gift();
                USER_ENERGY_D->count_all_prop(me);

                me->set_hp(me->get_max_hp()); // 升级加满气血
                me->set_mp(me->get_max_mp());

                send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
                          9043, 1, OVER_BODY, 9044, 1, OVER_BODY, PF_ONCE);

                result = sprintf(HIC "Bạn tăng lên cấp %d !", Level);
                send_user(me, "%c%s", '!', result);
                write_user(me, result);
                // mxTime = localtime(time());
                // log_file(sprintf("levelup_%d%02d%02d.txt", mxTime[TIME_YEAR], mxTime[TIME_MON] + 1, mxTime[TIME_MDAY]), sprintf("%s %s %d %s %d %s\n", short_time(), me->get_id(), me->get_number(), me->get_name(), Level, me->get_fam_name()));
                // TEACHER_D->add_shifu_exp(me, sub_exp); //奖励师傅经验
                //  "sys/user/huynhde"->add_phanthuong(me, sub_exp);
                if (me->get_org_name() != "")
                        "/sys/sys/manager"->upgrade(me);
                "/quest/zg_dict"->player_can_be_gala(me, 1); //	给予玩家战国宝典以及摇奖机会
        }

        if (get_login_flag() >= 3)
                send_user(this_object(), "%c%c%w%d%d", 0x3d, 40, BillionExp, Experience, UpgradeExp);

        return Experience;
}

// 函数：增添经验属性
int add_exp(int exp)
{
        set_upgrade_exp(UpgradeExp + exp); // 同步影响 upgrade_exp, 在 set_exp 前
        TASK_MASTER_D->check_quest(this_object(), exp, 2);
        if (BillionExp == 0)
        {
                set_exp(Experience + exp);
        }
        else if (BillionExp > 0)
        {
                if (exp > 0)
                {
                        Experience += exp % BILLION_NUMBER;
                        BillionExp += Experience / BILLION_NUMBER;
                        set_exp(Experience, BillionExp);
                }
                else if (exp < 0)
                {
                        Experience += exp % BILLION_NUMBER + BILLION_NUMBER;
                        BillionExp--;
                        set_exp(Experience, BillionExp);
                }
        }
        else
        {
                if (exp < 0)
                {
                        Experience += exp % BILLION_NUMBER;
                        BillionExp += Experience / BILLION_NUMBER;
                        set_exp(Experience, BillionExp);
                }
                else if (exp > 0)
                {
                        Experience += exp % BILLION_NUMBER - BILLION_NUMBER;
                        BillionExp++;
                        set_exp(Experience, BillionExp);
                }
        }

        return Experience;
}

// 函数：获取最大潜能
int get_max_potential() { return range_value(Level, 1, MAX_NUMBER) * 1000; } // 注意新登录情况

// 函数：获取潜能属性
int get_potential() { return Potential; }

// 函数：设置潜能属性
int set_potential(int point)
{
        if (point > get_max_potential())
                point = get_max_potential(); //send_user( this_object(), "%c%s", '!', "Tiềm năng của bạn đã max, không thể tăng thêm nữa." );
        point = range_value(point, 0, get_max_potential());
        if (Potential != point && get_login_flag() > 1)
                send_user(this_object(), "%c%c%d", 0x3d, 41, point);
        return Potential = point;
}

// 函数：增加潜能属性
int add_potential(int point)
{
        TASK_MASTER_D->check_quest(this_object(), point, 3);
        return set_potential(Potential + point);
}

// 函数：获取功德点
int get_bonus() { return Bonus; }
//函数：获取总功德点
int get_total_bonus() { return Total_bonus; }
// 函数：设置功德点
int set_bonus(int point)
{
        point = range_value(point, 0, get_max_bonus());
        if (Bonus != point && get_login_flag() > 1)
                send_user(this_object(), "%c%c%d", 0x3d, 42, point / 10);
        if (point > 0)
                Total_bonus = point;
        return Bonus = point;
}

// 函数：增加功德点
int add_bonus(int point) { return set_bonus(Bonus + point); }

// 函数：获取属性点
int get_gift_point() { return GiftPoint; }

// 函数：设置属性点
int set_gift_point(int point)
{
        if (GiftPoint != point && get_login_flag() > 1)
                send_user(this_object(), "%c%c%w", 0x3d, 43, point);
        return GiftPoint = point;
}

// 函数：增加属性点
int add_gift_point(int point) { return set_gift_point(GiftPoint + point); }

// 函数：获取最高等级
int get_max_level() { return MaxLevel; }

// 函数：设置最高等级
int set_max_level(int point) { return MaxLevel = point; }

// 函数：增加最高等级
int add_max_level(int point) { return set_max_level(MaxLevel + point); }

// 函数：获取等级属性
int get_level() { return Level; }

// 函数：设置等级属性
int set_level(int level)
{
        object leader, me, *inv;
        int point, i, size, number, cs, csx;

        me = this_object();
        cs = me->get_save_2("chuyensinh.score");
        if (is_player(me))
                level = range_value(level, 0, get_max_char_level());
        else
                level = range_value(level, 0, get_max_char_level_2());

        if (Level != level && get_login_flag() > 1)
        {
                send_user(me, "%c%c%w%d", 0x3d, 44, level, USER_EXP_D->get_level_exp(Reincarnation, level));

                //临时因为客户端不更新升级经验, 所以加上这个
                send_user(me, "%c%c%w%d%d%d%w%w%d%d%d%d", 0x3d, 164,
                          me->get_billion_exp(), me->get_exp(), me->get_potential(), me->get_bonus() / 10, me->get_gift_point(),
                          level, me->get_upgrade_exp(), USER_EXP_D->get_level_exp(me->get_reincarnation(), level), me->get_cash(), me->get_savings());
                if (get_login_flag() >= 3)
                {
                        switch (level)
                        {
                        case 1:
                                QUEST_TIPS->send_tips(me, "3");
                                break;
                        case 2:
                                QUEST_TIPS->send_tips(me, "5");
                                break;
                        case 3:
                                QUEST_TIPS->send_tips(me, "6");
                                break;
                        case 4:
                                QUEST_TIPS->send_tips(me, "7");
                                break;
                        case 5:
                                QUEST_TIPS->send_tips(me, "8");
                                break;
                        case 6:
                                QUEST_TIPS->send_tips(me, "9");
                                break;
                        case 8:
                                QUEST_TIPS->send_tips(me, "11");
                                break;
                        case 10:
                                //				QUEST_TIPS->send_tips(me, "2");
                                //				"/inh/user/mail"->sys_mail2(me->get_id(), me->get_number(), "百合仙子", "恭喜你顺利提升到十级！听说如意姐姐正在新手村（192, 149）进行一个新人送礼的活动, 她一定会给予你不少帮助的.\n");
                                break;
                        case 11:
                                QUEST_TIPS->send_tips(me, "10");
                                break;
                        case 30:
                                QUEST_TIPS->send_tips(me, "12");
                                break;
                        case 60:
                                QUEST_TIPS->send_tips(me, "13");
                                break;
                        }
                        "/quest/help"->send_level_tips(me, level);
                }
                //	add_gift_point( 4 );
                if (level > MaxLevel)
                {
                        add_gift_point((level - MaxLevel) * get_gift_point_times());
                        "/quest/help"->send_help_tips(me, 20);
                        "/quest/help"->send_help_tips(me, 36);
                        //			if (me->get_save("testbonus")) add_gift_point( (level - MaxLevel) * 2 );
                        if (MaxLevel < 30) // 带新手任务
                        {
                                if (leader = me->get_bonus_leader())
                                {
                                        switch (MaxLevel)
                                        {
                                        case 0..9:
                                                point = (level - MaxLevel) * 5;
                                                break;
                                        case 10..19:
                                                point = (level - MaxLevel) * 20;
                                                break;
                                        case 20..29:
                                                point = (level - MaxLevel) * 40;
                                                break;
                                        default:
                                                point = 0;
                                                break;
                                        }

                                        leader->add_bonus(point);
                                        write_user(leader, ECHO "Bạn trợ giúp " HIY "%s" ECHO " lên tới %d cấp (%+d), Công đức của bạn tăng " HIY "%+d.%d" ECHO ".",
                                                   me->get_name(), level, level - MaxLevel, point / 10, point % 10);

                                        if (level >= 30)
                                                TEAM_D->check_bonus_task(me->get_leader()); // 检查要带新手
                                }
                        }

                        MaxLevel = level;
                }
                inv = me->get_team();
                number = me->get_number();
                for (i = 0, size = sizeof(inv); i < size; i++)
                        if (inv[i])
                        {
                                if (me->get_number() != inv[i]->get_number())
                                        send_user(inv[i], "%c%c%d%c", 0x54, 5, number, level);
                        }
                if (!MAP_D->is_inside_battle(get_z(me)))
                        switch (Level) // 更新玩家种类
                        {
                        case 0..9:
                                switch (level)
                                {
                                case 0..9:
                                        break;
                                case 10..29:
                                        USER_D->sub_level_a_user(me);
                                        USER_D->add_level_b_user(me);
                                        break;
                                default:
                                        USER_D->sub_level_a_user(me);
                                        USER_D->add_level_c_user(me);
                                        break;
                                }
                                break;

                        case 10..29:
                                switch (level)
                                {
                                case 0..9:
                                        USER_D->sub_level_b_user(me);
                                        USER_D->add_level_a_user(me);
                                        break;
                                case 10..29:
                                        break;
                                default:
                                        USER_D->sub_level_b_user(me);
                                        USER_D->add_level_c_user(me);
                                        break;
                                }
                                break;

                        default:
                                switch (level)
                                {
                                case 0..9:
                                        USER_D->sub_level_c_user(me);
                                        USER_D->add_level_a_user(me);
                                        break;
                                case 10..29:
                                        USER_D->sub_level_c_user(me);
                                        USER_D->add_level_b_user(me);
                                        break;
                                default:
                                        break;
                                }
                                break;
                        }
        }

        return Level = level;
}

// -------------------------------------------------------------

// 函数：获取最大现金
int get_max_cash() { return MAX_NUMBER; } // 注意新登录情况

//knbkhoa
int get_knbkhoa() { return KnbKhoa; }
// 函数：设置手上现金
int set_knbkhoa(int gold)
{

        KnbKhoa = gold;
        return KnbKhoa;
}
int add_knbkhoa(int gold) { return set_knbkhoa(KnbKhoa + gold); }

// //HotKey
mixed get_hotkey() { return HotKey; }
mixed set_hotkey(string key, mixed value)
{
        return HotKey[key] = value;
}
mixed add_hotkey(string key, mixed value) { return set_hotkey(key, value); }
mixed delete_hotkey(string key) { map_delete(HotKey, key); }

//cashkhoa
int get_cashkhoa() { return CashKhoa; }
// 函数：设置手上现金
int set_cashkhoa(int gold)
{
        if (gold > get_max_cash())
                send_user(this_object(), "%c%s", '!', "Ngân lượng của bạn đã đạt tối đa, không thể gia tăng nữa");
        gold = range_value(gold, 0, get_max_cash()); // - MAX_NUMBER
        CashKhoa = gold;
        send_user(this_object(), "%c%c%c%w%s", 0x51, 1, 1, 0001, "Viện Trợ trò chơi");
        send_user(this_object(), "%c%c%c%w%w%s", 0x51, 1, 2, 0001, 4, "Ngân Lượng Khóa");
        "/sys/task/task"->send_task_intro(this_object(), 1, 1, 4);
        return CashKhoa;
}
int add_cashkhoa(int gold) { return set_cashkhoa(CashKhoa + gold); }

// 函数：获取手上现金
int get_cash() { return Cash; }

// 函数：设置手上现金
int set_cash(int gold)
{
        if (gold > get_max_cash())
                send_user(this_object(), "%c%s", '!', "Ngân lượng của bạn đã đạt tối đa, không thể gia tăng nữa");
        gold = range_value(gold, 0, get_max_cash()); // - MAX_NUMBER
        if (Cash != gold && get_login_flag() > 1)
                send_user(this_object(), "%c%c%d", 0x3d, 70, gold);
        return Cash = gold;
}

// 函数：增加手上现金
int add_cash(int gold)
{
        object who = this_object();
        object obj, *all;
        string result;
        int i, size;
        all = previous_object(-1);
        obj = previous_object();
        all -= ({who, 0});
        size = sizeof(all);
        for (i = size - 1; i >= 0; i--)
        {
                if (all[i]->is_npc())
                {
                        obj = all[i];
                        break;
                }
        }
        if (obj && obj->is_npc())
        {
                if (gold > 0)
                        result = sprintf("Nhận được @%s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", obj->get_name(), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), gold, get_z(who), get_x(who), get_y(who));
                else
                        result = sprintf("Trừ đi @%s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", obj->get_name(), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), gold, get_z(who), get_x(who), get_y(who));
                //"/sys/user/cmd"->log_item(result);
        }
        else if (obj)
        {
                if (gold > 0)
                        result = sprintf("Nhận đuwọc @%s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", get_file_name(obj), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), gold, get_z(who), get_x(who), get_y(who));
                else
                        result = sprintf("Trừ đi @%s %s,%d,%s,%s lượng 0 %d 0 %d_%d_%d", get_file_name(obj), who->get_name(), who->get_number(), get_ip_name(who), who->get_id(), gold, get_z(who), get_x(who), get_y(who));
                //"/sys/user/cmd"->log_item(result);
        }
        return set_cash(Cash + gold);
}

// 函数：有记录的add_cash
int add_cash2(int gold) { return set_cash(Cash + gold); }

// 函数：最高存款额度
int get_max_savings()
{
        switch (Reincarnation)
        {
        default:
                return range_value(Level, 1, MAX_NUMBER) * 1000000; // 注意新登录情况
        case 1:
                return range_value(Level, 1, MAX_NUMBER) * 2000000;
        case 2:
                return range_value(Level, 1, MAX_NUMBER) * 4000000;
        }
}

// 函数：获取存储金额
int get_savings() { return Savings; }

// 函数：设置存储金额
int set_savings(int gold)
{
        if (gold > get_max_savings())
                send_user(this_object(), "%c%s", '!', "Số tiền gửi vào Ngân Khố đã đến mức hạn cao nhất rồi");
        gold = range_value(gold, -MAX_NUMBER, get_max_savings());
        if (Savings != gold && get_login_flag() > 1)
                send_user(this_object(), "%c%c%d", 0x3d, 71, gold);
        return Savings = gold;
}

// 函数：增加存储金额
int add_savings(int gold) { return set_savings(Savings + gold); }

// 函数：获取伴侣标识
string get_marry() { return Marry; }

// 函数：设置伴侣标识
string set_marry(string id) { return Marry = id; }

// 函数：获取离婚次数
int get_divorced() { return Divorced; }

// 函数：设置离婚次数
int set_divorced(int num) { return Divorced = num; }

// 函数：增加离婚次数
int add_divorced(int num) { return Divorced += num; }

// 函数：获取ＰＫ标志
int get_pk() { return range_value(PK, 0, 65535); } // Cảnh báo : phòng ngựa tình huống xảy ra

// 函数：设置ＰＫ标志
int set_pk(int flag)
{
        object me = this_object();
        int old_pk = PK;

        PK = range_value(flag, 0, MAX_NUMBER);

        /*   if (old_pk<100 && PK>=100)
        {
                send_user( me, "%c%c%w%s", ':', 3, 0, "Ngươi giết người, nên phải chịu Ác Danh PK !\n"
                        ESC "Xác nhận\nCLOSE\n" );
        }
        else
        if (old_pk>=100 && PK<100)
        {
                send_user( me, "%c%c%w%s", ':', 3, 0, "Ngươi đã biết sám hối, tốt lắm !\n"
                        ESC "Xác nhận\nCLOSE\n" );
        }
        else
        if (PK>old_pk)
        {
        	set_effect(me, EFFECT_USER_PK, 600);
        	me->set_attack_mode(0);
        }*/
        //    if (PK>=300) me->set_attack_mode(0);
        if (me->get_save("gietnguoi") >= 1 && get_z(me) != 704 && PK >= 1000)
        {
                me->set_save("vaotu", 7200);
                me->set_login_flag(2);
                set_invisible(me, 1);
                set_effect(me, EFFECT_USER_LOGIN, 4);
                me->add_to_scene(704, 35, 25);
                send_user(me, "%c%c%w%s", ':', 3, 9963, "Ngươi giết quá nhiều người, nên Chu Vương phạt ngươi phải vào Nhà Ngục sám hối tội lỗi !\n" ESC "Xác nhận\nCLOSE\n");
        }
        if (PK < 100 && !get_effect(me, EFFECT_USER_PK))
        {
                //        me->set_char_type(PK_TYPE);    // Dạng PK chữ vàng
                me->set_char_type(PLAYER_TYPE_2); // Dạng PK chữ bình thường
        }
        else if (PK < 100 && get_effect(me, EFFECT_USER_PK))
        {
                me->set_char_type(PK_TYPE); // Dạng PK chữ vàng
        }
        else if (PK >= 100)
        {
                me->set_char_type(PK_TYPE_5); // Dạng pk chữ đỏ
        }
        else if (old_pk >= 100 && PK < 100)
        {
                if (!get_effect(me, EFFECT_USER_PK))
                {
                        me->set_char_type(PLAYER_TYPE_2); // Dạng PK chữ bình thường
                }
                else if (get_effect(me, EFFECT_USER_PK))
                {
                        me->set_char_type(PK_TYPE); // Dạng PK chữ vàng
                }
        }
        /*    else switch( PK )
        {
       case 0 : me->set_char_type(PLAYER_TYPE_2);  break;
    case 1..2 : me->set_char_type(PK_TYPE_1);  break;
    case 3..4 : me->set_char_type(PK_TYPE_3);  break;
      default : me->set_char_type(PK_TYPE_5);  break;
        }*/
        //        write_user(me, "%c%c%s", 0x3d, 35, " " HIR "[CHÚ Ý]" HIC "Điểm PK hiện tại của ngươi là : " NOR "" + flag);
        send_user(me, "%w%d", 435, range_value(PK, 0, 10000));
        return range_value(PK, 0, 65535); // Cảnh báo : phòng ngựa tình huống xảy ra
}

// 函数：增加ＰＫ标志
int add_pk(int flag) { return set_pk(PK + flag); }

// 函数：是否ＰＫ者
int is_pker()
{
        switch (PK)
        {
        case 0..2:
                return 0;
        case 3..4:
                return 1;
        default:
                return 2;
        }
}

// 函数：获取任务坐标
int get_task_xy() { return TaskXY; }

// 函数：设置任务坐标
varargs int set_task_xy(int p, int x, int y) // 支持两种方式
{
        if (!x && !y)
                return TaskXY = p;

        return TaskXY = p * 1000000 + x * 1000 + y;
}

// 函数：获取综合任务坐标
mapping get_mtask_xy()
{
        if (!mapp(mpTaskXY))
                return ([]);
        return copy(mpTaskXY);
}

// 函数：设置综合任务坐标
int set_mtask_xy(int z, int x, int y, string id, string intro) // id:参考send_mtask_xy
{
        if (!id)
                return 0;
        if (x <= 0 && y <= 0 && mapp(mpTaskXY) && mapp(mpTaskXY[z]))
                map_delete(mpTaskXY[z], id);
        if (!mapp(mpTaskXY))
                mpTaskXY = ([]);
        if (!mapp(mpTaskXY[z]))
                mpTaskXY[z] = ([]);
        if (!stringp(intro))
                intro = "";
        mpTaskXY[z][id] = (["xy":x * 1000 + y, "intro":intro, ]);
        return 1;
}

void send_mtask_xy(int z)
{
        int i, size, x0, y0;
        string *nId, id;
        object me = this_object();
        if (!mapp(mpTaskXY) || !mapp(mpTaskXY[z]))
                return;
        nId = keys(mpTaskXY[z]);
        for (i = 0, size = sizeof(nId); i < size; i++)
        {
                id = nId[i];
                if (!find_any_char(sprintf("%x#", id)))
                        continue;
                x0 = (mpTaskXY[z][id]["xy"]) / 1000;
                y0 = (mpTaskXY[z][id]["xy"]) % 1000;
                send_user(me, "%c%c%d%w%w%s", 0x54, 12, id, x0, y0, mpTaskXY[z][id]["intro"]);
        }
}