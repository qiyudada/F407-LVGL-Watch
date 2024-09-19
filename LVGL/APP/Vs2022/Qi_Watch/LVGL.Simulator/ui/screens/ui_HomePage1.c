#include "../ui.h"

Page_t Page_Home = { ui_HomePage_screen_init, ui_HomePage_screen_deinit, &ui_HomePage };

static void HomePage_timer_cb(lv_timer_t* timer)
{

}


void ui_HomePage_screen_init(void)
{
    ui_HomePage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_HomePage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    switch (Img_Index)
    {
        case 0:
            lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        case 1:
            lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg2_png, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
        case 2:
            lv_obj_set_style_bg_img_src(ui_HomePage, &ui_img_iu_bg3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
            break;
         default:
            break;
    }
    
    /*create clock*/
    ui_ClockNumberLabel = lv_label_create(ui_HomePage);
    lv_obj_set_width(ui_ClockNumberLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ClockNumberLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ClockNumberLabel, -1);
    lv_obj_set_y(ui_ClockNumberLabel, 72);
    lv_obj_set_align(ui_ClockNumberLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ClockNumberLabel, "15:20");
    lv_obj_set_style_text_color(ui_ClockNumberLabel, lv_color_hex(0xF3E7F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ClockNumberLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ClockNumberLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ClockNumberLabel, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_DateLabel = lv_label_create(ui_HomePage);
    lv_obj_set_width(ui_DateLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_DateLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_DateLabel, -2);
    lv_obj_set_y(ui_DateLabel, 107);
    lv_obj_set_align(ui_DateLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_DateLabel, "Tue 17");
    lv_obj_set_style_text_color(ui_DateLabel, lv_color_hex(0xF3E7F3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_DateLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DateLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_ClockNumberLabel, ui_event_ClockNumberLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_DateLabel, ui_event_DateLabel, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_HomePage, ui_event_HomePage, LV_EVENT_ALL, NULL);

    lv_timer_t* ui_HomePage1Timer = lv_timer_create(HomePage_timer_cb, 500, NULL);

}


void ui_HomePage_screen_deinit(void)
{
    
}


