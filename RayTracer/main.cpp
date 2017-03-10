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

int main()
{
    
    int imageHeight = 500,
        imageWidth = 500;
    
    Point cameraPosition = {0,-2,0};
    
    Vector cameraLook = {1,1,1}, //direction campera is pointing
    cameraUp = {0,-1,0}; //y-axis points up
    
    
	//Create Scene
    
    Camera camera(imageHeight, imageWidth, imageHeight, imageWidth, cameraPosition, cameraUp);
    camera.look(cameraLook);
    
    //Add shapes to the scene
    
//    Plane (point, vector, color)
    Plane ground({1, 1, 1}, {1, 0, 0}, green);
//    Sphere (point, radius, color);
//    Triangle tri({100,100,100}, {105,100,110}, {100,105,110});
    
    Sphere ball({0,5,0}, 0.5, blue);
    Sphere ball2({1,5,-1}, 3, red);
    
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(&ground));
//    scene.addShape(std::unique_ptr<Shape>(&tri));
    
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(&ball));
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(&ball2));
    

    

	//Render Scene
    std::vector<float> rgb;
    camera.render(ShapeList::getInstance(), rgb);

    //Create Image
    TGAImage *img = new TGAImage(imageWidth,imageHeight);
    
    //declare a temporary color variable
    Colour c;
    
    //Loop through image and set all pixels
    int i = 0;
    for(int x=imageHeight; x>0; x--){
        for(int y=imageWidth; y>0; y--){
            c.r = ValidColor(rgb[i]);
            c.g = ValidColor(rgb[i+1]);
            c.b = ValidColor(rgb[i+2]);
            c.a = 255;
            img->setPixel(c,x,y);
            i += 3;
        }
    }
    
    //write the image to disk
    string filename = "test.tga";
    img->WriteImage(filename);
}


