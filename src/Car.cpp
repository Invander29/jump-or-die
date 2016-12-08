#include "Car.h"
#include "Engine/Application.h"
#include "Images/Images.h"

const float Car::AREA_X = 24;
extern Image ImageCar;

Car::Car(std::shared_ptr<Managers::ShaderManager::Program> program, bool fromRight, float delayTime, float waitTime, float speed)
	: ModelObj(program, ":Car", &ImageCar), mFromRight(fromRight), 
		mTime(-delayTime), mWaitTime(waitTime), mSpeed(speed)
{
	// Create on one side or other
	mVisible = false;
	stopped = false;
	// TODO Rotate / Flip (don't drive backward)
	mScale = glm::vec3((mFromRight ? 0.4f : -0.4f), 0.4f, 0.4f);
}

void Car::gameover()
{
	stopped = true;

}

void Car::update()
{
	// Wait for a while, after that show yourself
	if (!mVisible) {
		mTime += Application::instance().speed();
		if (mTime > mWaitTime) {
			mTime = 0;
			mVisible = true;
		}
	} 
	// Move to next side
	else if (!stopped){
		// Rigth to left
		if (mFromRight) {
			mPosition.x -= mSpeed * Application::instance().speed();
			if (mPosition.x < -AREA_X) {
				mPosition.x = ((mFromRight) ? 1 : -1) * AREA_X;
			}
		} 
		// Left to right
		else {
			mPosition.x += mSpeed * Application::instance().speed();
			if (mPosition.x > AREA_X) {
				mPosition.x = ((mFromRight) ? 1 : -1) * AREA_X;
			}
		}
	}
}

void Car::draw(Scenes::Scene* scene)
{
	if (!mVisible) {
		return;
	}

	ModelObj::draw(scene);
}
