//
// Created by invander on 22.10.16.
//

#pragma once

#include <GL/gl3w.h>
#include <unordered_map>
#include <memory>
#include "../Lighting/LightTypes.h"

namespace Managers {

	/**
	 * Manging shaders and linking programs
	 */
	class ShaderManager {
	public:
		/**
		 * Helper for shader
		 */
		struct Shader {
			explicit Shader() {}
			explicit Shader(GLuint _id) : id(_id) {}
			GLuint id = 0;
			int counter = 1;
		};

		class ProgramPart
		{
		public:
			explicit ProgramPart() {}
			explicit ProgramPart(GLuint programId, GLuint vsId, GLuint fsId, const std::string& vs, const std::string& fs) 
				: mId(programId), mVertexShaderId(vsId), mFragmentShaderId(fsId), mVertexShader(vs), mFragmentShader(fs) {}
			~ProgramPart();

			GLuint id() const { return mId; }
			GLuint vertexShaderId() const { return mVertexShaderId; }
			GLuint fragmentShaderId() const { return mFragmentShaderId; }
			const std::string& vertexShader() const { return mVertexShader; }
			const std::string& fragmentShader() const { return mFragmentShader; }

		private:
			GLuint mId = 0;
			GLuint mVertexShaderId = 0;
			GLuint mFragmentShaderId = 0;

			std::string mVertexShader = std::string();
			std::string mFragmentShader = std::string();
		};

		/**
		 * Helper for program
		 */
		class Program {
		public:
			explicit Program() {}
			explicit Program(const std::string& name) 
			: mName(name) {}
			
			GLuint id() const;
			GLuint id(Lighting::Type type) const;

			const std::string& name() const { return mName; }
			std::shared_ptr<ProgramPart> withoutLight() const { return mWithoutLight; }
			std::shared_ptr<ProgramPart> phong() const { return mPhong; }

			friend ShaderManager;

		private:
			int mCounter = 1;
			std::string mName = std::string();
			std::shared_ptr<ProgramPart> mWithoutLight;
			std::shared_ptr<ProgramPart> mPhong;
		};

	public:
		/**
		 * Create shader manager
		 * @param path diretory of shaders
		 */
		explicit ShaderManager(const std::string& path = "shaders/");
		~ShaderManager();

		/**
		 * Create program from vertex and fragment shader
		 * @param name Name of the program
		 * @param vs Name of the file of vertex shader
		 * @param fs Name of the file of fragment shader
		 * @return zero if error or ID of program
		 */
		std::shared_ptr<Program> get(const std::string& name, const std::string& vs, const std::string& fs);

		/**
		 * Delete program from memory and OpenGL
		 * @param name Name of the program
		 * @return true if deleted
		 */
		bool remove(const std::string& name);

		/**
		* Delete program from memory and OpenGL
		* @param program structure with data
		* @return true if deleted
		*/
		bool remove(const Program& program);

	private:
		/**
		 * Create vertex shader from file
		 * @param filename path to file
		 * @return ID of shader
		 */
		GLuint createVertexShader(const std::string& filename);

		/**
		 * Create fragment shader from file
		 * @param filename path to file
		 * @return ID of shader
		 */
		GLuint createFragmentShader(const std::string& filename);

		/**
		 * Common function for creating shader
		 * @param filename path to file
		 * @param type vertex or fragment shader
		 * @return ID of shader
		 */
		GLuint createShader(const std::string& filename, GLenum type);

		std::shared_ptr<ProgramPart> createProgram(const std::string& name, const std::string& vs, const std::string& fs);

		/**
		 * Delete vertex shader from memory and OpenGL
		 * @param filename path to file
		 * @return true on success
		 */
		bool deleteVertexShader(const std::string& filename);

		/**
		 * Delete fragment shader from memory and OpenGL
		 * @param filename path to file
		 * @return true on success
		 */
		bool deleteFragmentShader(const std::string& filename);

		/**
		 * Clear all vertex shaders
		 */
		void clearVertexShaders();

		/**
		 * Clear all fragment shaders
		 */
		void clearFragmentShaders();

		/**
		 * Clear all programs
		 */
		void clearPrograms();

		std::string mPath;
		std::unordered_map<std::string, Shader> mVertexShaders;
		std::unordered_map<std::string, Shader> mFragmentShaders;
		std::unordered_map<std::string, std::shared_ptr<Program>> mPrograms;
	};
}
