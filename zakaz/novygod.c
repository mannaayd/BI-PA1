#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#define MAX_BRANCHES             3
#define DECORATION_NONE          0
#define DECORATION_CANDLE        1
#define DECORATION_SPARKLER      2


typedef struct TNode
{
    struct TNode   * m_Parent;
    struct TNode   * m_Branches[MAX_BRANCHES];
    int              m_Decoration;
} TNODE;
#endif /* __PROGTEST__ */

int                easyToCatchFire    ( TNODE           * root )
{
    if(!root) return 0;

    if(root->m_Decoration == DECORATION_SPARKLER &&
       ((root->m_Branches[0] && root->m_Branches[0]->m_Decoration == DECORATION_CANDLE) ||
        (root->m_Branches[1] && root->m_Branches[1]->m_Decoration == DECORATION_CANDLE) ||
        (root->m_Branches[2] && root->m_Branches[2]->m_Decoration == DECORATION_CANDLE) ||
        (root->m_Parent && root->m_Parent->m_Decoration == DECORATION_CANDLE)
       )) return 1;

    if(root->m_Decoration == DECORATION_CANDLE &&
       ((root->m_Branches[0] && root->m_Branches[0]->m_Decoration == DECORATION_SPARKLER) ||
        (root->m_Branches[1] && root->m_Branches[1]->m_Decoration == DECORATION_SPARKLER) ||
        (root->m_Branches[2] && root->m_Branches[2]->m_Decoration == DECORATION_SPARKLER) ||
        (root->m_Parent && root->m_Parent->m_Decoration == DECORATION_SPARKLER)
       )) return 1;

    if(root->m_Branches[0] && root->m_Branches[1] &&
       root->m_Branches[0]->m_Decoration == DECORATION_CANDLE &&
       root->m_Branches[1]->m_Decoration == DECORATION_SPARKLER
            ) return 1;

    if(root->m_Branches[0] && root->m_Branches[1] &&
       root->m_Branches[0]->m_Decoration == DECORATION_SPARKLER &&
       root->m_Branches[1]->m_Decoration == DECORATION_CANDLE
            ) return 1;

    if(root->m_Branches[2] && root->m_Branches[1] &&
       root->m_Branches[2]->m_Decoration == DECORATION_CANDLE &&
       root->m_Branches[1]->m_Decoration == DECORATION_SPARKLER
            ) return 1;

    if(root->m_Branches[2] && root->m_Branches[1] &&
       root->m_Branches[2]->m_Decoration == DECORATION_SPARKLER &&
       root->m_Branches[1]->m_Decoration == DECORATION_CANDLE
            ) return 1;

    if(root->m_Branches[0]) return easyToCatchFire(root->m_Branches[0]);
    if(root->m_Branches[1]) return easyToCatchFire(root->m_Branches[1]);
    if(root->m_Branches[2]) return easyToCatchFire(root->m_Branches[2]);
    return 0;
}

void               destroyTree        ( TNODE           * root );

int                cutBranch          ( TNODE          ** root,
                                        const char      * path )
{

    int l = 0;
    TNODE *act = (*root);
    for(;;l++)
    {
        if (path[l] == '\0') break;
        if (path[l] < '0' || path[l] > '2') return 0;
    }
    l = 0;
    while(1)
    {
        if(!act) return 0;
        if(path[l] == '\0')
        {
            if(l==0) *root = NULL;
            destroyTree(act);
            act = NULL;
            break;
        }
        if(path[l+1] == '\0')
        {
            TNODE *old = act;
            act = act->m_Branches[path[l] - 48];
            old->m_Branches[path[l] - 48] = NULL;
        }
        else act = act->m_Branches[path[l] - 48];
        l++;
    }
    return 1;
}

