#pragma once

#include "MySprite.h"
#include "float.h"
#include "mathtool/Box.h"
#include "mathtool/Vector.h"

namespace GMUCS425
{
	//this defines the transform of the agent
	class MyAgent
	{
	public:
		//movable: true if this agent can move
		//collision: true if this agent can collision with other agents
		MyAgent(bool movable = true, bool collision = true)
		{
			x = y = degree = 0;
			scale = 1;
			visible = true;
			sprite = NULL;
			this->movable = movable;
			this->collision = collision;
		}

		//react to the events
		virtual void handle_event(SDL_Event &e);

		//update this agent's motion, looks, sound, etc
		virtual void update();

		//render this agent
		virtual void display();

		//show HUD (heads-up display) or status bar
		virtual void draw_HUD();

		//transforms
		void rotate(float degree) { this->degree += degree; }
		void rotateTo(float degree) { this->degree = degree; }

		void tranlate(float x, float y)
		{
			this->x += x;
			this->y += y;
		}
		void tranlateTo(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void scaleTo(float s) { this->scale = s; }

		//display
		void show() { visible = true; }
		void hide() { visible = false; }

		//sprite, aka costume
		void setSprite(MySprite *sprite) { this->sprite = sprite; }

		//motion/animation
		//void glide(float x, float y, float seconds);

		bool collide(MyAgent *other);

		//ACCESS METHODS
		bool is_movable() const { return movable; }
		bool is_visible() const { return visible; }

		float getX() const { return x; }
		float getY() const { return y; }
		float getAngle() const { return degree; }
		float getScale() const { return scale; }

	protected:
		void draw_bounding_box();

		//current position and orientations
		float x, y;
		float degree; //rotation
		float scale;

		bool visible;
		bool movable;
		bool collision;

		MySprite *sprite; //current sprite
											//it is possible that you can have more than one sprites
											//vector<MySprite *> sprites; //the sprites
	};

	class MyZombieAgent : public MyAgent
	{
	public:
		MyZombieAgent(bool movable = true, bool collision = true)
				: MyAgent(movable, collision)
		{
			orig_x = INT_MAX;
			left = true;
			collide_with = NULL;
		}
		virtual void update();
		virtual void display();
		virtual void handle_event(SDL_Event &e);

	private:
		int orig_x;
		bool left;
		MyAgent *collide_with;
		int collision_free_timer = 10;
	};

	class MyCloudAgent : public MyAgent
	{
	public:
		MyCloudAgent(bool movable = true, bool collision = true)
				: MyAgent(movable, collision)
		{
			orig_y = INT_MAX;
			up = true;
			collide_with = NULL;
		}
		virtual void update();
		virtual void display();
		virtual void handle_event(SDL_Event &e);

	private:
		int orig_y;
		bool up;
		MyAgent *collide_with;
		int collision_free_timer = 10;
	};

	class MyChickenAgent : public MyAgent
	{
	public:
		MyChickenAgent(float innerRadius, float outerRadius, bool movable = true, bool collision = true) : MyAgent(movable, collision)
		{
			this->innerRadius = innerRadius;
			this->outerRadius = outerRadius;
			radius = FLT_MAX;
			center_x = center_y = INT_MAX;
			ccw = false;
			collide_with = NULL;
			velocity = mathtool::Vector2d(0, 0);
			collision_free_timer = collision_free_time;
		}
		virtual void update(MyAgent *player, std::list<MyAgent *> agents);
		virtual void display();
		virtual void handle_event(SDL_Event &e);

	private:
		mathtool::Vector2d velocity;
		float radius, innerRadius, outerRadius;
		int center_x, center_y;
		bool ccw;
		MyAgent *collide_with;
		int collision_free_timer;
		const int collision_free_time = 10;
	};

	class MyDragonAgent : public MyAgent
	{
	public:
		MyDragonAgent(bool movable = true, bool collision = true) : MyAgent(movable, collision)
		{
			health = 100;
			dx = dy = 0;
			collide_with = NULL;
			left = false;
		}
		virtual void handle_event(SDL_Event &e);
		virtual void update();
		virtual void draw_HUD();
		//render this agent
		virtual void display();
		int getHealth();

	private:
		int health;
		int dx, dy;
		bool left;
		MyAgent *collide_with;
	};

} //end namespace
