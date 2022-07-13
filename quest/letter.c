
// 变量：任务列表
string *Quest = ({
        "保镖",
        "采花小姑娘",
        "蔡煞星",
        "曹公子",
        "茶博士",
        "茶客",
        "茶叶商人",
        "乘凉的",
        "村长李大婶",
        "村姑",
        "当铺老板",
        "都城守卫",
        "杜老爹",
        "防具店老板",
        "放牛娃",
        "韩兵队长",
        "韩兵偏将",
        "韩兵统领",
        "韩非",
        "韩国士兵",
        "韩总管",
        "酒店老板",
        "客栈老板",
        "牢房守卫",
        "老妇人",
        "文教头",
        "老农",
        "李王妃",
        "刘捕头",
        "旅人",
        "苗苗",
        "牧童",
        "农家男孩",
        "农家女孩",
        "农民",
        "乞丐",
        "钱来发",
        "樵夫",
        "商人护卫",
        "神仙爷爷",
        "侍卫",
        "守卫",
        "孙姑娘",
        "铁匠",
        "王捕头",
        "王府守卫",
        "武器店老板",
        "武教头",
        "小安子",
        "小岛守卫",
        "小狗儿",
        "小姑娘",
        "小荷",
        "小娟",
        "小湘",
        "小絮",
        "小叶子",
        "小玉儿",
        "新手村村长",
        "杏花姑娘",
        "修理店老板",
        "药店老板",
        "义务医生",
        "驿站老板",
        "游历书生",
        "游侠龙少游",
        "渔夫",
        "渔民虾头",
        "渔民鱼蛋",
        "杂货店老板",
        "杂役",
        "张大娘",
        "张猎户",
        "赵大",
        "赵大娘",
        "赵大婶",
        "赵二",
        "赵老头",
        "赵若",
        "赵三",
        "赵双儿",
        "赵小妹",
        "赵小双",
        "赵馨",
        "赵馨儿",
        "朱恶少",
        "朱家打手",
        "朱老爷子",
        "珠宝商人",
});

int sizeof_quest = sizeof(Quest);

// 函数：获取任务
mapping get_quest( object who ) 
{ 
        mapping result = ([ ]);
        object *user;
        int level, i, size;

        level = who->get_level();

        if(     random(100) < 10
        &&      arrayp( user = USER_D->get_player() ) 
        &&      ( size = sizeof(user) ) )
        {
                i = random(size);
                if( user[i] && user[i] != who ) 
                {
                        result["name"] = sprintf( "送信给%s(%d)", user[i]->get_name(), user[i]->get_number() );
                        result["exp"] = level * 40;
                        return result;
                }
        }

        result["name"] = sprintf( "送信给%s", Quest[ random(sizeof_quest) ] );
        result["exp"] = level * 20;
        return result;
}
