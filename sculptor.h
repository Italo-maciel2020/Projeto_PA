#ifndef SCULPTOR_H
#define SCULPTOR_H

/**
 * @brief Criar uma escultura.
 * @details A partir de uma estrutura chamada de Voxel
 * criar uma escultura em 3D.
 */

struct Voxel {
    /**
   * @brief Cores
   * @details r -> Vermelho
   * g -> Verde
   * b -> Azul
   */
  float r,g,b; // Colors
  /**
   * @brief Transparência
   */
  float a;
// Transparency
  /**
   * @brief Existência
   * @details Determina se o Voxel deve existir ou não.
   * Para a variável atribuindo valor "false" o Voxel
   * em dada posição não existe. E para "true" o Voxel
   * será plotado.
   */
  bool isOn; // Included or not
};

class Sculptor {
protected:
    /**
   * @brief Voxel
   * @details Uma matriz 3D do tipo Voxel.
   */
  Voxel ***v;
  // 3D matrix
  /**
   * @brief Dimensões da Matriz 3D
   * @details
   */
  int nx,ny,nz; // Dimensions
  float r,g,b,a; // Current drawing color
public:
  /**
   * @brief Método Construtor
   * @param _nx receberá a quantidade de linhas para a matriz 3D
   * @param _ny receberá a quantidade de colunas para a matriz 3D
   * @param _nz receberá a quantidade de espaços para compor a matriz 3D
   */
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  /**
   * @brief Método Inserir Cor
   * @details Os parâmetros sendo uma variável do tipo ponto flutuantes a seguir receberão valores
   * dentre o intervalo (0.0-1.0) para inserir as cores em cada Voxel. A combinação das cores primárias,
   * resultam demais variáveis cores. Lembrando que a variável que recebe '0.0' indica a ausência de cor
   * e '1.0' é respectivamente a cor em sua tonalidade mais forte. O parâmetro 'alpha' indica a questão da
   * transparência do Voxel, se o seu valor for respectivo a '0.0' indica transparência total e para '1.0'
   * indica voxel totalmente opaco.
   * @param r : Vermelho
   * @param g : Verde
   * @param b : Azul
   * @param alpha : Transparência
   */
  void setColor(float r, float g, float b, float alpha);
  /**
   * @brief Método Inserir Voxel
   * @details A partir dos parâmetros pré-estabelecidos pelo o usuário, na posição
   * o Voxel será ativado, isto é a variável booleana 'is0n' receberá a atribuição
   * 'true'.
   * @param x
   * @param y
   * @param z
   */
  void putVoxel(int x, int y, int z);
  /**
   * @brief Método Cortar Voxel
   * @details  A partir dos parâmetros pré-estabelecidos pelo o usuário, na posição
   * o Voxel será ativado, isto é a variável booleana 'is0n' receberá a atribuição
   * 'false'.
   * @param x
   * @param y
   * @param z
   */
  void cutVoxel(int x, int y, int z);
  /**
   * @brief Método Inserir Box
   * @details Dado um intervalo
   * @param x0
   * @param x1
   * @param y0
   * @param y1
   * @param z0
   * @param z1
   */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief Método Cortar Box
   * @param x0
   * @param x1
   * @param y0
   * @param y1
   * @param z0
   * @param z1
   */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief Método Inserir Esfera
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param radius
   */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief Método Cortar Esfera
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param radius
   */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief Método Inserir Elipsóide
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param rx
   * @param ry
   * @param rz
   */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief Método Cortar Elipsóide
   * @param xcenter
   * @param ycenter
   * @param zcenter
   * @param rx
   * @param ry
   * @param rz
   */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief Método Escrever arquivo OFF
   * @param filename
   */
  void writeOFF(char* filename);
};

#endif // SCULPTOR_H
