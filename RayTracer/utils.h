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

static inline int ValidColor(int c){
    if(c > 255){
        return 255;
    } else if(c < 0) {
        return 0;
    }
    return c;
}

#endif /* utils_h */
