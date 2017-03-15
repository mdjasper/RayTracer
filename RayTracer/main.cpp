#include "ShapeList.hpp"
#include "Camera.hpp"
#include "Plane.hpp"
#include "Sphere.h"
#include "Triangle.hpp"

#include <iostream>
#include <cmath>
#include "utils.h"
#include "Constants.h"

#include "Image.h"

#include "UnitTest.h"

int main()
{
    
//    SphereTest();
//    TriangleTest();
    
    
    int imageHeight = 500,
        imageWidth = 500;
    
//    Point cameraPosition = {0, 0, -10};
    Point cameraPosition = {0, 0, 0};
    
    Vector cameraLook = {0, 0, 1}, //direction campera is pointing {1,1,1}
    cameraUp = {0,1,0};
    
    
	//Create Scene
    
    Camera camera(1, 1, 500, 500, cameraPosition, cameraUp);
    camera.look(cameraLook);
    
    //Add shapes to the scene
    
    Sphere *ball = new Sphere({0,0,10}, 2, blue);
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(ball));
    
    Sphere *ball2 = new Sphere({2,2,12}, 0.5, {255,255,255});
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(ball2));
    
    
//    Plane *ground = new Plane(Point{0,0,0}, Vector{0,1,0}, red);
//    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(ground));
    
//    Triangle *tri = new Triangle({-1,0,5}, {1,0,5}, {0,1,3}, red);
Triangle *tri = new Triangle({-1000,-4,1000}, {1000,-4,1000}, {0,-4,1}, red);
//    Triangle *tri = new Triangle({-50,-50,10}, {50,-50,10}, {0,50,10}, red);
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(tri));
    
    

    

	//Render Scene
    std::vector<float> rgb;
    camera.render(ShapeList::getInstance(), rgb);

    //Create Image
    TGAImage *img = new TGAImage(imageWidth,imageHeight);
    
    //declare a temporary color variable
    Colour c;
    
    //Loop through image and set all pixels
    int i = 0;
    for(int x = imageHeight; x > 0; x--){
        for(int y = 0; y < imageWidth; y++){
            c.r = ValidColor(rgb[i]);
            c.g = ValidColor(rgb[i+1]);
//            if(x % 10 == 0 || y % 10 == 0){
//                c.b = 100;
//            } else {
                c.b = ValidColor(rgb[i+2]);
//            }
            c.a = 255;
            img->setPixel(c, y, x);
            i += 3;
        }
    }
    
    
    //write the image to disk
    string filename = "test.tga";
    img->WriteImage(filename);
}


