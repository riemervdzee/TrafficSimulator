#ifndef CTRAFFICLANEGROUP_H
#define CTRAFFICLANEGROUP_H

class CTrafficLane;

class CTrafficLaneGroup
{
public:
    CTrafficLaneGroup();
    ~CTrafficLaneGroup();

    CTrafficLane* operator[](int index);
    void Clear();

private:
    CTrafficLane* lanes[8];
};

#endif // CTRAFFICLANEGROUP_H
