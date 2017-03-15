#include "cell.h"
#include <stdlib.h>
#include <string.h>

void next_generation(Solution* pSolution)
{
    if (pSolution == NULL)
    {
        return;
    }
    Cell_Node* link_head = pSolution->Head;
    Cell_Node* pNode = link_head;
    Cell_Node* pPreNode = NULL;
    Cell_Node* pNextNode = NULL;
    while (pNode != NULL)
    {
        pNextNode = pNode->next_cell;
        if (pNode->cell_status == DYING)
        {
            update_link_ngbs(link_head, pNode);
            if (pPreNode == NULL)
            {
                link_head = pNextNode;
            }
            else
            {
                pPreNode->next_cell = pNextNode;
            }
            free(pNode);
            pNode = pNextNode;
            continue;
        }
        else if (pNode->cell_status == NEWBORN)
        {
            update_link_ngbs(link_head, pNode);
            pNode->cell_status = ALIVE;
        }
        pPreNode = pNode;
        pNode = pNextNode;
    }
    
    pSolution->Head = link_head;
    pNode = link_head;
    while (pNode != NULL)
    {
        int cnt = 0;
        int index = 0;
        for (index = 0; index < 8; index++)
        {
            if (pNode->cell_ngbs[index])
                cnt++;
        }
        if (is_dying_cnt(cnt))
        {
            pNode->cell_status = DYING;
        }
        pNode = pNode->next_cell;
    }
    
    pNode = link_head;
    while (pNode != NULL)
    {
        if (pNode->cell_status == NEWBORN)
        {
            pNode = pNode->next_cell;
            continue;
        }
        int index = 0;
        for (index = 0; index < 8; index++)
        {
            if (!pNode->cell_ngbs[index])
            {
                Pos ngbpos = get_ngbs_position(pNode, index);
                if (ngbpos.x < 0 || ngbpos.y < 0 
                        || ngbpos.x >=pSolution->grid_width || ngbpos.y >= pSolution->grid_hight)
                {
                    continue;
                }
                bool cell_ngbs[8];
                memset(cell_ngbs, 0, 8);
                if (will_newborn(link_head, ngbpos, cell_ngbs))
                {
                    Cell_Node* pNewNode = (Cell_Node*)malloc(sizeof(Cell_Node));
                    pNewNode->cell_position = ngbpos;
                    pNewNode->cell_status = NEWBORN;
                    memcpy(pNewNode->cell_ngbs, cell_ngbs, sizeof(bool)*8);
                    pNewNode->next_cell = NULL;
                    link_head = insert_node_in_link(link_head, pNewNode);
                }
            }
        }
        pNode = pNode->next_cell;
    }
    pSolution->Head = link_head;
}

Pos get_ngbs_position(Cell_Node* pNode, int index)
{
    Pos ans;
    ans.x = 0;
    ans.y = 0;
    if (index > 7 || index < 0 )
    {
        return ans; 
    }
    int xdelta = index % 4 > 0 ? (index / 4 * (-2) + 1) : 0;
    int ydelta = (index + 2) % 4 > 0 ? (index + 2) / 4 * (-2) + 1 : 0;
    ans.x = pNode->cell_position.x + xdelta;
    ans.y = pNode->cell_position.y + ydelta;
    return ans;
}

int get_ngbs_index(int x, int y)
{
    int index = -1;
    if (x > 0)
    {
        index = -y + 2;
    }
    else if (x < 0)
    {
        index = y + 6;
    }
    else
    {
        index = y > 0 ? 0 : 4;
    }
    return index;
}

bool will_newborn(Cell_Node* pHead, Pos curPos, bool ngbs_status[])
{
    Cell_Node* pNode = pHead;
    
    int cnt = 0;

    while (pNode != NULL)
    {
        if (pNode->cell_position.x == curPos.x && pNode->cell_position.y == curPos.y)
        {
            return false;
        }
        if (pNode->cell_status != NEWBORN && is_neighbor(pNode->cell_position, curPos))
        {
            int index = get_ngbs_index(pNode->cell_position.x - curPos.x, pNode->cell_position.y - curPos.y);
            if (index >= 0)
            {
                ngbs_status[index] = true;
                cnt++;
            }    
        }
        pNode = pNode->next_cell;
    }

    if (is_alive_cnt(cnt))
    {
        return true;
    }
    return false;
}

bool is_neighbor(Pos firstPos, Pos secondPos)
{
    int xd = firstPos.x - secondPos.x;
    int yd = firstPos.y - secondPos.y;
    if (xd == 0 && yd == 0)
    {
        return false;
    }
    if (xd >= -1 && xd <= 1 && yd >= -1 && yd <= 1)
    {
        return true;
    }
    return false;
}

bool is_dying_cnt(int cnt)
{
    return (cnt != 2 && cnt != 3);
}

bool is_alive_cnt(int cnt)
{
    return (cnt == 3);
}

void update_link_ngbs(Cell_Node* pHead, Cell_Node* pNode)
{
    Cell_Node* ptmpNode = pHead;
    while (ptmpNode != NULL)
    {
        if (is_neighbor(ptmpNode->cell_position, pNode->cell_position))
        {
            int index = get_ngbs_index(pNode->cell_position.x - ptmpNode->cell_position.x, pNode->cell_position.y - ptmpNode->cell_position.y);
            if (pNode->cell_status == NEWBORN)
            {
                ptmpNode->cell_ngbs[index] = true;
            }
            else if (pNode->cell_status == DYING)
            {
                ptmpNode->cell_ngbs[index] = false;
            }
        }
        ptmpNode = ptmpNode->next_cell;
    }
}

Cell_Node* insert_node_in_link(Cell_Node* pHead, Cell_Node* pNode)
{
    Cell_Node* ptmpNode = pHead;
    Cell_Node* pPreNode = NULL;
    while (ptmpNode != NULL)
    {
        if (ptmpNode->cell_position.y > pNode->cell_position.y)
        {
            break;
        }
        if (ptmpNode->cell_position.y == pNode->cell_position.y && 
                ptmpNode->cell_position.x > pNode->cell_position.x)
        {
            break;
        }
        pPreNode = ptmpNode;
        ptmpNode = ptmpNode->next_cell;
    }
    if (pPreNode == NULL)
    {
        pNode->next_cell = pHead;
        return pNode;
    }
    else
    {
        pPreNode->next_cell = pNode;
        pNode->next_cell = ptmpNode;
    }
    return pHead;
}
