//
//  Textures.h
//  RayTracer
//
//  Created by Michael Jasper on 3/14/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#ifndef Textures_h
#define Textures_h

/*
 
 Texture Concept:
    
 2d: object with operator()(float u , floatV) -> T
 3d: object with operator()(float x,y,z) -> T
 
 */

template<typename T>
struct ConstantTexture{
public:
    ConstantTexture(T t) t(t){}
    T operator()(float u, float v){return T};
    T operator()(float x, float y, float z){return T};
private:
    const T t;
};

template<typename T>
ConstantTexture<T> makeConstantTexture(T t){
    return ConstantTexture<T>(t);
}

//auto myConstTex = ConstantTexture(Color{r,g,b});

template<typename A, typename B>
class AdditiveTexture{
public:
    AdditiveTexture(A a, B b)a(a), b(b){}
    T operator()(float u, float v){return a(u,v) + b(u,v)};
    T operator()(float x, float y, float z){return a(x,y,z) + b(x,y,z)};
private:
    const A a;
    const B b;
};

template<typename A, typename B>
AdditiveTexture<A,B> makeAdditiveTexture(A a, B b){
    return Additivetexture<A,B>(a,b);
}

//auto myAddTex = makeAdditiveTexture( makeConstantTexture(2.0), makeConstantTexture(1.0);


template<typename A, typename B>
class ScaleTexture{
public:
    ScaleTexture(A a, B b)a(a), b(b){}
    T operator()(float u, float v){return a(u,v) * b(u,v)};
    T operator()(float x, float y, float z){return a(x,y,z) * b(x,y,z)};
private:
    const A a;
    const B b;
};

template<typename A, typename B>
ScaleTexture<A,B> makeScaleTexture(A a, B b){
    return Additivetexture<A,B>(a,b);
}

//auto myScaleTex = makeScaleTexture( makeConstantTexture(2.0), makeConstantTexture(1.0);


/*
    Mix Texture
 */
template<typename A, typename B, typename C>
class MixTexture{
public:
    MixTexture(A a, B b, C c)a(a), b(b) c(c){}
    T operator()(float u, float v){return a(u,v) * (1-c(u,v)) + b(u,v) * c(u,v)};
    T operator()(float x, float y, float z){return a(x,y,z) * (1-c(x,y,z)) + b(x,y,z) * c(x,y,z)};
private:
    const A a;
    const B b;
    const C c;
};

template<typename A, typename B, typename C>
MixTexture<A,B> makeMixTexture(A a, B b, C c){
    return Additivetexture<A,B,C>(a,b,c);
}


/*
    Bilinear Mix Texture
 */


template<typename A, typename B, typename C, typename D>
class BilinearTexture{
public:
    MixTexture(A a, B b, C c, D c)a(a), b(b) c(c), d(d){}
    T operator()(float u, float v){
        auto s = a * (1 - u) + b * u;
        auto t = c * (1 - u) + d * u;
        auto s * (1 - v) + t * v;
    };
    T operator()(float x, float y, float z){return a(x,y,z) * (1-c(x,y,z)) + b(x,y,z) * c(x,y,z)};
private:
    const A a;
    const B b;
    const C c;
    const D d;
};

template<typename A, typename B, typename C, typename D>
MixTexture<A,B> makeMixTexture(A a, B b, C c, D d){
    return Additivetexture<A,B,C,D>(a,b,c,d);
}


//auto myAddTex = makeAdditiveTexture( makeConstantTexture(2.0), makeConstantTexture(1.0);

/*
    Image Texture
 */

class ImageTexture{
public:
    auto operator()(float u, float v) const {
        //look up (u,v) pixel in image and return
        return 1.0;
    }
    auto operator()(float x, float y, float z) const {
        //return 0 so things work
        return 0.0;
    }
};

/*
    Noise
 */

//class NoiseTexture{
    //do some perlin noise thing
//};

/*
    Turbulence
 */

class TurbulenceTexture{
    auto operator()(float u, float v){
        auto noise = NoiseTexture();
        auto cur = noise(u,v);
        for(int i = 2; i < 8; ++i){
            cur += noise(u*i, v*i) / i;
        }
        return cur;
    }
};


#endif /* Textures_h */
