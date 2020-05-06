#pragma once
#include "game_obj_h.h"

using namespace glm;
enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NA
};


/*
    This class encapsulates collision data that I can then use for resolving what to do after the collision event
    */
class CollisionData {

public:
    vec2 differenceVector;
    Direction direction;
    GLboolean collisonHappened;
    CollisionData() { differenceVector = vec2(0, 0); direction = NA; collisonHappened = false;}
};



class CollisionManager {

public:

	//To check collisions between two objects using the concept of AABB - AABB collisions. This approach I deemed practical for my demo engine, since it's a 2D game
	static bool CheckForCollision(GameObj& obj1, GameObj& obj2) {
		return (obj1.pos.x + obj1.size.x >= obj2.pos.x && obj2.pos.x + obj2.size.x >= obj1.pos.x) 
			&& (obj2.pos.y + obj2.size.y >= obj1.pos.y && obj1.pos.y + obj1.size.y >= obj2.pos.y);
	};

    //Since the Ball isn't a box, I'm using this method for better collision resolution
    static CollisionData CheckCollisionAABBCircle(BallObj& ball, GameObj& brick) // AABB - Circle collision
    {
        // Calculating the AABB info, the center and the half-extents)
        vec2 aabb_half_extents(brick.size.x / 2, brick.size.y / 2);
        vec2 aabb_center(
            brick.pos.x + aabb_half_extents.x,
            brick.pos.y + aabb_half_extents.y
        );
        vec2 circleCenter(ball.pos + ball.radius); //The center of the circle obj
        
        // Calculating the difference vector between both the centers
        vec2 difference = circleCenter - aabb_center;

        vec2 clamped = clamp(difference, -aabb_half_extents, aabb_half_extents);
        // Adding the clamped value to the AABB_center to get the value of box which is closest to circle
        vec2 closest = aabb_center + clamped;
        difference = closest - circleCenter;

    
        CollisionData collisionData;
        
        if (length(difference) < ball.radius) {
            collisionData.collisonHappened = true;
            collisionData.direction = DirectionResolution(difference);
            collisionData.differenceVector = difference;
        }
        else {
        
            collisionData.direction = UP;
            collisionData.differenceVector = vec2(0, 0);
        }

        return collisionData;
    }


    static Direction DirectionResolution(vec2 o)
    {
        vec2 directions[] = {
            vec2(0.0f, 1.0f),	//UP
            vec2(1.0f, 0.0f),	//RIGHT
            vec2(0.0f, -1.0f),	//DOWN
            vec2(-1.0f, 0.0f)	//LEFT
        };
        GLfloat maxVal = 0.0f;
        Direction mostProbableDirection = NA;
        
        int index = 0;
        while (index < 4) {
                
            //Calculating the dot product and evaluating if it's greater than the max val recorded; if it is then 
            //updating the max val and saving the direction as the result
            
            if (GLfloat dotProduct = dot(normalize(o), directions[index]) > maxVal) {
                maxVal = dotProduct;
                mostProbableDirection = (Direction)index; //the most probable direction
            }
            index++;
        }

        return mostProbableDirection;
    }
};