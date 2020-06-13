#include "header.h"
#include "bfs_header.h"


void bfs_mark(igraph_t *g, int *bfs_edge_marker, int *height, igraph_integer_t source, igraph_integer_t sink, unsigned char **buffer, unsigned long int *totalBytes)
{
	int count = 1, i, track = 0, num = 0, flag = 1, excess_val, flow;
	int start = source, *vid, vid_neighbour, eid1, eid2, from, to;
	int *edge_set = (int*)malloc(igraph_ecount(g)*sizeof(int));
	int *edge_visit = (int*)malloc(igraph_ecount(g)*sizeof(int));
    queue *q = (queue*)malloc(1*sizeof(queue));
	queue_init(q, igraph_ecount(g));
	int min_amt = 1000, tot_flow = 0;
    // printf("%d, %d",q->front,q->rear);
    vid = (int*)malloc(2*sizeof(int));
    /* for(i=0;i<igraph_vcount(g);i++)
	{
		printf("vid-height=%d\n",height[i]);

	}*/
    excess_val = igraph_cattribute_VAN(g, "excess", sink);
	while(excess_val > 0)
	{
        q->rear = -1;
        q->front = -1;
		for(i = 0; i < igraph_ecount(g); i++)
		{
			//igraph_edge(g, i, &from, &to);
			edge_visit[i] = 0;
      	    // printf("\nflow: %d, eid: %d, vid1: %d, vid2: %d, true: %d\n",(igraph_integer_t)igraph_cattribute_EAN(g,"flow",i), i, from, to, (igraph_integer_t)igraph_cattribute_EAN(g, "flow_true", i));
			// printf("\nflow: %d, eid: %d, vid1: %d, vid2: %d, true: %d\n",(igraph_integer_t)igraph_cattribute_EAN(g,"flow",i), i, from, to, (igraph_integer_t)igraph_cattribute_EAN(g, "flow_true", i));
		
		}
		push(q, source, count);
		track = 0;
      	while(!empty(q) && flag == 1)
		{		
			//printf("entering");	
			vid = pop(q);
			flag = 0;
			if(vid[0] == sink)
			{
		    	flag = 1;
		    	break;
			}		
        	count = vid[1];
 			igraph_vs_t vs;
			igraph_vit_t vit;
 	    	igraph_vs_adj(&vs, vid[0], IGRAPH_OUT);
			igraph_vit_create(g, vs, &vit);
        	//printf("vid=%d\n",vid[0]);              
			while(!IGRAPH_VIT_END(vit))
			{
				vid_neighbour = IGRAPH_VIT_GET(vit);
				// printf("neighbour: %d\n", vid_neighbour);            	
				igraph_get_eid(g, &eid1, vid[0], vid_neighbour, IGRAPH_DIRECTED, 1);
				igraph_get_eid(g, &eid2, vid_neighbour, vid[0], IGRAPH_DIRECTED, 1);
				// printf("array eid: %d, array eid: %d, %d\n", eid1, eid2, (igraph_integer_t)igraph_cattribute_EAN(g,"flow_true", eid1));
				if((igraph_integer_t)igraph_cattribute_EAN(g,"flow_true",eid1)>0 && (igraph_integer_t)igraph_cattribute_EAN(g,"flow",eid1)>0 && edge_visit[eid1]==0)
				{
					edge_visit[eid1]=1;
					q->eid[eid1]=count;
					// printf("count: %d, (%d, %d)\n", (igraph_integer_t)igraph_cattribute_EAN(g, "flow", eid1), vid, vid_neighbour);
					//for(int i = 0; i < igraph_ecount(g); i++)
					//  printf("%d\n", q->eid[i]);
					if(vid_neighbour!=sink)
						push(q, vid_neighbour, count+1);
					edge_set[track] = eid1;
					track++;
					igraph_cattribute_EAN_set(g, "level", eid1, count);
					if(min_amt>((igraph_integer_t)igraph_cattribute_EAN(g,"flow",eid1)))
						min_amt=(igraph_integer_t)igraph_cattribute_EAN(g,"flow",eid1);
					//printf("eid-(%d,%d,count : %d,%d)\n",vid[0],vid_neighbour,(igraph_integer_t)igraph_cattribute_EAN(g,"flow",eid1),min_amt);
					flag=1;
						break;
				}			
				IGRAPH_VIT_NEXT(vit);         
        	}               
			//printf("count=%d\n",count);
			igraph_vit_destroy(&vit);
			igraph_vs_destroy(&vs);
		}
		// freeup(q);
		//copy(buffer,buffer1);
		if(flag==1)
		{
			tot_flow+=min_amt;
			excess_val-=min_amt;
			//printf("\n num=%d\n",tot_flow);	
		
			for(i=0;i<track;i++)	
			{
				flow=(igraph_integer_t)igraph_cattribute_EAN(g, "flow", edge_set[i]);
				igraph_cattribute_EAN_set(g, "flow", edge_set[i], flow - min_amt);		  	     
			}
			create_puzzle(g, buffer, edge_set, track, source, sink, totalBytes);	  
		}
		else
		{
			printf("exiting..\n");
			exit(1);
		}
		min_amt = 1000;
    }      
}
