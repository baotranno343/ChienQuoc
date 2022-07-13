
// 变量：进阶书籍文件列表

string *giftname = ({ "0104", "0109", "0111", "0121", "0131", "0141", "0151", "0161", "0202", "0401", "0402", "0403", "0404", "0405", "0211", "0212", "0316", "0317", "0319", "0221", "0231", "0222", "0325", "0329", "0241", "0251", "0242", "0348", "0349", "0261", "0363", "0364", "0365", "0368", "0271", "0413", "0414", "0417", "0418", "0421", "0422", "0423", "0424", "0425", "0281", "0501", "0511", "0531", "0591", "0610", "0620", "0630", "0640", "0650", "0660", "0670", "0680", });

string *performname = ({ "0329", "05017", "05018", });

int sizeof_file = sizeof(giftname);

// 函数：获取进阶书籍文件
string get_book_file() { return sprintf("/item/95/%s", giftname[ random(sizeof_file) ]); }

// 函数：获取秘籍文件
string get_book_file_2() { return sprintf("/item/96/%s", giftname[ random(sizeof_file) ]); }

// 函数：获取特技书籍文件
string get_perform_file() { return sprintf("/item/skill/%s", performname[ random(sizeof(performname)) ]); }

// 函数：获取随机晶石
string get_diamond_file() { return sprintf("/item/93/%d", 9301+random(10)); }
