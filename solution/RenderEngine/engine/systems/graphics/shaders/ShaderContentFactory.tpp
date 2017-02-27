namespace sre
{

template <size_t SIZE>
void ShaderContentFactory::createShaderContent(const std::bitset<SIZE> &componentsBitset, std::string &outVertexContent, std::string &outFragmentContent)
{
	std::string vertexContentHeader;
	std::string fragmentContentHeader;
	std::string vertexContentImpl;
	std::string fragmentContentImpl;

	for (int i = 0; i <= EMaterialMap::SIZE; i++)
	{
		if (componentsBitset[i])
		{
			switch (i)
			{
				case EMaterialMap::COLOR:
					this->loadColorContentHeader(vertexContentHeader, fragmentContentHeader);
					this->loadColorContentImplementation(vertexContentImpl, fragmentContentImpl);
					break;
				case EMaterialMap::DIFFUSE:
					this->loadDiffuseContentHeader(vertexContentHeader, fragmentContentHeader);
					this->loadDiffuseContentImplementation(vertexContentImpl, fragmentContentImpl);
					break;
				case EMaterialMap::NORMAL:
					this->loadNormalMapContentHeader(vertexContentHeader, fragmentContentHeader);
					this->loadNormalMapContentImplementation(vertexContentImpl, fragmentContentImpl);
					break;
				case EMaterialMap::SPECULAR: break;
				case EMaterialMap::AMBIENT_OCCLUSION: break;
				default: break;
			}
		}
	}

	outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
	outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
}

} // namespace
