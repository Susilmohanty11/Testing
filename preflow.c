#include "header.h"
void preflow(igraph_t *g,int *height,int source)
{
	int excess_val = igraph_cattribute_VAN(g,"excess",source);
	igraph_integer_t from, to, eid, cap, amout_subtract, eid1, amount_subtract;
	igraph_vs_t vs;
    igraph_vit_t vit;
    igraph_vs_adj(&vs, source, IGRAPH_OUT);
	igraph_vit_create(g, vs, &vit);
	from = source;	
	
	while(!IGRAPH_VIT_END(vit))
	{
				
		to = IGRAPH_VIT_GET(vit);
		// printf("from = %d, to = %d\n", from, to);
        excess_val = igraph_cattribute_VAN(g, "excess", source);
		igraph_get_eid(g, &eid, from, to, IGRAPH_DIRECTED, 1);
		cap = (igraph_integer_t)igraph_cattribute_EAN(g, "weight", eid) - (igraph_integer_t)igraph_cattribute_EAN(g, "flow", eid);
		amount_subtract = min(excess_val, cap);
		// printf("excess_val: %d, cap: %d\n", excess_val, cap);
		// printf("as = %d, %d, %d\n", amount_subtract, excess_val, source);
		if(amount_subtract > 0)
		{
			igraph_cattribute_VAN_set(g, "excess", from, excess_val-amount_subtract);
			igraph_cattribute_EAN_set(g, "flow", eid, amount_subtract);
            igraph_cattribute_EAN_set(g, "flow_true", eid, 1);            
			igraph_get_eid(g, &eid1, to, from, IGRAPH_DIRECTED,1);
			igraph_cattribute_EAN_set(g, "flow", eid1, cap-amount_subtract);
			igraph_cattribute_VAN_set(g, "excess", to, amount_subtract);	
            if(strcmp("sink", igraph_cattribute_VAS(g, "type", to)) != 0)
		   		lift(g, height, to);
		}
		IGRAPH_VIT_NEXT(vit); // Adjacent verices
	}	

}

