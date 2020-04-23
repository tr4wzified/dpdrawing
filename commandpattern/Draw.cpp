
#include "Draw.h"
#include <string.h>
#include <list>
#include "DrawShape.h"
#include "Shape.h"

class Draw : public DrawShape
{
    std::list<DrawShape*> drawList;

    void takeDrawRequest(DrawShape* drawRequest)
    {
        drawList.push_back(drawRequest);
    }

    void executeDrawRequest()
    {
        for(DrawShape *r : drawList)
        {
            r->execute();
        }
        drawList.clear();
    }
};
