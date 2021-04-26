#include "Collider.h"

Collider::Collider(SDL_Rect rectangle,Type type, Module* listener):rect(rectangle),type(type) {
	listeners[0] = listener;

}

void Collider::SetPos(int x, int y) {
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r)const {	// colisionan?
	return (rect.x < r.x + r.w && 
		rect.x + rect.w > r.x && 
		rect.y < r.y + r.h &&
		rect.y + rect.h > r.y);
}

void Collider::AddListener(Module* listener)
{
	for (int i = 0; i < MAX_LISTENERS; ++i)
	{
		if (listeners[i] == nullptr)
		{
			listeners[i] = listener;
			break;
		}
		else if (listeners[i] == listener)
			break;
	}
}

bool Collider::Superpos(const SDL_Rect& r)const {	// colisionan?
	return (rect.x == r.x+r.w && rect.y == r.y+r.h);
}