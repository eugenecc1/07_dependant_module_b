#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");

extern void func_in_module_1(void);
void (*ptr_func_1)(void);

void func_in_module_2(void)
{
	printk("Function in Module 2 called\n\n");
}
EXPORT_SYMBOL(func_in_module_2);

static int my_init(void)
{
	printk("Module 2 Loaded\n");
	ptr_func_1 = symbol_get(func_in_module_1);
	if (ptr_func_1){
		ptr_func_1();
		symbol_put(func_in_module_1);
	
	}
	else
		printk("Other module not loaded\n\n");
	return 0;
}

static void my_exit(void)
{
	printk("Module 2 Removed\n");

}

module_init(my_init);
module_exit(my_exit);
