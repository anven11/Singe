#include <SingeStd.h>

#include "Mesh.h"

#include "Shader.h"
#include "Renderer.h"
#include "..\Utilities\FileSystem.h"
#include "..\Utilities\Macros.h"

namespace Singe
{
	namespace Graphics
	{
		void MeshSubset::Render(void) const
		{
			const Renderer* pRenderer = Renderer::Get();

			pRenderer->GetD3DImmediateContext()->Draw(m_vertexCount, m_vertexBufferOffset);
		}

		HRESULT Mesh::LoadFromFile(const std::wstring& filename)
		{
			const std::wstring filename_obj = filename + L".obj";
			const std::wstring filename_mtl = filename + L".mtl";

			//
			// Läs av .MTL-filen.
			//
			if (Singe::Utilities::FileSystem::FileExists(filename_mtl))
			{
				std::wifstream file;
				file.open(filename_mtl);
				if (!file.is_open() || file.bad())
				{
					return S_FALSE;
				}

				std::wstring currentMaterialName;
				MeshMaterial currentMaterial = { };

				std::wstring buffer;
				while (file >> buffer)
				{
					// Definera ett nytt material.
					// Här måste vi också spara det förra materialet.
					if (buffer == L"newmtl")
					{
						if (currentMaterialName.length() > 0)
						{
							m_materialMap.insert(std::pair<std::wstring, MeshMaterial>(currentMaterialName, currentMaterial));

							ZeroMemory(&currentMaterial, sizeof(MeshMaterial));
							currentMaterialName.clear();
						}

						std::wstring materialName;
						file >> materialName;
						currentMaterialName = materialName;
					}

					// Sätt emissive färg.
					else if (buffer == L"Ke")
					{
						file >> currentMaterial.emissive.x >> currentMaterial.emissive.y >> currentMaterial.emissive.z;
						currentMaterial.emissive.w = 1.0f;
					}

					// Sätt ambient färg.
					else if (buffer == L"Ka")
					{
						file >> currentMaterial.ambient.x >> currentMaterial.ambient.y >> currentMaterial.ambient.z;
						currentMaterial.ambient.w = 1.0f;
					}

					// Sätt diffuse färg.
					else if (buffer == L"Kd")
					{
						file >> currentMaterial.diffuse.x >> currentMaterial.diffuse.y >> currentMaterial.diffuse.z;
						currentMaterial.diffuse.w = 1.0f;
					}

					// Sätt specular färg.
					else if (buffer == L"Ks")
					{
						file >> currentMaterial.specular.x >> currentMaterial.specular.y >> currentMaterial.specular.z;
						currentMaterial.specular.w = 1.0f;
					}
				}

				// Spara det sista materialet.
				m_materialMap.insert(std::pair<std::wstring, MeshMaterial>(currentMaterialName, currentMaterial));

				file.close();
			}
			else
			{
				return ERROR_FILE_NOT_FOUND;
			}

			//
			// Läs av .OBJ-filen.
			//
			if (Singe::Utilities::FileSystem::FileExists(filename_obj))
			{
				std::vector<Vec3> vertexPositions;
				std::vector<Vec3> vertexNormals;
				std::vector<Vec2> vertexTexcoords;

				std::wifstream file;
				file.open(filename_obj);
				if (!file.is_open() || file.bad())
				{
					return S_FALSE;
				}

				std::map<std::wstring, MeshMaterial>::const_iterator currentMaterialIterator;

				std::wstring currentMaterialName;
				MeshSubset currentSubset;

				std::wstring buffer;
				while (file >> buffer)
				{
					// Registrera en position.
					if (buffer == L"v")
					{
						Vec3 tmp;
						file >> tmp.x >> tmp.y >> tmp.z;
						vertexPositions.push_back(tmp);
					}

					// Registrera en normal.
					else if (buffer == L"vn")
					{
						Vec3 tmp;
						file >> tmp.x >> tmp.y >> tmp.z;
						vertexNormals.push_back(tmp);
					}

					// Registrera en texturkoordinat.
					else if (buffer == L"vt")
					{
						Vec2 tmp;
						file >> tmp.x >> tmp.y;
						vertexTexcoords.push_back(tmp);
					}

					// Registrera en triangel.
					else if (buffer == L"f")
					{
						for (unsigned int f = 0; f < 3; f++)
						{
							unsigned int positionIndex, texcoordIndex, normalIndex;
							file >> positionIndex; file.ignore();	// a/
							file >> texcoordIndex; file.ignore();	// b/
							file >> normalIndex;					// c

							// OBJ indexerar med 1 som startindex. Så fixa till det.
							positionIndex--;
							texcoordIndex--;
							normalIndex--;

							MeshVertex vertex;
							vertex.position = vertexPositions[positionIndex];
							vertex.texcoord = vertexTexcoords[texcoordIndex];
							vertex.normal = vertexNormals[normalIndex];
							m_vertices.push_back(vertex);
						}

						/*UINT16 stage = 0;
						std::wstring tmp = L"";
						wchar_t c = '\0';
						MeshVertex vertex;
						vertex.position = Vec3(0, 0, 0);
						vertex.texcoord = Vec2(0, 0);
						vertex.normal = Vec3(0, 0, 0);

						while (true)
						{
							c = file.get();

							if (c == '/' || c == ' ' || c == '\n' || c == '\0')
							{
								if (tmp.length() > 0)
								{
									UINT16 index = std::stoi(tmp.c_str()) - 1;
									std::wcout << index + 1 << ' ';

									if (stage == 0) // Position.
									{
										vertex.position = vertexPositions[index];
									}
									else if (stage == 1) // Texcoord.
									{
										vertex.texcoord = vertexTexcoords[index];
									}
									else if (stage == 2) // Normal.
									{
										vertex.normal = vertexNormals[index];
									}

									tmp = L"";
								}
							}

							if (c == '\n' || c == '\0')
								break;

							if (c == '/')
							{
								stage++;
								continue;
							}

							if (c == ' ')
							{
								m_vertices.push_back(vertex);
								stage = 0;
								continue;
							}

							tmp += c;
						}*/
					}
			
					// Sätt det aktiva materialet. Ett nytt material betyder också ett nytt subset.
					else if (buffer == L"usemtl")
					{
						// Kolla om det redan finns ett aktivt material.
						if (currentMaterialName != L"")
						{
							// Det gör det. Spara det aktiva subsetet.
							currentSubset.m_vertexCount = (UINT)m_vertices.size() - currentSubset.m_vertexBufferOffset;
							m_subsets.push_back(currentSubset);
							ZeroMemory(&currentSubset, sizeof(MeshSubset));
						}

						file >> currentMaterialName;

						// Leta efter materialet.
						currentMaterialIterator = m_materialMap.cend();
						for (auto it = m_materialMap.cbegin(); it != m_materialMap.cend(); it++)
						{
							if (it->first == currentMaterialName)
							{
								// Materialet finns. Sätt det som aktivt.
								currentMaterialIterator = it;

								currentSubset.m_materialMapIterator = currentMaterialIterator;
								currentSubset.m_vertexBufferOffset = (UINT)m_vertices.size();

								break;
							}
						}

						// Materialet fanns inte.
						if (currentMaterialIterator == m_materialMap.cend())
						{
							file.close();
							MessageBox(nullptr, L"Material not found.", nullptr, MB_ICONERROR);
							return S_FALSE;
						}
					}
				}

				file.close();

				// Vi får inte glömma bort att spara det aktiva subsetet!
				currentSubset.m_vertexCount = (UINT)m_vertices.size() - currentSubset.m_vertexBufferOffset;
				m_subsets.push_back(currentSubset);

				m_vertexCount = (UINT)m_vertices.size();

				std::wcout << L"Mesh vertex count: " << m_vertexCount << std::endl;
				std::wcout << L"Mesh triangle count: " << m_vertexCount / 3 << std::endl;
			}
			else
			{
				return ERROR_FILE_NOT_FOUND;
			}

			return S_OK;
		}

		void Mesh::UpdateVertexBufferOffset(UINT offset)
		{
			for (auto it = m_subsets.begin(); it != m_subsets.end(); it++)
			{
				it->m_vertexBufferOffset += offset;
			}
		}
	}
}