#ifndef _USER_PAGEMANAGEMENT_H
#define _USER_PAGEMANAGEMENT_H

#include "lvgl.h"

/*Numbers of page stack depth*/
#define MAX_DEPTH 6

/*Page error message*/
#define Page_Error 255


/*Page management struct*/
typedef struct {
    void (*init)(void);
    void (*deinit)(void);
    lv_obj_t** page_obj;
} Page_t;

/*Page stack management struct*/
typedef struct {
    Page_t* pages[MAX_DEPTH];
    uint8_t top;
} PageStack_t;

extern PageStack_t PageStack;


Page_t* Page_Get_NowPage(void);
void Page_Back(void);
void Page_Back_Bottom(void);
void Page_Load(Page_t* newPage);
void Page_Skip_To(Page_t* page);
void Pages_init(void);
uint8_t page_stack_pop(PageStack_t* stack);


#endif

