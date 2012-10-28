#ifndef CSTATICSCENE_H
#define CSTATICSCENE_H

class CStaticScene
{
public:
    CStaticScene()
    : mLoaded( false) {}

    bool Load(const char* fileName);
    void Dispose();
    void Draw();

    // data members
    bool mLoaded;
};

#endif // CSTATICSCENE_H
