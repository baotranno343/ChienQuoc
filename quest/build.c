
// 变量：任务列表
string *Quest = ({
        "造化丹",
        "补心丹",
        "救急丹",
        "活心丹",
        "再造丸",

        "辟毒散",
        "清心丹",
        "天王散",
});

int sizeof_quest = sizeof(Quest);

// 函数：获取任务
string get_quest( object who ) { return Quest[ random(sizeof_quest) ]; }
