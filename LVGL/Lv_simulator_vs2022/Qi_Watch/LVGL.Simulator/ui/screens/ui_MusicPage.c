#include "../ui.h"

Page_t Page_Music = { ui_MusicPage_screen_init, ui_MusicPage_screen_deinit, &ui_MusicPage };

/*--------------------SCREEN: ui_MusicPage------------------------------*/
void ui_MusicPage_screen_init(void);
void ui_event_MusicPage(lv_event_t *e);
lv_obj_t *ui_MusicPage;
lv_obj_t *ui_MusicControl;
lv_obj_t *ui_Next;
lv_obj_t *ui_Back;
lv_obj_t *ui_IUPanel;
lv_obj_t *ui_HeartImage;
lv_obj_t *ui_SongnameLabel;
lv_obj_t *ui_SingerLabel;
lv_obj_t *ui_SongwordLabel;
lv_obj_t *ui_ShareImage;
lv_obj_t *ui_GomoreImage;


/*--------------------SCREEN: ui_MusicPage------------------------------*/

void ui_event_MusicPage(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back_Bottom();
       
    }
    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        Page_Back();
    }
}
void ui_MusicPage_screen_init(void)
{
    ui_MusicPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_MusicPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MusicPage, lv_color_hex(0x9E0766), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MusicPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_MusicPage, lv_color_hex(0x50034B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_MusicPage, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MusicControl = lv_imgbtn_create(ui_MusicPage);
    lv_imgbtn_set_src(ui_MusicControl, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_play_png, NULL);
    lv_imgbtn_set_src(ui_MusicControl, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_suspend_png, NULL);
    lv_imgbtn_set_src(ui_MusicControl, LV_IMGBTN_STATE_DISABLED, NULL, &ui_img_play_png, NULL);
    lv_imgbtn_set_src(ui_MusicControl, LV_IMGBTN_STATE_CHECKED_PRESSED, NULL, &ui_img_suspend_png, NULL);
    lv_imgbtn_set_src(ui_MusicControl, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &ui_img_suspend_png, NULL);
    lv_imgbtn_set_src(ui_MusicControl, LV_IMGBTN_STATE_CHECKED_DISABLED, NULL, &ui_img_play_png, NULL);
    lv_obj_set_height(ui_MusicControl, 40);
    lv_obj_set_width(ui_MusicControl, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_x(ui_MusicControl, 0);
    lv_obj_set_y(ui_MusicControl, 115);
    lv_obj_set_align(ui_MusicControl, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_MusicControl, LV_OBJ_FLAG_CHECKABLE);     /// Flags

    ui_Next = lv_img_create(ui_MusicPage);
    lv_img_set_src(ui_Next, &ui_img_next_png);
    lv_obj_set_width(ui_Next, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Next, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Next, 50);
    lv_obj_set_y(ui_Next, 113);
    lv_obj_set_align(ui_Next, LV_ALIGN_CENTER);
    lv_obj_add_state(ui_Next, LV_STATE_PRESSED);       /// States
    lv_obj_add_flag(ui_Next, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_CHECKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Next, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Back = lv_img_create(ui_MusicPage);
    lv_img_set_src(ui_Back, &ui_img_back_png);
    lv_obj_set_width(ui_Back, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Back, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Back, -50);
    lv_obj_set_y(ui_Back, 113);
    lv_obj_set_align(ui_Back, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Back, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Back, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_IUPanel = lv_obj_create(ui_MusicPage);
    lv_obj_set_width(ui_IUPanel, 100);
    lv_obj_set_height(ui_IUPanel, 100);
    lv_obj_set_x(ui_IUPanel, 0);
    lv_obj_set_y(ui_IUPanel, -44);
    lv_obj_set_align(ui_IUPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_IUPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_IUPanel, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_IUPanel, lv_color_hex(0x9C0462), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_IUPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_IUPanel, &ui_img_iu1_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_IUPanel, lv_color_hex(0x8B0A5A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_IUPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_IUPanel, 22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_IUPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HeartImage = lv_img_create(ui_MusicPage);
    lv_img_set_src(ui_HeartImage, &ui_img_heart_png);
    lv_obj_set_width(ui_HeartImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_HeartImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_HeartImage, 94);
    lv_obj_set_y(ui_HeartImage, -93);
    lv_obj_set_align(ui_HeartImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_HeartImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_HeartImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_SongnameLabel = lv_label_create(ui_MusicPage);
    lv_obj_set_width(ui_SongnameLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SongnameLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SongnameLabel, 0);
    lv_obj_set_y(ui_SongnameLabel, -147);
    lv_obj_set_align(ui_SongnameLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SongnameLabel, "Holssi");
    lv_obj_set_style_text_color(ui_SongnameLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SongnameLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_SongnameLabel, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SingerLabel = lv_label_create(ui_MusicPage);
    lv_obj_set_width(ui_SingerLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SingerLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SingerLabel, 0);
    lv_obj_set_y(ui_SingerLabel, -128);
    lv_obj_set_align(ui_SingerLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SingerLabel, "IU");
    lv_obj_set_style_text_color(ui_SingerLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SingerLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SongwordLabel = lv_label_create(ui_MusicPage);
    lv_obj_set_width(ui_SongwordLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SongwordLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SongwordLabel, -26);
    lv_obj_set_y(ui_SongwordLabel, 54);
    lv_obj_set_align(ui_SongwordLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SongwordLabel, "I believe I am a flower\nthat will bloom in time");
    lv_obj_set_style_text_color(ui_SongwordLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SongwordLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ShareImage = lv_img_create(ui_MusicPage);
    lv_img_set_src(ui_ShareImage, &ui_img_phsharefill_png);
    lv_obj_set_width(ui_ShareImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ShareImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ShareImage, 100);
    lv_obj_set_y(ui_ShareImage, -143);
    lv_obj_set_align(ui_ShareImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ShareImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ShareImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_GomoreImage = lv_img_create(ui_MusicPage);
    lv_img_set_src(ui_GomoreImage, &ui_img_gomore3_png);
    lv_obj_set_width(ui_GomoreImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GomoreImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GomoreImage, 102);
    lv_obj_set_y(ui_GomoreImage, 33);
    lv_obj_set_align(ui_GomoreImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_GomoreImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_GomoreImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_MusicPage, ui_event_MusicPage, LV_EVENT_ALL, NULL);

}

void ui_MusicPage_screen_deinit(void)
{

}
