#include "effect.h"
#include "Device.h"
#include "ResManager.h"
#include "Actiongun.h"
#include "object.h"

CEffect::CEffect(string nam, Point p, float t)
{
	sprite = GetSprite(nam).clone();
	pos = Point(p.x - sprite.get_width() / 2, p.y - sprite.get_height() / 2);
	timer = t;
	startTimer = t;
	if (t < 0)sprite.set_play_loop(false);
	type = "sprite";

}

CEffect::CEffect(Point p, Point p2, Colorf c, float t)
{
	color = c;
	pos = p;
	pos2 = p2;
	timer = t;
	startTimer = t;
	type = "laser";



}
void CEffect::update()
{
	timer -= getDeltaTime();
	if (type == "sprite")
		sprite.update(getDeltaTime() * 1000);


}

void CEffect::draw()
{
	if (type == "sprite")
	{
		if (alphaEffect)
			sprite.set_alpha(timer / startTimer);
		sprite.draw(GetGC(), pos.x, pos.y);
	}





}

bool CEffect::isAlive()
{
	if (timer < -0.9)return !sprite.is_finished();
	return timer > 0;
}