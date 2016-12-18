# 内核定时器
    struct timer_list{
        struct list_head entry; //内核使用
        unsigned long expires;　// 超时的jiffies 值
        void (* function)(unsigned long);// 超时处理函数
        unsigned long data;// 超时处理函数的参数
        struct tvec_base* base;
      }
## 操作函数
    * 初始化定时器队列结构
    void init_timer(struct timer_list *timer);
    * 启动定时器
    void add_timer(struct timer_list *timer);
    * 在定时器超时前将它删除
    void del_timer(struct timer_list *timer);
