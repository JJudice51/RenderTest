| #class VertexBufferLayout                                                                | Layout for the VertexBuffer                             |
|------------------------------------------------------------------------------------------|---------------------------------------------------------|
| private:                                                                                 |                                                         |
| std::vector<VertexBufferElement> m_Elements                                              | Elements of the VertexBuffer                            |
| unsigned int count                                                                       | the count of which index of the buffer it is at         |
| unsigned int m_Stride                                                                    | size of the type multiplied by the count added up       |
| public:                                                                                  |                                                         |
| VertexBufferLayout()                                                                     | Constructor for the Vertx Buffer Layout                 |
| template<typename T> void Push(unsigned int count)                                       |                                                         |
| template<> void Push<float>(unsigned int count)                                          | Pushes back the list of elements and adds to the stride |
| template<> void Push<unsigned int>(unsigned int count)                                   | Pushes back the list of elements and adds to the stride |
| template<> void Push<unsigned char>(unsigned int count)                                  | Pushes back the list of elements and adds to the stride |
| inline const std::vector<VertexBufferElement>& GetElement() const { return m_Elements; } | Gets and returns the Elements                           |
| inline unsigned int GetStride() const { return m_Stride; }                               | gets and returns the Stride                             |
|                                                                                          |                                                         |
|                                                                                          |                                                         |