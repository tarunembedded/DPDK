#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/queue.h>

#include <rte_memory.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_lcore.h>
#include <rte_per_lcore.h>
#include <rte_debug.h>

//#include <rte_ring_core.h>
//#include <rte_ring_elem.h>
#include <rte_common.h>
#include <rte_ring.h>
#include <rte_debug.h>
#include <rte_mempool.h>
#include <rte_string_fns.h>
#include <rte_mbuf.h>
#include <rte_mbuf_dyn.h>
#include <rte_mbuf_core.h>

#define MAX 3
//#define rte_pktmbuf_mtod (databuffer,int)

//#define SCHED_TX_RING_SZ 0x1000
 
                struct rte_mempool *mempool;
		struct rte_mbuf *mbuf;
		int *buffer;
		static char *databuffer;
		uint16_t t = 4;
                unsigned int n = 7;
		unsigned int cache_size = 0;
                const char *tring = "dhjwgf";
		const char* mbufpool;
		uint16_t priv_size;
		uint16_t data_room_size = 400;
                //unsigned int SCHED_TX_RING_SZ;
                //int socket_id;
                //unsigned int RING_F_SP_ENQ;
                int unused __attribute__((unused));
                struct rte_ring* ring;
		struct rte_ring* ring2;
		//struct rte_mbuf* mbuf;
                int enqueue1,enqueue2,dequeue1,dequeue2;

		size_t pkt_size;
		uint16_t len = 5;
		int z = 0,counter = 0;

static int lcore_hello(__attribute__((unused)) void *arg)
{
	unsigned lcore_id;
	lcore_id = rte_lcore_id();
	printf("This is from core %u\n",lcore_id);
	
	if(lcore_id == 3)
	{
		//pointer = (int *) rte_pktmbuf_pool_create_by_ops(mbufpool,n,0,priv_size,data_room_size,0,NULL);
		printf("Mempool Address is = %p\n",mempool);
		mbuf = rte_pktmbuf_alloc(mempool);
		printf("Mbuf Address is = %p\n",mbuf);
		databuffer = rte_pktmbuf_append (mbuf, 4);
		printf("Address of databuffer pointer to store data is = %p\n",databuffer);
		//printf("Mbuf Address is = %p\n",mbuf);
		printf("Mbuf value before initialization is %d\n",*databuffer);
		//*databuffer = 5;
		while(1)
		{
		//string = (int *) malloc (n*sizeof(int));
		//string = (int *)rte_pktmbuf_pool_create_by_ops(mbufpool,n,0,priv_size,data_room_size,0,NULL);
		//printf("%d\n",*buffer);	
	
		//for(int z=0; ; z++)
		//{
		//int z = 0;
		//*buffer = z + 1;
		//int z=0;
		*databuffer = 'A';
		enqueue1 = rte_ring_enqueue (ring,mbuf);
		//z++;
		//}
		}
	}
	else if (lcore_id == 4)
	{
		while(1)
		{
		dequeue1 = rte_ring_dequeue (ring,(void **)&mbuf);
		enqueue2 = rte_ring_enqueue (ring2,mbuf);
		}
	}

	else if (lcore_id == 5)
	{
		//*string++;
		while(1)
		{
		dequeue2 = rte_ring_dequeue (ring2,(void **)&mbuf);
		//databuffer = rte_mbuf_data_addr_default(mbuf);
		//databuffer = rte_mbuf_buf_addr (mbuf,mempool);
		databuffer= rte_pktmbuf_mtod (mbuf,char *);
		printf("The dequeue data from core 5 is = %c\n",*databuffer);
		counter++;
		printf("%d\n",counter);
		rte_pktmbuf_free(mbuf);
		//free(string);
		}
	}

	else
		return 1;

return 0;
}

int main(int argc, char **argv)
{
	int ret;
	//char *ptr = "Tarun"; 
       const char *arrptrs[MAX] = {"./my_helloworld","-l","2-5"};
	 
	//unsigned lcore_id;

	printf("The value of argc is %d\n",argc);
	for(int i=0;i<argc;i++)
	{
	printf("The value of argv is %s\n",argv[i]);
	}

	ret = rte_eal_init(MAX, (char**)&(arrptrs));

	if(ret < 0)
		rte_panic("Cannot init EAL\n");

	//RTE_LCORE_FOREACH_SLAVE(lcore_id){
	
		//rte_eal_remote_launch(lcore_hello, NULL, 3);
		
                //printf("The String Data is %s\n",string);

		//rte_ring_create(ring, 8192, string, RING_F_SP_ENQ);
	
		mempool = rte_pktmbuf_pool_create_by_ops(mbufpool,n,0,priv_size,data_room_size,0,NULL);

		ring  = rte_ring_create(tring, 8192, 0, RING_F_SP_ENQ);

		ring2 = rte_ring_create("ring2", 8, 0, RING_F_SP_ENQ);

		rte_eal_remote_launch(lcore_hello, mempool, 3);

                //enqueue1 = rte_ring_enqueue (result1,string);

                //printf("%d\n",enqueue1);
		
		rte_eal_remote_launch(lcore_hello, NULL, 4);

		//result2 = rte_ring_create(ring,8192,0,RING_F_SC_DEQ);

		//dequeue1 = rte_ring_dequeue(result2,enqueue1);
	
		//printf("%d\n",dequeue1);

		rte_eal_remote_launch(lcore_hello, NULL, 5);

	 	//free(string);	
	//lcore_hello(NULL);
	
	//rte_eal_mp_wait_lcore();

	rte_eal_cleanup();

	return 0;
}
