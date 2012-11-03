#ifndef CNETWORKVIEW_H
#define CNETWORKVIEW_H

#include "CAbstractView.h"

class CNetworkView : public CAbstractView
{
    public:
        CNetworkView();
        ~CNetworkView();

         // Send pending messages
         // process incoming message for trafficlights
         void UpdateNetwork(){}
};

#endif // CNETWORKVIEW_H
