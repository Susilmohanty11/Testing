#include "header.h"
#include "MPC_SHA256.c"
void copy(igraph_t *g, unsigned char **buffer_target, unsigned char **buffer_source)
{
    int size_text=40,vid;	
    for(vid = 0; vid < igraph_vcount(g); vid++)
	{
    	// buffer_target[vid]=(char*)malloc(size_text*sizeof(char));
	    strcpy(buffer_target[vid], buffer_source[vid]);
	}	
}


void create_puzzle(igraph_t *g,unsigned char **buffer,int *edge_set,int track,int source,int sink,unsigned long int *totalBytes)
{
 	int j = track-1, from, to, i, level = 0, prev_level = -1, k, m, level_test, s, len;
    char eid[20];
	char string_pass[65], string_passcat[65];
	unsigned char string_system[1000];
	unsigned char **y=(unsigned char**)malloc(igraph_ecount(g)*sizeof(unsigned char*));
	y_val **commit=(y_val**)malloc(igraph_vcount(g)*sizeof(y_val*));
    unsigned char **commitment=(unsigned char**)malloc(igraph_ecount(g)*sizeof(unsigned char*));
    unsigned int l;  
	unsigned char **buffer1=(unsigned char**)malloc(igraph_vcount(g)*sizeof(unsigned char*));
	unsigned char str_store[80];
	igraph_integer_t res;
    igraph_maxdegree(g, &res, igraph_vss_all(),IGRAPH_IN,IGRAPH_NO_LOOPS);
    for(i = 0; i < igraph_vcount(g); i++)
	    buffer1[i] = (char*)malloc(40*sizeof(char));
	copy(g, buffer1, buffer);
        
	for(i = 0; i < igraph_vcount(g); i++)	
		y[i] = (unsigned char*)malloc(32*sizeof(unsigned char));
	for(i = 0; i < igraph_vcount(g); i++)
	{
		commit[i]=(y_val *)malloc((res + 1)*sizeof(y_val));
		for(k=0;k<=res;k++)
		{
			commit[i][k].puzzle="";
		}  	
	}
    l = gcry_md_get_algo_dlen(GCRY_MD_SHA256);
	gcry_md_hd_t h;
	gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
    strcpy(str_store,"\0");
	strcpy(str_store,buffer[sink]);
        
	gcry_md_write(h, str_store, 32); /* hash some text */
	commit[sink][0].puzzle=gcry_md_read(h, GCRY_MD_SHA256);
	*totalBytes+=strlen(commit[sink][0].puzzle);
    gcry_md_close(h);
	//    exit(1);    
	j = track-1;

	for(; j >= 0; j--)
	{
		igraph_edge(g,edge_set[j], &from, &to);
        l = gcry_md_get_algo_dlen(GCRY_MD_SHA256);
        //printf("before buffering%d\n",l);
		gcry_md_hd_t h;
	    gcry_md_open(&h, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
		sprintf(eid,"%d",j);
		strcpy(str_store,"\0");
		strcpy(str_store,buffer[to]);
		strcat(str_store,eid);
		gcry_md_write(h,str_store,32); /* hash some text */
		strcpy(y[to],str_store);
		//y[to] = gcry_md_read(h, GCRY_MD_SHA256); /* get the result */
		//printf("node : %d,%d,%d\n", to,from,m);
		//for(i=0;i<l;i++)
		//	printf("%02x\n", y[to][i]);
        //gcry_md_reset(h);       
		gcry_md_close(h);
		l=gcry_md_get_algo_dlen(GCRY_MD_SHA256);
		gcry_md_hd_t vb;
	    gcry_md_open(&vb, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE);
		//gcry_md_hash_buffer(GCRY_MD_SHA256,commitment[to],y[to],strlen(commitment[to]));
		strcpy(str_store,"\0");
        len=0;
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
		//strcpy(str_store,y[to]);
        gcry_md_write(vb, str_store,32); /* hash some text */
        // int proof=main_proof_generate("p",y[to],"data/file.txt");
		//printf("p=%d\n",proof);
		//printf("\n\n");
		commitment[to] = gcry_md_read(h, GCRY_MD_SHA256);  
        /*printf("\n\nproof\n");
		for(i = 0; i < l; i++)
			printf("%c", str_store[i]);*/

		for(i=0;i<=res;i++)
		{
			if(commit[to][i].puzzle==(unsigned char*)"")
            {
				commit[to][i].puzzle=commitment[to];
				*totalBytes+=strlen(commit[to][i].puzzle);
				break;
			}
		}
		//sprintf(string_pass,"./mp p '%s' %s",y[to],"data/output.txt"); 
			
		//system(string_pass);                
		s = i;
		//printf("\nto=%d,%d\n",to,l);
		strcpy(string_pass,"");
        //  l=gcry_md_get_algo_dlen(GCRY_MD_SHA256);
		/*strcpy(string_system,"");
        //printf("\n%s\n",string_passcat);*/
		//printf("\n");
		//printf("\n%s---%s\n",string_passcat,string_system);
        //printf("\nafter %s---,%d\n",string_system,strlen(str_store));
		/*printf("\n\n");
		for(i=0;i<l;i++)
			printf("%02x", commitment[to][i]);*/
		//printf("\n\n");
		main_proof("p", str_store, "data/output.txt");
		for(i=0;i<l;i++)
		   	buffer[from][i]=buffer[from][i]^str_store[i];
		//printf("checking the proof given in %s for the commitment ","data/output.txt"); 
		len=0;
		strcpy(string_pass,"");
		for(i=0;i<32;i++)
		{
		   	sprintf(string_pass,"%02x",commitment[to][i]);
            str_store[len]=string_pass[0];
            str_store[len+1]=string_pass[1];
		    len+=2;
            //string_pass[i]=(char)y[to][i];
		}
		str_store[len]='\0';
		//printf("\nprogress:%s,%s\n",str_store,string_pass);
		main_proof("v", str_store, "data/output.txt");
		FILE *fp=fopen("data/output.txt", "rb");
		fseek(fp,0,SEEK_END);
		*totalBytes+=ftell(fp);
		fclose(fp);
		//printf("\nforming HLTC - between vertex %d and vertex %d, locking amount %d..%s\n",from,to,(igraph_integer_t)igraph_cattribute_EAN(g,"flow",edge_set[k]),str_store);
		gcry_md_close(vb);	
	}
        
 	gcry_md_hd_t hb;
	    		
	gcry_md_open(&hb, GCRY_MD_SHA256, GCRY_MD_FLAG_SECURE); /* initialise the hash context */
	strcpy(str_store,"");
	strcpy(str_store,buffer[source]);
	gcry_md_write(h, str_store, 32); /* hash some text */
	for(i=0;i<=res;i++)
	{
		if(commit[source][i].puzzle==(unsigned char*)"")
        {
			commit[source][i].puzzle=gcry_md_read(h, GCRY_MD_SHA256);
			*totalBytes+=strlen(commit[source][i].puzzle);
			break;
		}
	}
	
    gcry_md_close(hb);           
	solve_puzzle(g, edge_set, track, commit, buffer1, source, sink, res, totalBytes);
}
