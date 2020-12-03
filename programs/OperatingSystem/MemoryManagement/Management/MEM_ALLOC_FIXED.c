#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define STRMAX 80
#define MEMSIZE 64

typedef struct node{
    int segment_id;    /* セグメント番号 (空きには-1を割り当てる) */
    int begin_address; /* セグメントの開始位置 */
    int size;          /* セグメントサイズ */
    struct node *next_node; 
    struct node *prev_node;
} node;

node *head;   /* 連結リストの先頭ノードを指すポインタ */
int seg_id_counter;  /* 新規ノード作成時に割り当てるセグメント番号のカウンタ変数 */

int num_allocation;   /* allocate()を実行した回数 */
int num_deallocation; /* deallocate()を実行した回数 */
int num_compaction;   /* compaction()を実行した回数 */

int num_taverse;         /* allocate() でリンクをたどった回数の積算 */
int num_notExist_segID;  /* deallocate(id)で、id指定されたセグメントが存在しなかった回数 */
int num_oversize_reqest; /* 空セグメントのサイズ合計以上の要求を行ってしまった回数*/

int total_alloc_size;    /* allocate()で割当てたメモリサイズの積算 */
int total_reqested_size; /* allocate()で要求されたメモリサイズの積算 */
int total_space_size = MEMSIZE; /* 空セグメントのサイズの合計 */

int do_bestfit; /* フラグ変数:TRUEの状態でallocate()を実行するとbest_fitを実行*/
int do_debug;   /* フラグ変数:TRUEにすると、allocate()実行ごとに統計表示 */

void init(int, char**);
void allocate(int);
void deallocate(int);
void merge(node *);
void compact();
node *bestfit(int);
node *firstfit(int);
void print_segment_list();
void print_statistics();

int main(int argc, char **argv)
{
    char line[80];
    char cmd[80];
    int arg;
    init(argc,argv);
    while (fgets(line, STRMAX, stdin) != NULL){
        if (sscanf(line, "%s %d", cmd, &arg) > 0){

            switch (cmd[0]){
            case 'a': //Allocation    
            { 
                int request_size = arg;

                if (request_size <= 0){
                    printf("Can't allocate. Request size is too small.\n");
                    break;
                }
                if(request_size > total_space_size){
                    printf("Can't allocate. Request size is too big.\n");
                    break;
                }

                if (do_bestfit){
                    printf("allocate %dKB (best fit)\n", request_size);
                }else{
                    do_bestfit = FALSE;
                    printf("allocate %dKB (first fit)\n", request_size);
                }

                allocate(request_size);
                break;
            }

            case 'd': //Deallocation
            {
                int target_segment_id = arg;
                printf("deallocate: ID.%d\n", target_segment_id);

                if (target_segment_id < 0 || target_segment_id > seg_id_counter - 1){
                    printf("%d does not exist and cannot be deallocated.\n", target_segment_id);
                }else{
                    deallocate(target_segment_id);
                }      
                break;
            }

            case 'p': //Print
                if (!do_debug){
                    print_segment_list();
                }
                break;

            case 'c': //Compaction
                compact();
                break;

            default:
                printf("Error : this is not a valid command.\n");
                break;
            }
        }

        if (do_debug){
            printf("\n");
            print_statistics();
        }

        printf("\ncommand:");
    }
    printf("\n");
    print_statistics();
    exit(EXIT_SUCCESS);
}

void init(int argc, char ** argv)
{
    if ((argc > 1) && (strcmp(argv[1], "-d") == 0)){
        do_debug = TRUE;
    }
    if ((argc > 1) && (strcmp(argv[1], "-b") == 0)){
        do_bestfit = TRUE;
    }

    head = (node *)malloc(sizeof(node));
    head->segment_id    = -1;
    head->begin_address = 0;
    head->size          = MEMSIZE;
    head->next_node     = NULL;
    head->prev_node     = NULL;    
}

