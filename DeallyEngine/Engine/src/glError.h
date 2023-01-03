
#ifndef GLERROR_H
#define GLERROR_H

// Ask Opengl for errors:
// Result is printed on the standard output
// usage :
//      glCheckError(__FILE__,__LINE__);
void glCheckError(const char* file, unsigned int line);

#endif  
