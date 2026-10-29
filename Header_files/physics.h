#pragma once

#include <raylib.h>
#include <utility>
#include <vector>

using namespace std;

struct CollisionManager{
    protected:
        vector< tuple <Rectangle, bool, int> > collisionSet;
        int ID_count = 0;
    
        pair<float, Vector2> CheckCollision(const Rectangle& active, Vector2 velocity, float dt, const Rectangle& passive);

    public:
        pair<float, Vector2> CollisionHandler(int ID, const Rectangle collisionBox, const vector< tuple <Rectangle, bool, int> >& collisionSet, const Vector2 velocity, const float fixed_dt);
        
        pair <bool, vector< tuple <Rectangle, bool, int> >::iterator > checkID(int ID, vector< tuple <Rectangle, bool, int> >& collisionSet);

        int add(Rectangle collisionBox, bool isLevel, vector< tuple <Rectangle, bool, int> >& collisionSet);
        void remove(int& ID, vector< tuple <Rectangle, bool, int> >& collisionSet);
        void update(int ID, Vector2 position, vector< tuple <Rectangle, bool, int> >& collisionSet);
        void modify(int ID, Vector2 dimensions, bool isLevel, vector< tuple <Rectangle, bool, int> >& collisionSet);
};