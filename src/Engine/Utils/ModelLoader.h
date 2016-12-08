#pragma once

#include <GL/gl3w.h>
#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace Utils {

	/**
	 * Structure for handling vertex
	 */
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	/**
	 * Model loader
	 */
	class ModelLoader
	{
	public:
		/**
		 * Load from file
		 * @param filename path to file
		 * @return true on success
		 */
		bool load(const std::string& filename);

		/**
		 * Load from data (memory)
		 * @param data data
		 * @param size count of vertices
		 * @return true on success
		 */
		bool load(float* data, size_t size);
		
		/**
		 * Load from data (memory)
		 * @param data data
		 * @param size count of vertices
		 * @return true on success
		 */
		bool load(double* data, size_t size);
		
		/**
		 * Generate cpp file
		 * @param file name of the file
		 * @return true on success
		 */
		bool save(const std::string& file);

		/**
		 * Returns all vertices
		 */
		const std::vector<Vertex>& vertices() const { return mVertices; }

	private:
		std::vector <Vertex> mVertices;
	};

}