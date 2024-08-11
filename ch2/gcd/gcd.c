/**
 * simple.c
 *
 * A simple kernel module.
 *
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gcd.h>

/* This function is called when the module is loaded. */
static int simple_init(void)
{
       printk(KERN_INFO "[gcd] Loading Module\n");
       return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void)
{
       unsigned long greatest_common_divisor = gcd(3300, 24);
       printk(KERN_INFO "[gcd] %lu\n", greatest_common_divisor);
       printk(KERN_INFO "[gcd] Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GCD Logger");
MODULE_AUTHOR("SGG");
