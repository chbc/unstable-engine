namespace sre
{

template <size_t SIZE>
void ShaderContentFactory::createShaderContent
(
    const std::bitset<SIZE> &componentsBitset, 
    std::string &outVertexContent, std::string &outFragmentContent,
    const ShaderLightData &lightData
)
{
    this->lightData = lightData;

    std::string vertexContentHeader;
    std::string fragmentContentHeader;
    std::string vertexContentImpl;
    std::string fragmentContentImpl;

    for (int i = EComponentId::COLOR_MATERIAL; i <= EComponentId::AO_MATERIAL; i++)
    {
        if (componentsBitset[i])
        {
            switch (i)
            {
                case EComponentId::COLOR_MATERIAL:
                    this->loadColorContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadColorContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::LIT_MATERIAL:
                    this->loadLightsContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadLightsContentImplementation(vertexContentImpl, fragmentContentImpl);

                    if (this->lightData.hasAnyShadowCaster)
                    {
                        this->loadShadowsContentHeader(vertexContentHeader, fragmentContentHeader);
                        this->loadShadowsContentImplementation(vertexContentImpl, fragmentContentImpl);
                    }
                    break;
                case EComponentId::DIFFUSE_MATERIAL:
                    this->loadDiffuseContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadDiffuseContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::NORMAL_MATERIAL:
                    this->loadNormalMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadNormalMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::SPECULAR_MATERIAL:
                    this->loadSpecularMapContentHeader(vertexContentHeader, fragmentContentHeader);
                    this->loadSpecularMapContentImplementation(vertexContentImpl, fragmentContentImpl);
                    break;
                case EComponentId::AO_MATERIAL:
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
