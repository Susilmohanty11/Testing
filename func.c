#include "header.h"


void main_func(igraph_t *g,int *height,int source,int sink)
{
	igraph_integer_t vid, excess, vid_neighbour, eid1, res_cap, flow, amount_subtract, flag=0, eid2;
	preflow(g, height, source);
	while(1)
	{	
        flag = 0;
		for(vid = 0; vid < igraph_vcount(g); vid++)
		{
	    	if(strcmp("source",igraph_cattribute_VAS(g,"type",vid))!=0 && strcmp("sink",igraph_cattribute_VAS(g,"type",vid))!=0)
	      	{	
				excess = (igraph_integer_t)igraph_cattribute_VAN(g,"excess",vid);	
            	// printf("excess = %d, %d\n", excess, vid);
				//	 while(excess>0)
				if(excess > 0)
				{
					//printf("excess:%d\n",excess);
			        flag = 1;
					igraph_vs_t vs;
			        igraph_vit_t vit;
        			igraph_vs_adj(&vs, vid, IGRAPH_OUT);
					igraph_vit_create(g, vs, &vit);
			
					while(!IGRAPH_VIT_END(vit))
					{					
						vid_neighbour = IGRAPH_VIT_GET(vit);
						// printf("Vid: %d, Vit: %d", vid, vit);
						excess=(igraph_integer_t)igraph_cattribute_VAN(g, "excess", vid);	
                        // printf("%d neigh: %d, Height-vid: %d, Height-vid-neigh: %d\n",vid, vid_neighbour, height[vid], height[vid_neighbour]);   
						igraph_get_eid(g, &eid1, vid, vid_neighbour, IGRAPH_DIRECTED, 1);
						flow = (igraph_integer_t)igraph_cattribute_EAN(g, "flow", eid1);
						res_cap=(igraph_integer_t)igraph_cattribute_EAN(g, "weight", eid1) - flow;
						// printf("eid1 = %d, flow = %d, weight = %d\n", eid1, (igraph_integer_t)igraph_cattribute_EAN(g,"flow",eid1),(igraph_integer_t)igraph_cattribute_EAN(g,"weight",eid1));
						if(height[vid_neighbour] < height[vid] && (igraph_integer_t)igraph_cattribute_EAN(g, "flow", eid1) < (igraph_integer_t)igraph_cattribute_EAN(g, "weight", eid1))
						{                                                      
							amount_subtract = min(excess, res_cap);
							//printf("set flow neigh: %d, %d, %d\n", vid, vid_neighbour, flow + amount_subtract); 
               		        igraph_cattribute_VAN_set(g, "excess", vid, excess - amount_subtract);
							igraph_cattribute_EAN_set(g, "flow", eid1, flow + amount_subtract);
                            //igraph_cattribute_EAN_set(g,"flow_true",eid1,1);            

							igraph_get_eid(g, &eid2, vid_neighbour, vid, IGRAPH_DIRECTED, 1);						
							igraph_cattribute_EAN_set(g, "flow", eid2, (igraph_integer_t)igraph_cattribute_EAN(g, "weight", eid1) - flow - amount_subtract);
							if((igraph_integer_t)igraph_cattribute_EAN(g, "flow_true", eid2) == 0 && (igraph_integer_t)igraph_cattribute_EAN(g, "flow", eid1) != 0)
                                igraph_cattribute_EAN_set(g, "flow_true", eid1, 1);	
							approve_push(g, vid_neighbour, amount_subtract, height);
						}
						else
					        lift(g,height,vid);
						if(excess == 0)
					  		break;
						IGRAPH_VIT_NEXT(vit);
					}			
					igraph_vit_destroy(&vit);
					igraph_vs_destroy(&vs);       
				}	
			}
        }	
		if(flag == 0)
	  		break;
	}
       
 		//if(flag==0)      
}
