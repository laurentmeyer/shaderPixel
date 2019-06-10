#ifndef CUBE_H_
# define CUBE_H_

# include "Primitive.h"

class Cube : public Primitive
{
public:
  virtual ~Cube()
  {};

  virtual void draw();

protected:
  
};

#endif // CUBE_H_