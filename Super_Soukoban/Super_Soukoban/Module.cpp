#include "Module.h" 

Module::Module(bool startEnabled) : isEnabled(startEnabled)
{

}
//initialize the modules
bool Module::Init() {
	return true;
}
//starts the modules
bool Module::Start() {
	return true;
}

update_status Module::PreUpdate() {
	return update_status::UPDATE_CONTINUE;
}
update_status Module::Update() {
	return update_status::UPDATE_CONTINUE;
}
update_status Module::PostUpdate() {
	return update_status::UPDATE_CONTINUE;
}
//clean the modules
bool Module::CleanUp() {
	return true;
}

void Module::OnCollision(Collider* c1, Collider* c2) {

}
// to enable and disable modules
void Module::Enable()
{
	if (!isEnabled)
	{
		isEnabled = true;
		Start();
	}
}

void Module::Disable()
{
	if (isEnabled)
	{
		isEnabled = false;
		CleanUp();
	}
}