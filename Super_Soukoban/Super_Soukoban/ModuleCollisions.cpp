//#include "ModuleCollisions.h"
//#include "Application.h"
//#include "ModuleRender.h"
//#include "ModuleInput.h"
//#include "External_Libraries/SDL/include/SDL_scancode.h"
//
//ModuleCollisions::ModuleCollisions() {
//	for (uint i = 0; i < MAX_COLLIDERS;i++) {
//		colliders[i] = nullptr;
//	}
//
//	// Colliders paredes:
//	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
//	matrix[Collider::Type::WALL][Collider::Type::BOX] = true;
//	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
//
//	// Colliders cajas:
//	matrix[Collider::Type::BOX][Collider::Type::WALL] = true;
//	matrix[Collider::Type::BOX][Collider::Type::BOX] = true;
//	matrix[Collider::Type::BOX][Collider::Type::PLAYER] = true;
//
//	// Colliders player:
//	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
//	matrix[Collider::Type::PLAYER][Collider::Type::BOX] = true;
//	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
//}
//
//ModuleCollisions::~ModuleCollisions() {
//
//}
//
//update_status ModuleCollisions::PreUpdate() {
//	for (uint i = 0; i < MAX_COLLIDERS; i++) {
//		if(colliders[i]!=nullptr && colliders[i]->pendingToDelete==true){
//			delete colliders[i];
//			colliders[i] = nullptr;
//		}
//	}
//
//	Collider* c1;
//	Collider* c2;
//
//	for (uint i = 0; i < MAX_COLLIDERS; i++) {
//		if (colliders[i] == nullptr) {
//			continue;
//		}
//		c1 = colliders[i];
//		for (uint k=i+1; k < MAX_COLLIDERS; k++) {
//			if (colliders[k] == nullptr) {
//				continue;
//			}
//			c2 = colliders[k];
//			if (c1->Intersects(c2->rect)) {
//				if (matrix[c1->type][c2->type] && c1->listener) {
//					c1->listener->OnCollision(c1,c2);
//				}
//				if (matrix[c2->type][c1->type] && c2->listener) {
//					c2->listener->OnCollision(c2, c1);
//				}
//			}
//		}
//	}
//	return update_status::UPDATE_CONTINUE;
//}
//
