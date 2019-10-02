# routing_table_basic
## C program to demonstrate  the basic working of network routing table.

Running command example (under gcc compiler):

$gcc routingTableBasic.c -o routingTableBasic-v1.exe
<br>
$./routingTableBasic-v1.exe

Sample output:

idx[0]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[1]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[2]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[3]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
FOR-IF2:  idrtsize:5  i:0  dest:65535
IF i  -> i:0  idrtsize:5  ROUTING_TABLE_SIZE:5
idx[0]    seq:0 dest:1 src:65535 next:1 hop:1
idx[1]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[2]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[3]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
FOR-IF2:  idrtsize:5  i:1  dest:65535
IF i  -> i:1  idrtsize:5  ROUTING_TABLE_SIZE:5
idx[0]    seq:0 dest:1 src:65535 next:1 hop:1
idx[1]    seq:0 dest:4 src:65535 next:1 hop:1
idx[2]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[3]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
FOR-IF2:  idrtsize:5  i:2  dest:65535
IF i  -> i:2  idrtsize:5  ROUTING_TABLE_SIZE:5
idx[0]    seq:0 dest:1 src:65535 next:1 hop:1
idx[1]    seq:0 dest:4 src:65535 next:1 hop:1
idx[2]    seq:0 dest:3 src:65535 next:1 hop:1
idx[3]    seq:0 dest:65535 src:65535 next:0 hop:0
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
FOR-IF2:  idrtsize:5  i:3  dest:65535
IF i  -> i:3  idrtsize:5  ROUTING_TABLE_SIZE:5
idx[0]    seq:0 dest:1 src:65535 next:1 hop:1
idx[1]    seq:0 dest:4 src:65535 next:1 hop:1
idx[2]    seq:0 dest:3 src:65535 next:1 hop:1
idx[3]    seq:0 dest:2 src:65535 next:1 hop:1
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
got dest index!  idx:3  dest:2
the acquired entry deleted (idx:3 dest:2)
idx[0]    seq:0 dest:1 src:65535 next:1 hop:1
idx[1]    seq:0 dest:4 src:65535 next:1 hop:1
idx[2]    seq:0 dest:3 src:65535 next:1 hop:1
idx[3]    seq:0 dest:65535 src:65535 next:65535 hop:0
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
got dest index!  idx:2  dest:3
the acquired entry deleted (idx:2 dest:3)
idx[0]    seq:0 dest:1 src:65535 next:1 hop:1
idx[1]    seq:0 dest:4 src:65535 next:1 hop:1
idx[2]    seq:0 dest:65535 src:65535 next:65535 hop:0
idx[3]    seq:0 dest:65535 src:65535 next:65535 hop:0
idx[4]    seq:0 dest:65535 src:65535 next:0 hop:0
dest (node 4) found! dest's next hop:1
dest (node 3) could not be found!
