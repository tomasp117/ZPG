#pragma once
class Material
{
private:
	float ra;
	float rd;
	float rs;
	float shininess;

public:
	Material(float ra, float rd, float rs, float shininess);

	float getAmbient();
	float getDiffuse();
	float getSpecular();
	float getShininess();

	void setAmbient(float ra);
	void setDiffuse(float rd);
	void setSpecular(float rs);
	void setShininess(float shininess);
};

