// SPDX-License-Identifier: GPL-2.0-or-later
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Koval Kostiantyn <koftatfok@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training - Module 1");
MODULE_LICENSE("Dual BSD/GPL");

struct print_time_data {
	struct list_head list;
	ktime_t before;
	ktime_t after;
};

static LIST_HEAD(print_time_list);

void print_hello(void)
{
	struct print_time_data* data = kmalloc(sizeof(*data), GFP_KERNEL);

	if (!data)
		return;

	data->before = ktime_get();
	pr_info("Hello, world!\n");
	data->after = ktime_get();

	list_add(&data->list, &print_time_list);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct print_time_data* data, * tmp;
	int count = 0;

	list_for_each_entry_safe(data, tmp, &print_time_list, list) {
		pr_info("print %d took %lld ns\n",
			count++,
			ktime_to_ns(ktime_sub(data->after, data->before)));
		list_del(&data->list);
		kfree(data);
	}
}

static int __init hello1_init(void)
{
	pr_info("hello1 module loaded\n");
	return 0;
}

module_init(hello1_init);
module_exit(hello1_exit);