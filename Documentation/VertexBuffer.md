| #class VertexBuffer                               | Buffer that holds all the vertexes to be rendered |
|---------------------------------------------------|---------------------------------------------------|
| private:                                          |                                                   |
| unsigned int m_RendererID                         | ID for the Renderer                               |
| public:                                           |                                                   |
| VertexBuffer(const void* data, unsigned int size) | Constructor for the Vertex Buffer                 |
| ~VertexBuffer()                                   | Destructor for the Vertex Buffer                  |
| void Bind() const                                 | binds to the renderer                             |
| void Unbind() const                               | unbinds from the renderer                         |
|                                                   |                                                   |