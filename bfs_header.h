typedef struct stud{
    int **array, *eid;
    int size_queue;
    int front; 
	int rear;
}queue;

void queue_init(queue *q, int size_q)
{
	int i, j;
	q->size_queue = size_q;
	q->array = (int**)malloc((2*q->size_queue)*sizeof(int*));
    q->rear=-1;
    q->front=-1;
	for(i = 0; i < 2*q->size_queue; i++)
	{
        q->array[i] = (int*)malloc(2*sizeof(int));
		
	}
    q->eid = (int*)malloc(q->size_queue*sizeof(int));
    for(i = 0; i < q->size_queue; i++)
    	q->eid[i] = 0;
	for(i = 0; i < 2*q->size_queue; i++)
	  	for(j = 0; j < 2; j++)
            q->array[i][j] = 0;             
}

void freeup(queue *q)
{
	int i;
/*         for(i=0;i<2*q->size_queue;i++)
		free(q->array[i]);
	 free(q->array);*/

	free(q->eid);
	free(q);
}


int empty(queue *q)
{

	if(q->front==q->rear)
        return 1;
    return 0;
}

void push(queue *q, int eid, int count)
{
    q->front++;
	q->array[q->front][0] = eid;
	q->array[q->front][1] = count;
}

int *pop(queue *q)
{
	if(!empty(q))
	{
		q->rear++;
	    return q->array[q->rear];
	}
	else
        return NULL;
}

