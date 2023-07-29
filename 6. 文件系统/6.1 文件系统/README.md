## 文件存储

### inode

`inode` 是 Linux 和 Unix 操作系统中的一个重要概念，它是文件系统中的一个 `数据结构`，用于存储文件的元数据。每个文件和目录都有一个对应的 `inode` 来描述其属性和位置信息。

```shell
root@freecho:/opt/C/gcc/code# stat hello.c
  File: hello.c
  Size: 373             Blocks: 8          IO Block: 4096   regular file
Device: b301h/45825d    Inode: 1314593     Links: 1
Access: (0644/-rw-r--r--)  Uid: (    0/    root)   Gid: (    0/    root)
Access: 2023-07-26 21:29:11.655510006 +0800
Modify: 2023-07-26 21:29:11.655510006 +0800
Change: 2023-07-26 21:29:11.655510006 +0800
Birth: 2023-07-26 21:29:11.655510006 +0800
```

`inode` 结构包含了以下信息：不包含文件名

1. 文件类型：标识文件是普通文件、目录、符号链接等类型。
2. 文件权限：文件的读、写、执行权限。
3. 文件所有者和所属组：标识文件的所有者和所属的用户组。
4. 文件大小：文件的大小，以字节为单位。
5. 文件时间戳：记录文件的创建时间、修改时间和访问时间等。
6. 文件链接数：记录文件的硬链接数目。
7. 数据块指针：指向文件存储数据的数据块。

当系统中创建一个新文件时，会为该文件分配一个唯一的 `inode`，然后将文件的实际数据存储在数据块中，并将 `inode` 中的数据块指针指向这些数据块。在文件被访问或修改时，通过 `inode` 可以快速定位文件的数据块，而不需要遍历整个文件系统。

通过 `ls -i` 命令可以查看文件的 `inode` 号码。每个文件和目录在同一文件系统中具有唯一的 `inode` 号码。

`inode` 在文件系统的性能和管理中起着关键作用，它使得文件系统能够高效地管理文件和目录，并支持硬链接的使用。

### dentry

`dentry` ,  （即 `directory entry` 目录项）是 Linux 文件系统中的一个重要概念，用于管理文件系统中的目录。`dentry` 与 `inode` 相关联，共同组成了 Linux 文件系统中的目录项。其本质依然是结构体，重要成员变量有两个 `{文件名，inode，...}`，而文件内容(data)保存在磁盘盘块中

每个目录都包含一个或多个 `dentry`，每个 `dentry` 表示一个目录中的文件或子目录。`dentry` 记录了文件或目录的名称、文件类型和对应的 `inode` 号码等信息。当用户访问文件时，Linux 文件系统会通过 `dentry` 来快速定位文件的 `inode`，从而访问文件的实际数据。

在 Linux 文件系统中，`dentry` 会被缓存在内存中，以提高文件系统的性能。当用户访问文件时，系统首先会查找该文件对应的 `dentry` 是否已经缓存，如果已经缓存，则直接从 `dentry` 中获取 `inode` 信息，避免了不必要的磁盘访问。如果文件对应的 `dentry` 不在缓存中，系统会通过目录索引进行查找，并将找到的 `dentry` 缓存起来，以便下次快速访问。

`dentry` 与目录层次结构一起形成了文件系统的层次结构，通过 `dentry` 可以在文件系统中快速定位文件和目录，提高了文件系统的访问效率和性能。同时，`dentry` 的缓存机制也减少了不必要的磁盘访问，提高了整个文件系统的效率。

![](https://yy.liveout.cn/article/Learn/C/2023/fileSys1.png)

### 文件系统

文件系统是一组规则，规定对文件的存储及读取的一般方法。文件系统在磁盘格式化过程中指定。

以下为常见文件系统：

1. FAT32（File Allocation Table 32）：FAT32是一种较旧的文件系统，广泛应用于可移动介质（如USB闪存驱动器、SD卡等）。它是Windows系统和其他操作系统的通用文件系统。
2. NTFS（New Technology File System）：NTFS是Windows操作系统中使用的主要文件系统。它支持大文件和文件系统，并提供更高级的权限控制和数据安全性。
3. exFAT（Extended File Allocation Table）：exFAT是FAT32文件系统的改进版本，特别设计用于支持更大的文件和分区。它通常在移动存储设备和外部驱动器中使用。
4. ext2（Second Extended File System）：ext2是Linux系统早期的文件系统，不具备日志功能。虽然现在很少使用，但仍然是一些老旧系统的选择。
5. ext3（Third Extended File System）：ext3是ext2文件系统的改进版本，具有日志记录功能，可提供更好的数据完整性和恢复能力。
6. ext4（Fourth Extended File System）：ext4是Linux系统中目前最常用的文件系统，它是ext3文件系统的进一步改进，提供更高的性能和可靠性。ext4支持更大的文件和文件系统，并具备更高级的特性。

### 硬链接、软连接

`硬链接` 和 `软链接` （又称软连接）是 Linux 文件系统中两种不同类型的链接方式，用于在文件系统中创建文件或目录之间的关联。

1. 硬链接（Hard Link）：
   - 硬链接是目录项（dentry）中指向相同 inode 号的不同目录项。
   - 通过硬链接，多个文件名可以指向同一个数据块，实际上是同一个文件的不同访问入口。
   - 硬链接创建后，可以像普通文件一样操作，读写内容，删除等，但是不能对目录进行硬链接。
   - 硬链接不能跨文件系统创建，即硬链接必须位于同一个文件系统。
2. 软链接（Symbolic Link / Soft Link）：
   - 软链接是一个特殊的文件，它包含了指向另一个文件或目录的路径名。
   - 软链接类似于 Windows 系统的快捷方式，它只是一个指向目标的快捷方式而已。
   - 软链接可以跨文件系统创建，因为它只保存了目标文件或目录的路径名。
   - 删除软链接并不会影响目标文件或目录，但如果目标文件或目录被删除，软链接将变为"断链"。

对比：

- 硬链接是多个目录项指向同一个 inode，它们是文件系统中同一个文件的不同名字，文件大小和权限都是相同的。
- 软链接是一个特殊的文件，它保存了指向目标文件或目录的路径名，它是目标文件或目录的"快捷方式"，不占用实际数据块。

注意事项：

- 删除硬链接或软链接并不会删除目标文件本身。
- 硬链接不能跨文件系统创建，而软链接可以。

示例：

```shell
$ echo "Hello, hard link!" > original.txt
$ ln original.txt hard_link.txt    # 创建硬链接
$ ln -s original.txt soft_link.txt # 创建软链接

$ ls -l
-rw-r--r--  2 user user 18 May 18 2023 hard_link.txt
lrwxrwxrwx  1 user user 13 May 18 2023 soft_link.txt -> original.txt

$ cat hard_link.txt  # 输出："Hello, hard link!"
$ cat soft_link.txt  # 输出："Hello, hard link!"

$ rm original.txt   # 删除原始文件
$ cat hard_link.txt  # 输出："Hello, hard link!"，硬链接仍然存在
$ cat soft_link.txt  # 输出："cat: soft_link.txt: No such file or directory"，软链接断链
```

