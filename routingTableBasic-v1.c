/*
 * Copyright (c) 2019 Universiti Teknologi Malaysia (UTM)
 * Author: Yusnaidi Md Yusof <yusnaidi.kl@utm.my> <https://people.utm.my/yusnaidi>
 * Date: 2019/09/30
 * Version: 0.0.1
 * Published under the terms of the MIT License.
 *
 * All rights reserved.
 *
 * PERMISSION IS HEREBY GRANTED, FREE OF CHARGE, TO ANY PERSON OBTAINING A COPY
 * OF THIS SOFTWARE AND ASSOCIATED DOCUMENTATION FILES (THE "SOFTWARE"), TO DEAL
 * IN THE SOFTWARE WITHOUT RESTRICTION, INCLUDING WITHOUT LIMITATION THE RIGHTS
 * TO USE, COPY, MODIFY, MERGE, PUBLISH, DISTRIBUTE, SUBLICENSE, AND/OR SELL
 * COPIES OF THE SOFTWARE, AND TO PERMIT PERSONS TO WHOM THE SOFTWARE IS FURNISHED
 * TO DO SO, SUBJECT TO THE FOLLOWING CONDITIONS:
 * 
 * THE ABOVE COPYRIGHT NOTICE AND THIS PERMISSION NOTICE SHALL BE INCLUDED IN ALL
 * COPIES OR SUBSTANTIAL PORTIONS OF THE SOFTWARE.
 *
 * IN NO EVENT SHALL THE UNIVERSITI TEKNOLOGI MALAYSIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITI 
 * TEKNOLOGI MALAYSIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE UNIVERSITI TEKNOLOGI MALAYSIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE IS PROVIDED "AS IS", 
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE UNIVERSITI TEKNOLOGI MALAYSIA BE 
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
 * THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 
 * This program exercise the working component of a network routing structure.
 * The program consists of routing table construction and tasks relating 
 * routing table maintenance such as adding new entry, updating existing entry,
 * finding entry, and deleting entry. Part of the algorithms are cited from the
 * AODV routing protocol for TinyOS developed by Junseok Kim <jskim@usn.konkuk.ac.kr> 
 * and Jaime Munoz Martinez <http://www.jaimemunozmartinez.com> under the 
 * GNU General Public License (GPLv2).
 * 
 * The program has been tested and shall be running correctly under the compilation
 * of a standard gcc GNU compiler.
 * 
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
*/

#define ROUTING_TABLE_SIZE 5
#define INVALID_NODE_ID 0xFFFF
#define INVALID_INDEX 0xFF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int seq;
    int dest;
    int src;
    int nexthop;
    int hop;
}routing_table;

void initialize_routing_table();
void print_routing_table();

bool add_route_table(int seq, int dest, int src, int nexthop, int hop);
int get_route_table_index(int dest);
void del_route_table(int dest);
int get_next_hop(int dest);

routing_table rt[ROUTING_TABLE_SIZE];

int main(){

   initialize_routing_table(); 
   print_routing_table();
   add_route_table(0, 1, 1, 1, 1);
   add_route_table(0, 4, 1, 1, 1);
   add_route_table(0, 3, 1, 1, 1);
   add_route_table(0, 2, 1, 1, 1);
   del_route_table(2);
   del_route_table(3);
   get_next_hop(4);
   get_next_hop(3);
   return 0;
}

void initialize_routing_table(){
    
    for (int i = 0; i < ROUTING_TABLE_SIZE; i++){  
       rt[i].seq = 0;
       rt[i].dest = INVALID_NODE_ID;
       rt[i].src = INVALID_NODE_ID;
       rt[i].nexthop = 0;
       rt[i].hop = 0;
    }
}

void print_routing_table(){

   for (int i=0; i < ROUTING_TABLE_SIZE; i++){
      printf("idx[%d]    seq:%d dest:%lu src:%lu next:%d hop:%d\n", i, rt[i].seq, rt[i].dest, rt[i].src, rt[i].nexthop, rt[i].hop);   
   }
   printf("\r");
   printf("\r");
}

