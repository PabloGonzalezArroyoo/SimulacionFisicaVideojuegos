#include "Projectile.h"

Projectile::Projectile(PxTransform tr, Vector3 dir, float lTime, int tipo) {
	Vector4 color = Vector4(255, 255, 255, 1);
	int tam = 1;
	startTime = GetLastTime();
	pose = tr;
	lifeTime = lTime;

	switch (tipo) {
	case REVOLER:
		setProperties(23.56f, dir * 25.0f, Vector3(0, -0.096f, 0), 0.99f);
		color = Vector4(125, 125, 0, 1);
		renderItem = new RenderItem(CreateShape(PxBoxGeometry(tam, tam, tam)), &pose, color);
		break;

	case FIREBALL:
		setProperties(0.1f, dir * 20.0f, Vector3(0, 0.6f, 0), 0.99f);
		color = Vector4(255, 0, 0, 1);
		tam = 3;
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(tam)), &pose, color);
		break;

	case LASER:
		setProperties(0.1f, dir * 100.0f, Vector3(0, 0.0f, 0), 0.99f);
		color = Vector4(0, 0, 255, 1);
		renderItem = new RenderItem(CreateShape(PxBoxGeometry(tam, tam, tam * 10)), &pose, color);
		break;

	case TANK:
		setProperties(259.2f, dir * 50.0f, Vector3(0, -15.0f, 0), 0.99f);
		color = Vector4(0, 255, 0, 1);
		tam = 4;
		renderItem = new RenderItem(CreateShape(PxBoxGeometry(tam, tam - 1, tam)), &pose, color);
		break;

	default:
		setProperties(1, Vector3(), Vector3(), 0.99f);
		renderItem = new RenderItem(CreateShape(PxBoxGeometry(tam, tam, tam)), &pose, color);
		break;
	}
}

bool Projectile::integrate(double t) {
	Particle::integrate(t);
	vel += accl * t;
	vel *= powf(damping, t);

	// Eliminar tras 8 segundos
	if (startTime + lifeTime < GetLastTime()) return false;

	return true;
}