#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MEM_SIZE 1048576 //define the memory size(unit: byte)


/* algo 1-->first fit   2-->best fit  3-->worst fit */

/* Possible sizes of different processes */
int possible_sizes[] = {4, 8, 12, 16, 20,
                       24, 28, 32, 36, 40,
                       44, 48, 52, 56, 60,
                       64, 68, 72, 76, 80,
                       84, 88, 92, 96, 100};


/* record the starting addresses of different processes for three algorithms */
char* ff_pro_add[500];
char* bf_pro_add[500];
char* wf_pro_add[500];

/* record the sizes of different processes for three algorithms
   unit: KB */
int ff_pro_size[500];
int bf_pro_size[500];
int wf_pro_size[500];

/* process index of three algorithms */
int ff_pro_index = 0;
int bf_pro_index = 0;
int wf_pro_index = 0;

/* hole address information */
char* ff_hole_add[500];
char* bf_hole_add[500];
char* wf_hole_add[500];

/* hole size information
   unit: byte */
int ff_hole_size[500];
int bf_hole_size[500];
int wf_hole_size[500];

/* function decleartion */
int fill_up(int pro_num, int pro_size, char* mem_add, int mem_type);
int size_left(char* mem_add);

/*
pro_number: process number
pro_size  : process size(KB)
mem_add   : memory starting address
algo      : 1 --> ff memory ; 2 --> bf memory ; 3 --> wf memory
return 1 ---> fill successful
return 0 ---> fill unsuccessful
*/
int fill_up(int pro_num, int pro_size, char* mem_add, int algo)
{
    if(algo == 1)
    {
        if (size_left(mem_add) < pro_size * 1024)
        {
            return 0;
        }

        char* temp = mem_add;
    
        while(*temp == 'f')
        {
            temp++;
        }

        ff_pro_add[pro_num] = temp;
        ff_pro_size[pro_num] = pro_size;

        /* filling process */
        int i;
        for (i = 0; i < pro_size * 1024; i++)
        {
            *temp = 'f'; //f means filled up
            temp++;
        }

        return 1;
    }
    else if (algo == 2)
    {
        if (size_left(mem_add) < pro_size * 1024)
        {
            return 0;
        }

        char* temp = mem_add;
    
        while(*temp == 'f')
        {
            temp++;
        }

        bf_pro_add[pro_num] = temp;
        bf_pro_size[pro_num] = pro_size;

        /* filling process */
        int i;
        for (i = 0; i < pro_size * 1024; i++)
        {
            *temp = 'f'; //f means filled up
            temp++;
        }

        return 1;
    }
    else
    {
        if (size_left(mem_add) < pro_size * 1024)
        {
            return 0;
        }

        char* temp = mem_add;
    
        while(*temp == 'f')
        {
            temp++;
        }

        wf_pro_add[pro_num] = temp;
        wf_pro_size[pro_num] = pro_size;

        /* filling process */
        int i;
        for (i = 0; i < pro_size * 1024; i++)
        {
            *temp = 'f'; //f means filled up
            temp++;
        }

        return 1;
    }
}

/* calculate the size left for a memory space
   return unit: byte */
int size_left(char* mem_add)
{
    int i;
    int counter = 0;
    for(i = 0; i < MEM_SIZE; i++)
    {
        if(*(mem_add + i) == 'e')
        {
            counter++;
        }
    }
    return counter;
}

/* algo 1-->first fit;  2-->best fit  3-->worst fit */
int number_of_processes(int algo)
{
    int counter = 0;
    int i;
    if(algo == 1)
    {
        for(i = 0; i < 500; i++)
        {
            if (ff_pro_size[i] != 0)
            {
                counter++;
            }
        }
    }
    else if (algo == 2)
    {
        for(i = 0; i < 500; i++)
        {
            if(bf_pro_size[i] != 0)
            {
                counter++;
            }
        }
    }
    else 
    {
        for(i = 0; i < 500; i++)
        {
            if(wf_pro_size[i] != 0)
            {
                counter++;
            }
        }
    }
    return counter;
}