void allocate(int requested_mem_size)
{
    num_allocation++;
    total_reqested_size += requested_mem_size;

    struct node *found_segment;
    struct node *new_segment = (node *)malloc(sizeof(node));

    if (do_bestfit){
        found_segment = bestfit(requested_mem_size);
    }else{
        found_segment = firstfit(requested_mem_size);
    }

    if (found_segment == NULL){
        return;
    }

    //要求サイズと空きセグメントのサイズが同じであれば、空きセグメントのIDを書き換えるだけでよい
    if (found_segment->size == requested_mem_size){
        free(new_segment);
        found_segment -> segment_id = seg_id_counter++;   
    }

    //要求サイズが空きセグメントのサイズより小さければ空きセグメントを分割し、片方を割り当てて、もう片方は空きメモリとして再び管理する
    else
    {
        if (found_segment -> next_node != NULL){
            found_segment -> next_node -> prev_node = new_segment;
        }
        
        //分割後、空き領域となるセグメント
        new_segment -> segment_id    = -1;
        new_segment -> begin_address = found_segment -> begin_address + requested_mem_size;
        new_segment -> size          = found_segment -> size - requested_mem_size;
        new_segment -> prev_node     = found_segment;
        new_segment -> next_node     = found_segment -> next_node;

        // 分割後、プロセスとなるセグメント
        found_segment -> segment_id = seg_id_counter++;
        found_segment -> size       = requested_mem_size;
        found_segment -> next_node  = new_segment;
    }

    total_space_size -= found_segment -> size;
    total_alloc_size += found_segment -> size;
    print_segment_list();
    printf("total %d \n",total_space_size);

}


void deallocate(int target_id)
{
    int found_node = FALSE;
    struct node *index_node = head;
   
    num_deallocation++;

    while (index_node != NULL)
    {
        if (index_node -> segment_id == target_id)
        {   
            index_node -> segment_id =  -1;
            total_space_size += index_node -> size;
            found_node = TRUE;
            break;
        }
        index_node = index_node -> next_node;
    }

    if (found_node == FALSE){
        printf("Segment:%d is not found \n", target_id);
        num_notExist_segID++;
    }

    merge(index_node);
    print_segment_list();
}

void merge(node *target)
{
    struct node *deleted_node = head;

    while (deleted_node != target){
        deleted_node = deleted_node -> next_node;
    }

    if (deleted_node == head)
    {
        //先頭の連続する2つのセグメントが[1.空き][2.空き]となった場合、1に2をマージする
        if (deleted_node -> next_node -> segment_id == -1){
            head -> size      += head -> next_node -> size;
            head -> next_node  = head -> next_node -> next_node;
        }
    }
    else if (deleted_node->next_node == NULL)
    {    
        //末尾の連続する2つのセグメントが[1.空き][2.空き]となった場合、1に2をマージする
        if (deleted_node->prev_node->segment_id == -1)   {
            deleted_node -> prev_node -> size     += deleted_node -> size;
            deleted_node -> prev_node -> next_node = deleted_node -> next_node;
        }
    }
    else
    {
        // [1.空き][2.プロセス][3.空き]となっていて、[プロセス]を削除するケース。 1に残りをマージする。
        if (deleted_node -> prev_node -> segment_id == -1 && deleted_node -> next_node -> segment_id == -1)
        {
            deleted_node -> prev_node-> size += deleted_node -> size;
            deleted_node -> prev_node-> size += deleted_node -> next_node -> size;

            if (deleted_node -> next_node -> next_node != NULL){
                deleted_node -> prev_node -> next_node              = deleted_node->next_node->next_node;
                deleted_node -> next_node -> next_node -> prev_node = deleted_node->prev_node;
            }else{
                deleted_node->prev_node->next_node = NULL;
            }
        }

        // [1.プロセス][2.空き]となっていて、[プロセス]を削除するケース。1に2をマージする。
        else if (deleted_node -> next_node -> segment_id == -1)
        {
            deleted_node -> size += deleted_node -> next_node -> size;
            
            if (deleted_node -> next_node -> next_node != NULL){
                deleted_node -> next_node              = deleted_node -> next_node -> next_node;
                deleted_node -> next_node -> prev_node = deleted_node;
            }
            else{
                deleted_node -> next_node = NULL;
            }
        }

        // [1.空き][2.プロセス]となっていて、[プロセス]を削除するケース。1に2をマージする。
        else if (deleted_node -> prev_node -> segment_id == -1)
        {
            deleted_node -> prev_node -> size     += deleted_node -> size;
            deleted_node -> prev_node -> next_node = deleted_node -> next_node;
            deleted_node -> next_node -> prev_node = deleted_node -> prev_node;
        }

        else{
        }
    }
    return;
}

