
// 函数：生成二进制码
void SAVE_BINARY() { }

/*
赵钱孙李 周吴郑王 冯陈诸卫 蒋沈韩杨 朱秦尤许 何吕施张 孔曹严华 金魏陶姜 戚谢邹喻 柏水窦章
云苏潘葛 奚范彭郎 鲁韦昌马 苗凤花方 俞任袁柳 酆鲍史唐 费廉岑薛 雷贺倪汤 滕殷罗毕 郝邬安常
乐于时傅 皮卡齐康 伍余元卜 顾孟平黄 和穆萧尹 姚邵堪汪 祁毛禹狄 米贝明臧 计伏成戴 谈宋茅庞
熊纪舒屈 项祝董粱 杜阮蓝闵 席季麻强 贾路娄危 江童颜郭 梅盛林刁 钟徐邱骆 高夏蔡田 樊胡凌霍
虞万支柯 咎管卢莫 经房裘缪 干解应宗 丁宣贲邓 郁单杭洪 包诸左石 崔吉钮龚 程嵇邢滑 裴陆荣翁
荀羊於惠 甄魏家封 芮羿储靳 汲邴糜松 井段富巫 乌焦Tam弓 牧隗山谷 车侯宓蓬 全郗班仰 秋仲伊宫
宁仇栾暴 甘钭厉戎 祖武符刘 景詹束龙 叶幸司韶 郜黎蓟薄 印宿白怀 蒲台从鄂 索咸籍赖 卓蔺屠蒙
池乔阴郁 胥能苍双 闻莘党翟 谭贡劳逄 姬申扶堵 冉宰郦雍 卻璩桑桂 濮牛寿通 边扈燕冀 郏浦尚农
温别庄晏 柴翟阎充 慕连茹习 宦艾鱼容 向古易慎 戈廖庚终 暨居衡步 都耿满弘 匡国文寇 广禄阙东
殴殳沃利 蔚越夔隆 师巩厍聂 晁勾敖融 冷訾辛阚 那简饶空 曾毋沙乜 养鞠须丰 巢关蒯相 查后荆红
游竺权逯 盖後桓公 万俟司马 上官欧阳 夏侯诸葛 闻人东方 赫连皇甫 尉迟公羊 澹台公冶 宗政濮阳
淳于单于 太叔申屠 公孙仲孙 轩辕令狐 钟离宇文 长孙慕容 鲜于闾丘 司徒司空 亓官司寇 仉督子车
颛孙端木 巫马公西 漆雕乐正 壤驷公良 拓拔夹谷 宰父谷粱 晋楚闫法 汝鄢涂钦 段干百里 东郭南门
呼延归海 羊舌微生 岳帅缑亢 况后有琴 梁丘左丘 东门西门 商牟佘佴 伯赏南宫 墨哈谯笪 年爱阳佟
第五言福 百家姓终
*/

string *fname = ({
" Triệu"," Tiễn"," Tôn"," Lí"," Chu"," Ngô"," Trịnh"," Vương"," Phùng"," Trần"," Vệ"," Tương"," Trầm"," Hàn"," Dương"," Chu"," Tần"," Vưu"," Hứa"," Gì",
" Lữ"," Thi"," Trương"," Khổng"," Tào"," Nghiêm"," Hoa"," Kim"," Ngụy"," Đào"," Khương"," Thích"," Tạ"," Trâu"," Đậu"," Vân"," Tô"," Phan"," Phạm"," Bành",
" Lỗ"," Vi"," Mã"," Miêu"," Hoa"," Phương"," Nhâm"," Viên"," Liễu"," Bảo"," Sử"," Đường"," Sầm"," Tiết"," Lôi"," Hạ"," Nghê"," Thang"," Ân"," La",
" Hác"," Ổ"," Vu"," Phó"," Tề"," Ngũ"," Dư"," Cố"," Mạnh"," Hoàng"," Mục"," Tiêu"," Tiếu"," Diêu"," Uông"," Kì"," Mao"," Địch"," Tang"," Mang",
" Tống"," Mao"," Bàng"," Hùng"," Kỉ"," Chúc"," Đổng"," Lương"," Đỗ"," Nguyễn"," Cổ"," Giang"," Đồng"," Nhan"," Quách"," Mai"," Lâm"," Chung"," Từ"," Khâu",
" Lạc"," Cao"," Hạ"," Thái"," Điền"," Hồ"," Hoắc"," Vạn"," Kha"," Lô"," Mạc"," Cừu"," Đinh"," Đặng"," Hồng"," Bao"," Thạch"," Thôi"," Cung"," Trình",
" Bùi"," Lục"," Chân"," Đoạn"," Ô"," Tam"," Trữ"," Cừu"," Lưu"," Chiêm"," Long"," Diệp"," Bạch"," Trì"," Kiều"," Đàm"," Ngưu"," Ôn"," Trang"," Sài",
" Cổ"," Liêu"," Tằng"," Sa"," Quan",
// "司马","上官","欧阳","东方","尉迟","令狐","慕容","呼延","西门","南宫",
});

