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
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

#define BUFFER_SIZE 128
#define PROC_NAME "pid"

/**
 * This function is called each time the read the `/proc` file system.
 *
 * @param file A pointer to the file structure which is being read.
 * @param buf The output buffer, in user space.
 * @param count The expected lenght of the output.
 * @param pos The offset position of the buffer.
 *
 * @return The size of the buffer outputted by this call.
 *
 * This function is called repeatedly until it returns `0`, so
 * there must be logic that ensures it ultimately returns `0`
 * once it has collected the data that is to go into the
 * corresponding `/proc` file.
 *
 */
static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);
/**
 * This function is called each time we write to the /proc file system.
 *
 * @param file A pointer to the file structure which has been writen.
 * @param buf The input buffer, in user space.
 * @param count The size of the input buffer.
 * @param pos The offset position which is being read.
 */
static ssize_t proc_write(struct file *file, const char *buf, size_t count, loff_t *pos);

/* the current pid */
static long pid;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
static struct proc_ops proc_ops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};
#else
static struct file_operations proc_ops = {
    .owner = THIS_MODULE,
    .read = proc_read,
    .write = proc_write,
};
#endif

/* This function is called when the module is loaded. */
static int proc_init(void)
{
  // creates the /proc/pid entry
  // the following function call is a wrapper for
  // proc_create_data() passing NULL as the last argument
  proc_create(PROC_NAME, 0666, NULL, &proc_ops);

  printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

  return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void)
{

  // removes the /proc/hello entry
  remove_proc_entry(PROC_NAME, NULL);

  printk(KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
  int rv = 0;
  char buffer[BUFFER_SIZE];
  static int completed = 0;
  struct task_struct *tsk = NULL;

  if (completed)
  {
    completed = 0;
    return 0;
  }

  completed = 1;

  tsk = pid_task(find_vpid(pid), PIDTYPE_PID);

  rv = sprintf(buffer, "command = [%s] pid = [%ld] state = [%ld]\n", tsk->comm, pid, tsk->state);

  // copies the contents of buffer to userspace usr_buf
  if (copy_to_user(usr_buf, buffer, rv))
  {
    rv = -1;
  }

  return rv;
}

static ssize_t proc_write(struct file *file, const char __user *usr_buf, size_t count, loff_t *pos)
{
  char *k_buf;
  /* allocate kernel memory */
  k_buf = kmalloc(count, GFP_KERNEL);

  /* copies user space usr_buf to kernel buffer */
  if (copy_from_user(k_buf, usr_buf, count))
  {
    printk(KERN_ERR "Error copying from user\n");
    return -1;
  }

  printk(KERN_DEBUG "reading the next %lu bytes from buffer: \"%s\"\n", count, k_buf);
  sscanf(k_buf, "%ld", &pid);

  printk(KERN_DEBUG "just received pid = %ld\n", pid);

  kfree(k_buf);

  return count;
}

/* Macros for registering module entry and exit points. */
module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("pid");
MODULE_AUTHOR("PD/JG");
