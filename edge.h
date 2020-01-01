#ifndef EGDE_H
#define EGDE_H

/// This is edge if triangle
/*!
    \param direction stands for adding new point to the
    begin of to the end of current gxContour
*/
class gxEdge
{
public:
    gxEdge(int aknot1 = 0, int aknot2 = 0, int adirection = 0)
        :   knot1(aknot1),
            knot2(aknot2),
            direction(adirection)
    { }

    int knot1;
    int knot2;
    int direction;
};

#endif // EGDE_H
