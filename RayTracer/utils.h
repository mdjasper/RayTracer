//
//  utils.h
//  RayTracer
//
//  Created by Michael Jasper on 2/18/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <iostream>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

static int ValidColor(int c){
//    std::cout << c << std::endl;
//    int color = c <= 0 ? 0 : c;
//    color = color >= 255 ? 255 : color;
//    return color;
    return c;
}

#endif /* utils_h */
