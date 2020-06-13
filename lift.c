#include "header.h"

void lift(igraph_t *g, int *height, igraph_integer_t vid)
{
	igraph_integer_t neighbor, height_min = igraph_vcount(g)+100, eid1;
	int flag = 0;
	if(strcmp("source", igraph_cattribute_VAS(g,"type",vid)) != 0)
	{
		igraph_vs_t vs;
	    igraph_vit_t vit;
        igraph_vs_adj(&vs, vid, IGRAPH_OUT);
		igraph_vit_create(g, vs, &vit);
		flag = 0;	
        while(!IGRAPH_VIT_END(vit))
		{		
			neighbor = IGRAPH_VIT_GET(vit);
			igraph_get_eid(g, &eid1, vid, neighbor, IGRAPH_DIRECTED, 1);
			//printf("%d,%d\n",height_min,height[neighbor]);
            if((igraph_integer_t)igraph_cattribute_EAN(g, "flow", eid1) < (igraph_integer_t)igraph_cattribute_EAN(g, "weight", eid1))
			{
				flag = 1;
				height_min = min(height_min, height[neighbor]);
			}
			IGRAPH_VIT_NEXT(vit);
		}
        if(flag == 1 && height[vid] <= height_min)
		    height[vid]=height_min + 1;
            //printf("inc=%d,%d\n",vid,height[vid]);
	}
}


