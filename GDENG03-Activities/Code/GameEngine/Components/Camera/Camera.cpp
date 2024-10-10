#include "Camera.h"
#include "../Transform.h"


Camera::Camera(int width, int height) : AComponent("Camera", EComponentTypes::Camera)
{
	ProjectionType = EProjectionTypes::Perspective;
	AspectRatio = Vector2(width, height);
	FieldOfView = 60.f;
	clippingPlane = Vector2(0.1f, 1000.f);
}

Camera::Camera(std::string name, int width, int height) : AComponent(name, EComponentTypes::Camera)
{
	ProjectionType = EProjectionTypes::Perspective; 
	AspectRatio = Vector2(width, height); 
	FieldOfView = 60.f; 
	clippingPlane = Vector2(0.1f, 1000.f); 
}

Camera::~Camera()
{

}

void Camera::Perform()
{

}

VPMatrix Camera::CreateViewProjectionMatrix()
{
	if (transform == nullptr) return VPMatrix{};

	// https://gamedev.stackexchange.com/questions/178643/the-view-matrix-finally-explained
	Matrix view = Matrix::CreateLookAt(transform->Position, transform->Position + transform->GetLocalForward(), transform->GetLocalUp());

	Matrix projection = Matrix::Identity;
	if (ProjectionType == EProjectionTypes::Orthographic)
	{
		projection = Matrix::CreateOrthographic(AspectRatio.x, AspectRatio.y, clippingPlane.x, clippingPlane.y);
	}
	else if (ProjectionType == EProjectionTypes::Perspective)
	{
		//projection = Matrix::CreatePerspective(AspectRatio.x, AspectRatio.y, clippingPlane.x, clippingPlane.y);
		projection = Matrix::CreatePerspectiveFieldOfView(DirectX::XMConvertToRadians(FieldOfView), AspectRatio.x / AspectRatio.y, clippingPlane.x, clippingPlane.y);
	}

	view.Transpose();
	projection.Transpose();

	return VPMatrix{ view, projection };
}

Vector2 Camera::GetClippingPlane()
{
	return clippingPlane;
}

void Camera::SetClippingPlane(float nearZ, float farZ)
{
	clippingPlane = Vector2(nearZ, farZ);
}