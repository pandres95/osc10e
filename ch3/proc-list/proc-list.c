/**
 * hello.c
 *
 * Kernel module that communicates with /proc file system.
 *
 * The makefile must be modified to compile this program.
 * Change the line "simple.o" to "hello.o"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/version.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

/* This function is called when the module is loaded. */
static int mod_init(void)
{
  struct task_struct *task = NULL;

  printk(KERN_INFO "==============================\n");
  printk(KERN_INFO "Iterating over tasks linearly \n");
  printk(KERN_INFO "==============================\n");

  for_each_process(task)
  {
    printk(KERN_INFO "[[proc-list]] command = [%s] state = [%ld] pid = [%d]\n", task->comm, task->state, task->pid);
  }

  return 0;
}

/* This function is called when the module is removed. */
static void mod_exit(void)
{
  printk(KERN_INFO "[[proc-list]] Goodbye\n");
}

/* Macros for registering module entry and exit points. */
module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("proc-list");
MODULE_AUTHOR("PD/JG");
