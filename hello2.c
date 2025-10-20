// SPDX-License-Identifier: GPL-2.0-or-later
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_AUTHOR("Koval Kostiantyn <koftatfok@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training - Module 2");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0644);
MODULE_PARM_DESC(print_count, "Number of times to print 'Hello, world!' (default=1)");

static int __init hello2_init(void)
{
	uint i;

	if (print_count > 10) {
		pr_err("Error: print_count > 10\n");
		return -EINVAL;
	}

	if (print_count == 0 || (print_count >= 5 && print_count <= 10))
		pr_warn("Warning: print_count is %u\n", print_count);

	for (i = 0; i < print_count; i++)
		print_hello();

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2 module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);