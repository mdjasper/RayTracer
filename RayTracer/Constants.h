//
//  Constants.h
//  RayTracer
//
//  Created by Michael Jasper on 2/18/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

//dubug

static const bool debug = true;

//colors

struct Color {
    float r, g, b;
};

static const Color red   {1.0, 0.0, 0.0};
static const Color green {0.0, 1.0, 0.0};
static const Color blue  {0.0, 0.0, 1.0};
static const Color yellow{1.0, 1.0, 0.0};
static const Color white {1.0, 1.0, 1.0};

inline std::ostream& operator<<(std::ostream &output, Color c){
    
    output << "r: " << c.r << " g: " << c.g << " b: " << c.b << std::endl;
    return output;
}


#endif /* Constants_h */
