#include <stdbool.h>
#include <math.h>

struct vector
{
    float x;
    float y;
};

struct vector V_new(float x, float y);

struct vector V_diff(struct vector v1, struct vector v2);

struct vector V_unit(struct vector v);

float V_dotProduct(struct vector v1, struct vector v2);

float V_magnitude(struct vector v);

float V_PtPtDistance(struct vector A, struct vector P);

float V_PtLineDistance(struct vector A, struct vector B, struct vector P);

bool V_isInRegionII(struct vector P, struct vector A, struct vector B);

float V_PtSegmentDistance(struct vector P, struct vector A, struct vector B);