#pragma once

#include <glm/glm.hpp>

namespace ECS
{
	struct Camera
	{
		//constructor
		Camera()
		{
			//initialise camera matrices to identity
			_viewMatrix = glm::mat4(1.0f);
			_projMatrix = glm::mat4(1.0f);
			//initialise camera angles
			_cameraAngleX = 0.0f;
			_cameraAngleY = 0.0f;
			//initialise light position
			_lightPosition = glm::vec3(0.0f, 10.0f, 0.0f);
		}
		~Camera() {}


	public:

		//add camera
		void ChangeCameraAngleX(float value) { _cameraAngleX += value; }
		void ChangeCameraAngleY(float value) { _cameraAngleY += value; }
		void Draw();
		// This matrix represents the camera's position and orientation
		glm::mat4 _viewMatrix;

		// This matrix is like the camera's lens
		glm::mat4 _projMatrix;

		// Current rotation information about the camera
		float _cameraAngleX, _cameraAngleY;

		// Position of the single point-light in the scene
		glm::vec3 _lightPosition;
	};

}