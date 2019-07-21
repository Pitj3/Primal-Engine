#ifndef mesh_h__
#define mesh_h__

#include <vector>

#include "math/Vector3.h"
#include "math/Vector4.h"
#include "VertexArray.h"

struct Vertex
{
	Vector3f position;
	Vector2f uv;
	Vector3f normal;
	Vector3f tangent;
	Vector3f binormal;
	Vector4f color;
};

class Mesh
{
	public:
		Mesh();
		~Mesh();

		void build();
		void recalculateTangents();
		void recalculateNormals();

		void calculateBinormals();
		void triangulate();

		std::vector<Vector3f> positions;
		std::vector<Vector2f> uvs;
		std::vector<Vector3f> normals;
		std::vector<Vector3f> tangents;
		std::vector<Vector3f> binormals;
		std::vector<Vector4f> colors;

		std::vector<uint32_t> triangles;

		[[nodiscard]] VertexArray* getVAO() const;
		[[nodiscard]] IndexBuffer* getIBO() const;

	private:
		VertexArray* mVertexArray;
		IndexBuffer* mIndexBuffer;

		std::vector<Vertex> mVertices;
};

#endif // mesh_h__