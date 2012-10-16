#ifndef CNETWORKVIEW_H
#define CNETWORKVIEW_H

#include "CAbstractView.h"

class CNetworkView : public CAbstractView
{
    public:
        CNetworkView();
        ~CNetworkView();

         void UpdatePull(){}
         void UpdateNetwork(){}
};

#endif // CNETWORKVIEW_H
