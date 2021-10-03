#include "MyAgent.h"
#include "MyGame.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include "mathtool/Box.h"
#include "mathtool/Vector.h"

namespace GMUCS425
{
	void MyAgent::handle_event(SDL_Event &e)
	{
		if (this->movable)
		{
			//do nothing now...
		}
	}

	//update this agent's motion, looks, sound, etc
	void MyAgent::update()
	{
		//do nothing by default...
	}

	void MyAgent::display()
	{
		if (!this->visible)
			return; //not visible...
		//setup positions and ask sprite to draw something
		this->sprite->display(x, y, scale, degree);
	}

	//show HUD (heads-up display) or status bar
	void MyAgent::draw_HUD()
	{
		//draw nothing by defaut, your task to display the location of an agent
		//on the upper left corner
		//read http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php
	}

	bool MyAgent::collide(MyAgent *other)
	{
		mathtool::Box2d box1, box2;
		box1.x = this->x;
		box1.y = this->y;
		box1.width = this->sprite->getWidth(scale);
		box1.height = this->sprite->getHeight(scale);

		box2.x = other->x;
		box2.y = other->y;
		box2.width = other->sprite->getWidth(other->scale);
		box2.height = other->sprite->getHeight(other->scale);

		return box1.intersect(box2);
	}

	void MyAgent::draw_bounding_box()
	{
		float my_W = this->sprite->getWidth(scale);
		float my_H = this->sprite->getHeight(scale);

		SDL_Rect box; //create a rect
		box.x = x;		//controls the rect's x coordinate
		box.y = y;		// controls the rect's y coordinte
		box.w = my_W; // controls the width of the rect
		box.h = my_H; // controls the height of the rect

		SDL_Renderer *renderer = getMyGame()->getRenderer();
		SDL_SetRenderDrawColor(renderer, 255, 100, 0, 100);
		//SDL_RenderDrawPoint(renderer, x, y);
		SDL_RenderDrawRect(renderer, &box);

		box.w /= 10;
		box.h = box.w;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderFillRect(renderer, &box);
	}

