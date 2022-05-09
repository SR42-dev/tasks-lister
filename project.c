#include <linux/init.h> 
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>

// function to print the output on the console
void print_tree(struct task_struct *root)
{
    struct list_head *list;
    struct task_struct *new;
    struct task_struct *new_copy;
    list_for_each(list, &root->children)
    {
      char separator[100] = " ";
      new = list_entry(list, struct task_struct, sibling);
      new_copy = new;
      while(new_copy->parent != &init_task)
      {
        new_copy = new_copy->parent;
        strcat(separator, " ");
      }  
      printk("%s ->[%d] %s, state: %ld\n",separator, new->pid, new->comm, new->state);

      if((&new->children)->next != &new->children) print_tree(new);
    }
}

// this function is called when the module is loaded
int __init simple_init(void)
{
    printk(KERN_INFO "loading Module\n");

    print_tree(&init_task);

    printk(KERN_INFO "module loaded.\n");
    return 0;
}


// this function is called when the module is removed
void __exit simple_exit(void)
{
    printk(KERN_INFO "removing module\n");
}

// Macros for registering module entry and exit points
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("module to list all current tasks in a linux system in tree format");
MODULE_AUTHOR("SR42");
