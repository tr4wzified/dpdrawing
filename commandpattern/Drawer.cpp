#include "Drawer.h"

    DPDrawing::Drawer::Drawer(std::vector<std::unique_ptr<DrawShape>> drawList){
        this->drawList = drawList;
    }

    DPDrawing::Drawer::Drawer(){
        
    }

    void DPDrawing::Drawer::takeDrawRequest(std::unique_ptr<DrawShape>& drawRequest)
    {
        
        drawList.push_back(drawRequest);
    }

    void DPDrawing::Drawer::executeDrawRequests()
    {
        for(std::unique_ptr<DrawShape>& request : drawList)
        {
            request->Execute();
            request.reset();
        }
        drawList.clear();
    }

