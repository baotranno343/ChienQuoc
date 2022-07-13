
#include <effect.h>

// 函数:获取描述(持续)
string get_loop_faint_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_FAINT))
                return sprintf("Choáng:\n Khi bị Choáng sẽ không thể thực hiện bất cứ hành động nào.\n");
        else if (get_effect(me, EFFECT_CHAR_FAINT_2))
                return sprintf("Choáng:\n Khi bị Choáng sẽ không thể thực hiện bất cứ hành động nào.\n");
        else if (get_effect(me, EFFECT_SLEEP))
                return sprintf("Hôn Mê:\n Trong khi hôn mê sẽ không thể thực hiện bất cứ hành động nào,\n nhưng nếu bị tấn công sẽ tự động tỉnh lại.\n");
        else if (get_effect(me, EFFECT_CHAR_NO_MOVE))
                return sprintf("Không thể di chuyển:\n　　Khi bị trúng trạng thái này sẽ không thể di chuyền,\nnhưng có thể sử dụng kĩ năng pháp thuật.\n");
        else
                return sprintf("Choáng\n");
}

// 函数:获取描述(持续)
string get_loop_no_pf_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_NO_PF))
                return sprintf("Phong Ma:\n　　Không thể sử dụng bất cứ kĩ năng pháp thuật nào.\n");
        else
                return sprintf("Phong Ma\n");
}

// 函数:获取描述(持续)
string get_loop_slow_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_SLOW))
                return sprintf("Làm chậm:\n　　Tốc độ di chuyển giảm 50%%\n");
        else
                return sprintf("Làm chậm\n");
}

// 函数:获取描述(持续)
string get_loop_lazy_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_LAZY))
                return sprintf("Đóng băng:\n　　Tốc độ di chuyển và công kích giảm 50%%\n");
        else
                return sprintf("Đóng băng\n");
}

// 函数:获取描述(持续)
string get_loop_dream_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_DREAM_1))
                return sprintf("Mộng du:\n　　Không thể sử dụng bất cứ kĩ năng hay đạo cụ nào, nếu bị đánh sẽ lập tức tỉnh lại.\n");
        else
                return sprintf("Mộng du\n");
}

// 函数:获取描述(持续)
string get_loop_chaos_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_CHAOS))
                return sprintf("Hỗn loạn:\n　　Rối loạn tâm thần, lúc di chuyển không thể khống chế.\n");
        else
                return sprintf("Hỗn loạn\n");
}

// 函数:获取描述(持续)
string get_loop_wound_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_WOUND))
                return sprintf("Trọng thương:\n　　Ngoại công và Nội công giảm 30%%\n");
        else
                return sprintf("Trọng thương\n");
}

// 函数:获取描述(持续)
string get_loop_blood_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_BLOOD))
                return sprintf("Chảy máu:\n　　Mỗi 2 giây giảm Khí Huyết\n");
        else
                return sprintf("Chảy máu\n");
}

// 函数:获取描述(持续)
string get_loop_blind_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_BLIND))
                return sprintf("Mù loà:\n　　Phạm vi tầm mắt bị giảm đáng kể, độ chính xác giảm 50%%\n");
        else
                return sprintf("Mù loà\n");
}

// 函数:获取描述(持续)
string get_loop_burn_desc(object me)
{
        if (get_effect(me, EFFECT_USER_BURN))
                return sprintf("Thiêu đốt:\n　　Trong 12 giây không thể sử dụng kĩ năng hồi máu.");
        else
                return sprintf("Thiêu đốt\n");
}

// 函数:获取描述(持续)
string get_loop_king_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_KING))
                return sprintf("Hiệu quả Thiên Vương Tán:\n　　Tất cả thuộc tính tăng thêm 45%%\n");
        else
                return sprintf("Hiệu quả Thiên Vương Tán\n");
}

// 函数:获取描述(持续)
string get_loop_king_2_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_KING_2))
                return sprintf("Tác dụng phụ Thiên Vương Tán:\n　　Khí huyết và Ma lực còn lại 1\n");
        else
                return sprintf("Tác dụng phụ Thiên Vương Tán\n");
}

// 函数:获取描述(持续)
string get_loop_suppress_desc(object me)
{
        if (get_effect(me, EFFECT_CHAR_SUPPRESS))
                return sprintf("Áp chế Pháp Bảo:\n　　Kĩ năng đặc thù của Pháp Bảo bị mất hiệu quả.\n");
        else
                return sprintf("Áp chế Pháp Bảo\n");
}
