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
    int r, g, b;
};

static const Color red   {255,    0,      0   };
static const Color green {0,      255,    0   };
static const Color blue  {0,      0,      255 };
static const Color yellow{255,    255,    0   };




#endif /* Constants_h */
