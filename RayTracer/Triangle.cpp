//
//  Triangle.cpp
//  RayTracer
//
//  Created by Michael Jasper on 2/27/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#include "Triangle.hpp"
#include "utils.h"
#include <iostream>

#define T_EPSILON  0.1
//#define T_EPSILON2 0.1

#define E_EPSILON  0.001

Triangle::~Triangle(){}

BBox Triangle::getBoundingBox() const{
    
    Extent x,y,z;
    
    x.max = x.max > a.x ? x.max : a.x;
    x.max = x.max > b.x ? x.max : b.x;
    x.max = x.max > c.x ? x.max : c.x;
    
    y.max = y.max > a.y ? y.max : a.y;
    y.max = y.max > b.y ? y.max : b.y;
    y.max = y.max > c.y ? y.max : c.y;
    
    z.max = z.max > a.z ? z.max : a.z;
    z.max = z.max > b.z ? z.max : b.z;
    z.max = z.max > c.z ? z.max : c.z;
    
    x.min = x.min > a.x ? x.min : a.x;
    x.min = x.min < b.x ? x.min : b.x;
    x.min = x.min < c.x ? x.min : c.x;
    
    y.min = y.min > a.y ? y.min : a.y;
    y.min = y.min < b.y ? y.min : b.y;
    y.min = y.min < c.y ? y.min : c.y;
    
    z.min = z.min > a.z ? z.min : a.z;
    z.min = z.min < b.z ? z.min : b.z;
    z.min = z.min < c.z ? z.min : c.z;
    
    BBox box;
    box.x = x;
    box.y = y;
    box.z = z;
    
    return box;
}


bool Triangle::intersectP(Ray r) const{
    
    double long tval;
    
    double long A = a.x - b.x;
    double long B = a.y - b.y;
    double long C = a.z - b.z;
    
    double long D = a.x - c.x;
    double long E = a.y - c.y;
    double long F = a.z - c.z;
    
    double long G = r.d.x;
    double long H = r.d.y;
    double long I = r.d.z;
    
    double long J = a.x - r.o.x;
    double long K = a.y - r.o.y;
    double long L = a.z - r.o.z;
    
    double long EIHF = E*I - H*F;
    double long GFDI = G*F - D*I;
    double long DHEG = D*H - E*G;
    
    double long denom = 1/(A*EIHF + B*GFDI + C*DHEG);
    
    double long beta = (J*EIHF + K*GFDI + L*DHEG) * denom;
    
    if (beta <= 0.0f + E_EPSILON || beta >= 1.0f + E_EPSILON) return false;
    
    double long AKJB = A*K - J*B;
    double long JCAL = J*C - A*L;
    double long BLKC = B*L - K*C;
    
    double long gamma = (I*AKJB + H*JCAL + G*BLKC) * denom;
    if(gamma <= 0.0f + E_EPSILON  || beta + gamma >= 1.0f + E_EPSILON ) return false;
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) * denom;
    if(std::abs(tval) < T_EPSILON) return false;
    
    //if(std::abs(tval) < T_EPSILON2) std::cout << tval << std::endl;
    
    return true;
}


std::unique_ptr<HitRecord> Triangle::intersect(Ray r) const{
    double long tval;
    
    double long A = a.x - b.x;
    double long B = a.y - b.y;
    double long C = a.z - b.z;
    
    double long D = a.x - c.x;
    double long E = a.y - c.y;
    double long F = a.z - c.z;
    
    double long G = r.d.x;
    double long H = r.d.y;
    double long I = r.d.z;
    
    double long J = a.x - r.o.x;
    double long K = a.y - r.o.y;
    double long L = a.z - r.o.z;
    
    double long EIHF = E*I - H*F;
    double long GFDI = G*F - D*I;
    double long DHEG = D*H - E*G;
    
    double long denom = 1/(A*EIHF + B*GFDI + C*DHEG);
    
    double long beta = (J*EIHF + K*GFDI + L*DHEG) * denom;
    
    if (beta <= 0.0f + E_EPSILON || beta >= 1.0f + E_EPSILON) return nullptr;
    
    double long AKJB = A*K - J*B;
    double long JCAL = J*C - A*L;
    double long BLKC = B*L - K*C;
    
    double long gamma = (I*AKJB + H*JCAL + G*BLKC) * denom;
    if(gamma <= 0.0f + E_EPSILON || beta + gamma >= 1.0f + E_EPSILON) return nullptr;
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) * denom;
    
    Vector normal = cross((b-a), (c-a));
    return make_unique<HitRecord>(tval, normal, color, isGlass);
}
