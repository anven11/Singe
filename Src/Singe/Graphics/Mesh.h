#ifndef __MESH_H__
#define __MESH_H__

#include "..\Geometry\Vec3.h"
#include "..\Geometry\Vec2.h"
#include "..\Geometry\Vec4.h"

namespace Singe
{
	namespace Graphics
	{
		struct MeshMaterial
		{
			Vec4 emissive; // Emissive color.
			Vec4 ambient; // Ambient color.
			Vec4 diffuse; // Diffuse color.
			Vec4 specular; // Specular color.
			float specularPower; // Specular power.

			shared_ptr<ID3D11ShaderResourceView> diffuseTexture; // Diffuse texture name.
			shared_ptr<ID3D11ShaderResourceView> specularTexture; // Specular texture name.
			shared_ptr<ID3D11ShaderResourceView> bumpMapTexture; // Bump map texture name.
		};

		struct MeshVertex
		{
			Vec3 position;
			Vec2 texcoord;
			Vec3 normal;
		};

		struct MeshSubset
		{
			friend class Mesh;

		public:
			void Render(void) const;

			const MeshMaterial GetMaterial(void) const
			{
				return m_materialMapIterator->second;
			}

		private:
			UINT m_vertexBufferOffset; // Relativt till modellens startindex.
			UINT m_vertexCount;

			std::map<std::wstring, MeshMaterial>::const_iterator m_materialMapIterator;
		};

		class Mesh
		{
		public:
			HRESULT LoadFromFile(const std::wstring& filename);

			const std::vector<MeshVertex> GetVertices(void) const
			{
				return m_vertices;
			}

			const std::vector<MeshSubset> GetSubsets(void) const
			{
				return m_subsets;
			}

			void UpdateVertexBufferOffset(UINT offset);

			template<typename T>
			const std::vector<T> Copy(void);

		private:
			UINT m_vertexCount;
			std::vector<MeshVertex> m_vertices;
			std::vector<MeshSubset> m_subsets;
			std::map<std::wstring, MeshMaterial> m_materialMap;
		};

		// Schablonmetoder måste defineras i samma header.
		template<typename T>
		const std::vector<T> Mesh::Copy(void)
		{
			std::vector<T> tmp;
			for (auto it = m_vertices.cbegin(); it != m_vertices.cend(); it++)
			{
				T t = T(*it);
				tmp.push_back(t);
			}

			return tmp;
		}
	}
}

#endif // __MESH_H__