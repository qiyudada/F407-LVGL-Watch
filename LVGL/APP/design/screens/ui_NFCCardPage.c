#include "../ui.h"

Page_t Page_NFCCard = { ui_NFCCardPage_screen_init, ui_Navigation_screen_deinit, &ui_NFCCardPage };
/*--------------------SCREEN: ui_NFCCardPage------------------------------*/
void ui_NFCCardPage_screen_init(void);
lv_obj_t *ui_NFCCardPage;
lv_obj_t *ui_WriteCardPanel;
lv_obj_t *ui_WriteCardImage;
lv_obj_t *ui_writeCardLabel;
lv_obj_t *ui_WriteCardGoMoreImg;

lv_obj_t *ui_ReadCardPanel;
lv_obj_t *ui_ReadCardImage;
lv_obj_t *ui_ReadCardLabel;
lv_obj_t *ui_ReadCardGoMoreImg;

lv_obj_t *ui_CardDormancyPanel;
lv_obj_t *ui_CardDormancyImage;
void ui_event_CardDormancySwitch(lv_event_t *e);
lv_obj_t *ui_CardDormancySwitch;
lv_obj_t *ui_CardDormancyLabel;

lv_obj_t* ui_CardCommandLabel;

const lv_img_dsc_t *ui_imgset_calculator[1] = {&ui_img_calculator1_png};
const lv_img_dsc_t *ui_imgset_gomore[1] = {&ui_img_gomore3_png};
const lv_img_dsc_t *ui_imgset_iu[1] = {&ui_img_iu1_png};
const lv_img_dsc_t *ui_imgset_iu_bg[2] = {&ui_img_iu_bg2_png, &ui_img_iu_bg3_png};



void ui_event_NFCCardpage_cb(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_GESTURE && lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT)
    {
        lv_indev_wait_release(lv_indev_get_act());
        if(Page_Get_SecondPage()->page_obj==&ui_MenuPage)
        {
            Page_Back();
        }
        else
        Page_Back_Bottom();
    }
}

void ui_event_WriteCardGoMoreImg(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_label_set_text(ui_CardCommandLabel, "Writing card...");
    }
}

void ui_event_ReadCardGoMoreImg(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_CLICKED)
    {
        lv_label_set_text(ui_CardCommandLabel, "Reading card...");
    }
}

void ui_event_CardDormancySwitch(lv_event_t* e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t* target = lv_event_get_target(e);
    if (event_code == LV_EVENT_VALUE_CHANGED && lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Bluetooth_Open(e);
    }
    if (event_code == LV_EVENT_VALUE_CHANGED && !lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        Bluetoorh_Close(e);
    }
}


