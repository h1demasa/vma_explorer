# vma_explorer

I tested on Linux 6.11.0-9-generic.

Build vma_explorer Linux kernel module.

```sh
make
```

Load vma_explorer Kernel Module.
```sh
sudo insmod vma_explorer.ko 
```

Get log from `/proc/vma_info`.
```sh
sudo cat /proc/vma_info > vma_explorer.log
```

Split log from vma_explorer.log.
```sh
./split_process_vma_log.awk vma_explorer.log
```


This is the example of log that after executed `split_process_vma_log.awk`.
```systemd_1.txt
Process: systemd (PID: 1)
VMA ffff98fc462aa2e0:
  Start: 0x652aaef2b000, End: 0x652aaef32000
  Flags: 0x8000071
  Page Prot: 0x8000000000000025
  VM Operations:
    open handler:              0x0
    close handler:             0x0
    may_split handler:         0x0
    mremap handler:            0x0
    mprotect handler:          0x0
    fault handler:             filemap_fault+0x0/0xa00
    huge_fault handler:        0x0
    map_pages handler:         filemap_map_pages+0x0/0x570
    pagesize handler:          0x0
    page_mkwrite handler:      ext4_page_mkwrite+0x0/0x5b0
    pfn_mkwrite handler:       0x0
    access handler:            0x0
    find_special_page handler: 0x0
  Mapped file: /usr/lib/systemd/systemd
  -----------------
VMA ffff98fc462aa398:
  Start: 0x652aaef32000, End: 0x652aaef3e000
  Flags: 0x8000075
  Page Prot: 0x25
  VM Operations:
    open handler:              0x0
    close handler:             0x0
    may_split handler:         0x0
    mremap handler:            0x0
    mprotect handler:          0x0
    fault handler:             filemap_fault+0x0/0xa00
    huge_fault handler:        0x0
    map_pages handler:         filemap_map_pages+0x0/0x570
    pagesize handler:          0x0
    page_mkwrite handler:      ext4_page_mkwrite+0x0/0x5b0
    pfn_mkwrite handler:       0x0
    access handler:            0x0
    find_special_page handler: 0x0
  Mapped file: /usr/lib/systemd/systemd
  -----------------
VMA ffff98fc462aa228:
  Start: 0x652aaef3e000, End: 0x652aaef44000
  Flags: 0x8000071
  Page Prot: 0x8000000000000025
  VM Operations:
    open handler:              0x0
    close handler:             0x0
    may_split handler:         0x0
    mremap handler:            0x0
    mprotect handler:          0x0
    fault handler:             filemap_fault+0x0/0xa00
    huge_fault handler:        0x0
    map_pages handler:         filemap_map_pages+0x0/0x570
    pagesize handler:          0x0
    page_mkwrite handler:      ext4_page_mkwrite+0x0/0x5b0
    pfn_mkwrite handler:       0x0
    access handler:            0x0
    find_special_page handler: 0x0
  Mapped file: /usr/lib/systemd/systemd
  -----------------

  [...]
```