void ff_get_hole_information(char* mem_loc)
{
    char* mem_end = mem_loc + (1024 * 1024) - 1;
    int i;
    for (i = 0; i < 500; i++)
    {
        ff_hole_add[i] = NULL;
        ff_hole_size[i] = 0;
    }
    i = 0;
    char* start = mem_loc;
    char* end = mem_loc;
    while(1)
    {
        if(*start == 'f' && *end == 'f')
        {
            if (start == mem_end && end == mem_end)
            {
                return;
            }
            start++;
            end++;
        }
        else
        {

            if(start == mem_end && end == mem_end)
            {
                ff_hole_add[i] = start;
                ff_hole_size[i] = 1;
                return;
            }

            while(*end == 'e')
            {
                if (end == mem_end)
                {
                    ff_hole_add[i] = start;
                    ff_hole_size[i] = end - start + 1;
                    return; 
                }
                end++;
            }
            ff_hole_add[i] = start;
            ff_hole_size[i] = end - start;
            start = end;
            i++;
        }
    }
}

void bf_get_hole_information(char* mem_loc)
{
    char* mem_end = mem_loc + (1024 * 1024) - 1;
    int i;
    for (i = 0; i < 500; i++)
    {
        bf_hole_add[i] = NULL;
        bf_hole_size[i] = 0;
    }
    i = 0;
    char* start = mem_loc;
    char* end = mem_loc;
    while(1)
    {
        if(*start == 'f' && *end == 'f')
        {
            if (start == mem_end && end == mem_end)
            {
                return;
            }
            start++;
            end++;
        }
        else
        {

            if(start == mem_end && end == mem_end)
            {
                bf_hole_add[i] = start;
                bf_hole_size[i] = 1;
                return;
            }

            while(*end == 'e')
            {
                if (end == mem_end)
                {
                    bf_hole_add[i] = start;
                    bf_hole_size[i] = end - start + 1;
                    return; 
                }
                end++;
            }
            bf_hole_add[i] = start;
            bf_hole_size[i] = end - start;
            start = end;
            i++;
        }
    }
}

void wf_get_hole_information(char* mem_loc)
{
    char* mem_end = mem_loc + (1024 * 1024) - 1;
    int i;
    for (i = 0; i < 500; i++)
    {
        wf_hole_add[i] = NULL;
        wf_hole_size[i] = 0;
    }
    i = 0;
    char* start = mem_loc;
    char* end = mem_loc;
    while(1)
    {
        if(*start == 'f' && *end == 'f')
        {
            if (start == mem_end && end == mem_end)
            {
                return;
            }
            start++;
            end++;
        }
        else
        {

            if(start == mem_end && end == mem_end)
            {
                wf_hole_add[i] = start;
                wf_hole_size[i] = 1;
                return;
            }

            while(*end == 'e')
            {
                if (end == mem_end)
                {
                    wf_hole_add[i] = start;
                    wf_hole_size[i] = end - start + 1;
                    return; 
                }
                end++;
            }
            wf_hole_add[i] = start;
            wf_hole_size[i] = end - start;
            start = end;
            i++;
        }
    }
}

void update_hole_info(char* mem_add, int algo)
{
    if(algo == 1)
    {
        ff_get_hole_information(mem_add);
    }
    else if (algo == 2)
    {
        bf_get_hole_information(mem_add);
    }
    else 
    {
        wf_get_hole_information(mem_add);
    }
}

int number_of_holes(int algo)
{
    int i;
    int counter = 0;
    if(algo == 1)
    {
        for(i = 0; i < 500; i++)
        {
            if(ff_hole_size[i] != 0)
            {
                counter++;
            }
        }
    }
    else if(algo == 2)
    {
        for(i = 0; i < 500; i++)
        {
            if(bf_hole_size[i] != 0)
            {
                counter++;
            }
        }
    }
    else 
    {
        for(i = 0; i < 500; i++)
        {
            if(wf_hole_size[i] != 0)
            {
                counter++;
            }
        }
    }
    return counter;
}

/* return 1: allocation successful
   return 0: allocation fail 
   process_size unit : KB */
