# proc 文件系统(用户控制内核)
## 子目录
* apm         高级电源管理
* bus         总线和总线上的设备
* devices     可用的设备信息
* drier       已经启用的驱动程序
* interrupt   中断信息
* ioports     端口使用信息
* version     内核版本

## 操作
  * more
  * cat
  * vi

## 结构
### 内核描述


        struct proc_dir_entry {
	        unsigned int low_ino;
	        unsigned short namelen;
	        const char *name;
	        mode_t mode;
	        nlink_t nlink;
	        uid_t uid;
	        gid_t gid;
	        loff_t size;
	        const struct inode_operations *proc_iops;
	/*
	 * NULL ->proc_fops means "PDE is going away RSN" or
	 * "PDE is just created". In either case, e.g. ->read_proc won't be
	 * called because it's too late or too early, respectively.
	 *
	 * If you're allocating ->proc_fops dynamically, save a pointer
	 * somewhere.
	 */
	const struct file_operations *proc_fops;
	struct proc_dir_entry *next, *parent, *subdir;
	void *data;
	read_proc_t *read_proc;
	write_proc_t *write_proc;
	atomic_t count;		/* use count */
	int pde_users;	/* number of callers into module in progress */
	spinlock_t pde_unload_lock; /* proc_fops checks and pde_users bumps */
	struct completion *pde_unload_completion;
	struct list_head pde_openers;	/* who did ->open, but not ->release */};


## 操作
* 创建文件

        struct proc_dir_entry* create_proc_entry(const char *name, // 创建的文件名
                                            mode_t mode,　// 创建的文件属性
                                            struct proc_dir_entry *parent);// 路径

* 创建目录

        struct proc_dir_entry* proc_mkdir(const char *name, // 创建的文件名
                                          struct proc_dir_entry *parent);// 路径
* 删除目录和文件

        void remove_proc_entry(const char *name,
                                struct proc_dir_entry *parent)

* 读写回调函数
  * 读操作
        int read_fun(char *buffer, // 返回给用户的信息写在buffer < PAGE_SIZE
                    char **stat,
                    off_t off,　// 偏移量
                    int count,　
                    int *peof,　//读到文件末尾时　置　１
                    void *data);

  * 写操作
        int write_fun(struct file *file, // proc文件结构
                      const char *buffer, // 待写的数据
                      unsigned long count,// 大小
                      void *data);
