/*
 *   lo_net.c
 * 
 * 2018+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * Simple network driver which would give broad
 * understanding of layer2 operations.
 * initial commit. 
 * Each functions and APIS will be explained in the 
 * subsequent commits.
 */

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/etherdevice.h>
#include "lo_net.h"
#define DRV_NAME "lo_net"
#define pl()	printk("%d %s\n", __LINE__, __func__);

static int lo_net_dev_open(struct net_device *dev)
{
	pl();
	return 0;
}

static int lo_net_dev_close(struct net_device *dev)
{
	pl();
	return 0;
}

static int lo_net_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	pl();
	return 0;
}

static int lo_net_set_mac_address(struct net_device *dev, void *p)
{
	pl();
	return 0;
}

static int lo_net_set_mtu(struct net_device *dev, int mtu)
{
	dev->mtu = mtu;
	pl();
	return 0;
}

static int lo_net_set_ioctl(struct net_device *dev,
			struct ifreq *rq, int cmd)
{
	pl();
	return 0;
}

static const struct net_device_ops lo_net_net_ops = {
	.ndo_open = lo_net_dev_open,
	.ndo_stop = lo_net_dev_close,
	.ndo_start_xmit = lo_net_start_xmit,
	.ndo_set_mac_address = lo_net_set_mac_address, 
	.ndo_do_ioctl = lo_net_set_ioctl,
	.ndo_change_mtu = lo_net_set_mtu,
};

static int lo_net_probe (struct platform_device *lo_net_pdev)
{
	struct net_device *dev;
	struct lo_net_info *priv;
	struct device  *dp;
	uint32_t err;
	
	pl();
	dev = alloc_etherdev(sizeof(struct lo_net_info));
	if (!dev)
		return -ENODEV;

	strcpy (dev->name, "bala");
	priv = netdev_priv(dev);
	priv->rx_desc = LO_RX_DESC;	
	priv->tx_desc = LO_TX_DESC;

	dev->netdev_ops = &lo_net_net_ops;
	/* 
         *Todo: Fill all required info.
         */
	dp = &lo_net_pdev->dev;
	dp->platform_data = dev;
	err = register_netdev(dev);
	if (err) {
		printk("%d Failed\n", err);
	}

	return 0;
}

static int lo_net_remove(struct platform_device *lo_net_pdev)
{
	struct device  *dp;
	struct net_device *dev;

	pl();
	dp = &lo_net_pdev->dev;
	dev = (struct net_device *)dp->platform_data;
	unregister_netdev(dev);
	return 0;
}

static struct platform_driver lo_net_driver = {
	.probe = lo_net_probe,
	.remove = lo_net_remove,
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE, 
	},
};

/*
 * Todo: To make it device tree compatible
 * and to parse form dt.
 */
struct platform_device lo_net_device = {
	.name = DRV_NAME,
	.id = -1,
};

static int __init lo_net_init(void)
{
	platform_driver_register(&lo_net_driver);
	platform_device_register(&lo_net_device);
	pl();
	return 0;
}

static void __exit lo_net_exit(void)
{
	pl();
	platform_driver_unregister(&lo_net_driver);
	platform_device_del(&lo_net_device);
}

module_init(lo_net_init);
module_exit(lo_net_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WebEm");
