/*
 * Basic kernel module taking commandline arguments.
 *
 * Author:
 * 	Stefan Wendler (devnull@kaltpost.de)
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/gpio.h>

/*
 * The module commandline arguments ...
 */
static int speed = 5;

static int ios[2] = {-1, -1};
static int arr_argc = 0;

static int edge[2] = {-1, -1}; // de pin waarvan je de edges wil weten
static int count=0;

module_param(speed, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(speed, "An integer");
module_param_array(ios, int, &arr_argc, 0000);
MODULE_PARM_DESC(ios, "An array of integers");

module_param_array(edge, int, &arr_argc, 0000);
MODULE_PARM_DESC(edge, "An integer, that defines what pin edge you want");

// #define LED1 4

static struct timer_list blink_timer;
static long led1 = 0;
static long led2 = 0;

/*
 * Timer function called periodically
 */
static void blink_timer_func(struct timer_list *t)
{
	printk(KERN_INFO "%s\n", __func__);

	gpio_set_value(ios[0], led1);
	led1 = !led1;
	gpio_set_value(ios[1], led2);
	led2 = !led2;
	
	count = count+ 1;
	if (edge[0] == ios[0])
	{
		printk(KERN_INFO "Aantal edges: %d van led: %d, edge pin %d\n", count, ios[0], edge[0]);
	}

	if (edge[1] == ios[1])
	{
		printk(KERN_INFO "Aantal edges: %d van led %d, edge pin %d\n", count, ios[1], edge[1]);
	}
	
	
	/* schedule next execution */
	//blink_timer.data = !data;						// makes the LED toggle
	blink_timer.expires = jiffies + (speed*HZ); // 1 sec.
	add_timer(&blink_timer);
}

/*
 * Module init function
 */
static int __init clargmod_init(void)
{
	int i;
	int ret[2] = {0,0};

	printk(KERN_INFO "speed is an integer: %d\n", speed);

	for (i = 0; i < (sizeof ios / sizeof(int)); i++)
	{
		printk(KERN_INFO "ios[%d] = %d\n", i, ios[i]);
	}

	printk(KERN_INFO "got %d arguments for ios.\n", arr_argc);

	printk(KERN_INFO "%s\n", __func__);

	// register, turn off
	ret[0] = gpio_request_one(ios[0], GPIOF_OUT_INIT_LOW, "led1");
	ret[1] = gpio_request_one(ios[1], GPIOF_OUT_INIT_LOW, "led2");
	if (ret[0])
	{
		printk(KERN_ERR "Unable to request GPIOs: %d\n", ret[0]);
		return ret[0];
	}
	if (ret[1])
	{
		printk(KERN_ERR "Unable to request GPIOs: %d\n", ret[1]);
		return ret[1];
	}

	/* init timer, add timer function */
	//init_timer(&blink_timer);
	timer_setup(&blink_timer, blink_timer_func, 0);

	blink_timer.function = blink_timer_func;
	//blink_timer.data = 1L;							// initially turn LED on
	blink_timer.expires = jiffies + (speed*HZ); // 1 sec.
	add_timer(&blink_timer);

	return ret[0];
}

/*
 * Exit function
 */
static void __exit clargmod_exit(void)
{
	printk(KERN_INFO "%s\n", __func__);

	// deactivate timer if running
	del_timer_sync(&blink_timer);

	// turn LED off
	gpio_set_value(ios[0], 0);

	// unregister GPIO
	gpio_free(ios[0]);
	gpio_set_value(ios[1], 0);

	// unregister GPIO
	gpio_free(ios[1]);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Croes Robbe");
MODULE_DESCRIPTION("Basic Linux Kernel module taking command line arguments");

module_init(clargmod_init);
module_exit(clargmod_exit);