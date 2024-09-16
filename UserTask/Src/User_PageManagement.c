#include "User_PageManagement.h"
#include "ui.h"

/*MW PageStack define*/
PageStack_t PageStack;

/**
* @brief  PageStack init function
* @param  stack: pointer to stack
*/
static void page_stack_init(PageStack_t* stack)
{
	stack->top = 0;
}
/**
* @brief  PageStack push function
* @param  stack: pointer to stack
* @param  page: pointer to page
*/
static uint8_t page_stack_push(PageStack_t* stack, Page_t* page)
{
	if (stack->top >= MAX_DEPTH)
		return Page_Error;
	stack->pages[stack->top++] = page;
	return 0;
}
/**
* @brief  PageStack pop function
* @param  stack: pointer to stack
*/
static uint8_t page_stack_pop(PageStack_t* stack)
{
	if (stack->top <= 0)
		return Page_Error;
	stack->pages[--stack->top]->deinit();
	return 0;
}
/**
* @brief  PageStack is empty function
* @param  stack: pointer to stack
*/
static uint8_t page_stack_is_empty(const PageStack_t* stack)
{
	return stack->top == 0;
}

/**
* @brief  get the top page function
* @param  stack: pointer to stack
*/
static Page_t* get_top_page(PageStack_t* stack)
{
	/*Check the stack is empty or not*/
	if (stack->top == 0)
	{
		return NULL; /*if stack is empty*/
	}

	/*return the pointer of the page*/
	return stack->pages[stack->top - 1];
}

/**
* @brief  PageStack get top page function
*/

Page_t* Page_Get_NowPage(void)
{
	return get_top_page(&PageStack);
}

/**
 * @brief back to previous page
 * @param NULL
 */
void Page_Back(void)
{
	if (page_stack_is_empty(&PageStack))
	{
		/*if stack is empty and should be exited*/
		return;
	}

	/*pop current page*/
	page_stack_pop(&PageStack);
	if (page_stack_is_empty(&PageStack))
	{
		page_stack_push(&PageStack, &Page_Home);
		page_stack_push(&PageStack, &Page_Menu);
		Page_Menu.init();
		lv_scr_load_anim(*Page_Menu.page_obj, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true);
	}
	else
	{
		Page_t* previous_page = PageStack.pages[PageStack.top - 1];
		previous_page->init();
		lv_scr_load_anim(*previous_page->page_obj, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true);
	}

}

/**
 * back to bottom page home page
 *
 * @param NULL
 * @return NULL
 */
void Page_Back_Bottom(void) {

	if (page_stack_is_empty(&PageStack))
	{
		return;
	}
	/*filp all of page except stack bottom*/
	while (PageStack.top > 1)
	{
		page_stack_pop(&PageStack);
	}
	PageStack.pages[PageStack.top - 1]->init(); 
	lv_scr_load_anim(*PageStack.pages[PageStack.top - 1]->page_obj, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true);
}



/**
 * Load a new page to stack top
 *
 * @param newPage Page_t a new page
 * @return NULL
 */
void Page_Load(Page_t* newPage) {
	// 检查堆栈是否已满
	if (PageStack.top >= MAX_DEPTH - 1) {
		// 错误处理：堆栈满
		return;
	}

	// 如果堆栈非空，反初始化当前页面
	if (PageStack.top > 0) {
		PageStack.pages[PageStack.top - 1]->deinit();
	}

	// 将新页面推入堆栈
	page_stack_push(&PageStack, newPage);
	newPage->init(); // 初始化新页面
	lv_scr_load_anim(*newPage->page_obj, LV_SCR_LOAD_ANIM_FADE_ON, 100, 0, true);
}




/**
 * initialize the page manager & start home page
 *
 * @param NULL
 * @return NULL
 */
void Pages_init(void)
{
	page_stack_init(&PageStack);
	page_stack_push(&PageStack, &Page_Home);
	Page_Home.init();
	lv_disp_load_scr(*Page_Home.page_obj);
}

