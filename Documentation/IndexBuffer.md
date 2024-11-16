| #class IndexBuffer                                        | Holds an array of indeces to be bound to the renderer |
|-----------------------------------------------------------|-------------------------------------------------------|
| private:                                                  |                                                       |
| unsigned int m_RendererID                                 | ID of the Renderer this buffer will be bound to       |
| unsigned int m_Count                                      | Count inside the index buffer                         |
| IndexBuffer(const unsigned int* data, unsigned int count) | Constructor for the Index Buffer                      |
| ~IndexBuffer()                                            | Destructor for the Index Buffer                       |
| void Bind() const                                         | binds the index buffer to the renderer id             |
| void Unbind() const;                                      | unbinds the index buffer to the renderer id           |
| inline unsigned int GetCount() const { return m_Count; }  | gets an returns the m_Count    