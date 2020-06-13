#include "header.h"


void solve_puzzle(igraph_t *g, int *edge_set,int track, y_val **commit,unsigned char **buffer,int source,int sink,int res,unsigned long int *totalBytes)
{
	
	int j=track-1;
	unsigned int l;
	int from,to,i,level=0,prev_level=-1,k,m,level_test,s,flag=0,len;
        char eid[20];
	unsigned char string_pass[40];
        unsigned char **commitment=(unsigned char**)malloc(igraph_ecount(g)*sizeof(unsigned char*));
	unsigned char **y=(unsigned char**)malloc(igraph_ecount(g)*sizeof(unsigned char*));
	char str_store[80];
	for(i=0;i<igraph_vcount(g);i++)	
		y[i]=(unsigned char*)malloc(32*sizeof(unsigned char));
	gcry_md_hd_t h;
	gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
	strcpy(str_store,buffer[sink]);	
	gcry_md_write(h, str_store, 32); /* hash some text */	
	commitment[sink]=gcry_md_read(h, GCRY_MD_SHA256);
	
	if(commit[sink][0].puzzle!=commitment[sink])
        {
			
		printf("\nWrong commitment at sink, aborting...\n");
		exit(1);		

	}
	gcry_md_close(h);
	for(;j>=0;j--)
	{
                igraph_edge(g,edge_set[j],&from,&to);
                
		//	printf("solving for htlc (%d,%d) for amount %d, timeout period %d\n",from,to,(igraph_integer_t)igraph_cattribute_EAN(g,"flow",edge_set[k]),(igraph_integer_t)igraph_cattribute_EAN(g,"level",edge_set[k]));
			//printf("from-%d,%d\n",from,to);
			l=gcry_md_get_algo_dlen(GCRY_MD_SHA256);
			gcry_md_hd_t h;
	    		gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
		
			sprintf(eid,"%d",j);
			strcpy(str_store,"");
			strcpy(str_store,buffer[to]);
			strcat(str_store,eid);

			gcry_md_write(h, str_store, 32); /* hash some text */
			strcpy(y[to],str_store); /* get the result */
			//printf("node : %d,%d,%d\n", to,from,m);
			//for(i=0;i<l;i++)
			//	printf("%02x", y[to][i]);
         		gcry_md_close(h);      
                        l=32;
			gcry_md_hd_t hb;
	    		gcry_md_open(&hb, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
		 	strcpy(str_store,"\0");
                        len=0;
			*totalBytes+=strlen(y[to]);
			for(i=0;i<l && len<32;i++)
			{
			       	sprintf(string_pass,"%02x",y[to][i]);
		
                                str_store[len]=string_pass[0];
                                str_store[len+1]=string_pass[1];
			        len+=2;
                               //string_pass[i]=(char)y[to][i];
				//printf("\nprogress:%s,%s\n",str_store,string_pass);
			}
			str_store[len]='\0';
			gcry_md_write(h, str_store,32);
			commitment[to] = gcry_md_read(h, GCRY_MD_SHA256);  
			for(i=0;i<=res;i++)
			{
				if(commit[to][i].puzzle==commitment[to])
                                {
				//	printf("Found, success achieved\n");
					flag=1;
					break;
				}

			}                
			if(flag==0)
			{
				printf("wrong commitment, aborting..\n");
			//	exit(1);

			}
			flag=0;
/*			s=i;
			printf("\nto=%d\n",to);
			for(i=0;i<l;i++)
			        printf("%02x", commit[to][s].puzzle[i]);*/
			
			for(i=0;i<l;i++)
			   	buffer[from][i]=buffer[from][i]^y[to][i];
			
			gcry_md_close(hb);
		
	}

	gcry_md_hd_t vb;
	gcry_md_open(&vb, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
		
	gcry_md_write(vb, buffer[source], 32); /* hash some text */	
	commitment[source]=gcry_md_read(h, GCRY_MD_SHA256);
	for(i=0;i<=res;i++)
	{
			if(commit[source][i].puzzle==commitment[to])
                        {
				//printf("Found, source got success\n");
				flag=1;
				break;
			}

	}
	gcry_md_close(vb);
	if(flag==0)
	{
		printf("Incorrect commitemnt at source, aborting..\n");
		exit(1);

	}
	
}
