#ifndef OBJECT_INCLUDED
#define OBJECT_INCLUDED

typedef double Object;

#define object_add(self, other) (((Object)self) + ((Object)other))
#define object_mul(self, other) (((Object)self) * ((Object)other))

#endif // OBJECT_INCLUDED
