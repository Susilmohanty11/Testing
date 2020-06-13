#!/bin/sh

gcc create_graph.c -I/home/nslab/Downloads/igraph-0.8.2/include/ -L/usr/local/lib -ligraph -o create

./create 10 node_10/view1.graphml node_10/read_graph_edge_10.txt node_10/read_graph_weight_10.txt node_10/ripple-lcc.graph node_10/ripple-lcc.graph_CREDIT_LINKS node_10/degOrder-bi.txt
