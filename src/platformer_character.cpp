#include <platformer_character.h>
#include <iostream>

PlatformerCharacter::PlatformerCharacter(b2World & world)
{
	//Create the rectangle
	rect.setPosition(center_position - size / 2.f);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Green);
	//Create the body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = pixel2meter(center_position);
	myBodyDef.fixedRotation = true;
	body = world.CreateBody(&myBodyDef);

	//Create the fixtures
	b2FixtureDef box;
	b2PolygonShape box_shape;
	box_shape.SetAsBox(
		pixel2meter(size.x) / 2.f, pixel2meter(size.y) / 2.f);
	box.shape = &box_shape;
	box.friction = 0.f;

	b2FixtureDef foot;
	b2PolygonShape foot_shape;
	foot.isSensor = true;
	foot_shape.SetAsBox(
		pixel2meter(size.x-4.f) / 2.f, pixel2meter(2.0f) / 2.f,
		b2Vec2(0.f, pixel2meter(size.y)/2), 
		0.f);
	foot.shape = &foot_shape;
	contactData.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	contactData.data = this;
	foot.userData = &contactData;

	b2FixtureDef RightSide;
	b2PolygonShape RightSide_shape;
	RightSide.isSensor = true;
	RightSide_shape.SetAsBox(
		pixel2meter(2.f) / 2.f, pixel2meter(size.y) / 2.f,
		b2Vec2(pixel2meter(size.x) / 2, 0.f),
		0.f);
	RightSide.shape = &RightSide_shape;
	contactDataRight.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	contactDataRight.data = this;
	RightSide.userData = &contactDataRight;

	b2FixtureDef LeftSide;
	b2PolygonShape LeftSide_shape;
	LeftSide.isSensor = true;
	LeftSide_shape.SetAsBox(
		pixel2meter(2.f) / 2.f, pixel2meter(size.y) / 2.f,
		b2Vec2(0.f, 0.f),
		0.f);
	LeftSide.shape = &LeftSide_shape;
	contactDataLeft.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	contactDataLeft.data = this;
	LeftSide.userData = &contactDataLeft;

	body->CreateFixture(&box);
	body->CreateFixture(&foot);
	body->CreateFixture(&LeftSide);
}

PlatformerCharacter::~PlatformerCharacter()
{
}

void PlatformerCharacter::update(float move_axis, bool jump_button)
{
	//manage movements
	body->SetLinearVelocity(b2Vec2(walk_speed*move_axis, body->GetLinearVelocity().y));
	if (foot > 0 && jump_button)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -jump_speed));
	}
	center_position = meter2pixel(body->GetPosition());
	rect.setPosition(center_position - size / 2.f);
}

void PlatformerCharacter::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void PlatformerCharacter::touch_ground()
{
	foot++;
}

void PlatformerCharacter::leave_ground()
{
	foot--;
}

void PlatformerCharacter::touch_right_Wall()
{
	right++;
}

void PlatformerCharacter::leave_right_Wall()
{
	right--;
}

void PlatformerCharacter::touch_left_Wall()
{
	left++;
}

void PlatformerCharacter::leave_left_Wall()
{
	left--;
}

float PlatformerCharacter::get_x_center_position()
{
	return center_position.x;
}
