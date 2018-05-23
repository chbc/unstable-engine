namespace sre
{

template <size_t SIZE>
void ShaderContentFactory::createShaderContent(const std::bitset<SIZE> &componentsBitset, std::string &outVertexContent, std::string &outFragmentContent)
{
    std::string vertexContentHeader;
    std::string fragmentContentHeader;
    std::string vertexContentImpl;
    std::string fragmentContentImpl;

    for (int i = EComponentId::COLOR_RENDERER; i <= EComponentId::AO_RENDERER; i++)
    {
        if (componentsBitset[i])
        {
            switch (i)
            {
                case EComponentId::COLOR_RENDERER:
                    this->loadColorContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadColorContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::DIFFUSE_RENDERER:
                    this->loadDiffuseContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadDiffuseContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::NORMAL_RENDERER:
                    this->loadNormalMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadNormalMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::SPECULAR_RENDERER:
                    this->loadSpecularMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadSpecularMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::AO_RENDERER:
                    this->loadAOMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadAOMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                default: break;
            }
        }
    }

    outVertexContent = "#version 400\n" + vertexContentHeader + vertexContentImpl;
    outFragmentContent = "#version 400\n" + fragmentContentHeader + fragmentContentImpl;
}

} // namespace
