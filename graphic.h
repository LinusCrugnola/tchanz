#ifndef GRAPHIC_H
#define GRAPHIC_H

//FIXME: how does this work?

typedef const unsigned& cunsigned;

namespace graphic{
    bool draw_empty(cunsigned x, cunsigned y, cunsigned side, bool centered);
    bool draw_rhomb(cunsigned x, cunsigned y, cunsigned side, bool centered);
    bool draw_uniform(cunsigned x, cunsigned y, cunsigned side, bool centered);
    bool draw_diagonal(cunsigned x, cunsigned y, cunsigned side, bool centered);
    bool draw_grille(cunsigned x, cunsigned y, cunsigned side, bool centered);
}

#endif