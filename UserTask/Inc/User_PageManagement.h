#ifndef _USER_PAGEMANAGEMENT_H
#define _USER_PAGEMANAGEMENT_H

#include "lvgl.h"

typedef struct {
    void (*init)(void);
    void (*deinit)(void);
    lv_obj_t** page_obj;
} Page_t;




#endif