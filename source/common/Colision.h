#ifndef COLISION_H_INCLUDED
#define COLISION_H_INCLUDED


#include "Mathematic.h"
#include "Common.h"


class CCollisionObject
{
    vector3<> Vertices[4];
    vector3<> VerticesDef[4];
    int NumVertices;
    vector3<> Position;

    vector3<> ModelPosition;

    float Radius;

public:


    CCollisionObject() {}
    CCollisionObject(vector3<> *ver,int num, vector3<> pos);
    CCollisionObject(float rad, vector3<> pos);

    //  ~CCollisionObject(){//if(Vertices)delete []Vertices;}
    vector3<> GetVert(int id)
    {
        return Vertices[id];
    };
    void InitRect(int wid, int hig)
    {
        NumVertices=4;
        vector3<> ver[4]= {vector3<>(0,0,0),vector3<>(wid,0,0),vector3<>(wid,0,hig),vector3<>(0,0,hig)};
        //VerticesDef=new vector3<>[4];
        // Vertices=new vector3<>[4];
        float maxx=0,maxz=0,minx=0,minz=0;
        for (int a=0; a<4; a++)
        {
            VerticesDef[a]=ver[a];
            Vertices[a]=ver[a];
            if(ver[a].x()>maxx)maxx=ver[a].x();
            if(ver[a].z()>maxz)maxz=ver[a].z();
            if(ver[a].x()<minx)minx=ver[a].x();
            if(ver[a].z()<minz)minz=ver[a].z();
        }
        ModelPosition.setX((maxx+minx)/2);
        ModelPosition.setZ((maxz+minz)/2);


        Radius=max(maxx-minx,maxz-minz)/2;

    }


   bool CheckColision(CCollisionObject*obj);
    void SetPos(float x, float y)
    {
        Position.setX(x);
        Position.setZ(y);
        for(int a=0; a<NumVertices; a++)
            Vertices[a]=VerticesDef[a]+Position;

    }



    void SetPosttion(vector3<> pos)
    {
        Position=pos;
    }

    vector3<> GetPosition()
    {
        return Position;
    }



};

#endif // COLISION_H_INCLUDED
