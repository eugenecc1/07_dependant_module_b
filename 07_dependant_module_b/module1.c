#include<linux/module.h>
#include<linux/init.h>

MODULE_LICENSE("GPL");

extern void func_in_module_2(void);
void (*ptr_func_2)(void);

void func_in_module_1(void)
{
	printk("Function in Module 1 called\n\n");
}
EXPORT_SYMBOL(func_in_module_1);

static int my_init(void)
{
	printk("Module 1 Loaded\n");
	ptr_func_2 = symbol_get(func_in_module_2);
	if (ptr_func_2){
		ptr_func_2();
		symbol_put(func_in_module_2);
	
	}
	else
		printk("Other module not loaded\n\n");
	return 0;
}

static void my_exit(void)
{
	printk("Module 1 Removed\n");

}

module_init(my_init);
module_exit(my_exit);
