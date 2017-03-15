#include "load.h"
#include "cell.h"
#include "generate-image.h"
#include <stdio.h>

void print_solution(Solution* pSolution)
{
    Cell_Node* pNode = pSolution->Head;
    while (pNode != NULL)
    {
        if (pNode->cell_status != DYING)
            printf("%d %d\n", pNode->cell_position.x, pNode->cell_position.y);
        pNode = pNode->next_cell;
    }
}

int main(int argc, char*argv[])
{
    char filename[128] = {0};
    scanf("%s", filename);
    Solution* pSolution = load_grid(filename);
    if (pSolution == NULL)
    {
        return 0;
    }
    
    int step_index = 0;
    for (step_index = 0; step_index < pSolution->steps; step_index++)
    {
        print_solution(pSolution);
        printf("\n-------------------\n");
        sprintf(filename, "./out/%d.ppm", step_index);
        write_image(filename, pSolution);
        next_generation(pSolution);
    }
    return 1;
}