int                setDecoration      ( TNODE          ** root,
                                        const char      * path,
                                        int               decor )
{
    for(int l = 0;path[l] != '\0';l++) if (path[l] < '0' || path[l] > '2') return 0;
    if(!(*root))
    {
        (*root) = (TNODE*)malloc(sizeof(*(*root)));
        (*root)->m_Decoration = DECORATION_NONE;
        (*root)->m_Branches[0] = NULL;
        (*root)->m_Branches[1] = NULL;
        (*root)->m_Branches[2] = NULL;
        (*root)->m_Parent = NULL;
    }
    TNODE *act = (*root);
    for(int i = 0; path[i] != '\0'; i++)
    {
        if(!act->m_Branches[path[i]-48])
        {
            act->m_Branches[path[i]-48] = (TNODE*)malloc(sizeof(*act->m_Branches[path[i]-48]));
            act->m_Branches[path[i]-48]->m_Decoration = DECORATION_NONE;
            act->m_Branches[path[i]-48]->m_Branches[0] = NULL;
            act->m_Branches[path[i]-48]->m_Branches[1] = NULL;
            act->m_Branches[path[i]-48]->m_Branches[2] = NULL;
            act->m_Branches[path[i]-48]->m_Parent = act;
        }
        act = act->m_Branches[path[i]-48];
    }
    act->m_Decoration = decor;
    return 1;
}

void               destroyTree        ( TNODE           * root )
{
    if(!root) return;
    if(root->m_Branches[0])
    {
        destroyTree(root->m_Branches[0]);
        root->m_Branches[0] = NULL;
    }
    if(root->m_Branches[1])
    {
        destroyTree(root->m_Branches[1]);
        root->m_Branches[1] = NULL;
    }
    if(root->m_Branches[2])
    {
        destroyTree(root->m_Branches[2]);
        root->m_Branches[2] = NULL;
    }
    free(root);
}

#ifndef __PROGTEST__
int                main               ( void )
{
    TNODE * r;

    r = NULL;
    assert ( setDecoration ( &r, "000", DECORATION_SPARKLER ) == 1 );

    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "001", DECORATION_SPARKLER ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "002", DECORATION_SPARKLER ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "1", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] != NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
             && r -> m_Branches[1] -> m_Parent == r
             && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "01", DECORATION_NONE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] != NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[1] -> m_Parent == r
             && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] != NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[1] -> m_Parent == r
             && r -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( easyToCatchFire ( r ) == 0 );
    destroyTree ( r );

    r = NULL;
    assert ( setDecoration ( &r, "000", DECORATION_SPARKLER ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "002", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "2", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL
             && r -> m_Branches[2] -> m_Parent == r
             && r -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( easyToCatchFire ( r ) == 0 );
    destroyTree ( r );

    r = NULL;
    assert ( setDecoration ( &r, "0001", DECORATION_SPARKLER ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "000", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( easyToCatchFire ( r ) == 1 );
    destroyTree ( r );

    r = NULL;
    assert ( setDecoration ( &r, "012001", DECORATION_SPARKLER ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "012002", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] -> m_Branches[0] -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( easyToCatchFire ( r ) == 1 );
    assert ( cutBranch ( &r, "0120" ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( easyToCatchFire ( r ) == 0 );
    destroyTree ( r );

    r = NULL;
    assert ( setDecoration ( &r, "0123", DECORATION_SPARKLER ) == 0 );
    assert ( r == NULL );
    assert ( cutBranch ( &r, "012" ) == 0 );
    assert ( r == NULL );
    assert ( easyToCatchFire ( r ) == 0 );
    destroyTree ( r );

    r = NULL;
    assert ( setDecoration ( &r, "012", DECORATION_SPARKLER ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( setDecoration ( &r, "011", DECORATION_CANDLE ) == 1 );
    assert ( r != NULL
             && r -> m_Parent == NULL
             && r -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] != NULL
             && r -> m_Branches[1] == NULL
             && r -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Parent == r
             && r -> m_Branches[0] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Parent == r -> m_Branches[0]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Decoration == DECORATION_NONE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] != NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Decoration == DECORATION_CANDLE
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[1] -> m_Branches[2] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Parent == r -> m_Branches[0] -> m_Branches[1]
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Decoration == DECORATION_SPARKLER
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[0] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[1] == NULL
             && r -> m_Branches[0] -> m_Branches[1] -> m_Branches[2] -> m_Branches[2] == NULL );
    assert ( easyToCatchFire ( r ) == 1 );
    assert ( cutBranch ( &r, "" ) == 1 );
    assert ( r == NULL );
    assert ( easyToCatchFire ( r ) == 0 );
    assert ( cutBranch ( &r, "" ) == 0 );
    assert ( r == NULL );
    destroyTree ( r );
    return 0;
}
#endif /* __PROGTEST__ */
