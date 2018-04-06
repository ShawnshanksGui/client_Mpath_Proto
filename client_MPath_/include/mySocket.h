#ifndef _MYSOCKET_H_
#define _MYSOCKET_H_

#include "fcntl.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "common.h"
#include "data_manager.h"
/*
struct Param_Transmitter{
	int num_core;
	int id_path;
	char *addr_self;
	char *port_self; 
	char *addr_dst; 
	char *port_dst;	
};
*/

typedef struct sockaddr SA;

class Transmitter {
private:
	int sock_id;
	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;

	void Socket_for_udp();

	void Setsockopt(int , int , int, void *, int);

	void Bind(int, SA *, int) const;

//  Udp socket doesn't need to establish any connections!!!
//	void Connect(int sock_id, struct sockaddr *serv_addr, int len_sock_addr) const;

public:
//	Transmitter(int, struct sockaddr_in, struct sockaddr_in);
	Transmitter() {}

	~Transmitter();

	void transmitter_new(char *addr_self, char *port_self, 
		                 char *addr_dst,  char *port_dst); 
	
	void recv_td_func(int id_path, Data_Manager &data_smanager);


	void decaps_pkt(uchar &id_seg, uchar &block_id, uchar &symbol_id,
				    int originBlk_size, uchar &s_level, uchar &k_fec, 
				    uchar &m_fec); 

	int Send_udp(char *data, int len);
	int Recv_udp(char *buf_dst, int len);
};

#endif