void ui_NFCCardPage_screen_init(void)
{
    ui_NFCCardPage = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_NFCCardPage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_NFCCardPage, lv_color_hex(0xCDB9A7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NFCCardPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NFCCardPage, lv_color_hex(0xC59583), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_NFCCardPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_NFCCardPage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_NFCCardPage, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WriteCardPanel = lv_obj_create(ui_NFCCardPage);
    lv_obj_set_width(ui_WriteCardPanel, 230);
    lv_obj_set_height(ui_WriteCardPanel, 60);
    lv_obj_set_x(ui_WriteCardPanel, 0);
    lv_obj_set_y(ui_WriteCardPanel, -125);
    lv_obj_set_align(ui_WriteCardPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_WriteCardPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_WriteCardPanel, lv_color_hex(0xEEE765), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WriteCardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_WriteCardPanel, lv_color_hex(0xFABB09), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_WriteCardPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_WriteCardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_WriteCardPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_WriteCardPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_WriteCardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WriteCardImage = lv_img_create(ui_WriteCardPanel);
    lv_img_set_src(ui_WriteCardImage, &ui_img_writecard_png);
    lv_obj_set_width(ui_WriteCardImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WriteCardImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WriteCardImage, -90);
    lv_obj_set_y(ui_WriteCardImage, 0);
    lv_obj_set_align(ui_WriteCardImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_WriteCardImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_WriteCardImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_writeCardLabel = lv_label_create(ui_WriteCardPanel);
    lv_obj_set_width(ui_writeCardLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_writeCardLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_writeCardLabel, -30);
    lv_obj_set_y(ui_writeCardLabel, 0);
    lv_obj_set_align(ui_writeCardLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_writeCardLabel, "Write Card");
    lv_obj_set_style_text_color(ui_writeCardLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_writeCardLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_WriteCardGoMoreImg = lv_img_create(ui_WriteCardPanel);
    lv_img_set_src(ui_WriteCardGoMoreImg, &ui_img_tokenolt_png);
    lv_obj_set_width(ui_WriteCardGoMoreImg, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_WriteCardGoMoreImg, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_WriteCardGoMoreImg, 70);
    lv_obj_set_y(ui_WriteCardGoMoreImg, -1);
    lv_obj_set_align(ui_WriteCardGoMoreImg, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_WriteCardGoMoreImg, LV_OBJ_FLAG_CLICKABLE);    /*img obj must be clickable*/
    lv_obj_clear_flag(ui_WriteCardGoMoreImg, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ReadCardPanel = lv_obj_create(ui_NFCCardPage);
    lv_obj_set_width(ui_ReadCardPanel, 230);
    lv_obj_set_height(ui_ReadCardPanel, 60);
    lv_obj_set_x(ui_ReadCardPanel, 0);
    lv_obj_set_y(ui_ReadCardPanel, -60);
    lv_obj_set_align(ui_ReadCardPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ReadCardPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ReadCardPanel, lv_color_hex(0xEEE765), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ReadCardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_ReadCardPanel, lv_color_hex(0xFABB09), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_ReadCardPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_ReadCardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_ReadCardPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_ReadCardPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_ReadCardPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ReadCardImage = lv_img_create(ui_ReadCardPanel);
    lv_img_set_src(ui_ReadCardImage, &ui_img_readcard_png);
    lv_obj_set_width(ui_ReadCardImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ReadCardImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ReadCardImage, -90);
    lv_obj_set_y(ui_ReadCardImage, 0);
    lv_obj_set_align(ui_ReadCardImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ReadCardImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_ReadCardImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ReadCardLabel = lv_label_create(ui_ReadCardPanel);
    lv_obj_set_width(ui_ReadCardLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ReadCardLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ReadCardLabel, -30);
    lv_obj_set_y(ui_ReadCardLabel, 0);
    lv_obj_set_align(ui_ReadCardLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ReadCardLabel, "Read Card");
    lv_obj_set_style_text_color(ui_ReadCardLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ReadCardLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ReadCardGoMoreImg = lv_img_create(ui_ReadCardPanel);
    lv_img_set_src(ui_ReadCardGoMoreImg, &ui_img_tokenolt_png);
    lv_obj_set_width(ui_ReadCardGoMoreImg, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ReadCardGoMoreImg, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ReadCardGoMoreImg, 70);
    lv_obj_set_y(ui_ReadCardGoMoreImg, -1);
    lv_obj_set_align(ui_ReadCardGoMoreImg, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_ReadCardGoMoreImg, LV_OBJ_FLAG_CLICKABLE);    /*img obj must be clickable*/
    lv_obj_clear_flag(ui_ReadCardGoMoreImg, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_CardDormancyPanel = lv_obj_create(ui_NFCCardPage);
    lv_obj_set_width(ui_CardDormancyPanel, 230);
    lv_obj_set_height(ui_CardDormancyPanel, 60);
    lv_obj_set_x(ui_CardDormancyPanel, 0);
    lv_obj_set_y(ui_CardDormancyPanel, 6);
    lv_obj_set_align(ui_CardDormancyPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_CardDormancyPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_CardDormancyPanel, lv_color_hex(0xEEE25A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CardDormancyPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_CardDormancyPanel, lv_color_hex(0xFFBE08), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_CardDormancyPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_CardDormancyPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_CardDormancyPanel, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CardDormancyPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CardDormancyPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CardDormancyImage = lv_img_create(ui_CardDormancyPanel);
    lv_img_set_src(ui_CardDormancyImage, &ui_img_nfcoff_png);
    lv_obj_set_width(ui_CardDormancyImage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CardDormancyImage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CardDormancyImage, -90);
    lv_obj_set_y(ui_CardDormancyImage, 0);
    lv_obj_set_align(ui_CardDormancyImage, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CardDormancyImage, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_CardDormancyImage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_CardDormancySwitch = lv_switch_create(ui_CardDormancyPanel);
    lv_obj_set_width(ui_CardDormancySwitch, 50);
    lv_obj_set_height(ui_CardDormancySwitch, 25);
    lv_obj_set_x(ui_CardDormancySwitch, 70);
    lv_obj_set_y(ui_CardDormancySwitch, -1);
    lv_obj_set_align(ui_CardDormancySwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_CardDormancySwitch, lv_color_hex(0xEEC91F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CardDormancySwitch, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_CardDormancySwitch, lv_color_hex(0xF6EABA), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CardDormancySwitch, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CardDormancySwitch, lv_color_hex(0xF5E294), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CardDormancySwitch, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_set_style_bg_color(ui_CardDormancySwitch, lv_color_hex(0xEE5908), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CardDormancySwitch, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    ui_CardDormancyLabel = lv_label_create(ui_CardDormancyPanel);
    lv_obj_set_width(ui_CardDormancyLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CardDormancyLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CardDormancyLabel, -30);
    lv_obj_set_y(ui_CardDormancyLabel, 0);
    lv_obj_set_align(ui_CardDormancyLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CardDormancyLabel, "Dormancy");
    lv_obj_set_style_text_color(ui_CardDormancyLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardDormancyLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_CardCommandLabel = lv_label_create(ui_NFCCardPage);
    lv_obj_set_width(ui_CardCommandLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CardCommandLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CardCommandLabel, -1);
    lv_obj_set_y(ui_CardCommandLabel, 98);
    lv_obj_set_align(ui_CardCommandLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CardCommandLabel, "Waiting for Command...");
    lv_obj_set_style_text_color(ui_CardCommandLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CardCommandLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_CardCommandLabel, LV_TEXT_ALIGN_AUTO, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CardCommandLabel, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_WriteCardGoMoreImg, ui_event_WriteCardGoMoreImg, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ReadCardGoMoreImg, ui_event_ReadCardGoMoreImg, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CardDormancySwitch, ui_event_CardDormancySwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NFCCardPage, ui_event_NFCCardpage_cb, LV_EVENT_ALL, NULL);
    
}

void ui_NFCCardPage_screen_deinit(void)
{

}
