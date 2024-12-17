#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/sched/mm.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static struct proc_dir_entry *vma_file;

static void print_vma_info(struct seq_file *m, struct vm_area_struct *vma)
{
    seq_printf(m, "VMA %px:\n", vma);
    seq_printf(m, "  Start: 0x%lx, End: 0x%lx\n", vma->vm_start, vma->vm_end);
    seq_printf(m, "  Flags: 0x%lx\n", vma->vm_flags);
    seq_printf(m, "  Page Prot: 0x%lx\n", pgprot_val(vma->vm_page_prot));
    
    if (vma->vm_ops) {
        seq_printf(m, "  VM Operations:\n");
        seq_printf(m, "    open handler:              %pS\n", vma->vm_ops->open);
        seq_printf(m, "    close handler:             %pS\n", vma->vm_ops->close);
        seq_printf(m, "    may_split handler:         %pS\n", vma->vm_ops->may_split);
        seq_printf(m, "    mremap handler:            %pS\n", vma->vm_ops->mremap);
        seq_printf(m, "    mprotect handler:          %pS\n", vma->vm_ops->mprotect);
        seq_printf(m, "    fault handler:             %pS\n", vma->vm_ops->fault);
        seq_printf(m, "    huge_fault handler:        %pS\n", vma->vm_ops->huge_fault);
        seq_printf(m, "    map_pages handler:         %pS\n", vma->vm_ops->map_pages);
        seq_printf(m, "    pagesize handler:          %pS\n", vma->vm_ops->pagesize);
        seq_printf(m, "    page_mkwrite handler:      %pS\n", vma->vm_ops->page_mkwrite);
        seq_printf(m, "    pfn_mkwrite handler:       %pS\n", vma->vm_ops->pfn_mkwrite);
        seq_printf(m, "    access handler:            %pS\n", vma->vm_ops->access);
        seq_printf(m, "    find_special_page handler: %pS\n", vma->vm_ops->find_special_page);
    }
    
    if (vma->vm_file) {
        char buf[256];
        char *path = file_path(vma->vm_file, buf, sizeof(buf));
        if (!IS_ERR(path)) {
            seq_printf(m, "  Mapped file: %s\n", path);
        }
    }

    seq_printf(m, "  -----------------\n");
}

static void explore_task_mm(struct seq_file *m, struct task_struct *task)
{
    struct mm_struct *mm;
    struct vm_area_struct *vma;

    mm = get_task_mm(task);
    if (!mm)
        return;

    seq_printf(m, "Process: %s (PID: %d)\n", task->comm, task->pid);

    VMA_ITERATOR(iter, mm, 0);

    for_each_vma(iter, vma) {
        print_vma_info(m, vma);
    }

    mmput(mm);
}

static int vma_show(struct seq_file *m, void *v)
{
    struct task_struct *task;

    seq_printf(m, "VMA Information:\n");
    seq_printf(m, "=================\n\n");

    for_each_process(task) {
        explore_task_mm(m, task);
    }

    return 0;
}

static int vma_open(struct inode *inode, struct file *file)
{
    return single_open(file, vma_show, NULL);
}

static const struct proc_ops vma_ops = {
    .proc_open = vma_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init vma_explorer_init(void)
{
    vma_file = proc_create("vma_info", 0444, NULL, &vma_ops);
    if (!vma_file) {
        pr_err("Failed to create proc file\n");
        return -ENOMEM;
    }
    return 0;
}

static void __exit vma_explorer_exit(void)
{
    proc_remove(vma_file);
}

module_init(vma_explorer_init);
module_exit(vma_explorer_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hidemasa KAWASAKI");
MODULE_DESCRIPTION("VMA Explorer with File Output");