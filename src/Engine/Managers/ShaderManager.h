//
// Created by invander on 22.10.16.
//

#pragma once

#include <GL/gl3w.h>
#include <unordered_map>

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
			Shader() {}
			Shader(GLuint _id) : id(_id) {}
			GLuint id = 0;
			int counter = 1;
		};

		/**
		 * Helper for program
		 */
		struct Program {
			Program() {};
			Program(GLuint _id, const std::string& _name, const std::string& _vs, const std::string& _fs) 
			: id(_id), name(_name), vertexShader(_vs), fragmentShader(_fs) {}
			GLuint id = 0;
			int counter = 1;
			std::string name;
			std::string vertexShader;
			std::string fragmentShader;
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
		Program& get(const std::string& name, const std::string& vs, const std::string& fs);

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
		std::unordered_map<std::string, Program> mPrograms;
	};

}