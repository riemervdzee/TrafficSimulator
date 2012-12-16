#ifndef CTRAFFICLANEGROUP_H
#define CTRAFFICLANEGROUP_H

class CTrafficLane;
class CNetworkView;

class CTrafficLaneGroup
{
public:
    CTrafficLaneGroup();
    ~CTrafficLaneGroup();

    CTrafficLane* operator[](int index);
    void Clear();
    void SetNetwork(CNetworkView* network);

private:
    CTrafficLane* lanes[8];
};

#endif // CTRAFFICLANEGROUP_H
