#pragma once

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <memory>

#include "../Utils/Basics.h"
#include "../Lighting/LightTypes.h"
#include "../Managers/ShaderManager.h"

namespace Scenes
{
	class Scene;
}

namespace Models {

	/**
	 * Interface for game objects
	 */
	class GameObject {
	public:
		explicit GameObject() {};

		virtual ~GameObject() {};

		/**
		 * Update object per simulation frame
		 */
		virtual void update() = 0;

		/**
		 * Draw object per drawing frame
		 * @param view matrix of view
		 */
		virtual void draw(Scenes::Scene* scene) = 0;

	protected:
		class Uniform
		{
		public:
			explicit Uniform()
			{
				memset(mUni, -1, sizeof(mUni));
			}

			GLint& operator[] (Lighting::Type type)
			{
				switch (type) {
				case Lighting::Type::NONE: return mUni[0];
				case Lighting::Type::PHONG: return mUni[1];
				default: break;
				}

				// Never happens
				return mUni[0];
			}

			GLint& operator() ();

		private:
			GLint mUni[2];
		};

		/**
		 * Bint attrib from program to value
		 * @param program program ID
		 * @param attrib output for attrib to bind
		 * @param name name of variable
		 * @return true on success
		 */
		static bool bindAttrib(GLuint program, GLint &attrib, const char *name);

		/**
		 * Bind uniform from program to value
		 * @param program program ID
		 * @param attrib output for uniform to bind
		 * @param name name of uniform
		 * @return true on success
		 */
		static bool bindUniform(GLuint program, GLint &attrib, const char *name);

		/**
		* Bind uniform from program to value
		* @param program program ID
		* @param attrib output for uniform to bind
		* @param name name of uniform
		* @return true on success
		*/
		static bool bindUniform(std::shared_ptr<Managers::ShaderManager::Program> program, Uniform &uniform, const char *name);

		/**
		* Bind uniform from program to value
		* @param program program ID
		* @param attrib output for uniform to bind
		* @param name name of uniform
		* @return true on success
		*/
		static bool bindUniform(Lighting::Type type, std::shared_ptr<Managers::ShaderManager::Program> program, Uniform &uniform, const char *name);
	};

// Make smart
	MAKE_SMART(GameObject);

}
