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
#include "Plane.hpp"
#include "Sphere.h"
#include "Triangle.hpp"
#include "utils.h"
#include "Constants.h"

//Tests

#include "UnitTest.h"

using namespace tinyply;

int main()
{
    
//    BvhTest();
    
    
    //Time the performance
    auto start = chrono::steady_clock::now();
    
    int imageHeight = 100,
    imageWidth = 100;
    
    Point cameraPosition = {0,0,-1};
    
    Vector cameraLook = {0,0,1},
    cameraUp = {0,1,0};
    
    Camera camera(1, 1, imageHeight, imageWidth, cameraPosition, cameraUp);
    camera.look(cameraLook);
    
    //Create some random shapes
    srand (static_cast <unsigned> (time(0)));
    /*
    Sphere *s;
    int LO = -20;
    int HI = 20;
    Color cols[4] = {red,green,blue,yellow};
    BVH *tree = new BVH();
    
    for(int i = 0; i<10; i++){
        float x = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float y = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float z = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX)*2;
        s = new Sphere({x,y,z},r, green);
        
        tree->addShape(std::unique_ptr<Shape>(s));
    }
    
    s = new Sphere({0,0,0}, 5, red);
    tree->addShape(std::unique_ptr<Shape>(s));
    tree->balance();
    ShapeList::getInstance().addShape(std::unique_ptr<Shape>(tree));
    
    */
    
    
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
        std::vector<float> norms;
        std::vector<uint8_t> colors;
        
        std::vector<int> faces;
        std::vector<float> uvCoords;
        
        long vertexCount, normalCount, colorCount, faceCount, faceTexcoordCount, faceColorCount;
        vertexCount = normalCount = colorCount = faceCount = faceTexcoordCount = faceColorCount = 0;
        
        // The count returns the number of instances of the property group. The vectors
        // above will be resized into a multiple of the property group size as
        // they are "flattened"... i.e. verts = {x, y, z, x, y, z, ...}
        vertexCount = file.request_properties_from_element("vertex", { "x", "y", "z" }, verts);
        normalCount = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }, norms);
        colorCount = file.request_properties_from_element("vertex", { "red", "green", "blue", "alpha" }, colors);
        
        // For properties that are list types, it is possibly to specify the expected count (ideal if a
        // consumer of this library knows the layout of their format a-priori). Otherwise, tinyply
        // defers allocation of memory until the first instance of the property has been found
        // as implemented in file.read(ss)
        faceCount = file.request_properties_from_element("face", { "vertex_indices" }, faces, 3);
        faceTexcoordCount = file.request_properties_from_element("face", { "texcoord" }, uvCoords, 6);
        
        // Now populate the vectors...
        
        file.read(ss);
        
        
        // Good place to put a breakpoint!
        
        std::cout << "\tRead " << verts.size() << " total vertices (" << vertexCount << " properties)." << std::endl;
//        std::cout << "\tRead " << norms.size() << " total normals (" << normalCount << " properties)." << std::endl;
//        std::cout << "\tRead " << colors.size() << " total vertex colors (" << colorCount << " properties)." << std::endl;
        std::cout << "\tRead " << faces.size() << " total faces (triangles) (" << faceCount << " properties)." << std::endl;
//        std::cout << "\tRead " << uvCoords.size() << " total texcoords (" << faceTexcoordCount << " properties)." << std::endl;
        

        BVH *tree = new BVH();
        
        Triangle *t;
        float s = 5;
        for(int i = 0; i < faces.size(); i += 3){
            
            Point a{ verts[faces[i + 0] + 0]*s, verts[faces[i + 0] + 1]*s, verts[faces[i + 0] + 2]*s };
            Point b{ verts[faces[i + 1] + 0]*s, verts[faces[i + 1] + 1]*s, verts[faces[i + 1] + 2]*s };
            Point c{ verts[faces[i + 2] + 0]*s, verts[faces[i + 2] + 1]*s, verts[faces[i + 2] + 2]*s };
            
            std::cout << a;
            std::cout << b;
            std::cout << c;
            
            std::cout << std::endl;
            
            t = new Triangle(a,b,c, green);
            
            tree->addShape(std::unique_ptr<Shape>(t));
        }
        
        tree->balance();
        
        ShapeList::getInstance().addShape(std::unique_ptr<Shape>(tree));
        
        
    
    }
    
    catch (const std::exception & e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
     
    
    

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
    
    //end timing
    auto end = chrono::steady_clock::now();
    auto time_diff = end-start;
    std::cout << "Run Time: " << chrono::duration <double, milli> (time_diff).count() << " ms" << std::endl;
}
