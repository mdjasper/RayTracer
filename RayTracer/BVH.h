//
//  AccelerationStructure.h
//  RayTracer
//
//  Created by Michael Jasper on 3/16/17.
//  Copyright © 2017 Michael Jasper. All rights reserved.
//

#include <vector>
#include "Shape.hpp"
#include "BBox.hpp"

#ifndef BVH_h
#define BVH_h


struct Node{
    Node(): left(), right(), box(), isLeaf(false) {};
    Node *left;
    Node *right;
    BBox box{};
    bool isLeaf;
    std::vector<std::unique_ptr<Shape>> list;
    std::unique_ptr<HitRecord> hit(Ray r){
        std::unique_ptr<HitRecord> hit = nullptr;
        if(isLeaf){
            //is a leaf node, find the shape in list
            for (auto&& s : list){
                auto cur = s->hit(r);
                if (hit){
                    if (cur){
                        if (cur->t < hit->t){
                            std::swap(hit, cur);
                        }
                    }
                }
                else{
                    std::swap(hit, cur);
                }
            }
            return hit;
        } else {
            //not a leaf node, recursivly search for shape in left and right
            if(intersect(r, left->box)){
                //look in the left box
                hit = left->hit(r);
            }
            
            if(intersect(r, right->box) || hit == nullptr){
                //look in the right box
                hit = right->hit(r);
            }
        }
        return hit;
    }
    
    bool hitP(Ray r){
        bool hit = false;
        if(isLeaf){
            //is a leaf node, find the shape in list
            for (auto&& s : list)
            {
                if (s->hitP(r)){
                    return true;
                }
            }
            return false;
        } else {
            //not a leaf node, recursivly search for shape in left and right
            if(intersect(r, left->box)){
                //look in the left box
                hit = left->hitP(r);
            }
            
            if(intersect(r, right->box)){
                //look in the right box
                hit = right->hitP(r);
            }
        }
        return hit;
    }
    void balance(){
        //Get center X for all shapes in this node
        //And union BBoxs of all shapes in this node
        float center;
        for(auto &s : list){
            auto sbox = s->getBoundingBox();
            center += (sbox.x.min + sbox.x.max) / 2;
            box = union_(box, sbox);
        }
        center /= list.size();
        
        //Divide shapes into left or right IF list.size > 4
        if(list.size() >800){
            left = new Node();
            right = new Node();
        
            for(auto &s : list){
                auto sbox = s->getBoundingBox();
                float sCenter = (sbox.x.min + sbox.x.max) / 2;
                if(sbox.x.min < center){
                    right->list.push_back(std::move(s));
                } else {
                    left->list.push_back(std::move(s));
                }
            }
            list.clear();
            left->balance();
            right->balance();
        } else {
            isLeaf = true;
        }
    }
};

class BVH : public Shape{
public:
    BVH(){
        root = new Node{};
    };
    virtual ~BVH(){}
    BBox getBoundingBox() const override{
        return root->box;
    };
    void addShape(std::unique_ptr<Shape> s){
        root->list.push_back(std::move(s));
    };
    
    void balance(){
        root->balance();
    }
private:
    std::unique_ptr<HitRecord> intersect(Ray r) const override {
        return root->hit(r);
    };
    bool intersectP(Ray r) const override {
        return root->hitP(r);
    };
    Node *root;
};

#endif /* AccelerationStructure_h */