int allocate_ff(int process_number, int process_size, char* mem_loc)
{
    /* update hole information */
    update_hole_info(mem_loc, 1);
    int hole_num = number_of_holes(1);
    int i;
    int j;
    for (int i = 0; i < hole_num; i++)
    {
        if(ff_hole_size[i] >= process_size * 1024)
        {
            ff_pro_add[process_number] = ff_hole_add[i];
            ff_pro_size[process_number] = process_size;
            for(j = 0; j < process_size * 1024; j++)
            {
                *(ff_hole_add[i] + j) = 'f';
            }
            return 1;
        }
    }
    return 0;
}

/* return 1: allocation successful
   return 0: allocation fail 
   process_size unit : KB 
   Best fit approach*/
int allocate_bf(int process_number, int process_size, char* mem_loc)
{
    int i;
    int j;

    /* update hole information */
    update_hole_info(mem_loc, 2);
    int hole_num = number_of_holes(2);
    
    /* No holes exist */
    if (hole_num == 0)
    {
        return 0;
    }

    int difference[hole_num];   //for each cell: calculate hole_size[i] - process_size
    int smallestPositveDiffIndex = -1; 

    /* calculate the difference */
    for(i = 0; i < hole_num; i++)
    {
        difference[i] = bf_hole_size[i] - process_size * 1024;
    }

    /* check if there is any positve difference */
    for(i = 0; i < hole_num; i++)
    {
        if (difference[i] >= 0)
        {
            smallestPositveDiffIndex = i;
        }
    }

    /* All holes are too small */
    if(smallestPositveDiffIndex == -1)
    {
        return 0;
    }

    /* find the hole with the smallest difference */
    for(i = 0; i < hole_num; i++)
    {
        if (difference[i] >= 0 && difference[i] < difference[smallestPositveDiffIndex])
        {
            smallestPositveDiffIndex = i;
        }
    }


    bf_pro_add[process_number] = bf_hole_add[smallestPositveDiffIndex];
    bf_pro_size[process_number] = process_size;
    for(j = 0; j < process_size * 1024; j++)
    {
        *(bf_hole_add[smallestPositveDiffIndex] + j) = 'f';
    }
    return 1;
}

/* return 1: allocation successful
   return 0: allocation fail 
   process_size unit : KB 
   Worst fit approach*/
int allocate_wf(int process_number, int process_size, char* mem_loc)
{
    int i;
    int j;

    /* update hole information */
    update_hole_info(mem_loc, 3);
    int hole_num = number_of_holes(3);
    
    /* No holes exist */
    if (hole_num == 0)
    {
        return 0;
    }

    int difference[hole_num];   //for each cell: calculate hole_size[i] - process_size
    int largestPositveDiffIndex = -1; 

    /* calculate the difference */
    for(i = 0; i < hole_num; i++)
    {
        difference[i] = wf_hole_size[i] - process_size * 1024;
    }

    /* check if there is any positve difference */
    for(i = 0; i < hole_num; i++)
    {
        if (difference[i] >= 0)
        {
            largestPositveDiffIndex = i;
        }
    }

    /* All holes are too small */
    if(largestPositveDiffIndex == -1)
    {
        return 0;
    }

    /* find the hole with the biggest difference */
    for(i = 0; i < hole_num; i++)
    {
        if (difference[i] >= 0 && difference[i] > difference[largestPositveDiffIndex])
        {
            largestPositveDiffIndex = i;
        }
    }


    wf_pro_add[process_number] = wf_hole_add[largestPositveDiffIndex];
    wf_pro_size[process_number] = process_size;
    for(j = 0; j < process_size * 1024; j++)
    {
        *(wf_hole_add[largestPositveDiffIndex] + j) = 'f';
    }
    return 1;
}

