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
//  Udp socket doesn't need to establish any connections!!!
//	void Connect(int sock_id, struct sockaddr *serv_addr, int len_sock_addr) const;

public:
	int sock_id;

	struct sockaddr_in client_addr;
	struct sockaddr_in server_addr;

	socklen_t client_addr_len;
	socklen_t server_addr_len;

	void Socket_for_udp();
	void Socket_for_tcp();

	void Setsockopt(int , int , int, void *, int);

	void Bind(int, SA *, int) const;

	void Connect();
	int CheckConnect(int iSocket);

	void Connect_non_b();

//	Transmitter(int, struct sockaddr_in, struct sockaddr_in);
	Transmitter() {}

	~Transmitter();

	void transmitter_new(char *addr_self, char *port_self, 
		                 char *addr_dst,  char *port_dst); 

	void transmitter_new_tcp_sponsor(char *addr_self, char *port_self,
                					 char *addr_dst, char *port_dst);
	void transmitter_new_tcp_non_b_sponsor(char *addr_self, char *port_self,
                					  	   char *addr_dst, char *port_dst);

	void recv_td_func(int id_core, int id_path, Data_Manager &data_smanager);

//	void recv_func(int id_path, Data_Manager &data_smanager);

	void decaps_pkt(VData_Type *packet, uchar &id_seg, uchar &id_region, 
					uchar &block_id, uchar &symbol_id, int &originBlk_size,
					uchar &s_level, uchar &k_fec, uchar &m_fec); 

	int Send_udp(char *data_src, int len);
	int Recv_udp(char *data_dst, int len);

	int Send_tcp(char *data_src, int len);
	int Recv_tcp(char *data_dst, int len);
	
	int Recv_tcp_non_b(char *data_dst, int len);

	int Recv_tcp_fixed_len(char *data_dst, int len_specified);
	int Recv_tcp_non_b_fixed_len(char *data_dst, int len_specified);	


	int Sendto_tcp(char *data_src, int len);
	int Recvfrom_tcp(char *data_dst, int len);

	void Print_BlockData(shared_ptr<struct Block_Data> blk);
};

#endif
