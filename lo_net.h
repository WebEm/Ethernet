#ifndef __LO_NET_H
#define __LO_NET_H

#define LO_RX_DESC 128
#define LO_TX_DESC 128

/* one structure with all info
 * required for lo_net driver.
 */
struct lo_net_info {
	uint8_t duplex;
	uint8_t speed;
	dma_addr_t *rx_dma;
	dma_addr_t *tx_dma;
	unsigned int tx_desc;
	unsigned int rx_desc;
	unsigned int tx_q_len;
	struct net_device *ebmc_dev;
	void *priv_data;
	

};

#endif