void compact_ff(char* mem_loc)
{
    int i;
    int total_space_needed = 0;
    for(i = 0; i < 500; i++)
    {
        total_space_needed += ff_pro_size[i] * 1024;
    }

    /* modify first process */
    int first_process_index;
    for(i = 0; i < 500; i++)
    {
        if (ff_pro_size[i] != 0)
        {
            first_process_index = i;
            break;
        }
    }
    ff_pro_add[first_process_index] = mem_loc;
    int j = first_process_index;
    for (i = 0; i < 500; i++)
    {
        if (ff_pro_size[i] != 0 && i != j)
        {
            ff_pro_add[i] = ff_pro_add[j] + ff_pro_size[j] * 1024;
            j = i;
        }
    }

    /* empty first */
    for (i = 0; i < 1024 * 1024; i++)
    {
        *(mem_loc + i) = 'e'; //e means empty
    }

    for (i = 0; i < total_space_needed; i++)
    {
        *(mem_loc + i) = 'f'; //e means empty
    }
}

void compact_bf(char* mem_loc)
{
    int i;
    int total_space_needed = 0;
    for(i = 0; i < 500; i++)
    {
        total_space_needed += bf_pro_size[i] * 1024;
    }

    /* modify first process */
    int first_process_index;
    for(i = 0; i < 500; i++)
    {
        if (bf_pro_size[i] != 0)
        {
            first_process_index = i;
            break;
        }
    }
    bf_pro_add[first_process_index] = mem_loc;
    int j = first_process_index;
    for (i = 0; i < 500; i++)
    {
        if (bf_pro_size[i] != 0 && i != j)
        {
            bf_pro_add[i] = bf_pro_add[j] + bf_pro_size[j] * 1024;
            j = i;
        }
    }

    /* empty first */
    for (i = 0; i < 1024 * 1024; i++)
    {
        *(mem_loc + i) = 'e'; //e means empty
    }

    for (i = 0; i < total_space_needed; i++)
    {
        *(mem_loc + i) = 'f'; //e means empty
    }
}


void compact_wf(char* mem_loc)
{
    int i;
    int total_space_needed = 0;
    for(i = 0; i < 500; i++)
    {
        total_space_needed += wf_pro_size[i] * 1024;
    }

    /* modify first process */
    int first_process_index;
    for(i = 0; i < 500; i++)
    {
        if (wf_pro_size[i] != 0)
        {
            first_process_index = i;
            break;
        }
    }
    wf_pro_add[first_process_index] = mem_loc;
    int j = first_process_index;
    for (i = 0; i < 500; i++)
    {
        if (wf_pro_size[i] != 0 && i != j)
        {
            wf_pro_add[i] = wf_pro_add[j] + wf_pro_size[j] * 1024;
            j = i;
        }
    }

    /* empty first */
    for (i = 0; i < 1024 * 1024; i++)
    {
        *(mem_loc + i) = 'e'; //e means empty
    }

    for (i = 0; i < total_space_needed; i++)
    {
        *(mem_loc + i) = 'f'; //e means empty
    }
}

void compact(char* mem_loc, int algo)
{
    if(algo == 1)
    {
        compact_ff(mem_loc);
    }
    else if(algo == 2)
    {
        compact_bf(mem_loc);
    }
    else
    {
        compact_wf(mem_loc);
    }
}

/*
process_size (unit:KB)
return1: allocate successfully
return0: allocation failed
*/
int allocate(int process_number, int process_size, char* mem_loc, int algo)
{
    int indicator;
    if(algo == 1)
    {
        indicator = allocate_ff(process_number, process_size, mem_loc);
    }
    else if(algo == 2)
    {
        indicator = allocate_bf(process_number, process_size, mem_loc);
    }
    else
    {
        indicator = allocate_wf(process_number, process_size, mem_loc);
    }
    return indicator;
}

