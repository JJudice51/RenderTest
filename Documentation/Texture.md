| Class Texture                                   |                                                                       |   |
|-------------------------------------------------|-----------------------------------------------------------------------|---|
| private:                                        |                                                                       |   |
| unsigned int m_RendererID;                      | Identifier for the Renderer                                           |   |
| std::string m_FilePath;                         | Path to find a given texture to be loaded                             |   |
| unsigned char* m_LocalBuffer;                   | The Buffer made inside of the texture constructor to hold the texture |   |
| int m_Width;                                    | Width of the texture to be held in the local buffer                   |   |
| int m_Height;                                   | Height of the texture to be held in the local buffer                  |   |
| m_BPP                                           | Bits Per Pixel texture to be held in the local buffer                 |   |
| public:                                         |                                                                       |   |
| Texture(const std::string& path);               | Constructor for the texture                                           |   |
| ~Texture();                                     | Destructor for the texture                                            |   |
| void Bind(unsigned int slot = 0) const;         | Binds the texture to the renderer                                     |   |
| void Unbind() const;                            | Unbinds the texture to the renderer                                   |   |
| inline int GetWidth() const {return m_Width;}   | Gets the width variable of a given texture                            |   |
| inline int GetHeight() const {return m_Height;} | Gets the height variable of a given texture                           |   |