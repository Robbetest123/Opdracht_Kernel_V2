#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xd6f3c647, "module_layout" },
	{ 0xfff6fae, "param_array_ops" },
	{ 0x1ca6efca, "param_ops_int" },
	{ 0xfe990052, "gpio_free" },
	{ 0x97934ecf, "del_timer_sync" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x403f9529, "gpio_request_one" },
	{ 0x24d273d1, "add_timer" },
	{ 0x526c3a6c, "jiffies" },
	{ 0x2ba87a73, "gpiod_set_raw_value" },
	{ 0x592aaad1, "gpio_to_desc" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "BAE6247163ABC5C9BF2F40C");