/* algo: 1--> ff 2-->bf  3-->wf */
void status(char* mem_add, int algo)
{
    int i;
    if(algo == 1)
    {
        printf("===============Memory Information of First Fit algorithm===============\n");
        printf("size: 1MB\n");
        printf("Memory starting address: %p\n", mem_add);
        printf("Memory ending address:   %p\n", mem_add + (1024 * 1024) - 1);
        printf("\n");
        printf("++++++++++Process Information++++++++++\n");
        printf("------------------------------------------\n");
        for(int i = 0; i < 500; i++)
        {
            if (ff_pro_size[i] != 0)
            {
                printf("Process%d starting address: %p\n", i, ff_pro_add[i]);
                printf("Process%d size: %d KB\n", i, ff_pro_size[i]);
                printf("------------------------------------------\n");
            }
        }
        printf("\n");
        printf("+++++++++++Hole Information++++++++++++\n");
        printf("--------------------------------------\n");
        for(i = 0; i < 500; i++)
        {
            if(ff_hole_size[i] != 0)
            {
                printf("Hole%d starting address: %p\n", i, ff_hole_add[i]);
                printf("Hole%d size: %d KB\n", i, ff_hole_size[i] / 1024);
                printf("--------------------------------------\n");
            }
        }
        printf("\n");
    }
    else if (algo == 2)
    {
        printf("===============Memory Information of Best Fit algorithm===============\n");
        printf("size: 1MB\n");
        printf("Memory starting address: %p\n", mem_add);
        printf("Memory ending address:   %p\n", mem_add + (1024 * 1024) - 1);
        printf("\n");
        printf("++++++++++Process Information++++++++++\n");
        printf("------------------------------------------\n");
        for(int i = 0; i < 500; i++)
        {
            if (bf_pro_size[i] != 0)
            {
                printf("Process%d starting address: %p\n", i, bf_pro_add[i]);
                printf("Process%d size: %d KB\n", i, bf_pro_size[i]);
                printf("------------------------------------------\n");
            }
        }
        printf("\n");
        printf("+++++++++++Hole Information++++++++++++\n");
        printf("--------------------------------------\n");
        for(i = 0; i < 500; i++)
        {
            if(bf_hole_size[i] != 0)
            {
                printf("Hole%d starting address: %p\n", i, bf_hole_add[i]);
                printf("Hole%d size: %d KB\n", i, bf_hole_size[i] / 1024);
                printf("--------------------------------------\n");
            }
        }
        printf("\n");
    }
    else
    {
        printf("===============Memory Information of Worst Fit algorithm===============\n");
        printf("size: 1MB\n");
        printf("Memory starting address: %p\n", mem_add);
        printf("Memory ending address:   %p\n", mem_add + (1024 * 1024) - 1);
        printf("\n");
        printf("++++++++++Process Information++++++++++\n");
        printf("------------------------------------------\n");
        for(int i = 0; i < 500; i++)
        {
            if (wf_pro_size[i] != 0)
            {
                printf("Process%d starting address: %p\n", i, wf_pro_add[i]);
                printf("Process%d size: %d KB\n", i, wf_pro_size[i]);
                printf("------------------------------------------\n");
            }
        }
        printf("\n");
        printf("+++++++++++Hole Information++++++++++++\n");
        printf("--------------------------------------\n");
        for(i = 0; i < 500; i++)
        {
            if(wf_hole_size[i] != 0)
            {
                printf("Hole%d starting address: %p\n", i, wf_hole_add[i]);
                printf("Hole%d size: %d KB\n", i, wf_hole_size[i] / 1024);
                printf("--------------------------------------\n");
            }
        }
        printf("\n");
    }
}

/* algo 1-->frist fit   2-->best fit  3-->worst fit
   return 0 means that process has aleady been released
   return 1 means that process can be released */
int release(int pro_num, int algo)
{
    if(algo == 1)
    {
        /* process has been released already */
        if (ff_pro_add[pro_num] == 0)
        {
            return 0;
        }
        int byte_size = ff_pro_size[pro_num] * 1024;
        int i;
        for(i = 0; i < byte_size; i++)
        {
            *(ff_pro_add[pro_num] + i) = 'e';
        }
        ff_pro_size[pro_num] = 0;
        ff_pro_add[pro_num] = NULL;
        return 1;   
    }
    else if (algo == 2)
    {
        /* process has been released already */
        if (bf_pro_add[pro_num] == 0)
        {
            return 0;
        }
        int byte_size = bf_pro_size[pro_num] * 1024;
        int i;
        for(i = 0; i < byte_size; i++)
        {
            *(bf_pro_add[pro_num] + i) = 'e';
        }
        bf_pro_size[pro_num] = 0;
        bf_pro_add[pro_num] = NULL;
        return 1;   
    }
    else
    {
        /* process has been released already */
        if (wf_pro_add[pro_num] == 0)
        {
            return 0;
        }
        int byte_size = wf_pro_size[pro_num] * 1024;
        int i;
        for(i = 0; i < byte_size; i++)
        {
            *(wf_pro_add[pro_num] + i) = 'e';
        }
        wf_pro_size[pro_num] = 0;
        wf_pro_add[pro_num] = NULL;
        return 1;   
    }
}

