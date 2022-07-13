inherit COPY_MAP;
int is_copy_scene() { return 1; }
// 函数：构造处理
void create()
{
        object me = this_object();

        set_client_id(703);
        set_name("Lăng Ly Sơn Tầng 2"); //下层陵墓

        if (!clonep(me))
                return;

        set_heart_timer(me, set_heart_timer_2(me, getoid(me) % 10)); // 心跳随机
        set_heart_loop(me, 600);                                     // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
}