void print_segment_list()
{
    struct node *index_node = head;

    printf("  ");
    while (index_node != NULL)
    {
        if (index_node->segment_id == -1){
            printf("H("); //空きスペース(Hole)
        }else{
            printf("P("); //プロセス(Process)
        }

        if (index_node->segment_id != -1){
            printf("%d ", index_node->segment_id);
        }

        printf("%d %d) ", index_node->begin_address, index_node->size);
        index_node = index_node->next_node;
    }

    printf("\n |");

    index_node = head;
    while(index_node != NULL)
    {
        if (index_node->segment_id == -1)
        {
            for (int i = 0; i < (index_node -> size); i++){
                printf("H");
            }
        }
        else
        {
            for (int i = 0; i < (index_node -> size); i++){
                printf("P");
            }
        }
        printf("|");
        index_node = index_node -> next_node;
    }
    printf("\n");

    return;
}

void print_statistics()
{
    printf("Num of traverse: %.1d\n", num_taverse);
    printf("Num of allocation:%d\n", num_allocation);
    printf("Total allocationSize:%d\n", total_alloc_size);
    printf("Average Allocation Size: %.1f\n", (float)total_alloc_size / (float)num_allocation);
    printf("Total  requests:%d\n", total_reqested_size);
    printf("Num of compaction: %d\n\n", num_compaction);
}

struct node *firstfit(int requested_size)
{
    struct node *index_node = head;
    while (index_node != NULL)
    {
        if (index_node->segment_id == -1)
        {
            if (index_node -> size >= requested_size){
                return index_node;
            }
        }
        num_taverse++;
        index_node = index_node->next_node;
    }
    //小さな空き領域が散在していて割当て可能な領域がない場合、デフラグして再度firstfit()を実行する
    printf("\nExecute compaction\n");
    compact();
    num_compaction++;

    printf("\nAllocate again\n");
    return firstfit(requested_size);
}

node *bestfit(int requested_size)
{
    int found_node = FALSE;
    struct node *index_node  = head;
    struct node *return_node = (node *)malloc(sizeof(node));
    return_node -> size = 99999;

    while (index_node != NULL)
    {
        if (index_node -> segment_id == -1)
        {
            // 要求サイズを超える空きセグメントの中で、最小のものを探す
            if (index_node -> size >= requested_size && index_node -> size < return_node -> size){
                return_node = index_node;
                found_node = TRUE;
            }
        }
        num_taverse++;
        index_node = index_node->next_node;
    }

    if (found_node) {
        return return_node;
    }

    //小さな空き領域が散在していて割当て可能な領域がない場合、デフラグして再度firstfit()を実行する
    printf("\nExecute compaction\n");
    compact();
    num_compaction++;

    printf("\nAllocate again\n");
    return bestfit(requested_size);
}


void compact()
{
    printf("\nAllocate again\n");

    int num_space = 0;
    struct node *index_node = head;
    struct node *tail_node;

    while (index_node != NULL)
    {
        if (index_node -> segment_id != -1){
            tail_node = index_node;
        }
        else
        {
            if (index_node == head){
                // 先頭が空きセグメントであれば、2番目のセグメントを先頭に持ってくる
                head = index_node->next_node;
            }
            else if (index_node->next_node == NULL){
                // 末尾が空きセグメントであれば、リストから除外する)
                index_node -> prev_node -> next_node = NULL; 
            }
            else{
                // 空きセグメントの前後のセグメントを繋ぎ、空きセグメントをリストから除外する
                index_node->prev_node->next_node = index_node->next_node;
                index_node->next_node->prev_node = index_node->prev_node;
            }
            num_space++;
        }

        index_node = index_node->next_node;
    } 

    tail_node -> begin_address = (tail_node -> prev_node -> begin_address) + (tail_node -> prev_node -> size);

    //プロセスノードを前方に詰め終わったので、末尾に空きセグメントを繋げる
    struct node *new_space = (node *)malloc(sizeof(node));
    new_space -> segment_id    = -1;
    new_space -> begin_address = tail_node -> begin_address + tail_node -> size;
    new_space -> size          = total_space_size;
    new_space -> prev_node     = tail_node;
    new_space -> next_node     = NULL;

    tail_node -> next_node = new_space;
    print_segment_list();

}