int main()
{
    int i;
    int random;
    int stop_indicator;

    /* initialize three block of memories to implement three algoritms */
    char* ff_mem_add = (char*)malloc(MEM_SIZE);
    char* bf_mem_add = (char*)malloc(MEM_SIZE);
    char* wf_mem_add = (char*)malloc(MEM_SIZE);
    for (i = 0; i < 1024 * 1024; i++)
    {
        *(ff_mem_add + i) = 'e'; //e means empty
        *(bf_mem_add + i) = 'e'; //e means empty
        *(wf_mem_add + i) = 'e'; //e means empty
    }
    
    /* filling process */
    srand(time(NULL));
    while(1)
    {
        random = rand() % 25;  //generate random number [0, 24]        
        stop_indicator = fill_up(ff_pro_index, possible_sizes[random], ff_mem_add, 1);
        fill_up(bf_pro_index, possible_sizes[random], bf_mem_add, 2);
        fill_up(wf_pro_index, possible_sizes[random], wf_mem_add, 3);
        ff_pro_index++;
        bf_pro_index++;
        wf_pro_index++;
        if(stop_indicator == 0)
        {
            break;
        }
    }


    /* randomly release 10% */
    int total_process_number = number_of_processes(1);
    int number_needed_to_remove = total_process_number / 10;
    int temp = total_process_number % 10;
    int isremoved;
    srand(time(NULL));
    if(temp >= 5)
    {
        number_needed_to_remove++;
    }
    while(1)
    {
        random = rand() % total_process_number;
        isremoved = release(random, 1);
        release(random, 2);
        release(random, 3);
        if(isremoved == 1)
        {
            number_needed_to_remove--;
        }
        if(number_needed_to_remove == 0)
        {
            break;
        }
    }

    /* update hole information after removing 10% */
    update_hole_info(ff_mem_add, 1);
    update_hole_info(bf_mem_add, 2);
    update_hole_info(wf_mem_add, 3);

    /* Display memory information after removing 10% */
    printf("====================Memory Information after removing 10 percent====================\n");
    printf("\n");
    status(ff_mem_add, 1);
    status(bf_mem_add, 2);
    status(wf_mem_add, 3);
    printf("\n");

    /* compaction */
    compact(ff_mem_add, 1);
    compact(bf_mem_add, 2);
    compact(wf_mem_add, 3);

    /* update hole information after compaction */
    update_hole_info(ff_mem_add, 1);
    update_hole_info(bf_mem_add, 2);
    update_hole_info(wf_mem_add, 3);

    /* Display memory information after compaction */
    printf("====================Memory Information after Compaction==============================\n");
    printf("\n");
    status(ff_mem_add, 1);
    status(bf_mem_add, 2);
    status(wf_mem_add, 3);
    printf("\n");

    /* refilling the memories */
    int ff_stop_indicator = 1;
    int bf_stop_indicator = 1;
    int wf_stop_indicator = 1;
    srand(time(NULL));
    i = 0;
    while(i <= 10)
    {
        random = rand() % 25;
        allocate(ff_pro_index, possible_sizes[random], ff_mem_add, 1);
        allocate(bf_pro_index, possible_sizes[random], bf_mem_add, 2);
        allocate(wf_pro_index, possible_sizes[random], wf_mem_add, 3);
        i++;
        ff_pro_index++;
        bf_pro_index++;
        wf_pro_index++;
    }

    /* update hole information afte refilling */
    update_hole_info(ff_mem_add, 1);
    update_hole_info(bf_mem_add, 2);
    update_hole_info(wf_mem_add, 3);

    /* Display memory information after refilling */
    printf("=========================Memory Information after refilling==========================\n");
    printf("\n");
    status(ff_mem_add, 1);
    status(bf_mem_add, 2);
    status(wf_mem_add, 3);

    return 0;
}