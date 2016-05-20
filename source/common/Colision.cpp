#include "Colision.h"

CCollisionObject::CCollisionObject(vector3<>*ver,int num, vector3<> pos)
{
    Position=pos;
    NumVertices=num;

    // Vertices=new vector3<>[num];
    float maxx=0,maxz=0,minx=0,minz=0;
    for (int a=0; a<num; a++)
    {
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

CCollisionObject::CCollisionObject(float rad, vector3<> pos)
{

    Position=pos;
    NumVertices=0;
    Radius=rad;

}


void CalculateMinMax(vector3<> N, vector3<>* vec, int num, float& min, float& max)
{
    float d=N.x()*vec[0].x()+N.z()*vec[0].z();
    min=max=d;
    for(int i=0; i<num; i++)
    {
        float d=N.x()*vec[i].x()+N.z()*vec[i].z();
        if(d<min)
        {
            min=d;
        }
        if(d>max)
        {
            max=d;
        }
    }
}




bool IsSeparating(vector3<> N, vector3<> *vec1, int num1, vector3<> *vec2, int num2)
{
    float min1=0;
    float max1=0;
    float min2=0;
    float max2=0;
    CalculateMinMax(N, vec1,num1, min1, max1);
    CalculateMinMax(N, vec2,num2, min2, max2);
    if(min1>max2||min2>max1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


 bool CCollisionObject::CheckColision(CCollisionObject*obj)
{

//if(abs((ModelPosition-obj->ModelPosition).length())<Radius+obj->Radius)
  // {
       /*
          Mia³em zrobic kolizje dla sfer ale narazie mi sie nie chce :D

        if(NumVertices==0 && obj->NumVertices==0)return 1;

        if(NumVertices==0 || obj->NumVertices==0)
        {
        CColisionObjects *sphere,*nosphere;
        if(NumVertices==0){sphere=this;nosphere=obj;}
        else {sphere=obj;nosphere=obj;}

        for(int a=0;a<nosphere.NumVertices;a++)
        if(abs((ModelPosition-obj->ModelPosition).length())<Radius+obj->Radius)


        vector3<> N;
        int j;
        int i;
        for(j=NumVertices-1, i=0; i<NumVertices; j=i, i++)
        {
            vector3<> E;
            E.setX(Vertices[i].x()-Vertices[j].x());
            E.setZ(Vertices[i].z()-Vertices[j].z());
            N.setX(-E.z());
            N.setZ(E.x());
            if(IsSeparating(N, Vertices, NumVertices, obj->Vertices, obj->NumVertices))
            {
                return false;
            }
        }
        for(j=obj->NumVertices-1, i=0; i<obj->NumVertices; j=i, i++)
        {
            vector3<> E;
            E.setX(obj->Vertices[i].x()-obj->Vertices[j].x());
            E.setZ(obj->Vertices[i].z()-obj->Vertices[j].z());
            N.setX(-E.z());
            N.setZ(E.x());
            if(IsSeparating(N, Vertices, NumVertices, obj->Vertices, obj->NumVertices))
            {
                return false;
            }
        }
        return true;

    }
    return false;
*/
if(abs(Vertices[0].x()-obj->Vertices[0].x())>65 || abs(Vertices[0].y()-obj->Vertices[0].y())>65)return false;
    for(int a=0;a<4;a++)
    if(Vertices[a].x()>obj->Vertices[0].x() && Vertices[a].x()<obj->Vertices[1].x())
    if(Vertices[a].z()>obj->Vertices[0].z() && Vertices[a].z()<obj->Vertices[3].z())
    return true;

    return false;
}
