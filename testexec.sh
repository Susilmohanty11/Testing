#gcc -I/home/abriti/workbench/openssl/src  -fopenmp -o mp MPC_SHA256.c -lcrypto
#gcc -fopenmp -o mp MPC_SHA256.c -lcrypto

#gcc push_test.c func.c lift.c min.c preflow.c approve_push.c bfs.c payment.c create_puzzle.c solve.c -I/home/abriti/Desktop/Payment_Channels/igraph-0.7.1/include -I/home/abriti/Desktop/gocode/Code_Push_relabel/libgcrypt-1.8.4/src -I/home/abriti/workbench/openssl/src -L/usr/local/lib -fopenmp -ligraph -lgcrypt -lcrypt -o push_relabel 
gcc push_test.c func.c lift.c min.c preflow.c approve_push.c bfs.c payment.c create_puzzle.c solve.c -I/usr/local/include/igraph -I/home/nslab/Downloads/libgcrypt-1.8.5/src -L/usr/local/lib -fopenmp -ligraph -lgcrypt -lcrypto -lcrypt -o push_relabel 

#./push_relabel test_input_.txt test_weight.txt output_file.txt 0 4 node_10/sampleTr-0-pr.txt 
./push_relabel node_10/read_graph_edge_10.txt node_10/read_graph_weight_10.txt output_new.txt 0 6 node_10/sampleTr-0.txt
 echo $val.00 0 6 >> output_file.txt
 echo "\n" >> output_new.txt
#gcc push_test.c func.c lift.c min.c preflow.c approve_push.c bfs.c payment.c create_puzzle.c solve.c -I/home/cssc/Desktop/igraph-0.7.1/include -I/home/cssc/Desktop/openssl-1.0.2o/ -I/home/cssc/Desktop/libgcrypt-1.8.4/src -I/home/abriti/workbench/openssl/src -L/usr/local/lib -fopenmp -ligraph -lgcrypt -lcrypto -o push_relabel 
