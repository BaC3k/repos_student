
#include <linux/init.h>
#include <linux/module.h>


MODULE_LICENSE("GPL");


static char *word = "world";
module_param(word, charp, 0644);
MODULE_PARM_DESC(word, "Hello, ...");


static int n = 1;
module_param(n, int, 0644);
MODULE_PARM_DESC(n, "Number of Hello");

static int __init hello_init(void)
{
	int i;

	for (i = 0; i < n; i++)
		pr_alert("(%d) Hello, %s\n", i, word);
	return 0;
}

static void __exit hello_exit(void)
{
	pr_alert("I am getting killed\n");
}


module_init(hello_init);
module_exit(hello_exit);
