#include "Vector.h"

struct vector V_new(float x, float y)
{
    struct vector vector;
    vector.x = x;
    vector.y = y;
    return vector;
}

struct vector V_diff(struct vector v1, struct vector v2)
{
    return V_new(v2.x - v1.x, v2.y - v1.y);
}

float V_dotProduct(struct vector v1, struct vector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float V_magnitude(struct vector v)
{
    return sqrt(V_dotProduct(v, v));
}

struct vector V_unit(struct vector v)
{
    if (v.x == 0 && v.y == 0)
    {
        return V_new(1, 0);
    }

    return V_new(v.x / V_magnitude(v), v.y / V_magnitude(v));
}

float V_PtPtDistance(struct vector A, struct vector P)
{
    return V_magnitude(V_diff(A, P));
}

float V_PtLineDistance(struct vector A, struct vector B, struct vector P)
{
    struct vector AB = V_diff(A, B);
    struct vector AP = V_diff(A, P);

    return sqrt(pow(V_magnitude(AP), 2) - pow(V_dotProduct(AP, V_unit(AB)), 2));
}

bool V_isInRegionII(struct vector P, struct vector A, struct vector B)
{
    struct vector AB = V_diff(A, B);
    struct vector AP = V_diff(A, P);
    struct vector BP = V_diff(B, P);
    struct vector BA = V_diff(B, A);

    if (V_dotProduct(AB, AP) < 0)
        return false;
    if (V_dotProduct(BP, BA) < 0)
        return false;
    return true;
}

float V_PtSegmentDistance(struct vector P, struct vector A, struct vector B)
{
    if (V_isInRegionII(P, A, B))
    {
        return V_PtLineDistance(A, B, P);
    }

    if (V_PtPtDistance(A, P) < V_PtPtDistance(B, P))
        return V_PtPtDistance(A, P);
    return V_PtPtDistance(B, P);
}