bool add_route_table(int seq, int dest, int src, int nexthop, int hop){
   
   int i;
   int idrtsize = ROUTING_TABLE_SIZE;             //[5 = 5]

   for (i=0; i < ROUTING_TABLE_SIZE - 1; i++){    //                                    [0,1,2,3; 4; 1,2,3]
      //FOR-IF1
      if (rt[i].dest == dest){                    //dest found!, goto IF-idrtsize       <- say, at idx1(i=1) we found valid dest node, (rt[1].dest == dest) [2 == 2] 
         idrtsize = i;                            //                                    [(idrtsize) 1 = 1 (i)], before assignment, value idrtsize is 5
         printf("FOR-IF1:  idrtsize:%d  i:%d  dest:%d\n", idrtsize, i, rt[i].dest);
         break;
      }
      //FOR-IF2
      if (rt[i].dest == INVALID_NODE_ID){         //dest still not been added and had reach the end of the table, goto IF-i
         printf("FOR-IF2:  idrtsize:%d  i:%d  dest:%d\n", idrtsize, i, rt[i].dest);
         break;
      }
   }

   //IF-idrtsize
   if (idrtsize != ROUTING_TABLE_SIZE){  //update existing seq and hop
      if (rt[idrtsize].nexthop == nexthop){
         if(rt[idrtsize].seq < seq || rt[idrtsize].hop > hop){  //ensure avoiding routing-loop and ensure keep using shortest path
            rt[idrtsize].seq = seq;
            rt[idrtsize].hop = hop;
            printf("IF idrtsize  -> i:%d  idrtsize:%d  ROUTING_TABLE_SIZE:%d\n", i, idrtsize, ROUTING_TABLE_SIZE);
            print_routing_table();
            return true;
         }
      }
   //IF-i   
   } else if (i != ROUTING_TABLE_SIZE){  //add new route information into routing table
      rt[i].seq  = seq;
      rt[i].dest = dest;
      rt[i].nexthop = nexthop;
      rt[i].hop  = hop;
      printf("IF i  -> i:%d  idrtsize:%d  ROUTING_TABLE_SIZE:%d\n", i, idrtsize, ROUTING_TABLE_SIZE);
      print_routing_table();
      return true;
   }
   printf("routing table NOT updated\n");
   return false;
}

int get_route_table_index(int dest){

   for(int i=0; i < ROUTING_TABLE_SIZE; i++){
      if(rt[i].dest == dest){
         printf("got dest index!  idx:%d  dest:%d\n", i, rt[i].dest);  //got the index
         return i;
      }
   }
   printf("Index of dest not found!\n");
   return INVALID_INDEX;
}

void del_route_table(int dest){
   int i;
   int idx = get_route_table_index(dest);

   if(idx != INVALID_INDEX){
      for(i = idx; i < ROUTING_TABLE_SIZE - 1; i++){  //found the entry to delete, but before delete first have to do some checking
         if(rt[i+1].dest == INVALID_NODE_ID){ //if invalid node found in the routing table (starts with the following idx and onwards throughout the rt)
            break;
         }
         //delete the invalid node
         printf("the invalid node (idx:%d dest:%d) deleted and rt updated\n", i, rt[i].dest);
         rt[i] = rt[i+1];
      }
      //delete the found entry
      printf("the acquired entry deleted (idx:%d dest:%d)\n", i, rt[i].dest);
      rt[i].dest    = INVALID_NODE_ID;
      rt[i].nexthop = INVALID_NODE_ID;
      rt[i].hop     = 0;
      rt[i].seq     = 0;
      print_routing_table();
   } else{
      //default: fail to delete from routing table
      printf("FAIL to delete entry %d from routing table\n", dest);
   }
}

int get_next_hop(int dest){
   int i;
   for(i=0; i < ROUTING_TABLE_SIZE; i++){
      if(rt[i].dest == dest){   //for this node (dest)
         printf("dest (node %d) found! dest's next hop:%d\n", rt[i].dest, rt[i].nexthop);
         return rt[i].nexthop;  //this is its next-hop
      }
   }
   //default: dest could not be found
   printf("dest (node %d) could not be found!\n", dest);
   return INVALID_NODE_ID;
}