#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TSoldier
{
    struct TSoldier   * m_Next;
    int                 m_PersonalID;
    char                m_SecretRecord[64];
} TSOLDIER;

#endif /* __PROGTEST__ */

TSOLDIER         * mergePlatoons     ( TSOLDIER        * p1,
                                       TSOLDIER        * p2 )
{
    TSOLDIER *act1 = p1;
    TSOLDIER *act2 = p2;

    TSOLDIER *t1 = NULL;
    TSOLDIER *t2 = NULL;

    TSOLDIER *act = NULL;

    TSOLDIER *ret = NULL;

    while(1)
    {
        if(!act1 && !act2) break;
        if(!act1 && act)
        {
            act->m_Next = act2;
            break;
        }
        if(!act2 && act)
        {
            act->m_Next = act1;
            break;
        }

        if(!act1 && !act)
        {
            act = act2;
            ret = act;
            break;
        }
        if(!act2 && !act)
        {
            act = act1;
            ret = act;
            break;
        }

        if(act1 && act2)
        {
            t1 = act1;
            t2 = act2;
            act1 = act1->m_Next;
            act2 = act2->m_Next;
            t1->m_Next = t2;
            t2->m_Next = NULL;
            if(act) act->m_Next = t1;
            else
            {
                act = t1;
                ret = act;
            }
            act = t2;
        }

    }
    return ret;
}

void               splitPlatoon      ( TSOLDIER        * src,
                                       TSOLDIER       ** p1,
                                       TSOLDIER       ** p2 )
{
    int c = 0;
    TSOLDIER *act = src;
    TSOLDIER *old = NULL;
    while(act)
    {
        if(!act) break;
        c++;
        if(!act->m_Next && (c % 2) == 1) // !!!
        {
            if(old) old->m_Next = NULL;
            free(act);
            break;
        }
        old = act;
        act = act->m_Next;
    }
    act = src;
    *p1 = act;
    for(int i = 0; i < (c / 2); i++){
        old = act;
        act = act->m_Next;
    }
    if(old) old->m_Next = NULL;
    *p2 = act;
}

void               destroyPlatoon    ( TSOLDIER        * src )
{
    TSOLDIER * act = src;
    TSOLDIER * t = NULL;
    while(act)
    {
        t = act;
        act = act->m_Next;
        if(t) free(t);
    }
}
#ifndef __PROGTEST__
TSOLDIER         * createSoldier     ( int               id,
                                       TSOLDIER        * next )
{
    TSOLDIER * r = (TSOLDIER *) malloc ( sizeof ( *r ) );
    r -> m_PersonalID = id;
    r -> m_Next = next;
    /* r -> m_SecretRecord will be filled by someone with a higher security clearance */
    return r;
}
int main ( void )
{
    TSOLDIER * a, *b, *c;
    /* a = createSoldier ( 0,
                         createSoldier ( 1,
                                         createSoldier ( 2,
                                                         createSoldier ( 3,
                                                                         createSoldier ( 4, NULL )))));
     b = createSoldier ( 10,
                         createSoldier ( 11,
                                         createSoldier ( 12,
                                                         createSoldier ( 13,
                                                                         createSoldier ( 14, NULL )))));
     c = mergePlatoons ( a, b );
     assert ( c != NULL
              && c -> m_PersonalID == 0
              && c -> m_Next != NULL
              && c -> m_Next -> m_PersonalID == 10
              && c -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_PersonalID == 1
              && c -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
              && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 3
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     splitPlatoon ( c, &a, &b );
     assert ( a != NULL
              && a -> m_PersonalID == 0
              && a -> m_Next != NULL
              && a -> m_Next -> m_PersonalID == 10
              && a -> m_Next -> m_Next != NULL
              && a -> m_Next -> m_Next -> m_PersonalID == 1
              && a -> m_Next -> m_Next -> m_Next != NULL
              && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
              && a -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
              && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     assert ( b != NULL
              && b -> m_PersonalID == 12
              && b -> m_Next != NULL
              && b -> m_Next -> m_PersonalID == 3
              && b -> m_Next -> m_Next != NULL
              && b -> m_Next -> m_Next -> m_PersonalID == 13
              && b -> m_Next -> m_Next -> m_Next != NULL
              && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
              && b -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
              && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     destroyPlatoon ( a );
     destroyPlatoon ( b );

     a = createSoldier ( 0,
                         createSoldier ( 1,
                                         createSoldier ( 2, NULL )));
     b = createSoldier ( 10,
                         createSoldier ( 11,
                                         createSoldier ( 12,
                                                         createSoldier ( 13,
                                                                         createSoldier ( 14, NULL )))));
     c = mergePlatoons ( a, b );
     assert ( c != NULL
              && c -> m_PersonalID == 0
              && c -> m_Next != NULL
              && c -> m_Next -> m_PersonalID == 10
              && c -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_PersonalID == 1
              && c -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
              && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
              && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     splitPlatoon ( c, &a, &b );
     assert ( a != NULL
              && a -> m_PersonalID == 0
              && a -> m_Next != NULL
              && a -> m_Next -> m_PersonalID == 10
              && a -> m_Next -> m_Next != NULL
              && a -> m_Next -> m_Next -> m_PersonalID == 1
              && a -> m_Next -> m_Next -> m_Next != NULL
              && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
              && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     assert ( b != NULL
              && b -> m_PersonalID == 2
              && b -> m_Next != NULL
              && b -> m_Next -> m_PersonalID == 12
              && b -> m_Next -> m_Next != NULL
              && b -> m_Next -> m_Next -> m_PersonalID == 13
              && b -> m_Next -> m_Next -> m_Next != NULL
              && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
              && b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
     destroyPlatoon ( a );
     destroyPlatoon ( b );*/

    a = createSoldier ( 0,
                        createSoldier ( 1,
                                        createSoldier ( 2, NULL )));
    b = createSoldier ( 10,
                        createSoldier ( 11,
                                        createSoldier ( 12,
                                                        createSoldier ( 13, NULL ))));
    c = mergePlatoons ( a, b );
    assert ( c != NULL
             && c -> m_PersonalID == 0
             && c -> m_Next != NULL
             && c -> m_Next -> m_PersonalID == 10
             && c -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_PersonalID == 1
             && c -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
             && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
             && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    splitPlatoon ( c, &a, &b );
    assert ( a != NULL
             && a -> m_PersonalID == 0
             && a -> m_Next != NULL
             && a -> m_Next -> m_PersonalID == 10
             && a -> m_Next -> m_Next != NULL
             && a -> m_Next -> m_Next -> m_PersonalID == 1
             && a -> m_Next -> m_Next -> m_Next == NULL );
    assert ( b != NULL
             && b -> m_PersonalID == 11
             && b -> m_Next != NULL
             && b -> m_Next -> m_PersonalID == 2
             && b -> m_Next -> m_Next != NULL
             && b -> m_Next -> m_Next -> m_PersonalID == 12
             && b -> m_Next -> m_Next -> m_Next == NULL );
    destroyPlatoon ( a );
    destroyPlatoon ( b );

    return 0;
}
#endif /* __PROGTEST__ */
