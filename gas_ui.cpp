#include <lvgl.h>

// تعريف العناصر الرئيسية للواجهة
static lv_obj_t *btn_switch;
static lv_obj_t *label_gas_pct;
static lv_obj_t *label_status;
static lv_obj_t *label_temp;   // مؤشر حرارة المنظومة
static lv_obj_t *bar_gas_level;// شريط مستوى الغاز

// دالة الحدث عند الضغط على زر التحويل بين الغاز والبنزين
static void switch_event_handler(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED) {
        // هنا يتم إضافة أمرين لاحقاً لإرسال إشارة التحويل لوحدة AEB
        static bool is_gas_mode = true;
        is_gas_mode = !is_gas_mode;
        
        if (is_gas_mode) {
            lv_label_set_text(label_status, "الحالة: يعمل على الغاز (LPG)");
            lv_obj_set_style_bg_color(btn_switch, lv_color_hex(0x2ECC71), LV_PART_MAIN); // أخضر للغاز
        } else {
            lv_label_set_text(label_status, "الحالة: يعمل على البنزين");
            lv_obj_set_style_bg_color(btn_switch, lv_color_hex(0xE74C3C), LV_PART_MAIN); // أحمر للبنزين
        }
    }
}

void create_gas_ui(void) {
    // 1. الشاشة الرئيسية بلون خلفية داكن مناسب لديكور السيارة (Dark Theme)
    lv_obj_t *scr = lv_scr_act();
    lv_obj_set_style_bg_color(scr, lv_color_hex(0x111111), LV_PART_MAIN);

    // 2. عنوان الشاشة الرئيسي
    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "منظومة الغاز الذكية - BYD");
    lv_obj_set_style_text_color(title, lv_color_hex(0xF1C40F), 0); // لون أصفر مميز
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 15);

    // 3. شريط مستوى الغاز (Bar)
    bar_gas_level = lv_bar_create(scr);
    lv_obj_set_size(bar_gas_level, 350, 30);
    lv_obj_align(bar_gas_level, LV_ALIGN_CENTER, 0, -50);
    lv_bar_set_range(bar_gas_level, 0, 100);
    lv_bar_set_value(bar_gas_level, 75, LV_ANIM_ON); // قيمة تجريبية 75%
    // تلوين شريط التقدم
    lv_obj_set_style_bg_color(bar_gas_level, lv_color_hex(0x333333), LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar_gas_level, lv_color_hex(0x2ECC71), LV_PART_INDICATOR);

    // 4. نص نسبة الغاز المئوية
    label_gas_pct = lv_label_create(scr);
    lv_label_set_text(label_gas_pct, "مستوى الغاز: 75%");
    lv_obj_set_style_text_color(label_gas_pct, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align_to(label_gas_pct, bar_gas_level, LV_ALIGN_OUT_TOP_MID, 0, -10);

    // 5. مؤشر حرارة المنظومة (قيم تجريبية)
    label_temp = lv_label_create(scr);
    lv_label_set_text(label_temp, "حرارة المنظومة: 42°C");
    lv_obj_set_style_text_color(label_temp, lv_color_hex(0x3498DB), 0); // أزرق هادئ للحرارة
    lv_obj_align(label_temp, LV_ALIGN_CENTER, 0, 10);

    // 6. نص الحالة الحالي
    label_status = lv_label_create(scr);
    lv_label_set_text(label_status, "الحالة: يعمل على الغاز (LPG)");
    lv_obj_set_style_text_color(label_status, lv_color_hex(0xECF0F1), 0);
    lv_obj_align(label_status, LV_ALIGN_CENTER, 0, 55);

    // 7. زر التحويل (Toggle Button) بين الغاز والبنزين
    btn_switch = lv_btn_create(scr);
    lv_obj_set_size(btn_switch, 220, 60);
    lv_obj_align(btn_switch, LV_ALIGN_BOTTOM_MID, 0, -25);
    lv_obj_set_style_bg_color(btn_switch, lv_color_hex(0x2ECC71), LV_PART_MAIN);
    lv_obj_add_event_cb(btn_switch, switch_event_handler, LV_EVENT_CLICKED, NULL);

    // نص الزر
    lv_obj_t *btn_label = lv_label_create(btn_switch);
    lv_label_set_text(btn_label, "تبديل (غاز / بنزين)");
    lv_obj_center(btn_label);
}