int sizeof_fname = sizeof(fname);

string *criminal_name = ({    // 重犯

" Lão Đại"," Lão Nhị"," Lão Tam"," Lão Tứ"," Lão Ngũ"," Lão Lục"," Lão Thất"," Lão Bát"," Lão Cửu",
" Đương Gia"," Lão Đương Gia"," Đại Đương Gia"," Nhị Đương Gia"," Tam Đương Gia",
" Lão Hắc"," Đại Hắc"," Nhị Hắc"," Tam Hắc",
" Râu"," Đại Hồ Tử"," Nhị Hồ Tử"," Tam Râu",
" Mặt Rỗ"," Hạt Gai"," Nhị Mặt Rỗ"," Tam Mặt Rỗ",
});

int sizeof_criminal_name = sizeof(criminal_name);

string *thief_name = ({    // 窃贼

"Tiểu Tam","Tiểu Tứ","Tiểu Ngũ","Tiểu Lục","Tiểu Thất",
"Kê Nhân","Cẩu Nhân","Miêu Nhân","Thỏ Nhân",
});

int sizeof_thief_name = sizeof(thief_name);

string *banditi_name = ({    // 土匪

" Lão Đại"," Lão Nhị"," Lão Tam"," Lão Tứ"," Lão Ngũ"," Lão Lục"," Lão Thất"," Lão Bát"," Lão Cửu",
" Đương Gia"," Lão Đương Gia"," Đại Đương Gia"," Nhị Đương Gia"," Tam Đương Gia",
" Lão Hắc"," Đại Hắc"," Nhị Hắc"," Tam Hắc",
" Râu"," Đại Hồ Tử"," Nhị Hồ Tử"," Tam Râu",
" Mặt Rỗ"," Hạt Gai"," Nhị Mặt Rỗ"," Tam Mặt Rỗ",
});

int sizeof_banditi_name = sizeof(banditi_name);

string *robber_name = ({    // 大盗

" Lão Đại"," Lão Nhị"," Lão Tam"," Lão Tứ"," Lão Ngũ"," Lão Lục"," Lão Thất"," Lão Bát"," Lão Cửu",
" Đương Gia"," Lão Đương Gia"," Đại Đương Gia"," Nhị Đương Gia"," Tam Đương Gia",
" Lão Hắc"," Đại Hắc"," Nhị Hắc"," Tam Hắc",
" Râu"," Đại Hồ Tử"," Nhị Hồ Tử"," Tam Râu",
" Mặt Rỗ"," Hạt Gai"," Nhị Mặt Rỗ"," Tam Mặt Rỗ",
});

int sizeof_robber_name = sizeof(robber_name);

string *rascal_name = ({    // 混混

"Tiểu Tam","Tiểu Tứ","Tiểu Ngũ","Tiểu Lục","Tiểu Thất",
});

int sizeof_rascal_name = sizeof(rascal_name);

string *rascal_name_2 = ({    // 恶少

"Công Tử","Lão Đại","Lão Nhị","Lão Tam","Lão Tứ","Lão Ngũ","Lão Lục","Lão Thất",
});

int sizeof_rascal_name_2 = sizeof(rascal_name_2);

// 获取重犯姓名
string get_criminal_name() { return fname[ random(sizeof_fname) ] + " " + criminal_name[ random(sizeof_criminal_name) ]; }

// 获取窃贼姓名
string get_thief_name() { return fname[ random(sizeof_fname) ] + " " + thief_name[ random(sizeof_thief_name) ]; }

// 获取土匪姓名
string get_banditi_name() { return fname[ random(sizeof_fname) ] + banditi_name[ random(sizeof_banditi_name) ]; }

// 获取大盗姓名
string get_robber_name() { return fname[ random(sizeof_fname) ] + robber_name[ random(sizeof_robber_name) ]; }

// 获取混混姓名
string get_rascal_name() { return fname[ random(sizeof_fname) ] + rascal_name[ random(sizeof_rascal_name) ]; }

// 获取恶少姓名
string get_rascal_name_2() { return fname[ random(sizeof_fname) ] + rascal_name_2[ random(sizeof_rascal_name_2) ]; }
