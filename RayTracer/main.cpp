//STD

#include <iostream>
#include <cmath>
#include <chrono>
#include <cstdlib>

//3rd party

#include "Image.h"
#include "tinyply.h"

//Ray Tracer Classes

#include "ShapeList.hpp"
#include "BVH.h"
#include "Camera.hpp"
//#include "Plane.hpp"
#include "Sphere.h"
#include "Triangle.hpp"
#include "utils.h"
#include "Constants.h"

//Tests

#include "UnitTest.h"

using namespace tinyply;

int main(){
    
    TriangleTest();
    
    //Time the performance
    auto start = chrono::steady_clock::now();
    
    int imageHeight = 400,
    imageWidth = 400;
    
    Point cameraPosition = {0,2,5};
    
    Vector cameraLook = {0,0,-1},
    cameraUp = {0,1,0};
    
    Camera camera(1, 1, imageHeight, imageWidth, cameraPosition, cameraUp);
    camera.look(cameraLook);
    
    
    try{
        std::ifstream ss("/Users/mdjasper/Sites/sandbox/graphics2/RayTracer/RayTracer/bun_zipper_res4.ply", std::ios::binary);
        
        PlyFile file(ss);
        
        for (auto e : file.get_elements())
        {
            std::cout << "element - " << e.name << " (" << e.size << ")" << std::endl;
            for (auto p : e.properties)
            {
                std::cout << "\tproperty - " << p.name << " (" << PropertyTable[p.propertyType].str << ")" << std::endl;
            }
        }
        std::cout << std::endl;
        
        for (auto c : file.comments)
        {
            std::cout << "Comment: " << c << std::endl;
        }
        
        // Define containers to hold the extracted data. The type must match
        // the property type given in the header. Tinyply will interally allocate the
        // the appropriate amount of memory.
        std::vector<float> verts;
//        std::vector<float> norms;
//        std::vector<uint8_t> colors;
        
        std::vector<int> faces;
        std::vector<float> uvCoords;
        
        long vertexCount, normalCount, colorCount, faceCount, faceTexcoordCount, faceColorCount;
        vertexCount = normalCount = colorCount = faceCount = faceTexcoordCount = faceColorCount = 0;
        
        // The count returns the number of instances of the property group. The vectors
        // above will be resized into a multiple of the property group size as
        // they are "flattened"... i.e. verts = {x, y, z, x, y, z, ...}
        vertexCount = file.request_properties_from_element("vertex", { "x", "y", "z" }, verts);
//        normalCount = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }, norms);
//        colorCount = file.request_properties_from_element("vertex", { "red", "green", "blue", "alpha" }, colors);
        
        // For properties that are list types, it is possibly to specify the expected count (ideal if a
        // consumer of this library knows the layout of their format a-priori). Otherwise, tinyply
        // defers allocation of memory until the first instance of the property has been found
        // as implemented in file.read(ss)
        faceCount = file.request_properties_from_element("face", { "vertex_indices" }, faces, 3);
        faceTexcoordCount = file.request_properties_from_element("face", { "texcoord" }, uvCoords, 6);
        
        // Now populate the vectors...
        
        file.read(ss);
        
        
        std::cout << "\tRead " << verts.size() << " total vertices (" << vertexCount << " properties)." << std::endl;
        std::cout << "\tRead " << faces.size() << " total faces (triangles) (" << faceCount << " properties)." << std::endl;

        

        BVH *tree = new BVH(100);
        
        //Create Points from Vertices
        vector<Point> points;
        float scale = 20;
        for(int i = 0; i < verts.size(); i += 3){
            points.push_back({verts[i] * scale, verts[i+1] * scale, verts[i+2] * scale});
        }
        
        Triangle *t;
        Triangle *tp;
        for(int i = 0; i < faces.size(); i += 3){
            //std::cout << points[faces[i]] << points[faces[i+1]] << points[faces[i+2]] << std::endl;
            t = new Triangle(
                             points[ faces[i] ],
                             points[ faces[i+1] ],
                             points[ faces[i+2] ],
                             green,
                             true
                    );
            
            /*tp = new Triangle(
                             points[ faces[i+2] ],
                             points[ faces[i] ],
                             points[ faces[i+1] ],
                             green,
                              true
                             );*/
            
            tree->addShape(std::unique_ptr<Shape>(t));
//            tree->addShape(std::unique_ptr<Shape>(tp));
        }
        
        tree->balance();
        
        ShapeList::getInstance().addShape(std::unique_ptr<Shape>(tree));
        
    } catch (const std::exception & e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    
//    Triangle * ground0 = new Triangle({0,0,7},{100,0,-100},{-100,0,-100},blue);
//    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(ground0));
    
    Sphere * redBall = new Sphere({0,3,-5}, 2, red);
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(redBall));
    
    
    
    
    
    std::cout << "Tree balanced" << std::endl << "Rendering" << std::endl;
    

	//Render Scene
    std::vector<Pixel> rgb;
    camera.render(ShapeList::getInstance(), rgb);

    //Create Image
    TGAImage *img = new TGAImage(imageWidth,imageHeight);
    
    //declare a temporary color variable
    Colour c;
    
    //Loop through image and set all pixels
    for(Pixel p : rgb){
//        std::cout << p << std::endl;
        c.r = ValidColor(p.r * 255);
        c.g = ValidColor(p.g * 255);
        c.b = ValidColor(p.b * 255);
        c.a = 255;
        img->setPixel(c, p.x, p.y);
    }
    
    //write the image to disk
    string filename = "test.tga";
    img->WriteImage(filename);
    
    //end timing
    auto end = chrono::steady_clock::now();
    auto time_diff = end-start;
    std::cout << "Run Time: " << chrono::duration <double, milli> (time_diff).count() << " ms" << std::endl;
}