	void MyZombieAgent::display()
	{
		if (!this->visible)
			return; //not visible...
		//setup positions and ask sprite to draw something
		this->sprite->display(x, y, scale, degree, NULL, this->left ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
		draw_bounding_box();
	}

	void MyZombieAgent::update()
	{
		if (!this->collision)
		{
			if (collision_free_timer >= 0)
				this->collision_free_timer--;
			else
				collide_with = NULL; //no collision
		}

		this->collision = false;

		if (orig_x == INT_MAX)
			orig_x = x;
		if (left)
			x -= 2;
		else
			x += 2;
		if (x < orig_x - 100)
			left = false;
		if (x > orig_x + 100)
			left = true;
	}

	void MyZombieAgent::handle_event(SDL_Event &e)
	{
		//return;
		if (this->collision && collide_with != NULL)
		{
			//std::cout<<"already in collision with "<<collide_with<<std::endl;

			return;
		}

		if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 1)
			{
				if (e.user.data1 == this || e.user.data2 == this)
				{
					MyAgent *other = (MyAgent *)((e.user.data1 != this) ? e.user.data1 : e.user.data2);

					if (other != collide_with)
					{
						collide_with = other;
						left = !left;
					}
					this->collision_free_timer = 10;
					this->collision = true;
				}
				//else collide_with=NULL; //no collision
			}
		}
	}

	// CUSTOM CLOUD AGENT
	void MyCloudAgent::display()
	{
		if (!this->visible)
			return; //not visible...
		//setup positions and ask sprite to draw something
		this->sprite->display(x, y, scale, degree, NULL, this->up ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
		draw_bounding_box();
	}

	void MyCloudAgent::update()
	{
		if (!this->collision)
		{
			if (collision_free_timer >= 0)
				this->collision_free_timer--;
			else
				collide_with = NULL; //no collision
		}

		this->collision = false;

		if (orig_y == INT_MAX)
			orig_y = y;
		if (up)
			y -= 2;
		else
			y += 2;
		if (y < orig_y - 100)
			up = false;
		if (y > orig_y + 100)
			up = true;
	}

	void MyCloudAgent::handle_event(SDL_Event &e)
	{
		//return;
		if (this->collision && collide_with != NULL)
		{
			//std::cout<<"already in collision with "<<collide_with<<std::endl;

			return;
		}

		if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 1)
			{
				if (e.user.data1 == this || e.user.data2 == this)
				{
					MyAgent *other = (MyAgent *)((e.user.data1 != this) ? e.user.data1 : e.user.data2);

					if (other != collide_with)
					{
						collide_with = other;
						up = !up;
					}
					this->collision_free_timer = 10;
					this->collision = true;
				}
				//else collide_with=NULL; //no collision
			}
		}
	}

	void MyChickenAgent::display()
	{
		//MyAgent::display();
		if (!this->visible)
			return; //not visible...
		//setup positions and ask sprite to draw something
		this->sprite->display(x, y, scale, degree, NULL, this->ccw ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		draw_bounding_box();
	}

	void MyChickenAgent::handle_event(SDL_Event &e)
	{
		//std::cout<<"--------------------------------------"<<std::endl;
		if (this->collision && collide_with != NULL)
		{
			//std::cout<<"already in collision with "<<collide_with<<std::endl;

			return;
		}
		//else
		//  std::cout<<"NO in collision: this->collision="<<this->collision<<" with "<<collide_with<<std::endl;

		if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 1)
			{
				if (e.user.data1 == this || e.user.data2 == this)
				{
					MyAgent *other = (MyAgent *)((e.user.data1 != this) ? e.user.data1 : e.user.data2);
					if (other != this->collide_with)
					{
						//std::cout<<"changed to: "<<other<<" from " << collide_with<<std::endl;
						collide_with = other;
						ccw = !ccw;
					}
					this->collision_free_timer = 10;
					this->collision = true;
				} //end if
			}		//end if
		}			//end if
	}

	void MyChickenAgent::update(MyAgent *player, std::list<MyChickenAgent *> enemies)
	{
		//std::cout<<"this->collision_free_timer="<<this->collision_free_timer<<std::endl;
		using namespace mathtool;

		if (!this->collision)
		{
			if (collision_free_timer >= 0)
				this->collision_free_timer--;
			else
				collide_with = NULL; //no collision
		}
		this->collision = false;

		Vector2d position = Vector2d(x, y);
		// do something on the position of the player to the current chicken agent.

		float distance = (position - Vector2d(player->getX(), player->getY())).normsqr();
		if (distance < (6400))
		{
			// std::cout << "enemy is close!" << distance << "\n";
		}

		Vector2d velocity = Vector2d(0, 0);
		// do something on the position of enemies
		for (MyChickenAgent *enemy : enemies)
		{
			Vector2d diff = Vector2d(enemy->x, enemy->y) - position;
			float distance_sqr = diff.normsqr();
			if (distance_sqr < innerRadius * innerRadius)
			{
				velocity = velocity - diff;
			}
			else if (distance_sqr > outerRadius * outerRadius)
			{
				velocity = velocity + diff / distance_sqr;
			}
		}

		velocity = velocity.normalize();

		x += velocity[0];
		y += velocity[1];

		// std::cout << m_enemies.size() << "\n";

		// if (radius == FLT_MAX)
		// {
		// 	radius = 30;
		// 	center_x = x;
		// 	center_y = y - radius;
		// }

		// float angle = (ccw) ? 0.1 : -0.1;
		// float cos_t = cos(angle);
		// float sin_t = sin(angle);

		// float dx = x - center_x;
		// float dy = y - center_y;
		// float d = sqrt(dx * dx + dy * dy);
		// dx = dx / d;
		// dy = dy / d;

		// x = (int)((cos_t * dx - sin_t * dy) * radius) + center_x;
		// y = (int)((sin_t * dx + cos_t * dy) * radius) + center_y;
	}

	void MyDragonAgent::handle_event(SDL_Event &e)
	{
		const int delta = 5;

		if (e.type == SDL_USEREVENT)
		{
			if (e.user.code == 1)
			{
				if (e.user.data1 == this || e.user.data2 == this)
				{
					// this->collision = true;
					// this->collide_with = (MyAgent *)((e.user.data1 != this) ? e.user.data1 : e.user.data2);
					// if (IsType<MyZombieAgent>(collide_with) || IsType<MyChickenAgent>(collide_with))
					// {
					// 	health -= 1;
					// }
				}
			}
		}

		//if(this->collision) return;
		if (e.type == SDL_KEYDOWN)
		{
			dx = dy = 0;
			const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
			if (currentKeyStates[SDL_SCANCODE_UP])
			{
				dy = -delta;
			}
			else if (currentKeyStates[SDL_SCANCODE_DOWN])
			{
				dy = delta;
			}
			else if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				left = true;
				dx = -delta;
			}
			else if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				left = false;
				dx = delta;
			}

			x += dx;
			y += dy;
		}
	}

	void MyDragonAgent::update()
	{
		// if (this->collision && this->collide_with)
		// {
		// 	int vx = this->collide_with->getX() - x;
		// 	int vy = this->collide_with->getY() - y;
		// 	if ((dx == 0 && dy == 0) || (vx * dx + vy * dy) <= 0)
		// 	{
		// 		float d = 1.0 / sqrt((vx * vx) + (vy * vy));
		// 		dx = vx * d;
		// 		dy = vy * d;
		// 	}

		// 	x -= dx;
		// 	y -= dy;
		// 	dx /= 2;
		// 	dy /= 2;
		// }

		// this->collision = false;
	}

	void MyDragonAgent::display()
	{
		//MyAgent::display();
		if (!this->visible)
			return; //not visible...
		//setup positions and ask sprite to draw something
		this->sprite->display(x, y, scale, degree, NULL, this->left ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
		draw_bounding_box();
	}

	int MyDragonAgent::getHealth()
	{
		return health;
	}

	void MyDragonAgent::draw_HUD()
	{
		std::stringstream ss;
		ss << "x=" << x << " y=" << y << " health=" << health;
		SDL_Renderer *renderer = getMyGame()->getRenderer();
		static TTF_Font *font = NULL;

		if (font == NULL)
		{
			font = TTF_OpenFont("fonts/Demo_ConeriaScript.ttf", 24); //this opens a font style and sets a size
			if (font == NULL)
			{
				std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return;
			}
		}

		SDL_Color color = {200, 100, 0};																									 // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
		SDL_Surface *surfaceMessage = TTF_RenderText_Solid(font, ss.str().c_str(), color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
		SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);		 //now you can convert it into a texture

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 10;	 //controls the rect's x coordinate
		Message_rect.y = 50;	 // controls the rect's y coordinte
		Message_rect.w = 150;	 // controls the width of the rect
		Message_rect.h = 30;	 // controls the height of the rect

		//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

		//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
		SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

		//Don't forget too free your surface and texture
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
	}

} //end namespace
